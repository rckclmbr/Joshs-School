// Class FileSystem simulates a simple computer file system.



#define	BLOCK	1024			// size of a file block
#define	NBLOCKS	1024			// number of blocks in the filesystem
#define	NAMESZ	64 - 3 * sizeof(int)	// maximum filename length
#define	DIRSIZE	16			// maximum number of entries in a directory
#define	MAXOPEN	16			// maximum number of files that may be opened
#define	FATBLK	0			// location of the FAT block
#define	ROOTBLK	4			// location of the root block
#define	DATABLK	5			// location of the first data block
#define	NIL	-1			// error return and block link terminator
#define	_CRT_SECURE_NO_DEPRECATE	// silence and MS/C++ deprecation warnings


#include <fstream>
using namespace std;


enum { READ, WRITE };			// file open modes
enum { FS_FILE, FS_DIR };		// flags distinguishing a file and directory
					// additional flags may be defined here
					// for other purposes



// defines the structure of a single directory entry

struct dir_ent
{
	char	name[NAMESZ];
	int		size;
	int		modes;
	int		link;
};



// defines the structure of an entry in the open files table

struct file_ent
{
	char*	buffer; // Stuff is stored in the buffer before being written
	int	bufp;		// BLOCK if read, 0 if write
	int	pointer;	// File table pointer field
	int	block;
	dir_ent*	dir;
};



class FileSystem
{
	private:
		fstream		file;			// simulated filesystem
		int		FAT[4*BLOCK];		// file access table
		dir_ent		root[DIRSIZE];		// root directory
		dir_ent		current[DIRSIZE];	// current directory
		int		dir_block;		// block address of current directory
		file_ent	open_files[MAXOPEN];	// open files table

	public:
			FileSystem();
			~FileSystem();

		// high-level operations
		void	list();
		void	remove(char* name);
		void	rename(char* old_name, char* new_name);
		void	mkdir(char* file);
		void	cd(char* file);
		void	pwd();

		// low-level operations
		int		create(char* name);
		int		open(char* name, int mode);
		void	close(int fd);
		int		read(int fd, char* buffer, int count);
		void	write(int fd, char* buffer, int count);
		void	flush(int fd);

	private:
		void	pwd(int parent, int child);
		int		getByName(dir_ent dir[DIRSIZE], char* name);
		void 	readBlock(int block, char* buffer);
		void	writeBlock(int block, char* buffer);
		void	loadFAT();
		void	saveFAT();
		int		allocate();
};

