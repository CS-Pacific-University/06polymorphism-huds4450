//****************************************************************************** 
// File name:	 Parcel.h
// Author:		 Maximus Hudson
// Date:		   05/03/2021
// Class:		   CS 250
// Assignment: Polymorphism
// Purpose:		 Demonstrate Polymorphism
//******************************************************************************
#pragma once

#include <iostream>
#include <string>

using namespace std;

class Parcel {
  public:
    Parcel();
    Parcel(string , string , int , int , int);

    virtual void print(ostream& ) const;
    virtual bool read(istream& );
   
    virtual bool isTID(int&) const;
 
    virtual int getDeliveryDay() = 0;
    virtual double getRush() = 0;
    virtual double getInsure() = 0;
    virtual double getCost() = 0;

  protected:
    string mAddressTo;
    string mAddressFrom;
    int mWeight;
    int mTID;
    int mDistance;
    bool mbRush = false;
    bool mbInsure = false;
};