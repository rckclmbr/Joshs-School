// creates a new (or resets) a simulated filesystem 1 MB in size.


#include "FileSystem.h"
#include <fstream>
#include <memory.h>
using namespace std;


int main()
{
	// open the file for output - discard existing data
	fstream	file("filesystem", ios::out | ios::trunc | ios::binary);

	char	block[BLOCK];
	memset(block, 0, BLOCK);

	// move to the start of the file for writing
	file.seekp(FATBLK * BLOCK);

	// write 0's to the full file
	for (int i = 0; i < NBLOCKS; i++)
		file.write(block, BLOCK);



	// reserve first 4 blocks for FAT;
	// write the initial root directory
	// at the fifth block.

	char	name[NAMESZ];
	int	size = 1;
	int	modes = FS_DIR;
	int	link = ROOTBLK;

	memset(name, 0, NAMESZ);		// sets name to all nulls
	memcpy(name, "/", 1);			// sets the root name to "/"

	file.seekp(ROOTBLK * BLOCK);		// sets the file pointer to the root block
	file.write(name, NAMESZ);		// writes name
	file.write((char*)&size, sizeof(int));	// writes size
	file.write((char*)&modes, sizeof(int));	// writes modes
	file.write((char*)&link, sizeof(int));	// writes link
}

