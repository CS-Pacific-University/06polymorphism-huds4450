//****************************************************************************** 
// File name:	 Letter.cpp
// Author:		 Maximus Hudson
// Date:		   05/03/2021
// Class:		   CS 250
// Assignment: Polymorphism 
// Purpose:		 Demonstrate Polymorphism
//******************************************************************************

#include "Letter.h"
#include <iostream>
#include <string>
#include <iomanip>

//******************************************************************************
// Constructor:	Letter
//
// Description:	Call the Parcel default constructor 
//
// Parameters:	none
//
// Returned:		none
//******************************************************************************
Letter::Letter() : Parcel() {

}

//******************************************************************************
// Constructor:	Letter
//
// Description:	Call the Parcel default constructor 
//
// Parameters:	to        - where package is going to
//              from      - where the package is from
//              weight    - package weight
//              tracking  - package tracking number
//              distance  - distance package travels
//
// Returned:		none
//******************************************************************************
Letter::Letter(string to, string from, int weight,
               int tracking, int distance) :
              Parcel(to, from, weight,
                     tracking, distance) {
}

//******************************************************************************
//Function:		  read
//
//Description:	Reads the Letter from an input
//
//Parameters:		rcIn - stream to read from
//
//Returned:		  True if read in correctly; false if not
//******************************************************************************
bool Letter::read(istream& rcIn) {
  bool bGoodRead = false;

  if (Parcel::read(rcIn)) {
    bGoodRead = true;
  }
  return bGoodRead;
}

//******************************************************************************
// Function:	    print
//
// Description:	  Print the Letter to the stream
//
// Parameters:	  rcOut - the stream to print to
//
// Returned:	    none
//******************************************************************************
void Letter::print(ostream& rcOut) const {
  Parcel::print(rcOut);

}

//******************************************************************************
// Function:	    getCost
//
// Description:	  Gets the cost of the package
//
// Parameters:	  none
//
// Returned:      baseCost - cost of the package
//******************************************************************************
double Letter::getCost() {
  const double LETTER_COST = 0.45;

  double  baseCost = LETTER_COST * mWeight;

  if (mbRush) {
    baseCost += getRush();
  }
  if (mbInsure) {
    baseCost += getInsure();
  }

  return baseCost;
}

//******************************************************************************
// Function:	    getDeliveryDay
//
// Description:	  Gets the amount of days for the package to travel
//
// Parameters:	  None
//
// Returned:	    deliveryDay - days took to travel
//******************************************************************************
int Letter::getDeliveryDay() {
  const int MIN_DAY = 1;
  const int ZERO = 0;
  const int MIN_DISTANCE = 100;

  int deliveryDay = MIN_DAY;


  if (mDistance > MIN_DISTANCE) {
    deliveryDay = mDistance / MIN_DISTANCE + mDistance % MIN_DISTANCE;
  }

  if (mbRush) {
    deliveryDay -= MIN_DAY;
    if (deliveryDay <= ZERO) {
      deliveryDay = MIN_DAY;
    }
  }

  return deliveryDay;
}

//******************************************************************************
// Function:	    getRush
//
// Description:	  Cost to rush package
//
// Parameters:	  None
//
// Returned:	    Cost to rush the package (to be added to baseCost)
//******************************************************************************
double Letter::getRush() {
  const double RUSH = 10;
  mbRush = true;

  return RUSH;
}

//******************************************************************************
// Function:	    getInsure
//
// Description:	  Cost to insure a package
//
// Parameters:	  None
//
// Returned:	    Cost to insure the package (to be added to baseCost)
//******************************************************************************
double Letter::getInsure() {
  const double INSURE_COST = 0.45;
  mbInsure = true;

  return INSURE_COST;
}