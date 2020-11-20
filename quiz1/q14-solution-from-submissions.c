/** This code was replicated in many submissions, so I felt it worth including.
 * Both approaches are valid, but there is a risk with accessing an element in a
 * list by jumping through next.  That risk is no safety net.  In this trivial
 * case, certainly fine.  For more complex data structures, best to have a
 * pointer only refer to data stored in the memory pointed to.  To access the
 * "next" element the pointer should move, or another one be used. */
#include <stdio.h>
#include <stdlib.h>

/* list of nodes, each with a single integer */
struct element {
  struct element *next;
  int value;
};

/* protypes for functions defined after main */
struct element *elementalloc(void);
struct element *listinitialize(void);
struct element *insertnewelement(struct element *, int);
void printlist(struct element *);

/* main
 * Creates an ordered list
 * Elements added to the list must be inserted maintaining the list
 * in an ordered state
 */
int main() {
  struct element *listhead = NULL;
  listhead = listinitialize();
  for (int i = 3; i < 100; i += 11) {
    listhead = insertnewelement(listhead, i);
  }
  printlist(listhead);
}

/* allocate memory for a new list element */
struct element *elementalloc(void) {
  return (struct element *)malloc(sizeof(struct element));
}

/* simple list initialization function */
struct element *listinitialize() {
  const int numbers[7] = {4, 9, 13, 18, 27, 49, 60};
  struct element *newlist = NULL;
  struct element *tail = NULL;
  struct element *temp = NULL;
  for (int i = 0; i < 7; i++) {
    if (newlist == NULL) {
      newlist = elementalloc();
      newlist->next = NULL;
      newlist->value = numbers[i];
      tail = newlist;
    } else {
      temp = elementalloc();
      temp->value = numbers[i];
      temp->next = NULL;
      tail->next = temp;
      tail = tail->next;
    }
  }
  return newlist;
}

/* function to insert elements into an ordered list */
struct element *insertnewelement(struct element *listhead, int x) {
  struct element *newelement;
  newelement = elementalloc();

  newelement->value = x;

  /* does the empty list need to be considered?  Why was it considered? */
  if (listhead == NULL) {
    listhead = newelement;
    listhead->next = NULL;
    return listhead;
  }

  /* Insertion at head of list, easy to perform quickly and exit */
  if (listhead->value > x) {
    newelement->next = listhead;
    listhead = newelement;
    return listhead;
  }

  struct element *iter = listhead;

  /** There is at least one element in the list, instead of tracking the
   * previous element, look ahead in the list and move along to the insertion
   * point */
  while (iter->next != NULL && iter->next->value < x) {
    iter = iter->next;
  }

  /* Perform the insertion */
  newelement->next = iter->next;
  iter->next = newelement;

  return listhead;
}

/* print the list and the respective memory locations in list order */
void printlist(struct element *listhead) {
  while (listhead != NULL) {
    printf("Memory: %p contains value: %d\n", (void *)listhead,
           listhead->value);
    listhead = listhead->next;
  }
}
