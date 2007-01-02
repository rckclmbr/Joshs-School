// Header file for portion of the record besides the key

class DataRecord {                      // class to hold a record

private: float price_;                   // the price of the item
         int quantity_;                  // quantity in stock
         char name_[20];                 // desc of the item


public:  DataRecord(float p, int q, char n[]); //constructor
	 DataRecord();			       //  functions
	 DataRecord(const DataRecord&);        //copy constructor
	 void price(float p);                  //set price
	 float price();                        //read price
	 void quantity(int q);                 //set quantity
	 int quantity();                       //read quantity
	 void name(char n[]);                  //set name
	 char* name();                         //read name
         void DataRecord::operator=(const DataRecord&);  //overload =
};

