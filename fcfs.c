#define MAX 100

typedef struct {
    int id;
    int at;
    int bt;
} Process;

void fcfs(Process p[], int n) {
	Process temp;
	int twt = 0;
	int wt[MAX] = {0}, tat[MAX] = {0};
	float awt = 0;
	
	int i, j;
	
	// sort by arrival time
	for(i = 0; i < n; i++)
		for(j = 0; j < n-i-1; j++)
			if(p[j].at > p[j+1].at) {
				temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
			
	// compute for waiting time
	for(i = 0; i < n; i++)
		wt[i] = wt[i-1] + p[i-1].bt;
	
	// compute for turnaround time
	for(i = 0; i < n; i++)
		tat[i] = wt[i] + p[i].bt;
	
	for(i = 0; i < n; i++) {
		// total waiting time
		twt += wt[i];
		
		printf("P[%d]\n", p[i].id);
		printf("Start Time: %d End Time: %d\n", tat[i-1], tat[i]);
		printf("Waiting time: %d\n", wt[i]);
		printf("Turnaround time: %d\n", tat[i]);
		printf("************************************\n");
	}
	
	awt = (float)twt/n;
	printf("Average waiting time: %.2f\n", awt);
}

int main() {
	Process test1, test2, test3, test4, test5;
	
    //	0 5 1   --  fcfs - 5 processes - 1 (ignore - rr only)
    //	2 10 3  --  id - at - bt
    //	3 1 3   --  id - at - bt
    //	1 4 24  --  id - at - bt
    //	4 0 2   --  id - at - bt
    //	5 48 2  --  id - at - bt

	test1.id = 2;
	test1.at = 10;
	test1.bt = 3;
	
	test2.id = 3;
	test2.at = 1;
	test2.bt = 3;
	
	test3.id = 1;
	test3.at = 4;
	test3.bt = 24;
	
	test4.id = 4;
	test4.at = 0;
	test4.bt = 2;
	
	test5.id = 5;
	test5.at = 48;
	test5.bt = 2;
	
	Process oop[5] = {test1, test2, test3, test4, test5};
	
	fcfs(oop, 5);
	
	return 0;
}