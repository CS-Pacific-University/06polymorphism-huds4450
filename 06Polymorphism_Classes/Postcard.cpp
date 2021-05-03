//****************************************************************************** 
// File name:	 Postcard.cpp
// Author:		 Maximus Hudson
// Date:		   05/03/2021
// Class:		   CS 250
// Assignment: Polymorphism
// Purpose:		 Demonstrate Polymorphism
//******************************************************************************

#include <iostream>
#include <string>
#include <iomanip>
#include "Postcard.h"

//******************************************************************************
// Constructor:	Postcard
//
// Description:	Call the Employee default constructor, set mMessage to empty
//              string
//
// Parameters:	none
//
// Returned:		none
//******************************************************************************
Postcard::Postcard() : Parcel(), mMessage(" "){
}

//******************************************************************************
// Constructor:	Postcard
//
// Description:	Call the Parcel default constructor 
//
// Parameters:	to        - where package is going to
//              from      - where the package is from
//              weight    - package weight
//              tracking  - package tracking number
//              distance  - distance package travels
//              message   - message to send
//
// Returned:		none
//******************************************************************************
Postcard::Postcard(string to, string from, int weight,
  int tracking, int distance, string message) :
  Parcel(to, from, weight,
    tracking, distance), mMessage(message) {
 
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
bool Postcard::read(istream& rcIn) {
  bool bGoodRead = false;

  if (Parcel::read(rcIn) && rcIn >> mMessage) {
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
void Postcard::print(ostream& rcOut) const {
  Parcel::print(rcOut);

  cout << "\t" << mMessage;
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
double Postcard::getCost() {
  const double POSTCARD_COST = 0.15;

  double baseCost = POSTCARD_COST;

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
int Postcard::getDeliveryDay() {
  const int MIN_DAY = 1;
  const int RUSHED = 2;
  const int ZERO = 0;
  const int MIN_DISTANCE = 10;

  int deliveryDay = MIN_DAY;

  if (mDistance > MIN_DISTANCE) {
    deliveryDay = deliveryDay / MIN_DISTANCE + deliveryDay % MIN_DISTANCE;
  }

  if (mbRush) {
    deliveryDay -= RUSHED;
    if (deliveryDay <= ZERO) {
      deliveryDay = MIN_DAY;
    }
  }

  return deliveryDay;
}

//******************************************************************************
// Function:	    getInsure
//
// Description:	  Cost to insure a package
//
// Parameters:	  None
//
// Returned:	    INSURE_COST - Cost to insure the package 
//                              (to be added to baseCost)
//******************************************************************************
double Postcard::getInsure() {
  const double INSURE_COST = 0.15;
  mbInsure = true;

  return INSURE_COST;
}

//******************************************************************************
// Function:	    getRush
//
// Description:	  Cost to rush a package
//
// Parameters:	  None
//
// Returned:	    RUSH_COST - Cost to insure the package 
//                            (to be added to baseCost)
//******************************************************************************
double Postcard::getRush() {
  const double RUSH_COST = 0.25;
  mbRush = true;

  return RUSH_COST;
}