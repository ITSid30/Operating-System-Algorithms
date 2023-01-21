 /*Name : Siddhesh Bajad
  Assignment 3 : Job scheduling algorithms. 
  1. FCFS AND 2. Round Robin   */

#include <stdio.h>

struct process {
  int name;
  int priority;
  int arr_time;
  int ser_time;
  int start_time;
  int end_time;
  int tat;
  int wait_time;
};

void input(struct process *p, int n) {
  int i = 0;
  printf("%d", n);
  for (i = 0; i < n; i++) {
    printf("\nEnter name of Process %d : ", i + 1);
    scanf("%d", &p[i].name);
    printf("Enter Arrival Time of Process %d : ", i + 1);
    scanf("%d", &p[i].arr_time);
    printf("Enter Service Time of Process %d : ", i + 1);
    scanf("%d", &p[i].ser_time);
    printf("Enter Proirity of Process %d : ", i + 1);
    scanf("%d", &p[i].priority);
  }
}

float *calculation(struct process *p, int n) {
  int st = p[0].arr_time, et = 0;
  for (int i = 0; i < n; i++) {
    if (p[i].arr_time > p[i - 1].end_time) {
      st += p[i].arr_time - p[i - 1].end_time;
    }
    p[i].start_time = st + et;
    p[i].end_time = st + et + p[i].ser_time;
    et = p[i].end_time - st;
    // st = p[i].end_time;
    p[i].tat = p[i].end_time - p[i].arr_time;
    p[i].wait_time = p[i].tat - p[i].ser_time;
  }

  int i, j, tatsum = 0, wtsum = 0;
  for (i = 0; i < n; i++) {
    tatsum += p[i].tat;
    wtsum += p[i].wait_time;
  }

  float avgtat = (float)tatsum / n;
  float avgwt = (float)wtsum / n;

  printf("\n\n\tAverage Turn Around Time = %f\n\tAverage Waiting Time = %f\n",
         avgtat, avgwt);
}

void print_data(struct process *p, int n) {
  printf("\nProcess\tPriority\tArr_Time\tSer_Time\tStart_Time\tEnd_"
         "Time\tTAT\tWait_T\n");
  for (int i = 0; i < n; i++) {
    printf("%d  \t\t%d \t\t%d \t\t%d \t\t%d \t\t%d \t\t%d \t\t%d\n", p[i].name,
           p[i].priority, p[i].arr_time, p[i].ser_time, p[i].start_time,
           p[i].end_time, p[i].tat, p[i].wait_time);
  }
}

void sort(struct process *p, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (p[j].arr_time > p[j + 1].arr_time) {
        int temp = p[j].arr_time;
        p[j].arr_time = p[j + 1].arr_time;
        p[j + 1].arr_time = temp;
        temp = p[j].name;
        p[j].name = p[j + 1].name;
        p[j + 1].name = temp;
        temp = p[j].ser_time;
        p[j].ser_time = p[j + 1].ser_time;
        p[j + 1].ser_time = temp;
        temp = p[j].priority;
        p[j].priority = p[j + 1].priority;
        p[j + 1].priority = temp;
      }
    }
  }
}

void round_robin(struct process *p, int n)
{
  int time_quantum;
  printf("\nEnter the Time quantum of Processor : ");
  scanf("%d", &time_quantum);

  sort(p,n);
  int rem[n], visited[n], str[n];
  for(int i=0;i<n;i++)
    {
      rem[i] = p[i].ser_time;
    }
  for(int i=0;i<n;i++)
    {
      visited[i] = 0;
    }
  for(int i=0;i<n;i++)
    {
      str[i] = 0;
    }
  int t=p[0].arr_time, i=0, count = 0, k=0;
  while(count != n) 
    {
      int c = 0;
      for(int j=0;j<n;j++)
        {
          if(rem[j] == 0 )
          {
            c++;
            continue;
          }
          if(p[j].arr_time <= t && !str[j])
          {
            str[j] = 1;
            i = j;
            break;
          }
          if(p[j].arr_time > t && c == j )
          {
            k = j;
            t = p[k].arr_time;
            i = k;
            break;
          }
        } 
      
      if(p[i].arr_time <= t && !visited[i])
      {
        if(p[i].ser_time == rem[i])
        {
          p[i].start_time = t;
        }
        if(rem[i] != 0 && !visited[i])
        {
          if(rem[i] <= time_quantum)
          {
            t += rem[i];
            rem[i] = 0;
            p[i].end_time = t;
            p[i].tat = p[i].end_time - p[i].arr_time;
            p[i].wait_time = p[i].tat - p[i].ser_time;
            visited[i] = 1;
            count++;
          }
          else{
            t += time_quantum;
            rem[i] -= time_quantum;
          }
        }
      }
      else if(p[i].arr_time > t && !visited[i])
      {
        i = -1;
      }

      i++;
      i %= n;
    }

  float avgtat = 0, avgwt = 0;
  for (int i = 0; i < n; i++) 
  {
    avgtat += p[i].tat;
    avgwt += p[i].wait_time;
  }
  printf("\n\n\tAverage Turn Around Time = %f\n\tAverage Waiting Time = %f\n",
         avgtat/n, avgwt/n);
}  

int main() {
  int ch, n;
  printf("Enter number of processes : ");
  scanf("%d", &n);
  struct process p[n];
  input(p, n);
  sort(p, n);
  printf("\nThe FCFS Algorithm solution is : \n");
  calculation(p, n);
  print_data(p, n);
  printf("--------------------------------------------------------------------\n");
  printf("\n\nThe Round Robin Algorithm solution is : \n");
  round_robin(p, n);
  print_data(p, n);
  printf("--------------------------------------------------------------------\n");

  // printf("\n\nThe Priority Preemptive Algorithm solution is : \n");
  // priority_preemptive(p, n);
  // print_data(p, n);
  // printf("--------------------------------------------------------------------\n");
  return 0;
}
