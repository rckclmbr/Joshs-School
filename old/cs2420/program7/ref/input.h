// Header file for class to get input from the user. 

class Input {

 private: int flag_;                // flag of 1 means to print prompts

 public:  Input();                  // constructor function
          int   key();              // get the key (the bar code)
          float price();            // get the price
          int   quantity();         // get the quantity
          char* name();             // get the product name
          int   yes();              // return true if prompts wanted
};


