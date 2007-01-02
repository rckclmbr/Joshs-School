#include "stdinc.h"
#include "basic-data-record.h"
#include "dictionary-record.h"

DictRecord::DictRecord(int k, DataRecord d){  //constructor function
  key_ = k;                                   //  initializes key to k
  data_ = d;                                  //  and data to d
  next_ = prev_ = 0;                        //  both ptrs intially 0
}

DictRecord::DictRecord(){                     //constructor function
  DataRecord d;                               //  that takes no arguments
  key_ = 0;
  data_ = d;         
  next_ = prev_ = 0;                        //  both ptrs intially 0
}
