//****************************************************************************** 
// File name:	 Parcel.cpp
// Author:		 Maximus Hudson
// Date:		   05/03/2021
// Class:		   CS 250
// Assignment: Polymorphism
// Purpose:		 Demonstrate Polymorphism
//******************************************************************************

#include <iostream>
#include <string>
#include <iomanip>
#include "Parcel.h"

Parcel::Parcel() {
  mAddressFrom = ' ';
  mAddressTo = ' ';
  mWeight = 0;
  mTID = 0;
  mDistance = 0;
}

Parcel::Parcel(string to, string from, int weight,
               int tracking, int distance) {
  mAddressTo = to;
  mAddressFrom = from;
  mTID = tracking;
  mDistance = distance;
  mWeight = weight;
}

void Parcel::print(ostream& rcOStream) const {
  rcOStream << "TID: " << mTID << "\t" << "From: " << mAddressFrom <<
               "\t" << "To: " << mAddressTo;
  if (mbInsure) {

    cout << "\t" << "INSURED";
  }
  if (mbRush) {
    cout << "\t" << "RUSH";
  }
}

bool Parcel::read(istream& rcIStream) {

  bool bGoodRead = false;

  if (rcIStream >> mTID >> mAddressTo >> mAddressFrom >> mWeight >> mDistance) {
    bGoodRead = true;
  }

  return bGoodRead;
}

bool Parcel::isTID(int& rcTID) const{

  bool bMatch = false;

  if (rcTID == mTID) {
    bMatch = true;
  }

  return bMatch;
}