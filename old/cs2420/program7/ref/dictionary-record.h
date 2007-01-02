// Header file for a complete dicitonary record.  The convention for the
//   member variables is that they end with a underscore.  Procedures
//   with the name obtained by removing the underscore will be used to
//   get and set the values of these variables

class DictRecord {
  friend class CSC120Dictionary;   // allows dictionary to access the private
                                  //  data -- this allows next_ and prev_
                                  //  from being exposed to the user program
 private: int key_;               // the key
          DataRecord data_;       // the data record
          DictRecord* next_;      // a pointer to the next dictionary record
          DictRecord* prev_;      // a pointer to the previous dict. record
          DictRecord(int k, DataRecord);     //constructor 
          DictRecord();                      //  functions
};

