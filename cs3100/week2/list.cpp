// Joshua Braegger
// CS3100
// Assignment 1

#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <iomanip>
using namespace std;

#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <string.h>
#include <time.h>

int examine(char*,char*);

struct modes {
	unsigned others : 3;
	unsigned group  : 3;
	unsigned user   : 3;
	unsigned type   : 7;
};

union short_to_modes
{
	unsigned short statmode;
	struct modes conv;
};

char* fmodes[] = { "---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx" };

int main(int argc, char* argv[])
{
	int i;

	if(argc < 2)
		examine("./*","");

	for(i = 1; i < argc; i++)
		examine(argv[i],"");

	return 0;

}

int examine(char* argv, char* dir)
{
	struct _stat			file_info;
	union short_to_modes 	convert;
		  _finddata_t		data;
		  intptr_t			handle;

	if((handle = _findfirst(argv, &data)) > 0) {
		do
		{
			// Filter out the . and .. directories
			if(strcmp(data.name,".") == 0 || strcmp(data.name,"..") == 0)
				continue;
				
			_stat(data.name, &file_info);
			convert.statmode = file_info.st_mode;

			// Print if directory
			if(_S_IFDIR & file_info.st_mode) {
				cout << "d";
			}
			else
				cout << "-";

			// Print permissions
			cout << fmodes[convert.conv.user] << 
					fmodes[convert.conv.group] << 
					fmodes[convert.conv.others];

			// Print filesize
			cout << setw(9) << data.size;

			struct tm* t = localtime(&data.time_write);

			// Print Date
			char buffer[48];
			strftime(buffer, 256," %m/%d/%Y", t);
			fputs(buffer,stdout);

			// Print time
			cout << " " << 
				setw(2) << setfill('0') << t->tm_hour << ":" <<
				setw(2) << t->tm_min  << ":" << 
				setw(2) << t->tm_sec;

			cout << setfill(' ');

			cout << " " << dir << data.name << endl;
		} while(!(_findnext(handle, &data)));

		_findclose(handle);
	}
	
	return 0;
}
