// the Shell class implements a simple commandline interface (CLI)
// that drives the simulated filesystem.
//
// Commands entered at the prompt into integer tokens through an
// associative array backed by a fast lookup mechanism.
// Installing new commands requires four steps:
// 1. Add a new enumeration to "tokens" at the beginning of the class.
// 2. Add a string representing the command to the commands array at
//    the beginning of the constructor.
// 3. Add an appropriate case to the switch in the run function.
// 4. Add an appropriate entry to the help function at the bottom of the file.
// take care that the token and the string are added at the same
// location in their respective lists.


#include "FileSystem.h"
#include <iostream>
#include <string>
#include <map>
using namespace std;





class Shell
{
	private:
		enum tokens { UNKNOWN, EXIT, LIST, COPY, VIEW,
			REMOVE, RENAME, MKDIR, CD, PWD, XCOPY, HELP };

		string				command;
		string				args;
		map<string, int, less<string>>	commandMap;
		FileSystem			fs;

	public:
			Shell();
	const	char*	getArg();
		int	next();
		void	run();
		void	help();
		void	view(char* file);
		void	xcopy(char* x_file, char* l_file);
		void	copy(char* old_file, char* new_file);
};





// initializes the associative array.

Shell::Shell()
{
	char*	commands[] = { "unknown", "exit", "list", "copy", "view",
		"remove", "rename", "mkdir", "cd", "pwd", "xcopy", "help" };
	for (int i = 1; i < sizeof(commands)/sizeof(char*); i++)
		commandMap[commands[i]] = i;

	cout << "Type help for a list of commands\n";
}




// extracts an optional argument from the commandline input.

const char* Shell::getArg()
{
	int	i = args.find(' ');
	if (i == -1)
		return args.c_str();
	static string c;
	c = args.substr(0, i);
	args = args.substr(i+1, args.length());
	return c.c_str();
}




// gets the next command from the command line -- including optional arguments.

int Shell::next()
{
	string	commandline;

	cout << "> ";
	getline(cin, commandline);

	int	i = commandline.find(' ');

	if (i == -1)
	{
		command = commandline;
		args = "";
	}
	else
	{
		command = commandline.substr(0, i);
		args = commandline.substr(i+1, commandline.length());
	}

	return commandMap[command];
}




// loops executing commands from the command line.

void Shell::run()
{
	bool		running = true;

	while(running)
	{
		int	c = next();
		switch(c)
		{
			case EXIT :
				running = false;
				break;
			case LIST :
				fs.list();
				break;
			case COPY :
				{
					char arg1[1000];
					char arg2[1000];
					strcpy(arg1, getArg());
					strcpy(arg2, getArg());
					copy(arg1, arg2);
					break;
				}
			case VIEW :
				{
					char arg[1000];
					strcpy(arg, getArg());
					view(arg);
					break;
				}
			case REMOVE :
				{
					char arg[1000];
					strcpy(arg, getArg());
					fs.remove(arg);
					break;
				}
			case RENAME :
				{
					char arg1[1000];
					char arg2[1000];
					strcpy(arg1, getArg());
					strcpy(arg2, getArg());
					fs.rename(arg1, arg2);
					break;
				}
			case MKDIR :
				{
					char arg[1000];
					strcpy(arg, getArg());
					fs.mkdir(arg);
					break;
				}
			case CD :
				{
					char arg[1000];
					strcpy(arg, getArg());
					fs.cd(arg);
					break;
				}
			case PWD :
				fs.pwd();
				break;
			case XCOPY :
				{
					char arg1[1000];
					char arg2[1000];
					strcpy(arg1, getArg());
					strcpy(arg2, getArg());
					xcopy(arg1, arg2);
					break;
				}
			case HELP :
				help();
				break;
			default:
			      cerr << "UNKNOWN COMMAND: " << command << endl;
			      break;
		}
	}
}



// displays the contents of the named file on the console.

void Shell::view(char* file)
{
	if (strlen(file) == 0)
	{
		cerr << "USAGE: view <file>\n";
		return;
	}

	char	buffer[BLOCK + 1];
	int	fd = fs.open(file, READ);
	int	count;

	while ((count = fs.read(fd, buffer, BLOCK)) > 0)
	{
		buffer[count] = '\0';
		cout << buffer;
	}

	cout << endl;
	fs.close(fd);
}



// copies a file from the external (i.e., real) file system to a file
// in the simulated file system.

void Shell::xcopy(char* x_file, char* l_file)
{
	if (strlen(x_file) == 0 || strlen(l_file) == 0)
	{
		cerr << "USAGE: xcopy <external_file> <local_file>\n";
		return;
	}


	int	 fd = fs.create(l_file);
	char	 buffer[BLOCK];
	ifstream in(x_file, ios::in | ios::binary);

	while(!in.eof())
	{
		in.read(buffer, BLOCK);
		fs.write(fd, buffer, in.gcount());
	}

	fs.flush(fd);
	fs.close(fd);
}



// copies a file in the simulated filesystem to a new file in the simulated filesystem.
// In the current implementation both files must be in the same (current) directory.

void Shell::copy(char* old_file, char* new_file)
{
	if (strlen(old_file) == 0 || strlen(new_file) == 0)
	{
		cerr << "USAGE: copy <old_file> <new_file>\n";
		return;
	}

	int	fdin = fs.open(old_file, READ);

	if (fdin == NIL)
	{
		cerr << "ERROR: unable to open \"" << old_file << "\" for reading\n";
		return;
	}

	int	fdout = fs.create(new_file);

	if (fdout == NIL)
	{
		fs.close(fdin);
		cerr << "ERROR: unable to open \"" << new_file << "\" for writing\n";
		return;
	}

	char	buffer[BLOCK];
	int	count;
	while((count = fs.read(fdin, buffer, BLOCK)) > 0)
		fs.write(fdout, buffer, count);

	fs.flush(fdout);
	fs.close(fdin);
	fs.close(fdout);
}



// prints a list of available commands and their format.

void Shell::help()
{
	cout << "help\n\tdisplay this list of commands\n\n";
	cout << "exit\n\tterminate the cli/file system simulator\n\n";
	cout << "list [dir]\n\tlist the contends of directory dir or\n\tthe current directory if dir is not specified\n\n";
	cout << "copy <source> <destination>\n\tcopy simulated source file to simulated destination file\n\n";
	cout << "view <file>\n\twrite simulated file to the console\n\n";
	cout << "remove <file | dir>\n\tremove simulated file or directory\n\n";
	cout << "rename <old> <new>\n\trename old simulated file or directory to new name\n\n";
	cout << "mkdir <dir>\n\tmake a new simulated directory\n\n";
	cout << "cd [dir]\n\tchange to simulated directory if specified or\n\tto simulated root directory\n\n";
	cout << "pwd\n\tprint the full path of the current working directory\n\n";
	cout << "xcopy <external> <sim>\n\tcopy the external file (from the \"real\" file system)\n\tto the simulated file\n\n";
}


// execution startup.

int main()
{
	Shell	cli;

	cli.run();

	return 0;
}

