/*******************/
/** Dani Horowitz **/
/*******************/

#include "basic-data-record.h"
#include "dictionary-record.h"

const int TABLE_SIZE=100;

class CSC120Dictionary
{
public:
	CSC120Dictionary(void); // initialize all dictionary entries to NULL
	void insert(int, DataRecord);           
	void del(int);
	void update(int, int, DataRecord);
	DataRecord* search(int);
	void save();
	void load();
	void print();
private:
	DictRecord* stuff[100];
};