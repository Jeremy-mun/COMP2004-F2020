#include "pidmanager.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* As an alternative to stdbool.h simple macros and a typedef can be used */
// #define FALSE 0
// #define TRUE 1
// typedef int bool;

// typedef struct pid_type {
//   int pidnum;
//   /* process control block */
//   struct pid_type *nextpid;
// } pid_type;

/* One global list, defined in the header file */
/* static pid_type *pidlist; */

int allocate_map(void) {
  pidlist = NULL;
  if (pidlist != NULL)
    return -1;
  else
    return 1;
}

int allocate_pid(void) {
  /* Memory allocation for the new pid to be inserted */
  pid_type *temp;
  temp = (pid_type *)malloc(sizeof(pid_type));

  /* Special case: First pid item */
  if (pidlist == NULL) {
    temp->pidnum = MINPID;
    /* circular list: Single item points to itself */
    temp->nextpid = temp;
    pidlist = temp;
    return temp->pidnum;

    /* Special case: Single pid item */
  } else if (pidlist == pidlist->nextpid) {
    /* not much different than a mult-item list, but do not need to do
    any searching.  There is a flaw ... What is the flaw? */
    temp->pidnum = (pidlist->pidnum + 1);
    temp->nextpid = pidlist->nextpid;
    pidlist->nextpid = temp;
    pidlist = temp;
    return temp->pidnum;

    /* Generic case: Multiple pids in the list, find the next available pid */
  } else {
    pid_type *pidfinder = pidlist;
    bool found = false, wrapped = false;
    while (!found && !wrapped) {
      if ((*pidfinder).pidnum < MAXPID &&
          ((pidfinder->nextpid->pidnum > pidfinder->pidnum + 1) ||
           (pidfinder->nextpid->pidnum < pidfinder->pidnum))) {
        /* Found a hole in the pidlist, insert here */
        temp->pidnum = pidfinder->pidnum + 1;
        temp->nextpid = pidfinder->nextpid;
        pidfinder->nextpid = temp;
        pidlist = temp;
        found = true;
      } else if (pidfinder->pidnum == MAXPID &&
                 pidfinder->nextpid->pidnum != MINPID) {
        /** Reached end of pidlist (maximum value), and lowest number is
         * available */
        temp->pidnum = MINPID;
        temp->nextpid = pidfinder->nextpid;
        pidfinder->nextpid = temp;
        pidlist = temp;
        found = true;

      } else {
        /** Move pidfinder along the list. PID number will not matter as the
         * list is circular. */
        pidfinder = pidfinder->nextpid;
        if (pidfinder == pidlist)
          /* If we return to the starting node, then there are no free pids */
          wrapped = true;
      }
    }
    if (!found && wrapped)
      return -1;
    else
      return temp->pidnum;
  }
}

void release_pid(int delpid) {
  pid_type *pidfinder = pidlist;
  pid_type *pidprev; /* how to get the previous element in list? */
  pid_type *temppid = NULL;

  if (pidlist == NULL) {
    /* No PIDS */
    return;

  } else if (pidlist == pidlist->nextpid) {
    /* One PID */
    if (pidfinder->pidnum == delpid) {
      /* Only delete PID if it matches requested PID */
      temppid = pidlist;
      pidlist = NULL;
      free(temppid);
      return;
    } else {
      /* not the PID you're looking for */
      return;
    }

  } else {
    /* List contains more than one PID */
    if (pidfinder->pidnum == delpid) {
      /* Special case for head of list deletion */

      /* quickly loop around to find the prev list element */
      pidprev = pidfinder->nextpid;
      while (pidprev->nextpid != pidfinder)
        pidprev = pidprev->nextpid;

      /* perform the deletion */
      temppid = pidfinder;
      pidprev->nextpid = pidfinder->nextpid;
      pidlist = pidfinder->nextpid;
      free(temppid);
      return;

    } else {
      /* Find and delete */
      pidprev = pidfinder;
      pidfinder = pidfinder->nextpid;
      bool found = false;
      while (!found && pidfinder != pidlist) {
        if (pidfinder->pidnum == delpid) {
          /* Eureka we found the PID in the list */
          temppid = pidfinder;
          pidprev->nextpid = pidfinder->nextpid;
          free(temppid);
          found = true;
        } else {
          /* We didn't find it, move along */
          pidprev = pidfinder;
          pidfinder = pidfinder->nextpid;
        }
      }
      return;
    }
  }
  /** Could eliminate all the return statements and put one here. Would this be
   * a good idea or not? Explain. */
}

/** Utility function that will print the global PID list.  For each item in
 * the list the following are printed:
 * - the address of list item
 * - data (PID number)
 * - address of next pointer */
void print_pids(void) {
  /** Simple utility function to print the pointer addresses, and the contents
   * of each item in the PID list */
  if (pidlist == NULL) {
    printf("NO PIDs\n");
    return;
  }
  pid_type *i = pidlist;
  bool wrapped = false;
  printf("---\n");
  while (!wrapped) {
    printf("Address: %p\tContents: pidnum: %d\tnextpid: %p\n", (void *)i,
           i->pidnum, (void *)(*i).nextpid);
    /**
     * ! Note the use of a different way access data in a struct referenced in a
     * pointer This is equivalent to: i = i->nextpid;
     */
    i = (*i).nextpid;
    if (i == pidlist)
      wrapped = true;
  }
  printf("---\n");
}
