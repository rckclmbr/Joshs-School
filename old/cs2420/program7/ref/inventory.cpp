// driver for testing ADT Dictionary implementation with hashing

#include "stdinc.h"
#include "dictionary.h"
#include "input.h"

//****** Function Prototypes*****************************************/
void addrecord(Input prompts, CSC120Dictionary &d);  // add a record
void view(Input prompts,      CSC120Dictionary  d);  // view a record
void update(Input prompts,    CSC120Dictionary &d);  // update a record
void delrecord(Input prompts, CSC120Dictionary &d);  // delete a record


//****** Driver *****************************************************/
int main()
{
  CSC120Dictionary d;
  Input prompts;
  int stop=0;         // stop when stop = 1
  int choice;         // user choice

  d.load();           // loads the dictionary (if doing extra part)

  // while user not done, ask for menu choices and process them.
  // Note that there is no fancy input validation done.

  while (stop==0)
    {
      if (prompts.yes()){
	cout << endl << "Here are the menu choices: " << endl;
	cout << "   1. Insert a new record in database." << endl;
	cout << "   2. View record in the database." << endl;
	cout << "   3. Update record in the database. " << endl;
	cout << "   4. Delete an item from the database" << endl;
	cout << "   5. Exit " << endl;
	cout << "Please select (1,2,3,4,5)? ";
      }
      cin >> choice;
      if (choice==1) addrecord(prompts,d);
      else if (choice==2) view(prompts,d);
      else if (choice==3) update(prompts,d);
      else if (choice==4) delrecord(prompts,d);
      else if (choice==5)
	{
	  d.save();     // saves the dictionary (if doing extra part)
	  stop=1;
	}
    }
    return 0;
}

// Functions processing the menu choices
void addrecord(Input prompts, CSC120Dictionary& d)  // add a record
{
   int key;
   DataRecord rec,         //  data record (has all data except for the key)
              *found;      //  result of search with key


   key = prompts.key();              //get the inputs 
   rec.price(prompts.price());      // and fill rec with all but they key
   rec.quantity(prompts.quantity());
   rec.name(prompts.name());
   found = d.search(key);                      //check if the key is in use
   if (found)
     cout <<  "This bar code " << key << " is already in use." << endl;
   else 
     d.insert(key,rec);                       //insert it in the dictionary
 }

void view(Input prompts, CSC120Dictionary d)  // view a record
{
   int key;                 // the key 
   DataRecord *x;           // a pointer to the datarecord for key

   key = prompts.key();     // get the key
   x = d.search(key);       // search for the record
   if (x == 0)
      cout << "Bar code " << key << " not in use." << endl;

   else {                    // get the data and then print it
      cout << "Bar code: " << key << endl;
      cout << "---Product price: " << x->price() << endl;
      cout << "---Quantity in stock: " << x->quantity() << endl;
      cout << "---Product name: " << x->name() << endl;
   }
}

void update(Input prompts, CSC120Dictionary &d)  // update a record
{

   int key,                     // the key
       change,                  // 1 if user wants to make a change
       new_key;                 // new value for key
   DataRecord new_data,         // new data record being created
              *found,
              *ptr;              // original data

   key = prompts.key();         // get the key
   ptr = d.search(key);           // search for the record
   if (ptr == 0)
      cout << "Bar code " << key << " not in use." << endl;
   else {
      if (prompts.yes()){
         cout << "Bar code currently " << key;
         cout << ". (Type 1 to update, 0 to leave): ";
       }
      cin >> change;
      if (change){
	  new_key = prompts.key();
          found = d.search(new_key);
          if (found){
             cout <<  "Bar code " << new_key;
	     cout << " is already in use so it will not be changed." << endl;
          }
	}
      else new_key = key;

      if (prompts.yes()){
         cout << "Product price currently " << ptr->price();
	 cout << ".  (Type 1 to update, 0 to leave): ";
       }
      cin >> change;
      if (change)
	new_data.price(prompts.price());
      else new_data.price(ptr->price());

      if (prompts.yes()){
         cout << "Quantity in stock currently " << ptr->quantity();
         cout << ".  (Type 1 to update, 0 to leave): ";
       }
      cin >> change;
      if (change)
	new_data.quantity(prompts.quantity());
      else
	new_data.quantity(ptr->quantity());

      if (prompts.yes()){
         cout << "Product name currently " << ptr->name();
	 cout << ".  (Type 1 to update, 0 to leave): ";
       }
      cin >> change;
      if (change) 
	new_data.name(prompts.name());
      else 
	new_data.name(ptr->name());

// update the dictionary

      d.update(key,new_key,new_data);
      }
}

void delrecord(Input prompts, CSC120Dictionary &d)  // delete a record
{
   int key = prompts.key();   // get the key
   d.del(key);                // delete it
}
