//****************************************************************************** 
// File name:	 Postcard.h
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

using namespace std;

class Postcard : public Parcel {
public:

  Postcard();
  Postcard(string, string, int, int , int, string );


  virtual void print(ostream& ) const;
  virtual bool read(istream& );

  virtual int getDeliveryDay() override;
  virtual double getCost() override;
  virtual double getInsure();
  virtual double getRush();

private:
  string mMessage;
};