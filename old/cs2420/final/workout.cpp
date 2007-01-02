void Workout::getDataFromFile(void)
{
	char temp[256];
	string temp2 = "spacer";

	while(temp2 != "")
	{
		infile.getline(temp,80,'\n');
		temp2 = temp;

		if(temp2.find("Day: ") == 0)
		{
			temp2 = temp2.substr(5);
			day = atoi(temp2.c_str());
		}
		else if(temp2.find("Name: ") == 0)
		{
			temp2 = temp2.substr(6);
			workout_name = temp2;
		}
		else if(temp2.find("Reps: ") == 0)
		{
			temp2 = temp2.substr(6);
			sets = atoi(temp2.c_str());
		}
		else if(temp2.find("Sets: ") == 0)
		{
			temp2 = temp2.substr(6);
			reps = atoi(temp2.c_str());
		}
		else if(temp2.find("Weight: ") == 0)
		{
			temp2 = temp2.substr(8);
			weight = atoi(temp2.c_str());
		}
	} 
}

void Workout::putDataToFile(void)
{
	outfile << "Day: " << day << endl;
	outfile << "Name: " << workout_name << endl;
	outfile	<< "Reps: " << reps << endl;
	outfile << "Sets: " << sets << endl;
	outfile << "Weight: " << weight << endl;
	outfile << endl;
	outfile.flush();
}

void Workout::put_data(void)
{
	cout << "Enter day of week (1 - 7): ";
	cin >> day;
	cout << "Enter name of workout: ";
	cin.ignore();
	getline(cin, workout_name, '\n');
	cout << "Enter reps done: ";
	cin >> reps;
	cout << "Enter sets done: ";
	cin >> sets;
	cout << "Enter weight (0 if none): ";
	cin >> weight;
}

void Workout::get_data(void)
{
	cout << "|---------------------------------------|" << endl;
	cout << setiosflags(ios::left) << "| Day " << setw(3) << day 
		 << resetiosflags(ios::left) <<  setw(32) << "|" << endl;
	cout << setiosflags(ios::left)
		 << "| Workout Name: " << setw(20) << workout_name
		 << resetiosflags(ios::left) << setw(5) << "|" << endl;
	cout << "| " << setw(3) 
		 << reps << " reps, " << setw(3) << sets << " sets, ";
	if(weight != 0)
	{
		cout << setw(3) << weight << " lbs ";
		cout << setw(11) << "|" << endl;
	}
	else
		cout << setw(19) << "|" << endl;
	cout << "|---------------------------------------|" << endl;
	cout << endl << endl;
}
