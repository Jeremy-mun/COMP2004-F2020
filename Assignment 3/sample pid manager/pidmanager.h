#ifndef PIDMANAGER
#define PIDMANAGER

#define MINPID 300
#define MAXPID 5000

typedef struct pid_type {
  int pidnum;
  /* process control block */
  struct pid_type *nextpid;
} pid_type;

/* One global list */
static pid_type *pidlist;

/* prototypes for functions defined in the .c file */
int allocate_map(void);
int allocate_pid(void);
void release_pid(int pid);
void print_pids(void);

#endif
