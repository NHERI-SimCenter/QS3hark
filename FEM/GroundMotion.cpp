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
                                                                        
// $Revision: 1.11 $
// $Date: 2008-02-29 22:35:36 $
// $Source: /usr/local/cvs/OpenSees/SRC/domain/groundMotion/GroundMotion.cpp,v $
                                                                        
// Written: fmk 
// Created: 05/98
// Revision: A


#include <GroundMotion.h>
#include <TimeSeriesIntegrator.h>
#include <TrapezoidalTimeSeriesIntegrator.h>
#include <ID.h>
#include <string>
#include <iostream>

GroundMotion::GroundMotion(TimeSeries *dispSeries, 
			   TimeSeries *velSeries, 
			   TimeSeries *accelSeries,
			   TimeSeriesIntegrator *theIntegratr,
			   double dTintegration, double factor)
: theAccelSeries(accelSeries), theVelSeries(velSeries),
 theDispSeries(dispSeries), theIntegrator(theIntegratr),
 data(3), delta(dTintegration), fact(factor)
{

  if (theAccelSeries != 0 && theVelSeries == 0 ) 
    theVelSeries = this->integrate(theAccelSeries, delta);

  if (theVelSeries != 0 && theDispSeries == 0 ) 
    theDispSeries = this->integrate(theVelSeries, delta);
}



GroundMotion::GroundMotion(int theClassTag)
:
 theAccelSeries(0), theVelSeries(0), theDispSeries(0), theIntegrator(0),
 data(3), delta(0.0), fact(1.0)
{

}

GroundMotion::~GroundMotion()
{
  if (theAccelSeries != 0)
    delete theAccelSeries;
  if (theVelSeries != 0)
    delete theVelSeries;
  if (theDispSeries != 0)
    delete theDispSeries;
  if (theIntegrator != 0)
    delete theIntegrator;
}


void
GroundMotion::setIntegrator(TimeSeriesIntegrator *integrator)
{
  if (theIntegrator != 0)
    delete theIntegrator;

  theIntegrator = integrator;
}

TimeSeries*
GroundMotion::integrate(TimeSeries *theSeries, double delta)
{
  // check that an integrator & accel series exist
  if(theIntegrator == 0) {
    theIntegrator = new TrapezoidalTimeSeriesIntegrator();

    if(theIntegrator == 0) {
      std::cerr << "WARNING:GroundMotion::integrate() - no TimeSeriesIntegrator provided - failed to create a Trapezoidal .. memory problems! \n";
      return 0;
    }
  }

  if(theSeries == 0) {
    std::cerr << "GroundMotion::integrate - no TimeSeries specified\n";
    return 0;
  }

  // integrate the series, if no vel series exists set it to new one
  TimeSeries *theNewSeries = theIntegrator->integrate(theSeries, delta);

  if(theNewSeries == 0) {
    std::cerr << "GroundMotion::integrate - no TimeSeriesIntegrator failed to integrate\n";
    return 0;
  }

  return theNewSeries;
}

double 
GroundMotion::getDuration(void)
{
  if (theAccelSeries != 0)
    return theAccelSeries->getDuration();
  else
    return 0.0;
}

double 
GroundMotion::getPeakAccel(void)
{
  if (theAccelSeries != 0)
    return fact*(theAccelSeries->getPeakFactor());
  else
    return 0.0;

}

double 
GroundMotion::getPeakVel(void)
{
  if (theVelSeries != 0)
    return fact*(theVelSeries->getPeakFactor());

  // if theAccel is not 0, integrate accel series to get a vel series
  else if (theAccelSeries != 0) {
    theVelSeries = this->integrate(theAccelSeries, delta);
    if (theVelSeries != 0)
      return fact*(theVelSeries->getPeakFactor());      
    else
      return 0.0;
  }
  return 0.0;
}

double 
GroundMotion::getPeakDisp(void)
{
  if (theDispSeries != 0)
    return fact*(theDispSeries->getPeakFactor());

  // if theVel is not 0, integrate vel series to get disp series
  else if (theVelSeries != 0) {
    theDispSeries = this->integrate(theVelSeries, delta);
    if (theDispSeries != 0)
      return fact*(theDispSeries->getPeakFactor());      
    else
      return 0.0;
  }

  // if theAccel is not 0, integrate vel series to get disp series
  else if (theAccelSeries != 0) {
    theVelSeries = this->integrate(theAccelSeries, delta);
    if (theVelSeries != 0) {
      theDispSeries = this->integrate(theVelSeries, delta);
      if (theDispSeries != 0)
	return fact*(theDispSeries->getPeakFactor());      
      else
	return 0.0;
    } else
      return 0.0;
  }

  return 0.0;
}

double 
GroundMotion::getAccel(double time)
{
  if (time < 0.0)
    return 0.0;
  
  if (theAccelSeries != 0)
    return fact*(theAccelSeries->getFactor(time));
  else
    return 0.0;
}     



double 
GroundMotion::getVel(double time)
{
  if (time < 0.0)
    return 0.0;
  
  if (theVelSeries != 0)
    return fact*(theVelSeries->getFactor(time));      
  
  // if theAccel is not 0, integrate accel series to get a vel series
  else if (theAccelSeries != 0) {
    //std::cerr << " WARNING: GroundMotion::getVel(double time) - integration is required to get the ground velocities from the ground accelerations\n";
    theVelSeries = this->integrate(theAccelSeries, delta);
    
    if (theVelSeries != 0) {
      return fact*(theVelSeries->getFactor(time));      
      
    } else {
      std::cerr << " WARNING: GroundMotion::getVel(double time) - failed to integrate\n";
      return 0.0;
    }
  }

  return 0.0;
}

double 
GroundMotion::getDisp(double time)
{
  if (time < 0.0)
    return 0.0;

  if (theDispSeries != 0)
    return fact*(theDispSeries->getFactor(time));

  // if theVel is not 0, integrate vel series to get disp series
  else if (theVelSeries != 0) {
    std::cerr << " WARNING: GroundMotion::getDisp(double time) - integration is required to get the ground displacements from the ground velocities\n";
    theDispSeries = this->integrate(theVelSeries, delta);
    if (theDispSeries != 0)
      return fact*(theDispSeries->getFactor(time));      
    else
      return 0.0;
  }

  // if theAccel is not 0, integrate vel series to get disp series
  else if (theAccelSeries != 0) {    
    std::cerr << " WARNING: GroundMotion::getDisp(double time) - default integration required to get the ground displacements from the ground velocities via the ground accelerations\n";
    theVelSeries = this->integrate(theAccelSeries, delta);
    if (theVelSeries != 0) {
      theDispSeries = this->integrate(theVelSeries, delta);
      if (theDispSeries != 0)
	return fact*(theDispSeries->getFactor(time));      
      else
	return 0.0;
    } else
      return 0.0;
  }

  return 0.0;
}

const Vector &
GroundMotion::getDispVelAccel(double time)
{
  if (time < 0.0) {
    data(0) = 0.0;
    data(1) = 0.0;
    data(2) = 0.0;
    return data;
  }

  if (theAccelSeries != 0 && theVelSeries != 0 && theDispSeries != 0) {
    data(0) = fact*(theDispSeries->getFactor(time));
    data(1) = fact*(theVelSeries->getFactor(time));
    data(2) = fact*(theAccelSeries->getFactor(time));
  } else {
    data(2) = this->getAccel(time);
    data(1) = this->getVel(time);
    data(0) = this->getDisp(time);
  }

  return data;
}


