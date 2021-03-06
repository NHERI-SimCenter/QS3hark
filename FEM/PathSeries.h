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
                                                                        
// $Revision: 6225 $
// $Date: 2016-03-03 22:07:01 +0100 (ju., 03 mar. 2016) $
// $URL: svn://peera.berkeley.edu/usr/local/svn/OpenSees/trunk/SRC/domain/pattern/PathSeries.h $

#ifndef PathSeries_h
#define PathSeries_h

// Written: fmk 
// Created: 07/99
// Revision: A
//
// Description: This file contains the class definition for PathSeries.
// PathSeries is a TimeSeries class which linear interpolates the
// load factor using user specified control points provided in a vector object.
// the points in the vector are given at regular time increments pathTimeIncr
// apart. (could be provided in another vector if different)

#include <TimeSeries.h>

class Vector;

class PathSeries : public TimeSeries
{
  public:
    // constructors
    PathSeries(int tag,
        const Vector &thePath,
        double pathTimeIncr = 1.0,
        double cfactor = 1.0,
        bool useLast = false,
        bool prependZero = false,
        double startTime = 0.0);
    PathSeries(int tag,
        const char *fileName, 
        double pathTimeIncr = 1.0,
        double cfactor = 1.0,
        bool useLast = false,
        bool prependZero = false,
        double startTime = 0.0);
    PathSeries();
    
    // destructor
    ~PathSeries();
    
    TimeSeries *getCopy(void);
    
    // method to get factor
    double getFactor(double pseudoTime);
    double getDuration ();
    double getPeakFactor ();
    double getTimeIncr (double pseudoTime) {return pathTimeIncr;}

    
  protected:
    
  private:
    Vector *thePath;      // vector containg the data points
    double pathTimeIncr;  // specifies the time increment used in load path vector
    double cFactor;       // additional factor on the returned load factor
    int otherDbTag;       // a database tag needed for the vector object
    int lastSendCommitTag;
    bool useLast;
    double startTime;
};

#endif

