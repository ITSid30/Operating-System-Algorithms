#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void sort1(int *a, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (a[j] > a[j + 1]) {
        int temp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = temp;
      }
    }
  }
}

void sort2(int *a, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (a[j] < a[j + 1]) {
        int temp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = temp;
      }
    }
  }
}

int main() {
  int n;
  printf("Enter size of array : ");
  scanf("%d", &n);
  int a[n];
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  printf("\n");
  int p = fork();
  if (p > 0) {
    sort1(a, n);
    for (int i = 0; i < n; i++) {
      printf("%d , PID = %d, PPID = %d\n", a[i], getpid(), getppid());
      sleep(1);
    }
    sleep(50);
    // wait(&p);
    printf("\n\nThe Parent Process Terminated !!\n");
  } else if (p == 0) {
    sort2(a, n);
    for (int i = 0; i < n; i++) {
      printf("\t\t%d , PID = %d, PPID = %d\n", a[i], getpid(), getppid());
      sleep(3);
    }
    printf("\n\n\t\tThe Child Process Terminated !!\n");
  }
}
