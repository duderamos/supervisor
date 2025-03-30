#define _POSIX_SOURCE
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

void sig_handler(int);

int child_pid;

int main(void) {
  child_pid = fork();
  if (child_pid < 0) {
    perror("fork");
    exit(1);
  }

  signal(SIGINT, &sig_handler);
  signal(SIGTERM, &sig_handler);

  /* child code */
  if (child_pid == 0) {
    char *args[] = {"./service.sh", NULL};

    if (execvp(args[0], args) == -1) {
      perror("execvp failed");
    }
  }

  printf("running...\n");
  while(wait(NULL) != -1 || errno == EINTR);
  printf("parent finishing...\n");
  sleep(1);

  printf("parent finished\n");
  return 0;
}

void sig_handler(int signo) {
  int i;
  int status;

  if (signo == SIGTERM) {
    printf("\n\n%d: %d - %d\n", getpid(), child_pid, signo);
    printf("%d\n\n\n", kill(child_pid, SIGINT));
    for(i = 0; i < 10 ; i++) {
      status = kill(child_pid, 0);
      if (errno == 10) break;
      printf("%d %d %d\n\n", child_pid, i, errno);
      sleep(1);
    }

    if (i >= 10 && child_pid != status) {
      printf("\n\nService still running. Sending term %d\n\n", child_pid);
      kill(child_pid, SIGTERM);
    }
  }
}
