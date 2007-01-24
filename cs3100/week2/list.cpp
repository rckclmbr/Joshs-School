#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <iomanip>
using namespace std;

#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <string.h>
#include <time.h>

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
	{
		fprintf(stderr, "USAGE: list <directory/file>\n");
		exit(1);
	}

	for(i = 1; i < argc; i++)
		examine(argv[i]);

	return 0;

}

int examine(char* argv)
{
	struct stat				file_info;
	union short_to_modes 	convert;
		  _finddata_t		data;
		  intptr_t			handle;

	_stat(argv, &file_info);
	convert.statmode = file_info.st_mode;

	if(_S_IFDIR & file_info.st_mode)
			cout << "d";
	else
			cout << "-";

	cout << fmodes[convert.conv.user] << 
			fmodes[convert.conv.group] << 
			fmodes[convert.conv.others] << endl;

	handle = _findfirst(argv, &data);
	cout << data.name << endl;

	struct tm* t = localtime(&data.time_write);

	cout << setw(2) << setfill('0') << t->tm_hour << endl;
	_findclose(handle);
					
	return 0;
}
