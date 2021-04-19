typedef struct {
    int id;
    int at;
    int bt;
} Process;

void fcfs(Process p[], int n) {
	Process temp;
	int twt = 0;
	int st[n], et[n], wt[n], tat[n];
	float awt = 0;
	
	int i, j;
	
	// initialize values
	for(i = 0; i < n; i++) {
		st[i] = 0;
		et[i] = 0;
		wt[i] = 0;
		tat[i] = 0;
	}
	
	// sort by arrival time
	for(i = 0; i < n; i++){
		for(j = 0; j < size-i-1; j++){
			if(p[j].at > p[j+1].at) {
				temp = P[j];
				p[j] = P[j+1];
				p[j+1] = temp;
			}
		}
	}

	// compute for times
	st[0] = p[0].at;
	et[0] = st[0] + p[0].bt;
	tat[0] = p[0].bt - p[0].at;
	for(i = 1; i < n; i++) {
		st[i] = st[i-1] + p[i-1].bt;
		et[i] = st[i] + p[i].bt;
		wt[i] = st[i] - p[i].at;
		tat[i] = wt[i] + p[i].bt;
		if(st[i] < p[i].at) {
			st[i] = p[i].at;
			et[i] = st[i] + p[i].bt;
			wt[i] = 0;
			tat[i] = p[i].bt;
		}
		// total waiting time
		twt += wt[i];
	}
	
	// print results
	for(i = 0; i < n; i++) {
		printf("P[%d]\n", p[i].id);
		printf("Start Time: %d End Time: %d\n", st[i], et[i]);
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
