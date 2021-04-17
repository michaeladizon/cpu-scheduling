typedef struct {
    int id;
    int at;
    int bt;
} Process;

void nsjf(Process p[], int n) {
	Process temp, t[n];
	int twt = 0, tbt = 0, same = 1;;
	int st[n], et[n], wt[n], tat[n];
	float awt = 0;
	
	int i, j, k;

	// initialize values
	for(i = 0; i < n; i++) {
		st[i] = 0;
		et[i] = 0;
		wt[i] = 0;
		tat[i] = 0;
		t[i] = p[i];
	}
	
	// sort by arrival time
	for(i = 0; i < n; i++){
		for(j = 0; j < n-i-1; j++){
			if(p[j].at > p[j+1].at) {
				temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
		}

	// check if AT is the same for all
	for(i = 0; i < n; i++)
		if(t[0].at != p[i].at)
			same = 0;
	
	if(same) {
		// if same, sort by burst time
		for(i = 0; i < n; i++){
			for(j = 0; j < n-i-1; j++){
				if(p[j].bt > p[j+1].bt) {
					temp = p[j];
					p[j] = p[j+1];
					p[j+1] = temp;
				}
			}
		}
	}
	else {
		// else, sort by burst time for (arrival < burst)
		k = 1;
		for(i = 0; i < n; i++) {
			tbt += p[i].bt; // total burst time
			for(j = k; j < n; j++)
				// if process has arrived -- sort
				if(tbt >= p[j].at && p[j].bt < p[k].bt) {
					temp = p[k];
					p[k] = p[j];
					p[j] = temp;
				}
			k++;
		}
	}

	// compute for times
	et[0] = p[0].bt;
	tat[0] = p[0].bt - p[0].at;
    for(i = 1; i < n; i++) {
        st[i] = st[i-1] + p[i-1].bt;
		et[i] = st[i] + p[i].bt;
		wt[i] = p[i-1].bt + p[i-1].at + wt[i-1] - p[i].at;
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
	
    //	1 5 1   --  nsjf - 5 processes - 1 (ignore - rr only)
    //	1 2 6   --  id - at - bt
    //	2 5 2   --  id - at - bt
    //	3 1 8   --  id - at - bt
    //	4 0 3   --  id - at - bt
    //	5 4 4   --  id - at - bt

	test1.id = 1;
	test1.at = 2;
	test1.bt = 6;
	
	test2.id = 2;
	test2.at = 5;
	test2.bt = 2;
	
	test3.id = 3;
	test3.at = 1;
	test3.bt = 8;
	
	test4.id = 4;
	test4.at = 0;
	test4.bt = 3;
	
	test5.id = 5;
	test5.at = 4;
	test5.bt = 4;
	
	Process oop[5] = {test1, test2, test3, test4, test5};
	
	nsjf(oop, 5);
	
	return 0;
}