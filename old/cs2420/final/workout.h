#include "headers.h"

class Workout
{
	private:
		string workout_name;
		int day;
		int reps;
		int sets;
		int weight;

	public:
		Workout() { day = 0; reps = 0; sets = 0; weight = 0; }
		void put_data(void);
		void get_data(void);
		void getDataFromFile(void);
		void putDataToFile(void);
		string get_workout_name(void) { return workout_name; }
		int get_day(void) { return day; }

};

#include "workout.cpp"
