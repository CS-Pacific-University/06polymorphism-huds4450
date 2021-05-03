//****************************************************************************** 
// File name:	 Overnight.cpp
// Author:		 Maximus Hudson
// Date:		   05/03/2021
// Class:		   CS 250
// Assignment: Polymorphism
// Purpose:		 Demonstrate Polymorphism
//******************************************************************************

#include <iostream>
#include <string>
#include <iomanip>
#include "Overnight.h"

//******************************************************************************
// Constructor:	Postcard
//
// Description:	Call the Employee default constructor, set mVolume to 0
//
// Parameters:	none
//
// Returned:		none
//******************************************************************************
Overnight::Overnight() : Parcel(), mVolume(0) {
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
//              volume    - volume of the package
//
// Returned:		none
//******************************************************************************
Overnight::Overnight(string to, string from, int weight,
  int tracking, int distance, int volume) :
  Parcel(to, from, weight,
    tracking, distance), mVolume(volume) {
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
bool Overnight::read(istream& rcIn) {
  bool bGoodRead = false;

  if (Parcel::read(rcIn) && rcIn >> mVolume) {
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
void Overnight::print(ostream& rcOut) const {
  Parcel::print(rcOut);

  cout << "\t" << "OVERNIGHT!";
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
double Overnight::getCost() {
  const double MAX_COST = 20;
  const double MIN_COST = 12;
  const double RUSH_TOTAL = 1.75;
  const double INSURE_TOTAL = 1.25;

  double baseCost = 0;

  if (mVolume > 100) {
    baseCost = MAX_COST;
  }
  if (mVolume <= 100) {
    baseCost = MIN_COST;
  }
  if (mbRush) {
    baseCost *= RUSH_TOTAL;
  }
  if (mbInsure) {
    baseCost *= INSURE_TOTAL;
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
int Overnight::getDeliveryDay() {
  const int MIN_DAY = 1;
  const int ZERO = 0;
  const int MIN_DISTANCE = 1000;

  int deliveryDay = MIN_DAY;

  if (mDistance <= MIN_DISTANCE) {
    deliveryDay = MIN_DAY;
  }

  if (mDistance > MIN_DISTANCE) {
    deliveryDay = mDistance / MIN_DISTANCE;
    if (mDistance % MIN_DISTANCE > ZERO) {
      deliveryDay += MIN_DAY;
    }
  }

  if (mbRush) {
    deliveryDay = MIN_DAY;
  }

  return deliveryDay;
}

//******************************************************************************
// Function:	    getRush
//
// Description:	  Cost to rush a package
//
// Parameters:	  None
//
// Returned:	    rushCsot  - Cost to insure the package 
//                            (to be added to baseCost)
//******************************************************************************
double Overnight::getRush() {
  double const RUSH = 0.75;

  double rushCost = getCost() * RUSH;
  mbRush = true;
  return rushCost;
}

//******************************************************************************
// Function:	    getInsure
//
// Description:	  Cost to insure a package
//
// Parameters:	  None
//
// Returned:	    insureCost  - Cost to insure the package 
//                              (to be added to baseCost)
//******************************************************************************
double Overnight::getInsure() {
  const int INSURE = 4;

  double insureCost = getCost() / 4;
  mbInsure = true;
  return insureCost;
}