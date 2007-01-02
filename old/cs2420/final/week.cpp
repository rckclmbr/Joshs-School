
void Week::getDataFromFile(void)
{
	char temp[256];
	string temp2;
	bool more = true;
	
	char ch = infile.get();
	if(ch == '\n')
		more = false;
	else
		infile.unget();

	while(more) 
	{
		Workout *newWorkout = new Workout();
		newWorkout->getDataFromFile();
		workouts.push_back(newWorkout);
		ch = infile.get();
		if(ch == '\n')
			more = false;
		else
			infile.unget();
	}
}

void Week::putDataToFile(void)
{
	
	outfile << "Week: " << week_number << endl;
	if(person_weight != 0)
		outfile << "Weight: " << person_weight << endl;
	list<Workout*>::iterator i;
	for(i = workouts.begin(); i != workouts.end(); i++)
	{
		(*i)->putDataToFile();
	}
	outfile << endl;
}

Week::Week(int w)
{
	week_number = w;
	person_weight = 0;
}

Week::~Week()
{
	Workout* tempworkout = new Workout();
	list<Workout*>::iterator i;

	while(!workouts.empty())
		workouts.pop_back();
}

void Week::put_weight(void)
{
	int temp_weight;

	cout << "Enter weight for the week: ";
	cin >> temp_weight;
	if(!temp_weight)
		cout << "Invalid entry, nothing set" << endl;
	else
	{
		person_weight = temp_weight;
		cout << "Weight set" << endl;
	}
}

int Week::get_weight(void)
{
	return person_weight;
}

void Week::add_workout(void)
{
	Workout *new_workout = new Workout();
	new_workout->put_data();
	workouts.push_back(new_workout);
	cout << "Entry added" << endl;
}

void Week::del_workout(int day, string workout_name)
{
	Workout* tempWorkout = find_workout(day, workout_name);
	if(tempWorkout == NULL)
		cout << endl << "That doesn't exist" << endl;
	else
	{
		workouts.remove(tempWorkout);
		cout << "Workout deleted!" << endl;
	}
	cout << endl;
}

void Week::view_workout(int day, string workout_name)
{
	Workout* tempWorkout = find_workout(day, workout_name);
	if(tempWorkout == NULL)
		cout << endl << "That doesn't exist" << endl << endl;
	else
		tempWorkout->get_data();
}

void Week::view_workouts(void)
{
	list<Workout*>::iterator i;
	for(i = workouts.begin(); i != workouts.end(); i++)
	{
		(*i)->get_data();
	}
	cout << endl;
}

void Week::view_workoutsByDay(int day)
{
	list<Workout*>::iterator i;
	for(i = workouts.begin(); i != workouts.end(); i++)
	{
		if((*i)->get_day() == day)
		{
			(*i)->get_data();
		}
	}
	
	cout << endl;
}

void Week::view_workoutsByName(string name)
{
	list<Workout*>::iterator i;
	for(i = workouts.begin(); i != workouts.end(); i++)
	{
		if((*i)->get_workout_name() == name)
		{
			(*i)->get_data();
		}
	}
}

Workout* Week::find_workout(int day, string workout_name)
{
	list<Workout*>::iterator i;
	for(i = workouts.begin(); i != workouts.end(); i++)
	{
			if((*i)->get_day() == day && 
							(*i)->get_workout_name() == workout_name)
				return *i;
	}
	return NULL;
}
