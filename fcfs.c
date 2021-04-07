#define MAX 100

typedef struct {
    int id;
    int at;
    int bt;
} Process;

void fcfs(Process p[], int n) {
	Process temp;
	int twt = 0;
	int st[MAX] = {0}, wt[MAX] = {0}, tat[MAX] = {0};
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
	
	awt = (float)twt/3;
	printf("Average waiting time: %.2f\n", awt);
}

int main() {
	Process test1, test2, test3;
	Process test4, test5, test6, test7, test8;
	Process test9, test10, test11, test12, test13;
	
    //	0 3 1   --  fcfs - 3 processes - 1 (ignore - rr only)
    //	0 0 24  --  id - at - bt
    //	1 0 3   --  id - at - bt
    //	2 0 3   --  id - at - bt

	test1.id = 0;
	test1.at = 0;
	test1.bt = 24;
	
	test2.id = 1;
	test2.at = 0;
	test2.bt = 3;
	
	test3.id = 2;
	test3.at = 0;
	test3.bt = 3;
	
    //	0 5 2
    //	2 10 3
    //	3 1 3
    //	1 4 24
    //	4 0 2
    //	5 48 2

	test4.id = 2;
	test4.at = 10;
	test4.bt = 3;
	
	test5.id = 3;
	test5.at = 1;
	test5.bt = 3;
	
	test6.id = 1;
	test6.at = 4;
	test6.bt = 24;
	
	test7.id = 4;
	test7.at = 0;
	test7.bt = 2;
	
	test8.id = 5;
	test8.at = 48;
	test8.bt = 2;
	
    //1 2 6
    //2 5 3
    //3 1 8
    //4 0 3
    //5 4 4

	test9.id = 1;
	test9.at = 2;
	test9.bt = 6;
	
	test10.id = 2;
	test10.at = 5;
	test10.bt = 3;
	
	test11.id = 3;
	test11.at = 1;
	test11.bt = 8;
	
	test12.id = 4;
	test12.at = 0;
	test12.bt = 3;
	
	test13.id = 5;
	test13.at = 4;
	test13.bt = 4;
	
	Process oop1[3] = {test1, test2, test3};
	Process oop2[5] = {test4, test5, test6, test7, test8};
	Process oop3[5] = {test9, test10, test11, test12, test13};
	
	fcfs(oop1, 3);
//	fcfs(oop2, 5);
//	fcfs(oop3, 5);
	
	return 0;
}