void Main_List::getDataFromFile(void)
{
	char temp[256];
	string temp2;

	while(!infile.eof())
	{
		infile.getline(temp, 80, '\n');
		temp2 = temp;
		
		if(temp2.find("Week: ") == 0)		// If it's a new week
		{
			temp2 = temp2.substr(6);
			int week_number = atoi(temp2.c_str());

			Week *newWeek = new Week(week_number);
			newWeek->getDataFromFile();
			weeks.push_back(newWeek);
		}
	}
}

void Main_List::putDataToFile(void)
{
	outfile.open("data.dat");

	list<Week*>::iterator i;
	for(i = weeks.begin(); i != weeks.end(); i++)
	{
		(*i)->putDataToFile();
	}

	outfile.close();
}

Week* Main_List::find_week(int week_num)
{
	list<Week*>::iterator i;

	for(i = weeks.begin(); i != weeks.end(); i++)
	{
		if((*i)->get_week() == week_num)
		{
			return *i;
		}
	}
	return NULL;
}

void Main_List::add_week(void)
{
	int weeknum;

	cout << "Enter week number: ";
	cin >> weeknum;
	Week *tempweek = find_week(weeknum);
	if(tempweek)
		cout << "Week already exists" << endl;
	else
	{
		Week* new_week = new Week(weeknum);
		weeks.push_back(new_week);
		cout << "Week added!" << endl;
	}
	cout << endl;
}

void Main_List::del_week(int week_num)
{
	Week* tempWeek = find_week(week_num);
	if(tempWeek == NULL)
		cout << endl << "That week doesn't exist" << endl;
	else
	{
		weeks.remove(tempWeek);
		cout << "Week deleted!" << endl;
	}
	cout << endl;

}

void Main_List::view_weeksThatExist(void)
{
	list<Week*>::iterator i;
	cout << "Weeks that exist: ";
	for(i = weeks.begin(); i != weeks.end(); i++)
	{
		cout << (*i)->get_week() << ", ";
	}
}
