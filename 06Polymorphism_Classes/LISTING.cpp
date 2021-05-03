//############################################################################
//Letter.h 
//############################################################################
//****************************************************************************** 
// File name:	 Letter.h
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

class Letter : public Parcel {
public:
  Letter();
  Letter(string, string, int, int, int);


  virtual void print(ostream&) const ;
  virtual bool read(istream&);

  virtual int getDeliveryDay() override;
  virtual double getCost() override;
  virtual double getInsure();
  virtual double getRush();
};   
  
//############################################################################
//Overnight.h 
//############################################################################
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
  
//############################################################################
//Parcel.h 
//############################################################################
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
  
//############################################################################
//Postcard.h 
//############################################################################
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
  
//############################################################################
//Driver.cpp 
//############################################################################
//****************************************************************************** 
// File name:	 Driver.cpp
// Author:		 Maximus Hudson
// Date:		   05/03/2021
// Class:		   CS 250
// Assignment: 06 - Polymorphism
// Purpose:		 Demonstrate Polymorphism
// Hours:      ~ 10 hours
//******************************************************************************
#include "Parcel.h"
#include "Letter.h"
#include "Overnight.h"
#include "Postcard.h"
#include "vld.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

const int MAX_NUM_MAIL = 25;

int getUserTID(int& uTID);
void checkChoice(int& choice);

//******************************************************************************
// Function:    main
//
// Description:	Demonstrate Polymorphism
//              Declare an array of base class pointers and derived
//              class objects.
//              Call functions on base class pointer.
//
// Parameters:	none
//
// Returned:		exit status
//******************************************************************************
int main() {
  const int MAX_NUM_MAIL = 25;

  const char POSTCARD = 'P';
  const char LETTER = 'L';
  const char OVERNIGHT = 'O';

  char mailType;

  int numOfMail = 0;
  int userChoice = 0;
  int userTID = 0;

  Parcel* apcMail[MAX_NUM_MAIL];

  for (int i = 0; i < MAX_NUM_MAIL; i++) {
    apcMail[i] = nullptr;
  }

  ifstream inFile;

  inFile.open("parcels.txt");
  if (!inFile.is_open()) {
    cout << "File is not open!";
    return EXIT_FAILURE;
  }

  while (!inFile.eof() && inFile >> mailType) {
    switch (mailType) {
    case LETTER:
      apcMail[numOfMail] = new Letter;
      apcMail[numOfMail]->read(inFile);
      numOfMail++;
      break;
    case OVERNIGHT:
      apcMail[numOfMail] = new Overnight;
      apcMail[numOfMail]->read(inFile);
      numOfMail++;
      break;
    case POSTCARD:
      apcMail[numOfMail] = new Postcard;
      apcMail[numOfMail]->read(inFile);
      numOfMail++;
      break;
    default:
      break;
    }
  }

  cout << fixed << setprecision(2);

  cout << "Mail Simulator!" << endl << endl;

  bool isRunnin = true;

  while (isRunnin) {
    cout << "1. Print All" << endl;
    cout << "2. Add Insurance" << endl;
    cout << "3. Add Rush" << endl;
    cout << "4. Deliver" << endl;
    cout << "5. Quit" << endl;

    cout << endl;

    checkChoice(userChoice);

    cout << endl;

    if (userChoice == 1) {
      for (int i = 0; i < numOfMail; i++) {
        if (apcMail[i]) {
          apcMail[i]->print(cout);
          cout << endl;
        }
      }
      cout << endl;
    }

    if (userChoice == 2) {
      getUserTID(userTID);
      for (int i = 0; i < numOfMail; i++) {
        if (apcMail[i]) {
          if (apcMail[i]->isTID(userTID)) {
            cout << "Added Insurance for $" << apcMail[i]->getInsure() << endl;
            apcMail[i]->print(cout);
            cout << endl;
            break;
          }
        }
      }
      cout << endl;
    }

    if (userChoice == 3) {
      getUserTID(userTID);
      for (int i = 0; i < numOfMail; i++) {
        if (apcMail[i]) {
          if (apcMail[i]->isTID(userTID)) {
            cout << "Added Insurance for $" << apcMail[i]->getRush() << endl;
            apcMail[i]->print(cout);
            break;
          }
        }
      }
      cout << endl << endl;
    }

    if (userChoice == 4) {
      getUserTID(userTID);
      for (int i = 0; i < numOfMail; i++) {
        if (apcMail[i]) {
          if (apcMail[i]->isTID(userTID)) {
            cout << "Delivered!" << endl;
            cout << apcMail[i]->getDeliveryDay() << " Day, $" <<
              apcMail[i]->getCost() << endl;
            apcMail[i]->print(cout);
            delete apcMail[i];
            apcMail[i] = nullptr;
            break;
          }
        }
      }
      cout << endl << endl;
    }

    if (userChoice == 5) {
      for (int i = 0; i < MAX_NUM_MAIL; i++) {
          if (apcMail[i]) {
            delete apcMail[i];
          }
      }
      isRunnin = false;
      break;
    }
  }
  return EXIT_SUCCESS;
}

//******************************************************************************
//Function:		  checkChoice
//
//Description:	Validates the user inputted choice value
//
//Parameters:		choice - number the user inputs in terminal
//
//Returned:		  None
//******************************************************************************
void checkChoice(int& choice) {
  const int OPTION_ONE = 1;
  const int OPTION_TWO = 2;
  const int OPTION_THREE = 3;
  const int OPTION_FOUR = 4;
  const int OPTION_FIVE = 5;

  do {
    cout << "Choice> ";
    while (!(cin >> choice) ) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  } while (OPTION_ONE != choice && OPTION_TWO != choice &&
    OPTION_THREE != choice && OPTION_FOUR != choice && OPTION_FIVE != choice);

}

//******************************************************************************
//Function:		  getUserTID
//
//Description:	Gets the user's TID
//
//Parameters:		uTID - User inputted TID
//
//Returned:		  uTID 
//******************************************************************************
int getUserTID(int& uTID) {
  cout << "TID> ";
  cin >> uTID;

  return uTID;
}   
  
//############################################################################
//Letter.cpp 
//############################################################################
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
               int tracking, int distance) : Parcel(to, from, weight,
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
  
//############################################################################
//Overnight.cpp 
//############################################################################
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
                     Parcel(to, from, weight, tracking, distance), 
                     mVolume(volume) {
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
  
 
//############################################################################
//Parcel.cpp 
//############################################################################
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
  
 
//############################################################################
//Postcard.cpp 
//############################################################################
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
                   Parcel(to, from, weight, tracking, distance),
                   mMessage(message) {
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