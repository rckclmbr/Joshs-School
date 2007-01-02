#include "basic-data-record.h"
#include "stdinc.h"

DataRecord::DataRecord(){
  price_ = 0.0;
  quantity_ = 0;
  strcpy(name_," ");
}

DataRecord::DataRecord(float price, int quantity, char *name){
  price_ = price;
  quantity_ = quantity;
  strcpy(name_,name);
}

DataRecord::DataRecord(const DataRecord& d){
  price_ = d.price_;
  quantity_ = d.quantity_;
  strcpy(name_,d.name_);
}

void DataRecord::operator=(const DataRecord& d){
  price_ = d.price_;
  quantity_ = d.quantity_;
  strcpy(name_,d.name_);
}

void DataRecord::price(float p){
  price_ = p;
}

float DataRecord::price(){
  return price_;
}

void DataRecord::quantity(int q){
  quantity_ = q;
}

int DataRecord::quantity(){
  return quantity_;
}

void DataRecord::name(char n[]){
  strcpy(name_,n);
}

char* DataRecord::name(){
  return name_;
}

