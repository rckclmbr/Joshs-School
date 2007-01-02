/*******************/
/** Dani Horowitz **/
/*******************/

#include "stdinc.h"
#include "dictionary.h"
#include <fstream.h>

// multiplication method for computing a hash function
// with m = 100 and A = .618
int hash(int k)
{
	double a = .618, frac;
	int hash_value;
	
	frac = (k * a) - (int)(k * a);		// computes k*a - floor(k*a)
	hash_value = (int)(100.0 * frac);	// keeps most two significant digits of
										// frac to return as the hash value
	return (hash_value);
}

// constructor function initializes array of pointers to point to NULL
CSC120Dictionary::CSC120Dictionary()
{
	for (int i=0; i < 100; i++) stuff[i] = NULL;
}

// adds a record with given key and data to the front of the list
void CSC120Dictionary::insert(int key, DataRecord data_rec)
{
	int index = hash(key);
	DictRecord* temp = new DictRecord(key, data_rec);
	if (stuff[index] != NULL)
	{
		stuff[index]->prev_ = temp;
		temp->next_ = stuff[index];
	}
	stuff[index] = temp;
	return;
}

// deletes a record with given key from the list
void CSC120Dictionary::del(int key)
{
	// traverse list looking for specified key
	DictRecord* i;
	bool found = false;
	for (i = stuff[hash(key)]; i != NULL; i=i->next_)
	{
		if (i->key_ == key)
		{
			found = true;

			// fix linked list pointers
			if (i->prev_ != NULL) (i->prev_)->next_ = i->next_;
			else stuff[hash(key)] = NULL;
			if (i->next_ != NULL) (i->next_)->prev_ = i->prev_;
			break;
		}
	}
	if (found) delete (i);
	else cout << "\nItem not found";
	return;
}

// replaces an existing record with a new key and data
void CSC120Dictionary::update(int old_key, int new_key, DataRecord new_data)
{
	del(old_key);
	insert(new_key, new_data);
	return;
}

// searches the list for a key and returns its location
DataRecord* CSC120Dictionary::search(int key)
{
	DataRecord* temp = NULL;

	// traverse list looking for specified key
	for (DictRecord* i = stuff[hash(key)]; i != NULL; i=i->next_)
	{
		if (i->key_ == key)
		{
			temp = &(i->data_);
			break;
		}
	}
	return (temp);
}

// copies the hash table to an external text file
void CSC120Dictionary::save()
{
	ofstream merchandise("input.dat");
	for (int i=0; i<100; i++)
	{
		for (DictRecord* list = stuff[i]; list != NULL; list=list->next_)
		{
			merchandise << list->key_ << " ";
			merchandise << (list->data_).price() << " ";
			merchandise << (list->data_).quantity() << " ";
			merchandise << (list->data_).name() << endl;
		}
	}
	cout << "\n\tData has been saved to an external data file\n";
	merchandise.close();
	print();
	return;
}

// imports data in an external text file into the hash table
void CSC120Dictionary::load()
{
	char tempName[20];
	float tempPrice;
	int tempStock, tempKey;

	ifstream merchandise("input.dat");
	if (!merchandise)
	{
		cerr << "\nI need a data file";
		exit(1);
	}

	// read data and place in hash table accordingly
	while ( !merchandise.eof() )
	{
		merchandise >> tempKey;
		merchandise >> tempPrice;
		merchandise >> tempStock;
		merchandise >> tempName;

		DataRecord newData(tempPrice, tempStock, tempName);
		insert(tempKey, newData);
	}
	
	cout << "\n\tData has been loaded from an external data file\n";
	merchandise.close();
	return;
}

// print out the hash table
void CSC120Dictionary::print()
{
	cout << "\nDemonstration of the Hash Table:\n";
	for (int i=0; i<100; i++)
	{
		cout << "\nindex " << i << ":  ";
		for (DictRecord* list = stuff[i]; list != NULL; list=list->next_)
			cout << (list->data_).name() << " ";
	}
	cout << endl;
	return;
}