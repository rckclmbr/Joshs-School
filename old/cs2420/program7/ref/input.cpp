// Class to get input from the user.  It only prints a prompt to the terminal
//    when requested.

#include "input.h"
#include "stdinc.h"

Input::Input(){
  cout << endl << "Would you like prompts (yes=1, no=0)? ";
  cin >> flag_;
  cout << endl << endl;
}

int Input::key(){       // get the key (the bar code)
  int key;
  if (flag_)
    cout << "   Bar code (key): ";
  cin >> key;
  return key;
}

float Input::price(){   // get the price
  float price;
  if (flag_)
    cout << "   Price: ";
  cin >> price;
  return price;
}

int Input::quantity(){   // get the quantity
  int quantity;
  if (flag_)
    cout << "   Quantity in stock: ";
  cin >> quantity;
  return quantity;
}

char* Input::name(){     // get the product name
  char *name;
  name = new char[20];
  if (flag_)
    cout << "   Product name (max 20 characters, no spaces!): ";
  cin >> name;
  return name;
}

int Input::yes(){   // return true if prompts are desired
  return flag_;
}
