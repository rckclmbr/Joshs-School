#include "headers.h"

class Main_List
{
	private:
		list<Week*> weeks;

	public:
		void add_week(void);
		void del_week(int);
		void view_weeksThatExist(void);	// View weeks that exist (printed to console)
		Week* find_week(int);
		void putDataToFile(void);
		void getDataFromFile(void);
};

#include "main_list.cpp"
