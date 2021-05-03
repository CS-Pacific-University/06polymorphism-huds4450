//****************************************************************************** 
// File name:	 Overnight.h
// Author:		 Maximus Hudson
// Date:		   05/03/2021
// Class:		   CS 250
// Assignment: Polymorphism
// Purpose:		 Demonstrate Polymorphism
//******************************************************************************

#pragma once

#include <iostream>
#include <string>
#include "Parcel.h"

class Overnight : public Parcel {
public:
  Overnight();
  Overnight(string, string, int, int, int, int);

  virtual void print(ostream&) const;
  virtual bool read(istream&);
  virtual double getCost() override;
  virtual int getDeliveryDay() override;
  virtual double getInsure();
  virtual double getRush();

private:
  int mVolume;
};