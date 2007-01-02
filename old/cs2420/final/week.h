#include "headers.h"

class Week {
	private:
		int person_weight;			// Weight of person that week
		list<Workout*> workouts;	// List of workouts done for that week

	public:
		int week_number;			// Week of workout tracking

		Week() {  person_weight = 0; }
		Week(int); 
		~Week();
		void put_weight(void);				// Set weight for the week
		int get_weight(void);				// Get weight for the week
		void add_workout(void);	
		void del_workout(int, string);		// Remove a workout according to
											// its day of week and name
		void view_workout(int, string);		// view a single workout
											// by its day of week and name
		void view_workouts(void);			// view all workouts for the week
		void view_workoutsByDay(int);		// View the workouts for a specific
											// day of the week
		void view_workoutsByName(string);
		int get_week(void) { return week_number; }
		Workout* find_workout(int, string);	// Find workout by day of week and
											// its name
		void getDataFromFile(void);
		void putDataToFile(void);
};

#include "week.cpp"
