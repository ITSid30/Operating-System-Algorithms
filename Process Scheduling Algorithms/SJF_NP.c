// SJF NP Algorithm
#include <stdio.h>

struct process
{
	int name;
	int arr_time;
	int ser_time;
	int priority;
	int start_time;
	int end_time;
	int tat;
	int wait_time;	
};

void input(struct process *p, int n)
{
	for(int i=0;i<n;i++)
	{
		printf("\nEnter name of process %d : ", i+1);
		scanf("%d", &p[i].name);
		printf("Enter Arrival Time of process %d : ", i+1);
		scanf("%d", &p[i].arr_time);
		printf("Enter Service Time of process %d : ", i+1);
		scanf("%d", &p[i].ser_time);
		printf("Enter Priority of process %d : ", i+1);
		scanf("%d", &p[i].priority);
	}
}

void sort(struct process *p, int n)
{
	int temp;
	for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<n-i-1;j++)
		{
			if(p[j].arr_time > p[j+1].arr_time)
			{
				temp = p[j].arr_time;
				p[j].arr_time = p[j+1].arr_time;
				p[j+1].arr_time = temp;
				temp = p[j].ser_time;
				p[j].ser_time = p[j+1].ser_time;
				p[j+1].ser_time = temp;
				temp = p[j].name;
				p[j].name = p[j+1].name;
				p[j+1].name = temp;
				temp = p[j].priority;
				p[j].priority = p[j+1].priority;
				p[j+1].priority = temp;
			}	
		}
	}
}

void print_data(struct process *p, int n)
{
	printf("\nName\t\tPriority A.T\t\tB.T\t\tS.T\t\tE.T\t\tTAT\t\tW.T");
	printf("\n------------------------------------------------------------------\n");
	for(int i=0;i<n;i++)
	{
		printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].name, p[i].priority, p[i].arr_time, p[i].ser_time, p[i].start_time, p[i].end_time, p[i].tat, p[i].wait_time);

	}
	printf("\n\n");
}

void calculation(struct process *p, int n)
{
	int t = p[0].arr_time;
	int visited[n], rem[n];
	for(int i=0;i<n;i++)
	{
		visited[i] = 0;
		rem[i] = p[i].ser_time;
	}
	int count = 0, i=0, min_index, min = 99999;
	
	while(count != n)
	{
		min = 9999;
		int c = 0;
		for(int j=0;j<n;j++)
		{
			if(p[j].arr_time <= t && !visited[j])
			{
				if(p[j].ser_time < min)
				{
					min = p[j].ser_time;
					min_index = j;
					//rem[j] = 0;
				}
				
			}
			if(rem[j] == 0 )  //&& !visited[j]
			{
				c += 1;
			}
			if(p[j].arr_time > t && c == j)
			{
				t = p[j].arr_time;
				min_index = j;
			} 
		}
		
		i = min_index;
		
		if(p[i].arr_time <= t)
		{
			p[i].start_time = t;
			t += p[i].ser_time;
			p[i].end_time = t;
			rem[i] = 0;
			visited[i] = 1;
			count++;
		}
		else if(p[i].arr_time > t)
		{
			t = p[i].arr_time;
			p[i].start_time = t;
 			t += p[i].ser_time;
			rem[i] = 0;
			p[i].end_time = t ;
			visited[i] = 1;
			count++;
		}
		i++;
	}

	float avgtat = 0, avgwt = 0;
	for(int i=0;i<n;i++)
	{
		p[i].tat = p[i].end_time - p[i].arr_time;
		p[i].wait_time = p[i].tat - p[i].ser_time;
		avgtat += p[i].tat;
		avgwt += p[i].wait_time;
	}

	printf("\n\nAverage Turn Around Time =  %f\nAverage Waiting Time = %f\n\n", avgtat/n, avgwt/n);
}


int main()
{
	int n;
	printf("Enter number of Processes : ");
	scanf("%d", &n);
	struct process p[n];
	
	input(p,n);
	sort(p,n);
	printf("\nThe Shortest Job Remaining First Algorithm is : \n");
	
	calculation(p,n);
	print_data(p,n);
	return 0;
}
