# Creating and Destroying Multiple Processes

```c++
// Most code from https://www.geeksforgeeks.org/creating-multiple-process-using-fork/
#include <sys/types.h> // For pid_t object
#include <signal.h> // For SIGINT, kill(), and raise().
#include <stdio.h> // Does the actual forking

void parentKillHandle() {
	kill(n1, SIGINT); // Kill the children
	kill(n2, SIGINT);
}

int main()
{
	// Creating first child
	pid_t n1 = fork(); // int type works too!

	// Creating second child. First child
	// also executes this line and creates
	// grandchild.
	pid_t n2 = fork();

	if (n1 > 0 && n2 > 0) {
		atexit(parentKillHandle); // When parent ends, parentKillHandle will end child processes.
		printf("parent\n");
		printf("%d %d \n", n1, n2);
		printf(" my id is %d \n", getpid());

		// code
		
		raise(SIGINT); // Kill self
		// Program won't get here
	}
	else if (n1 == 0 && n2 > 0)
	{
		printf("First child\n");
		printf("%d %d \n", n1, n2);
		printf("my id is %d \n", getpid());
	}
	else if (n1 > 0 && n2 == 0)
	{
		printf("Second child\n");
		printf("%d %d \n", n1, n2);
		printf("my id is %d \n", getpid());
	}
	else {
		printf("third child\n");
		printf("%d %d \n", n1, n2);
		printf(" my id is %d \n", getpid());
	}
	return 0;
}
```
