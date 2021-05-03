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
      for (int i = 0; i < MAX_NUM_MAIL; i++) {\
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