# Get_next_line
#💾/42/Core_Curriculum/Get_next_line

# General concepts of the project
- The goal is to program a function that reads from the file and returns a new line. (\n)
- When you call the function again on the same file, it grabs the next line. 
- A (-1) is returned if an error occurred. 
- A (0) is returned if the file is finished reading.
- And a (1) is returned if a line is read.

# File descritpors (fd)
To manipulate a file in C, we must first inform the operating system of our intentions with the open function of the fcntl.h library. In this system call, we need to specify the path towards the file we’d like to open, as well as the way in which we want to access it with flags, like this:
```c
open("file.txt", O_RDONLY); // read only
open("file.txt", O_WRONLY); // write only
open("file.txt", O_RDWR);   // read write
```
The system ensures that the file does exist and that we have the correct permissions to open it. If all goes well, the system sends a small non-negative integer called a file descriptor (or fd, for short). From now on, we will only use this file descriptor to refer to the file, instead of its name.

Note: file descriptors 0, 1, and 2 are reserved for the standard input, the standard output, and the standard error output respectively. Our file might be assigned a number 3 or higher. That will depend on how many files the operating system already has opened.

If there is any issue, for exemple if we ask to open a file that doesn’t exist, or a file we don’t have the permission to open, the function will return -1.

Finally, when we are done manipulating a file, we must de-reference the file descriptor with the `close()` function of the `<unistd.h>` library.

```c
#include <fcntl.h>
#include <unistd.h>

int	main(void)
{
	int	fd;

//	We open the file and assign the returned file descriptor
//	to the fd variable in order to use it later:
	fd = open("fichier.txt", O_RDONLY);
//	Then we make sure the file was correctly opened:
	if (fd == -1)
		return (-1);
//	...
//	And we close the file with the reference to its fd:
	close(fd);
	return (0);
}
```

The get_next_line function won’t have to open or close any file, though. It only has to worry about reading from a file descriptor it receives as a parameter. For that, it will use the read function in order to… well, read the contents of a file.

# Reading a file
The [[unistd.h#read]] function, from the [[unistd.h]] library, loads the contents of a file into memory, in part or in full, using its file descriptor.
* the file descriptor. This is the fd we receive as a parameter in the get_next_line function,
* a buffer, a pointer towards a memory area where we can temporarily store the characters we read,
* a size in bytes to read, in other words, the number of characters to read. In this project, it will be our BUFFER_SIZE, which will only be defined at compilation time.

The read function also returns the number of characters that it has read, or -1 in case of error.

# The BUFFER_SIZE
In get_next_line, we can’t just read characters one by one until we hit a `\n`. We are forced to read a certain number of characters at once, determined by a BUFFER_SIZE that we don’t know in advance. For instance, a file with the following text has 34 total characters:
```
1 = one
2 = two
3 = three
4 = four
```

If we have a BUFFER_SIZE of 1, we will have to call the read function 35 times to read the entire text. In this case, we can relatively easily stop at the 8th call, when we hit a \n and return the first line. Then read will be at the correct position if we call get_next_line a second time to get the second line.

However, if our BUFFER_SIZE is 100, we will read the entire text with a single call to the read function. In that case, all we have to do is get the characters before the \n from the buffer and return that, right?

Yes, but that won’t be enough: what is going to happen when we call get_next_line again to get the second line of our text? Nothing. The read function will be at the end of the file with nothing left to read. And the rest of the characters in the buffer will have disappeared…

# Static Variables in C
At each function call, the static variable x never loses its value.
Indeed, regular local variables (like our buffer) are very short-lived. The minute the function in which they were declared ends, they are de-referenced from the stack and slip out of memory.

A static variable doesn’t lose its memory that easily. Its data persists until the end of the program, whether or not the function in which it was declared ends. In this project, a static variable is necessary to store the extra characters, read after a \n. That way, when we call get_next_line again to get the next line, those characters are not lost.

# Laying Out the gnl Code
Now that we have a firm grip on the concepts, it is time to organize our code. There are of course as many ways to code get_next_line as there are programmers, what follows is only one method out of many!

# A Function to Read From the File Descriptor
This function will read from the file descriptor in a loop until we detect a \n or the end of the file:
* create a reading loop that stops when the read function returns 0, which means we are at the end of the file and there is nothing left to read,
	* read from the file descriptor,
	* if read returns -1, there was an error, free all allocated memory and stop everything,
	* save the read characters in a static variable (strjoin the buffer to the static),
	* check to see if there is a \n in the static variable: if yes, stop the loop, if no, continue.

# A Function to Get the Line to Return
If this function is called, it means we know for a fact that there is a \n in the static variable (or that there is nothing left to read in the file). We will extract the characters up to the \n to get the line we must later return:
