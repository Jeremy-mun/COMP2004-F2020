#include <stdio.h>
#include <stdlib.h>

/* list of nodes, each with a single integer */
struct element {
  struct element *next;
  int value;
};

/* protypes for functions defined after main */
struct element *elementalloc(void);
struct element *
listinitialize(void); /* put void in parameters to stop warning */
struct element *insertnewelement(struct element *, int); /* Named incorrectly */
void printlist(struct element *);

/** main
 * Creates an ordered list
 * Elements added to the list must be inserted maintaining the list
 * in an ordered state
 */
int main() {
  struct element *listhead = NULL;
  listhead = listinitialize();

  /* Print list before, to compare with after insertion */
  printf("--- List before insertion ---\n");
  printlist(listhead);

  /* Insert the new elements */
  for (int i = 3; i < 100; i += 11) {
    listhead = insertnewelement(listhead, i);
  }

  /* Print list after to compare with before insertion */
  printf("--- List after insertion ---\n");
  printlist(listhead);
}

/* Allocate memory for a new list element */
struct element *elementalloc(void) {
  return (struct element *)malloc(sizeof(struct element));
}

/* Simple list initialization function.  Hard coded random values. */
struct element *listinitialize() {
  const int numbers[7] = {4, 9, 13, 18, 27, 49, 60};
  struct element *newlist = NULL;
  struct element *tail = NULL;
  struct element *temp = NULL;
  for (int i = 0; i < 7; i++) {
    /* First element insertion */
    if (newlist == NULL) {
      newlist = elementalloc();
      newlist->next = NULL;
      newlist->value = numbers[i];
      tail = newlist;
    } /* Remaining element insertion */
    else {
      temp = elementalloc();
      temp->value = numbers[i];
      temp->next = NULL;
      tail->next = temp;
      tail = tail->next;
    }
  }
  return newlist;
}

/* Function to insert elements into an ordered list */
struct element *insertnewelement(struct element *listhead, int x) {

  /* Setup new element to prepare for insertion */
  struct element *newelement;
  newelement = elementalloc();
  newelement->value = x;

  struct element *iter = listhead;
  /* Now figure out where in the list the element is to be inserted */
  /* Nasty assumption that the list must have at least one element */

  /** List is not doubly linked, so keep track of the previous element and
   * search for the insertion point */
  struct element *previous = NULL;

  /** Scan the list to find the insertion point, moving previous pointer and
   * current pointer */
  while (iter && iter->value < newelement->value) {
    /* Move along the list */
    previous = iter;
    iter = iter->next;
  }

  /** Special case when inserting at head of list.  The preceeding loop did not
   * change previous pointer */
  if (previous == NULL) {
    /** Insert at start of list, listhead will change, so be sure to modify
     * newelement first */
    newelement->next = listhead; /* or NULL */
    listhead = newelement;
  } else {
    /** There is a previous, but there are 2 cases for iter
     * 1. iter = NULL, appending at end of list
     * 2. iter != NULL inserting in middle
     * For each case it is sufficient to asssign newelement->next to iter
     */
    newelement->next = iter;
    previous->next = newelement;
  }

  /** Unless inserting at head of list, the variable listhead will be unchanged.
   * This type of pass in and return is a C-ism, as C passes only by value
   */
  return listhead;
}

/* Print the list and the respective memory locations in list order */
void printlist(struct element *listhead) {
  while (listhead != NULL) {
    printf("Memory: %p contains value: %d\n", (void *)listhead,
           listhead->value);
    listhead = listhead->next;
  }
}
