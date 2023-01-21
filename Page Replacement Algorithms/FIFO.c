#include <stdio.h>

// 1. FIFO Algorithm

int main(void) {
  int n, p;
  printf("Enter no of Frames : ");
  scanf("%d", &n);
  printf("Enter no of Pages as a string : ");
  scanf("%d", &p);
  int frame[n], fi[n], page[p];
  for (int i = 0; i < n; i++) {
    fi[i] = 0;
    frame[i] = -1;
  }
  printf("Enter the pages string : ");
  for (int i = 0; i < p; i++)
    scanf("%d", &page[i]);
  // for(int i=0;i<n;i++)
  //  printf("%d ", frame[i]);
  // printf("\n");
  int pf = 0, k = 0, flag = 0;
  printf("\n\nThe FIFO Page Replacement Algorithm is : \n");
  for (int i = 0; i < p; i++) {
    flag = 0;
    for (int j = 0; j < n; j++) {
      if (frame[j] == page[i]) {
        flag = 1;
      }
    }
    if (flag == 1) {
      for (int j = 0; j < n; j++) {
        if (frame[j] == -1)
          printf("- ");
        else
          printf("%d ", frame[j]);
      }
      printf("\n");
      continue;
    }
    if (fi[k] == 0) {
      frame[k] = page[i];
      fi[k] = 1;
      pf++;
    } else {
      // flag = 0;

      // if(flag != 1)
      //{
      frame[k] = page[i];
      pf++;
      //}
    }
    for (int j = 0; j < n; j++) {
      if (frame[j] == -1)
        printf("- ");
      else
        printf("%d ", frame[j]);
    }
    // printf("%d %d %d", frame[0], frame[1], frame[2]);
    printf("\n");
    k++;
    k %= n;
  }
  printf("\nNo. of Page Faults = %d\n", pf);
  
  return 0;
  }
