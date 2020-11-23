#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../log.c/src/log.h"
#include "pointnode.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdouble-promotion"

int main() {
  log_set_level(LOG_WARN);

  PointNode *head = 0x0;
  PointNode *i = NULL, *temp = NULL;
  int x, y = 0;
  float dist, totaldistance = 0;

  FILE *fd = fopen("points.txt", "r+");
  if (fd != NULL) {
    while ((fscanf(fd, "%d,%d", &x, &y)) != EOF) {
      log_debug("Read in values: %d,%d", x, y);
      if (head == NULL) {
        /* only run first time when no points have been read */
        head = palloc();
        head->next = NULL;
        head->x = x;
        head->y = y;
        i = head;
        log_trace("First node initalized as: %d,%d", i->x, i->y);
      } else {
        /* for all points EXCEPT for the first */
        log_trace("Allocating temporary node");
        temp = palloc();
        temp->next = NULL;
        temp->x = x;
        temp->y = y;
        log_trace("Set temp to: %d,%d", temp->x, temp->y);
        /* calculate distance between i and temp */
        dist = hypotf(i->x - temp->x, i->y - temp->y);
        totaldistance += dist;
        log_trace("Running total length is: %.2f", totaldistance);
        printf("%d,%d - %d,%d : %.2f\n", i->x, i->y, temp->x, temp->y, dist);
        i->next = temp;
        i = temp;
      }
    }
    printf("Total path: %.2f\n", totaldistance);
  }
}

#pragma GCC diagnostic pop
