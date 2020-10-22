/**
 * Example program demonstrating UNIX pipes.
 *
 * Figures 3.21 & 3.22
 *
 * @author Silberschatz, Galvin, and Gagne
 * Operating System Concepts  - Tenth Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void) {
  char write_msg[BUFFER_SIZE] = "Greetings";
  char read_msg[BUFFER_SIZE];
  pid_t pid;

  /* Each pipe has a read and write end.  The defines above are a good
   * way to use mnemonics instead of remembering which end is for
   * reading and which for writing
   */
  int fd[2];

  /* create the pipe */
  /* Because fd is an array, using the variable without an index passes the
   * value of the memory address, in other words, the pointer.  Pipe takes
   * a pointer as an argument so the types match.
   * This call shows a common C-ism.  Pass pointers and return an int error
   * code
   */
  if (pipe(fd) == -1) {
    fprintf(stderr, "Pipe failed");
    return 1;
  }

  /* now fork a child process */
  pid = fork();

  /* Both processes now start running from here
   * Both processes will check for a correct PID
   */
  if (pid < 0) {
    fprintf(stderr, "Fork failed");
    return 1;
  }

  /********************************************************/
  if (pid > 0) { /* parent process */
    /* close the unused end of the pipe */
    close(fd[READ_END]);

    /* write to the pipe */
    fprintf(stderr, "Parent writing to pipe\n");
    write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);

    /* close the write end of the pipe */
    close(fd[WRITE_END]);
  }

  /********************************************************/
  else { /* child process */
    /* close the unused end of the pipe */
    close(fd[WRITE_END]);

    /* read from the pipe */
    fprintf(stderr, "Child reading from pipe\n");
    read(fd[READ_END], read_msg, BUFFER_SIZE);
    printf("child read %s\n", read_msg);

    /* close the write end of the pipe */
    close(fd[READ_END]);
  }
  /********************************************************/

  return 0;
}
