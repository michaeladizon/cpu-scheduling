#include <stdio.h>

#define MAX 400

typedef struct {
    int id;  // process ID
    int at;  // arrival time
    int bt;  // burst time
    int bursted; // boolean checker if process has fully bursted
} Process;

void print(Process p[], int st[], int et[], int wt[], int tat[], int n) {
	int i;
	for(i = 0; i < n; i++) {
		printf("P[%d]\n", p[i].id);
		printf("Start Time: %d End Time: %d\n", st[i], et[i]);
		printf("Waiting time: %d\n", wt[i]);
		printf("Turnaround time: %d\n", tat[i]);
		printf("************************************\n");
	}
}

void sort_arrival (Process P[], int size) {
	Process temp;
	int i, j;
	for(i = 0; i < size; i++){
		for(j = 0; j < size-i-1; j++){
			if(P[j].at > P[j+1].at) {
				temp = P[j];
				P[j] = P[j+1];
				P[j+1] = temp;
			}
		}
	}
}

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
	sort_arrival(p, n);

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
	print(p, st, et, wt, tat, n);
	
	awt = (float)twt/n;
	printf("Average waiting time: %.2f\n", awt);
}

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
	sort_arrival(p, n);

	// check if AT is the same for all
	for(i = 0; i < n; i++) {
		if(t[0].at != p[i].at)
			same = 0;
	}
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
	
	// print results
	print(p, st, et, wt, tat, n);
	
	awt = (float)twt/n;
	printf("Average waiting time: %.2f\n", awt);
}

//Shortest Job First Pre-Emptive
void PSJF (Process p[], int n){
	//declare variables needed for the process
	int i, j;
	int total_time = 0; //total processing time
	int wt[n], tat[n]; //waiting time, turnaround time
	int total_wait = 0; //totalwaiting time
	int bt[n]; //burst times
	int min_burst; //minimum burst time
	int start[n][n];//for storing of start times
	int end[n][n]; //for storing of end times
	int curr_time; //current time in the CPU schedule
	int current_p; //index of the current process
	int previous_p;//index of the previous process
	int pCounter[n]; //to be used for the update of index for process
	int size = 0; // size = pCounter[index]
	
	float awt = 0; //average waiting time
	
	Process temp[n];
	
	//initialization of temporary array of processes && other arrays
	for (i = 0; i < n; i++){
		temp[i] = p[i];
		wt[i] = 0;
		tat[i] = 0;
		pCounter[i] = 0;
		for(j = 0; j < n; j++){
			start[i][j] = 1000; //garbage value as temp value for the matrices
			end[i][j] = 1000;
		}
	}
	/*
	Pseudocode:
	   	- sort by arrival time (in case it is in random)
	   	- get total process time:
	      for i = 0; i < n; i++
	           total += process[i]
	    
		- at i = 0: initialize to first process arrived
	   	- start loop (maybe while or do-while) of processing each time
	      while i <= total process time: (WE START AT i = 1)
	    		- decrement burst time of current process
	    		- check for new arrivals
	    		- compare burst time
	    		- update curr_p index based on comparison (UPDATE IF x[curr_p].bt > x[next_p].bt
	    		- repeat until total burst time
	    		- IF FULLY BURST:
	    			* get wait time and turnaround time for specific process
	    			* burst time formula: wt = curr_time - bt - at
	    			* turnaround time formula: tat = burst time + wait time
	    			* print alongside with start time and end times (FURTHER BRAINSTORMING)
	*/
	// sort by arrival time
	sort_arrival(temp, n);
	for(i = 0; i < n; i++){
		//assign burst time of each process to burst time array (following ordered processes by a.t) & compute total process time / total burst time 
		bt[i] = temp[i].bt;
		total_time += bt[i];
	}
	
	//initialize to first arrived process (initiallizing = current process = previous process)
	//also add starting time to the start matrix
	previous_p = 0;
	current_p = 0;
	start[current_p][0] = 0;
	
	//follow start loop
	for(curr_time = 1; curr_time <= total_time; curr_time++){
		//if the current process has not fully burst, and arrival time is within the current ms time, we reduce the time left before full burst of the process
		if(bt[current_p] > 0 && temp[current_p].at <= curr_time){
			bt[current_p]--;
		}
		// if curr_p != previous_p, the process has changed; update end of the previous process
		if(current_p != previous_p){
			//update end time of the previous process, and increment counter for the process array
			if ( (end[previous_p][pCounter[previous_p]] == 1000) && (pCounter[previous_p] < n) && (temp[previous_p].bursted != 1) ){
				end[previous_p][pCounter[previous_p]] = curr_time - 1;
				pCounter[previous_p] += 1;
			}
			
			//now we place the start time of the current process to the start matrix
			if(start[current_p][pCounter[current_p]] == 1000){
				start[current_p][pCounter[current_p]] = curr_time - 1;
			}
		}
		
		else{
		//update the end of the current process IF it is fully bursted (in this state, use bt)
			if( (end[current_p][pCounter[current_p]] == 1000) && (pCounter[current_p] < n) && (bt[current_p] == 0) ){
				end[current_p][pCounter[current_p]] = curr_time;
				pCounter[current_p] += 1;
			}
		}
		
		//if fully burst, we print start and end time, as well as compute for the waiting time and turnaround time
		//wait time formula: wt = curr_time - bt - at
		//turnaround time formula: tat = burst time + wait time
		if(bt[current_p] <= 0 && temp[current_p].bursted != 1){
			size = pCounter[current_p];
			temp[current_p].bursted = 1;
			wt[current_p] = curr_time - temp[current_p].bt - temp[current_p].at;
			tat[current_p] = temp[current_p].bt + wt[current_p];
			total_wait += wt[current_p];
			
			printf("P[%d]\n", temp[current_p].id);
			for(i = 0; i < size; i++)
			{
				printf("Start Time: %d End Time: %d\n", start[current_p][i], end[current_p][i]);
				
			}
			printf("Waiting time: %d\n", wt[current_p]);
			printf("Turnaround time: %d\n", tat[current_p]);
			printf("************************************\n");
		}
		
		//now we update index for current process by checking newly arrived processes and comparing their burst times
		previous_p = current_p; //for splits
		min_burst = 12345; //garbage value
		for (i = 0; i < n; i++){
			//if arrival time is within the current ms time, it means the process has arrived/just arrived, and is part of comparison
			if(temp[i].at <= curr_time && temp[i].bursted != 1){
				//if minimum burst is garbage value, we set a new minimum burst based from previous process
				if(min_burst == 12345){
					min_burst = bt[i];
					current_p = i;
				}
				//else, we compare burst times of the two processes
				else if (min_burst != bt[i] && min_burst > bt[i]){
					min_burst = bt[i];
					current_p = i;
				}
			}
		}
	}
	
	awt = (float)total_wait/n;
	printf("Average waiting time: %.2f\n", awt);
	
}

int main() {
	FILE *fp;
	
	int i = 0, arr[MAX], num;
	char filename[25];
	Process p[100];
	
	printf("Filename: ");
	scanf("%s", &filename);
	fp = fopen(filename, "r");
	
	while((fscanf(fp, "%d", &num)) != EOF) {
		arr[i] = num;
		i++;
	}
	
	fclose(fp);
	
	int n = i, j = 0, algo, nProcesses, tSlice;
	
	// assign algorithm, number of processes, and time slice value from input
	algo = arr[0];
	nProcesses = arr[1];
	tSlice = arr[2];
	
	// store inputs in a Process array
	for(i = 3; i < n; i+=3) {
		p[j].id = arr[i];
		p[j].at = arr[i+1];
		p[j].bt = arr[i+2];
		j++;
	}
	
	switch(algo) {
		case 0:
			fcfs(p, nProcesses);
			break;
		case 1:
			nsjf(p, nProcesses);
			break;
		case 2:
			PSJF(p, nProcesses);
			break;
//		case 3:
//			rr();
//			break;
	}
		
	return 0;
}
