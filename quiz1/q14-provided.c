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
struct element *insertelement(struct element *, int);
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

  struct element *iter = listhead;
  while () {
  }

  return listhead;
}

/* print the list and the respective memory locations in list order */
void printlist(struct element *listhead) {
  while (listhead != NULL) {
    printf("Memory: %p contains value: %d\n", listhead, listhead->value);
    listhead = listhead->next;
  }
}
