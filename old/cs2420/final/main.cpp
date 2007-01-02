#include "headers.h"
#include "workout.h"
#include "week.h"
#include "main_list.h"

using namespace std;

void use_week(int week_num);
Main_List *MyList = new Main_List();

int main()
{
	// Retrieve data if we can open it
	infile.open("data.dat");
	if(infile.is_open())
	{
		MyList->getDataFromFile();
		cout << "Datafile opened!" << endl << endl;	
		infile.close();
	}

	int choice = 0;

	while(choice != 6)
	{
		cout << "Main Menu" << endl;
		cout << "------------" << endl;
		cout << "1.  Select a week" << endl;
		cout << "2.  Add a week" << endl;
		cout << "3.  Delete a week" << endl;
		cout << "4.  View what weeks exists" << endl;
		cout << "5.  Save data to file \"data.dat\": " << endl;
		cout << "6.  Quit" << endl;
		cout << "Choice: ";
		cin >> choice;
		cout << endl;
		int week_num;
		switch(choice)
		{
			case 1:
				cout << "Which week do you want to work with? ";
				cin >> week_num;
				use_week(week_num);
				break;
			case 2:
				MyList->add_week();
				break;
			case 3:
				cout << "Which week do you want to delete? ";
				cin >> week_num;
				MyList->del_week(week_num);
				cout << "Week deleted!" << endl << endl;
				break;
			case 4:
				MyList->view_weeksThatExist();
				cout << endl << endl;
				break;
			case 5:
				MyList->putDataToFile();
				cout << "Saved!" << endl << endl;
				break;
			case 6:
				break;
			default:
				cout << "Invalid choice" << endl;
				break;
		}
	}

	return 0;
}

void use_week(int week_num)
{
	Week* CurrWeek = MyList->find_week(week_num);
	int choice = 0;
	int day = 0;
	string workout_name = "";

	if(CurrWeek == NULL)
		cout << "No week of that number exists" << endl;
	else
	{
		cout << "Selected: Week " << week_num << endl << endl;
		while(choice != 7)
		{
			cout << "Workout Menu" << endl;
			cout << "--------------" << endl;
			cout << "1.  Add a workout" << endl;
			cout << "2.  Remove a workout" << endl;
			cout << "3.  View a workout" << endl;
			cout << "4.  View all workouts for the week" << endl;
			cout << "5.  View all workouts for a day" << endl;
			cout << "6.  View all workouts of specific name for the week (for tracking): " << endl;
			cout << "7.  Main Menu" << endl;
			cout << "Choice: ";
			cin >> choice;
			cout << endl;
			switch(choice)
			{
				case 1:
					CurrWeek->add_workout();
					break;
				case 2:
					cout << "Enter day to erase: ";
					day = 0;
					cin >> day;
					cout << "Enter workout name to erase: ";
					workout_name = "";
					cin.ignore();
					getline(cin, workout_name);
					CurrWeek->del_workout(day, workout_name);
					cout << endl;
					break;
				case 3:
					cout << "Enter day to view: ";
					day = 0;
					cin >> day;
					cout << "Enter workout name to view: ";
					workout_name = "";
					cin.ignore();
					getline(cin, workout_name);
					CurrWeek->view_workout(day, workout_name);
					cout << endl;
					break;
				case 4:
					CurrWeek->view_workouts();
					cout << endl;
					break;
				case 5:
					day = 0;
					cout << "Enter day you want to view: ";
					cin >> day;
					CurrWeek->view_workoutsByDay(day);
					cout << endl;
					break;
				case 6:
					workout_name = "";
					cout << "Enter name of workouts to view: ";
					cin.ignore();
					getline(cin, workout_name);
					CurrWeek->view_workoutsByName(workout_name);
					cout << endl;
					break;
				case 7:
					break;
				default: 
					cout << "Invalid Choice" << endl;
					break;
			}
		}
	}
	cout << endl;
}
