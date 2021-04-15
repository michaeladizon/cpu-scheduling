//Pre-emptive Shortest Job First

#define MAX 100

typedef struct {
    int id;  //process ID
    int at;  //arrival Time
    int bt;  //Burst Time
    int bursted; //boolean checker if process has fully bursted
} Process;

void sort_arrival (Process P[], int size){
	Process temp;
	int i, j;
	for(i = 0; i < size; i++)
		for(j = 0; j < size-i-1; j++)
			if(P[j].at > P[j+1].at) {
				temp = P[j];
				P[j] = P[j+1];
				P[j+1] = temp;
			}
}

//Shortest Job First Pre-Emptive
void PSJF (Process p[], int n){
	//declare variables needed for the process
//	char print_results[n][10][255]; //storage for printing of result
	
	int i;
	int total_time = 0; //total processing time
	int wt[n], tat[n]; //waiting time, turnaround time
	int total_wait = 0; //totalwaiting time
	int bt[n]; //burst times
	int min_burst; //minimum burst time
	int starts[n], ends[n]; //start and end times (NOTE: THIS IS JUST TEMPORARY FOR NOW)
	int curr_time;
	int current_p;
	int previous_p;
	
	float awt = 0; //average waiting time
	
	Process temp[n];
	
	//initialization of temporary array of processes && other arrays
	for (i = 0; i < n; i++){
		temp[i] = p[i];
		wt[i] = 0;
		tat[i] = 0;
		starts[i] = 1000; //garbage
		ends[i] = 1000; //garbage
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
	
//	printf("before sort: \n");
//	for (i = 0; i < n; i++){
//		printf("process %d at burst time %d, arrival time: %d \n", temp[i].id, temp[i].bt, temp[i].at);
//	}
	// sort by arrival time
	sort_arrival(temp, n);
/*	
	printf("\nafter sort: \n");
	for(i = 0; i < n; i++)
		printf("process %d at burst time %d, arrival time: %d \n", temp[i].id, temp[i].bt, temp[i].at);

	printf("\n\n");
*/	
	for(i = 0; i < n; i++){
		//assign burst time of each process to burst time array (following ordered processes by a.t) & compute total process time / total burst time 
		bt[i] = temp[i].bt;
		total_time += bt[i];
	}
	
	//initialize to first arrived process (initiallizing = current process = previous process)
	previous_p = 0;
	current_p = 0;
	starts[current_p] = 0;
	
	//follow start loop
	for(curr_time = 1; curr_time <= total_time; curr_time++){
//		printf("curr_time = %d\n", curr_time);
//		printf("current_p = %d\t\t previous_p = %d\n", current_p, previous_p);
		//if the current process has not fully burst, and arrival time is within the current ms time, we reduce the time left before full burst of the process
		if(bt[current_p] > 0 && temp[current_p].at <= curr_time){
//			printf("%d > 0 && %d <= %d\n", bt[current_p], temp[current_p].at, curr_time);
//			printf("reducing burst time for process %d...\n", temp[current_p].id);
//			printf("%d -> ", bt[current_p]);
			bt[current_p]--;
//			printf("%d\n", bt[current_p]);
		}
		
		//if index of current process is not equal with the index of the previous process, indicate the split by the start and end time (use char matrix later on)
//		if(current_p != previous_p){
//			
//		}
		
		//if fully burst, we print start and end time, as well as compute for the waiting time and turnaround time
		//wait time formula: wt = curr_time - bt - at
		//turnaround time formula: tat = burst time + wait time
		if(bt[current_p] <= 0 && temp[current_p].bursted != 1){
//			printf("finished burst...\n");
//			printf("%d <= 0\n\n", bt[current_p]);
			temp[current_p].bursted = 1;
			ends[current_p] = curr_time;
			wt[current_p] = curr_time - temp[current_p].bt - temp[current_p].at;
			tat[current_p] = temp[current_p].bt + wt[current_p];
			total_wait += wt[current_p];
			
			printf("P[%d]\n", temp[current_p].id);
			printf("Start Time: %d End Time: %d\n", starts[current_p], ends[current_p]);
			printf("Waiting time: %d\n", wt[current_p]);
			printf("Turnaround time: %d\n", tat[current_p]);
			printf("************************************\n");
		}
		
		//now we update index for current process by checking newly arrived processes and comparing their burst times
		previous_p = current_p; //for splits
		min_burst = 12345; //garbage value
		for (i = 0; i < n; i++){
//			printf("min burst: %d\n", min_burst);
//			printf("bt[%d]: %d\n", i, bt[i]);
			//if arrival time is within the current ms time, it means the process has arrived/just arrived, and is part of comparison
			if(temp[i].at <= curr_time && temp[i].bursted != 1){
//				printf("%d <= %d\n", temp[i].at, curr_time);
				//if minimum burst is garbage value, we set a new minimum burst based from previous process
				if(min_burst == 12345){
//					printf("garbage; setting min burst...\n");
					min_burst = bt[i];
					current_p = i;
				}
				//else, we compare burst times of the two processes
				else if (min_burst != bt[i] && min_burst > bt[i]){
//					printf("%d != %d && %d > %d\n", min_burst, bt[i], min_burst, bt[i]);
					min_burst = bt[i];
					current_p = i;
					
					if(i == 0 && starts[i] == 1000){
						starts[i] = curr_time;
					}
					
					else if(starts[i] == 1000 && i == current_p){
						starts[i] = curr_time;
//						printf("starts[%d] = %d\n", i, (curr_time));
					}
				}
			}
		}
		//double sure for loop in case garbage section hindered changing of start time while change of current_p; we exclude i = 0 since we set it from the start (TEMPORARILY)
		for (i = 1; i < n; i++){
			if(starts[i] == 1000 && i == current_p)
				starts[i] = curr_time;
		}
		
//		for (i = 0; i < n; i++){
//				printf("P[%d] = %d\n", temp[i].id, starts[i]);
//		}
//			
//		printf("\n");
	}
	
	awt = (float)total_wait/n;
	printf("Average waiting time: %.2f\n", awt);
	
}

int main() {
//	Process test1, test2, test3, test4, test5;
	Process test1, test2, test3, test4, test5, test6;
	
    // 2 5 1    - PSJF - 5 processes - 1 (only for RR)
	// 1 0 7	- Id no. - at - bt
	// 2 2 5	- Id no. - at - bt
	// 3 3 3	- Id no. - at - bt
	// 4 5 8	- Id no. - at - bt
	// 5 6 5	- Id no. - at - bt

	test1.id = 2;
	test1.at = 2;
	test1.bt = 5;
	
	test2.id = 4;
	test2.at = 5;
	test2.bt = 8;
	
	test3.id = 1;
	test3.at = 0;
	test3.bt = 7;
	
	test4.id = 5;
	test4.at = 6;
	test4.bt = 5;
	
	test5.id = 3;
	test5.at = 3;
	test5.bt = 3;
	
	Process oop1[5] = {test1, test2, test3, test4, test5};	
	PSJF(oop1, 5);
	printf("\n");

	test1.id = 2;
	test1.at = 1;
	test1.bt = 5;
	
	test2.id = 4;
	test2.at = 3;
	test2.bt = 6;
	
	test3.id = 6;
	test3.at = 5;
	test3.bt = 8;
	
	test4.id = 1;
	test4.at = 0;
	test4.bt = 9;
	
	test5.id = 3;
	test5.at = 2;
	test5.bt = 10;
	
	test6.id = 5;
	test6.at = 4;
	test6.bt = 4;
	
	Process oop2[6] = {test1, test2, test3, test4, test5, test6};
	
	PSJF(oop2, 6);
	
	return 0;
}
