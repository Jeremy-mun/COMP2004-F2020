#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
  pid_t pid;
  /* fork a child process */
  pid = fork();

  if (pid < 0) { /* error occurred */
    fprintf(stderr, "Fork Failed");
    return 1;

  } else if (pid == 0) { /* child process */
    execlp("ls", "ls", "-l", (char *)0 );

  } else { /* parent process */
    /* parent will wait for the child to complete */
    wait(NULL);
    printf("Child Complete\n");
  }

  return 0;
}
