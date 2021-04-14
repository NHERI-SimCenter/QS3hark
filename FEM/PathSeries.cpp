/* ****************************************************************** **
**    OpenSees - Open System for Earthquake Engineering Simulation    **
**          Pacific Earthquake Engineering Research Center            **
**                                                                    **
**                                                                    **
** (C) Copyright 1999, The Regents of the University of California    **
** All Rights Reserved.                                               **
**                                                                    **
** Commercial use of this program without express permission of the   **
** University of California, Berkeley, is strictly prohibited.  See   **
** file 'COPYRIGHT'  in main directory for information on usage and   **
** redistribution,  and for a DISCLAIMER OF ALL WARRANTIES.           **
**                                                                    **
** Developed by:                                                      **
**   Frank McKenna (fmckenna@ce.berkeley.edu)                         **
**   Gregory L. Fenves (fenves@ce.berkeley.edu)                       **
**   Filip C. Filippou (filippou@ce.berkeley.edu)                     **
**                                                                    **
** ****************************************************************** */
                                                                        
// $Revision: 6475 $
// $Date: 2016-09-23 09:00:15 +0200 (vi., 23 sep. 2016) $
// $URL: svn://peera.berkeley.edu/usr/local/svn/OpenSees/trunk/SRC/domain/pattern/PathSeries.cpp $
                                                                        
// Written: fmk 
// Created: 07/99
// Revision: A
//
// Purpose: This file contains the class definition for PathSeries.
// PathSeries is a concrete class. A PathSeries object provides
// a linear time series. the factor is given by the pseudoTime and 
// a constant factor provided in the constructor.

#include <PathSeries.h>
#include <Vector.h>
#include <math.h>

#include <fstream>
using std::ifstream;

#include <iomanip>
using std::ios;

#include <PathTimeSeries.h>
#include <string>
#include <iostream>



PathSeries::PathSeries()	
  :TimeSeries(0),
   thePath(0), pathTimeIncr(0.0), cFactor(0.0), otherDbTag(0), lastSendCommitTag(-1)
{
  // does nothing
}

PathSeries::PathSeries(int tag,
		       const Vector &theLoadPath, 
		       double theTimeIncr, 
		       double theFactor,
		       bool last,
               bool prependZero,
               double tStart)
  :TimeSeries(tag, 0),
   thePath(0), pathTimeIncr(theTimeIncr), cFactor(theFactor),
   otherDbTag(0), lastSendCommitTag(-1), useLast(last), startTime(tStart)
{
  // create a copy of the vector containg path points
  if (prependZero == false) {
    thePath = new Vector(theLoadPath);
  } else {
    // prepend a zero value
    thePath = new Vector(1 + theLoadPath.Size());
    thePath->Assemble(theLoadPath, 1);
  }

  // ensure we did not run out of memory
  if (thePath == 0 || thePath->Size() == 0) {
    std::cerr << "PathSeries::PathSeries() - ran out of memory constructing";
    std::cerr << " a Vector of size: " <<  theLoadPath.Size() << "\n";
    if (thePath != 0)
      delete thePath; 
    thePath = 0;
  }
}

PathSeries::PathSeries(int tag,
		       const char *fileName, 
		       double theTimeIncr, 
		       double theFactor,
		       bool last,
               bool prependZero,
               double tStart)
  :TimeSeries(tag, 0),
   thePath(0), pathTimeIncr(theTimeIncr), cFactor(theFactor),
   otherDbTag(0), lastSendCommitTag(-1), useLast(last), startTime(tStart)
{
  // determine the number of data points .. open file and count num entries
  int numDataPoints = 0;
  double dataPoint;

  ifstream theFile;
  theFile.open(fileName);

  if (theFile.bad() || !theFile.is_open()) {
    std::cerr << "WARNING - PathSeries::PathSeries()";
    std::cerr << " - could not open file " << fileName << "\n";
  } else {
    while (theFile >> dataPoint)
      numDataPoints++;
  }   
  theFile.close();

  // create a vector and read in the data
  if (numDataPoints != 0) {

    // increment size if we need to prepend a zero value
    if (prependZero == true)
      numDataPoints++;
    
    // first open the file
    ifstream theFile1;
    theFile1.open(fileName, ios::in);
    if (theFile1.bad() || !theFile1.is_open()) {
      std::cerr << "WARNING - PathSeries::PathSeries()";
      std::cerr << " - could not open file " << fileName << "\n";
    } else {

      // now create the vector
      thePath = new Vector(numDataPoints);

      // ensure we did not run out of memory
      if (thePath == 0 || thePath->Size() == 0) {
    std::cerr << "PathSeries::PathSeries() - ran out of memory constructing";
    std::cerr << " a Vector of size: " << numDataPoints << "\n";

	if (thePath != 0)
	  delete thePath;
	thePath = 0;
      }

      // read the data from the file
      else {
	int count = 0;
    if (prependZero == true)
      count++;
	while (theFile1 >> dataPoint) {
	  (*thePath)(count) = dataPoint;
	  count++;
	}
      }

      // finally close the file
      theFile1.close();
    }
  }
}

PathSeries::~PathSeries()
{
  if (thePath != 0)
    delete thePath;
}

TimeSeries *
PathSeries::getCopy(void) {
  return new PathSeries(this->getTag(), *thePath, pathTimeIncr, cFactor,
                        useLast, false, startTime);
}

double
PathSeries::getFactor(double pseudoTime)
{
  // check for a quick return
  if (pseudoTime < startTime || thePath == 0)
    return 0.0;

  // determine indexes into the data array whose boundary holds the time
  double incr = (pseudoTime-startTime)/pathTimeIncr; 
  int incr1 = floor(incr);
  int incr2 = incr1+1;
  int size = thePath->Size();

  if (incr2 >= size) {
    if (useLast == false)
      return 0.0;
    else
      return cFactor*(*thePath)[size-1];
  } else {
    double value1 = (*thePath)[incr1];
    double value2 = (*thePath)[incr2];
    return cFactor*(value1 + (value2-value1)*(incr - incr1));
  }
}

double
PathSeries::getDuration()
{
  if (thePath == 0)
  {
    std::cerr << "WARNING -- PathSeries::getDuration() on empty Vector" << "\n";
	return 0.0;
  }
  return (startTime + thePath->Size()*pathTimeIncr);
}

double
PathSeries::getPeakFactor()
{
  if (thePath == 0)
  {
    std::cerr << "WARNING -- PathSeries::getPeakFactor() on empty Vector" << "\n";
	return 0.0;
  }

  double peak = fabs((*thePath)[0]);
  int num = thePath->Size();
  double temp;

  for (int i = 1; i < num; i++)
  {
	temp = fabs((*thePath)[i]);
	if (temp > peak)
	  peak = temp;
  }
  
  return (peak*cFactor);
}
