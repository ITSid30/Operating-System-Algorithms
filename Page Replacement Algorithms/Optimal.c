#include <stdio.h>

int main() {
  int no_frames, page_len;
  printf("Enter no of page frames : ");
  scanf("%d", &no_frames);
  printf("Enter length of page string : ");
  scanf("%d", &page_len);

  int frame[no_frames], page[page_len], fi[no_frames];

  for (int i = 0; i < no_frames; i++) {
    frame[i] = -1;
    fi[i] = 0;
  }
  printf("Enter the Page string : ");
  for (int i = 0; i < page_len; i++) {
    scanf("%d", &page[i]);
  }

  int f = 0, pf = 0, k = 0;
  int future[no_frames];
  for (int i = 0; i < page_len; i++) {
    f = 0;
    for (int j = 0; j < no_frames; j++) {
      if (frame[j] == page[i]) {
        f = 1;
      }
    }

    if (f == 1) {
      for (int i = 0; i < no_frames; i++) {
        if (frame[i] == -1)
          printf("- ");
        else
          printf("%d ", frame[i]);
      }
      printf("\n");
      continue;
    }
    if (fi[k] == 0) {
      frame[k] = page[i];
      fi[k] = 1;
      pf++;
      k++;
      k %= no_frames;
      for (int i = 0; i < no_frames; i++) {
        if (frame[i] == -1)
          printf("- ");
        else
          printf("%d ", frame[i]);
      }
      printf("\n");
      continue;
    } else {
      for (int i = 0; i < no_frames; i++)
        future[i] = 0;
      int max = 0;
      for (int l = 0; l < no_frames; l++) {
        for (int j = i + 1; j < page_len; j++) {
          if (frame[l] == page[j]) {
            future[l] = j;
            break;
          }
        }
        if (future[l] == 0)
          future[l] = 9999;
      }
      int index = 0;
      for (int k = 0; k < no_frames; k++) {
        if (max < future[k]) {
          max = future[k];
          index = k;
        }
      }
      k = index;
      frame[k] = page[i];
      pf++;

      for (int i = 0; i < no_frames; i++) {
        if (frame[i] == -1)
          printf("- ");
        else
          printf("%d ", frame[i]);
      }
      printf("\n");
    }
  }

  printf("\n\nNo of Page Faults are : %d\n\n", pf);
}
