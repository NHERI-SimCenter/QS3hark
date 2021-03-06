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
                                                                        
// $Revision: 1.5 $
// $Date: 2010-02-04 00:32:01 $
// $Source: /usr/local/cvs/OpenSees/SRC/domain/pattern/TimeSeries.h,v $
                                                                        
#ifndef TimeSeries_h
#define TimeSeries_h

// Written: fmk 
// Created: 07/99
// Revision: A
//
// Purpose: This file contains the class definition for TimeSeries.
// TimeSeries is an abstract class. A TimeSeries object is used to
// determine the load factor to be applied to the loads in a pettern.
// to the model. 
//
// What: "@(#) TimeSeries.h, revA"

#include <TaggedObject.h>

//#include <OPS_Globals.h>
//#include <Information.h>


class TimeSeries : public TaggedObject
{
  public:
    TimeSeries(int tag, int classTag);
    TimeSeries(int classTag);
    virtual ~TimeSeries();

    virtual TimeSeries *getCopy(void) =0;

    // pure virtual functions
    virtual double getFactor (double pseudoTime) = 0;
    virtual double getDuration () = 0;
    virtual double getPeakFactor () = 0;

    virtual double getTimeIncr (double pseudoTime) = 0;


  protected:

  private:
};

/*
extern void OPS_clearAllTimeSeries(void);
extern bool OPS_addTimeSeries(TimeSeries *newComponent);
extern TimeSeries *OPS_getTimeSeries(int tag);
extern bool OPS_removeTimeSeries(int tag);
*/

#endif
