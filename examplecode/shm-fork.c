/**
 * Simple program demonstrating shared memory in POSIX systems.
 *
 * This is the producer process that writes to the shared memory region.
 *
 * Figure 3.16
 *
 * To compile, enter
 * 	gcc shm-posix-producer.c -lrt
 *
 * @author Silberschatz, Galvin, and Gagne
 * Operating System Concepts  - Tenth Edition
 * Copyright John Wiley & Sons - 2018
 */

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpointer-arith"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void producer(void);
void consumer(void);

int main() {
  pid_t pid;
  pid = fork();
  if( pid < 0){
    fprintf(stderr, "Fork failed\n");
    return 1;
  }
  if( pid > 0)
    producer();
  else
    consumer();

  return 0;
}

void producer() {
  const int SIZE = 4096;
  const char *name = "OS";
  const char *message0 = "Studying ";
  const char *message1 = "Operating Systems ";
  const char *message2 = "Is Fun!\n";

  int shm_fd;
  void *ptr;

  /* create the shared memory segment */
  shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  /* octal  u    g    o
   *        rwx  rwx  rwx
   *        110  110  110
   */

  /* configure the size of the shared memory segment */
  ftruncate(shm_fd, SIZE);

  /* now map the shared memory segment in the address space of the process */
  ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (ptr == MAP_FAILED) {
    printf("Map failed\n");
    /* a void function should not return anything */
    return ;
  }
  /**
   * Now write to the shared memory region.
   *
   * Note we must increment the value of ptr after each write.
   */

  sprintf(ptr, "%s", message0);
  ptr += strlen(message0);
  sprintf(ptr, "%s", message1);
  ptr += strlen(message1);
  sprintf(ptr, "%s", message2);
  ptr += strlen(message2);
}

void consumer() {
  const char *name = "OS";
  const int SIZE = 4096;

  int shm_fd;
  void *ptr;
  /* int i; */

  /* open the shared memory segment */
  shm_fd = shm_open(name, O_RDONLY, 0666);
  if (shm_fd == -1) {
    printf("shared memory failed\n");
    exit(-1);
  }

  /* now map the shared memory segment in the address space of the process */
  ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
  if (ptr == MAP_FAILED) {
    printf("Map failed\n");
    exit(-1);
  }

  /* now read from the shared memory region */
  printf("%s", (char *)ptr);

  /* remove the shared memory segment */
  if (shm_unlink(name) == -1) {
    printf("Error removing %s\n", name);
    exit(-1);
  }
}

#pragma clang diagnostic pop
