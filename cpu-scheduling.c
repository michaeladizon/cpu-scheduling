/**********************************************
	Names: 	 Dizon, Michaela Nicole P.
			 Marasigan, Giann Jericho Mari F.
	Group:	 39
	Section: S16
***********************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX 400

// ascii
#define V 186
#define H 205
#define TL 201
#define TR 187
#define BL 200
#define BR 188
#define M 206
#define TM 203
#define LM 204
#define RM 185
#define BM 202

typedef struct {
    int id;  // process ID
    int at;  // arrival time
    int bt;  // burst time
    int bursted; // boolean checker if process has fully bursted
} Process;

// displays the process table's top border and headings
void print_top() {
	// top border
	printf("%c%c%c%c%c%c%c%c", TL, H, H, H, H, H, H, TM); // ID
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", H, H, H, H, H, H, H, H, H, H, H, H, H, H, TM); // AT
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c", H, H, H, H, H, H, H, H, H, H, H, H, TM); // BT
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c", H, H, H, H, H, H, H, H, H, H, H, H, TM); // ST
	printf("%c%c%c%c%c%c%c%c%c%c%c", H, H, H, H, H, H, H, H, H, H, TM); // ET
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", H, H, H, H, H, H, H, H, H, H, H, H, H, H, TM); // WT
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, TR); // TAT
	// headings
	printf("%c  ID  %c Arrival Time %c Burst Time %c Start Time %c End Time %c Waiting Time %c Turnaround Time %c\n", V,V,V,V,V,V,V,V);

	printf("%c%c%c%c%c%c%c%c", LM, H, H, H, H, H, H, M); // ID
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", H, H, H, H, H, H, H, H, H, H, H, H, H, H, M); // AT
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c", H, H, H, H, H, H, H, H, H, H, H, H, M); // BT
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c", H, H, H, H, H, H, H, H, H, H, H, H, M); // ST
	printf("%c%c%c%c%c%c%c%c%c%c%c", H, H, H, H, H, H, H, H, H, H, M); // ET
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", H, H, H, H, H, H, H, H, H, H, H, H, H, H, M); // WT
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, RM); // TAT
}

// displays the process table's bottom border
void print_bottom() {
	// bottom border
	printf("%c%c%c%c%c%c%c%c", BL, H, H, H, H, H, H, BM); // ID
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", H, H, H, H, H, H, H, H, H, H, H, H, H, H, BM); // AT
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c", H, H, H, H, H, H, H, H, H, H, H, H, BM); // BT
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c", H, H, H, H, H, H, H, H, H, H, H, H, BM); // ST
	printf("%c%c%c%c%c%c%c%c%c%c%c", H, H, H, H, H, H, H, H, H, H, BM); // ET
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", H, H, H, H, H, H, H, H, H, H, H, H, H, H, BM); // WT
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, H, BR); // TAT
}

// displays a table containing the details of each process
void print_table(Process p[], int st[], int et[], int wt[], int tat[], int twt, int ttt, int n) {
	int i, j;

	// print top border and headings
	print_top();

	// print values
	for(i = 0; i < n; i++)
		printf("%c  %2d  %c      %2d      %c     %2d     %c     %2d     %c    %2d    %c      %2d      %c       %2d        %c\n",
			V, p[i].id, V, p[i].at, V, p[i].bt, V, st[i], V, et[i], V, wt[i], V, tat[i], V);
	
	// print bottom border
	print_bottom();

	// print total and average times
	float awt = (float)twt/n;
	float att = (float)ttt/n;
	printf("\nTotal waiting time: %d\n", twt);
	printf("Average waiting time: %.2f\n\n", awt);
	printf("Total Turnaround time: %d\n", ttt);
	printf("Average waiting time: %.2f\n\n", att);
}

// displays a visual representation of the order of processes
void print_gantt(Process p[], int st[], int et[], int n) {
	int i, j;

	printf("Gantt Chart (may need to increase terminal width for proper printing)\n");

	// top border
    printf("%c", TL);
	for(j = 1; j < p[0].bt; j++) printf("%c%c", H, H);
	printf("%c%c", H, TM);
	for(i = 1; i < n; i++) {
		for(j = 0; j < p[i].bt; j++) printf("%c%c", H, H);
		printf("%c", H);
		if(i < n-1) printf("%c", TM);
	}
	printf("%c\n", TR);

	// print process IDs
	printf("%c", V);
	for(j = 0; j < p[0].bt - 2; j++) printf(" ");
	printf("%2d", p[0].id);
	for(j = 0; j < p[0].bt - 1; j++) printf(" ");
	printf("%c", V);

	for(i = 1; i < n; i++) {
		for(j = 0; j < p[i].bt - 1; j++) printf(" ");
		printf("%2d ", p[i].id);
		for(j = 0; j < p[i].bt - 1; j++) printf(" ");
		printf("%c", V);
	}
	printf("\n");

	// bottom border
    printf("%c", BL);
	for(j = 0; j < p[0].bt-1; j++) printf("%c%c", H, H);
	printf("%c%c", H, BM);
	for(i = 1; i < n; i++) {
		for(j = 0; j < p[i].bt; j++) printf("%c%c", H, H);
		printf("%c", H);
		if(i < n-1) printf("%c", BM);
	}
	printf("%c\n", BR);

	// print start and end times
	printf("%2d", st[0]);
	for(j = 0; j < p[0].bt-1; j++) printf("  ");
	for(i = 1; i < n; i++) {
		printf("%2d", st[i]);
		for(j = 0; j < p[i].bt; j++) printf("  ");
		// printf(" ");
	}
	printf("%2d", et[n-1]);
}

// sorts processes by arrival time
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

// First-Come First-Serve
void fcfs(Process p[], int n) {
	Process temp;
	int twt = 0, ttt = 0;
	int st[n], et[n], wt[n], tat[n];
	
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
	ttt += tat[0];
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
		// total turnaround time
		ttt += tat[i];
	}
	
	// print table
	print_table(p, st, et, wt, tat, twt, ttt, n);
	
	// print gantt chart
	print_gantt(p, st, et, n);
}

// Non-preemptive Shortest-Job First
void nsjf(Process p[], int n) {
	Process temp, t[n];
	int twt = 0, ttt = 0, tbt = 0, same = 1;;
	int st[n], et[n], wt[n], tat[n];
	
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

	// check if AT is the same for all processes
	for(i = 0; i < n; i++)
		if(t[0].at != p[i].at) same = 0;
	
	if(same) {
		// if same, sort by burst time
		for(i = 0; i < n; i++)
			for(j = 0; j < n-i-1; j++)
				if(p[j].bt > p[j+1].bt) {
					temp = p[j];
					p[j] = p[j+1];
					p[j+1] = temp;
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
	ttt += tat[0];
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
		// total turnaround time
		ttt += tat[i];
    }
	
	// print table
	print_table(p, st, et, wt, tat, twt, ttt, n);

	// print gantt chart
	print_gantt(p, st, et, n);
}

// Preemptive Shortest-Job First
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
	int nProcessburst = 0; //number of processes bursted
	
	float awt = 0; //average waiting time
	
	// for printing purposes only (at = st -- bt = et)
	int cnt = n;
	Process order[n*n];
	
	Process temp[n];
	
	//initialization of temporary array of processes && other arrays
	for (i = 0; i < n; i++){
		temp[i] = p[i];
		wt[i] = 0;
		tat[i] = 0;
		pCounter[i] = 0;
		for(j = 0; j < n; j++){
			start[i][j] = -1; //garbage value as temp value for the matrices
			end[i][j] = -1;
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
	      while the number of processes bursted != number of processes:
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
	curr_time = temp[current_p].at + 1;
	start[current_p][0] = temp[current_p].at;
	
	// print table's top border and headings
	print_top();

	int k = 0;

	//follow start loop
	while(nProcessburst != n){
		//if the current process has not fully burst, and arrival time is within the current ms time, we reduce the time left before full burst of the process
		if(bt[current_p] > 0 && temp[current_p].at <= curr_time){
			bt[current_p]--;
		}
		
		//update the end of the current process IF it is fully bursted (in this state, use bt)
		if( (end[current_p][pCounter[current_p]] == -1) && (pCounter[current_p] < n) && (bt[current_p] == 0) ){
			end[current_p][pCounter[current_p]] = curr_time;
			pCounter[current_p] += 1;
		}
	
		//if fully burst, we print start and end time, as well as compute for the waiting time and turnaround time
		//turnaround time formula: tat = curr_time - arrival time
		//wait time formula: wt = tat - bt
		if(bt[current_p] <= 0 && temp[current_p].bursted != 1){
			size = pCounter[current_p];
			temp[current_p].bursted = 1;
			tat[current_p] = curr_time - temp[current_p].at;
			wt[current_p] = tat[current_p] - temp[current_p].bt;
			total_wait += wt[current_p];

			// print values in table
			if(size > 1) {
				cnt++;
				printf("%c  %2d  %c     %3d      %c    %3d     %c    %3d     %c   %3d    %c              %c                 %c\n",
						V, temp[current_p].id, V, temp[current_p].at, V, temp[current_p].bt, V, start[current_p][0], V, end[current_p][0], V, V, V);
			}
			else
				printf("%c  %2d  %c     %3d      %c    %3d     %c    %3d     %c   %3d    %c     %3d      %c      %3d        %c\n",
						V, temp[current_p].id, V, temp[current_p].at, V, temp[current_p].bt, V, start[current_p][0], V, end[current_p][0], V, wt[current_p], V, tat[current_p], V);
			
			order[k].id = temp[current_p].id;
			order[k].at = start[current_p][0]; // start time
			order[k].bt = end[current_p][0]; // end time
			k++;

			for(i = 1; i < size-1; i++) {
				printf("%c      %c              %c            %c    %3d     %c   %3d    %c     %3d      %c      %3d        %c\n",
					V, V, V, V, start[current_p][i], V, end[current_p][i], V, wt[current_p], V, tat[current_p], V);
				order[k].id = temp[current_p].id;
				order[k].at = start[current_p][i];
				order[k].bt = end[current_p][i];
				k++;
			}

			if(size > 1) {
				printf("%c      %c              %c            %c    %3d     %c   %3d    %c     %3d      %c      %3d        %c\n",
					V, V, V, V, start[current_p][size-1], V, end[current_p][size-1], V, wt[current_p], V, tat[current_p], V);
				order[k].id = temp[current_p].id;
				order[k].at = start[current_p][i];
				order[k].bt = end[current_p][i];
				k++;
			}
			
			nProcessburst++;
		}

		//now we update index for current process by checking newly arrived processes and comparing their burst times
		previous_p = current_p; //for splits
		min_burst = -1; //garbage value
		for (i = 0; i < n; i++){
			//if arrival time is within the current ms time, it means the process has arrived/just arrived, and is part of comparison
			if(temp[i].at <= curr_time && temp[i].bursted != 1){
				//if minimum burst is garbage value, we set a new minimum burst based from previous process
				if(min_burst == -1){
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
		
		// if curr_p != previous_p, the process has changed; update end of the previous process
		if(current_p != previous_p){
			//update end time of the previous process, and increment counter for the process array
			if ( (end[previous_p][pCounter[previous_p]] == -1) && (pCounter[previous_p] < n) && (temp[previous_p].bursted != 1) ){
				end[previous_p][pCounter[previous_p]] = curr_time;
				pCounter[previous_p] += 1;
			}
			
			//now we place the start time of the current process to the start matrix
			if(start[current_p][pCounter[current_p]] == -1){
				start[current_p][pCounter[current_p]] = curr_time;
			}
		}
		curr_time++;
	}
	
	// print table's bottom border
	print_bottom();

	// print average waiting time
	awt = (float)total_wait/n;
	printf("\nTotal waiting time: %d\n", total_wait);
	printf("Average waiting time: %.2f\n\n", awt);

	// print gantt chart
	printf("Gantt Chart (may need to increase terminal width for proper printing)\n");

	sort_arrival(order, cnt);
	
	// top border
    printf("%c", TL);
	for(j = 1; j < order[0].bt-order[0].at; j++) printf("%c%c", H, H);
	if(order[0].bt-order[0].at <= 1) printf("%c%c", H, H);
	printf("%c%c", H, TM);
	for(i = 1; i < cnt; i++) {
		for(j = 0; j < order[i].bt-order[i].at; j++) printf("%c%c", H, H);
		printf("%c", H);
		if(i < cnt-1) printf("%c", TM);
	}
	printf("%c\n", TR);

	// print process IDs
	printf("%c", V);
	for(j = 0; j < order[0].bt-order[0].at-2; j++) printf(" ");
	printf("%2d", order[0].id);
	if(order[0].bt-order[0].at-2 < 0) printf(" ");
	for(j = 0; j < order[0].bt-order[0].at-1; j++) printf(" ");
	printf("%c", V);

	for(i = 1; i < cnt; i++) {
		for(j = 0; j < order[i].bt-order[i].at-1; j++) printf(" ");
		printf("%2d ", order[i].id);
		for(j = 0; j < order[i].bt-order[i].at-1; j++) printf(" ");
		printf("%c", V);
	}
	printf("\n");

	// bottom border
    printf("%c", BL);
	for(j = 0; j < order[0].bt-order[0].at-1; j++) printf("%c%c", H, H);
	if(order[0].bt-order[0].at <= 1) printf("%c%c", H, H);
	printf("%c%c", H, BM);
	for(i = 1; i < cnt; i++) {
		for(j = 0; j < order[i].bt-order[i].at; j++) printf("%c%c", H, H);
		printf("%c", H);
		if(i < cnt-1) printf("%c", BM);
	}
	printf("%c\n", BR);
	
	// print start and end times
	printf("%2d", order[0].at);
	for(j = 0; j < order[0].bt-order[0].at-1; j++) printf("  ");
	for(i = 1; i < cnt; i++) {
		printf("%2d", order[i].at);
		for(j = 0; j < order[i].bt-order[i].at; j++) printf("  ");
	}
	printf("%2d", order[cnt-1].bt);
}

void RR (Process p[], int n, int slice){
	//declare variables needed for the process
	int i, j;
	int wt[n], tat[n]; //waiting time, turnaround time
	int total_wait = 0; //totalwaiting time
	int bt[n]; //burst times
	int start[n][n];//for storing of start times
	int end[n][n]; //for storing of end times
	int curr_time; //current time in the CPU schedule
	int current_p; //index of the current process
	int next_p;//index of the previous process
	int pCounter[n]; //to be used for the update of index for process
	int size = 0; // size = pCounter[index]
	int nProcessburst = 0; //number of processes bursted
	int difference = 0;
	int max = n-1; //index of last element in process array; max boundary
	int min = 0;
	int blanks = 0; //flag for instance of process blanks

	float awt = 0; //average waiting time
	
	// for printing purposes only (at = st -- bt = et)
	int cnt = n;
	Process order[n*n];
	
/*
	idea:
		- concept: as quantum gets higher than all burst times, it becomes fcfs
		in case it isn't, same coding concept as PSJF
*/
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

	sort_arrival(temp, n);
/*
		Idea:
			- we loop until all the processes have been fully bursted
			- for decreasing of each process burst:
				* since we have quantum time (for slice and decrease):
					- decrease the burst time of the process with the quantum slice IF THE DIFFERENCE >= 0
					- IF THE DIFFERENCE < 0, THE SUBTRAHEND IS THE SAME WITH THE MINUEND
					
			- For decrease of the burst time:
				* record start time and end time of the process
				* if FULLY BURSTED:
					- calculate waiting time and turnaround time
					- formula for tat: exit time - arrival time
					- formula for wt: tat - burst time
					- display details
					- increment nProcess
				* ELSE:
					- increment index for traversing the array of processes
					- UNLESS:
						- IF THE NEXT PROCESS HASN'T ARRIVED YET (COMPARE curr_time+1  && temp[i].at), GO BACK TO THE VERY START OF THE ARRAY
						- IF THE NEXT PROCESS HAS BEEN FULLY BURSTED, SKIP PROCESS AND LOOK FOR THE NEXT PROCESS (Consider looping condition for this)
*/
	for(i = 0; i < n; i++){
	//assign burst time of each process to burst time array (following ordered processes by a.t) & compute total process time / total burst time 
		bt[i] = temp[i].bt;
	}
	
	//initialize to first arrived process (initiallizing = current process = next process)
	//also add starting time to the start matrix
	next_p = 0;
	current_p = 0;
	curr_time = temp[current_p].at;
	start[current_p][0] = temp[current_p].at;
	
	// print table's top border and headings
	print_top();
	int k = 0;

	while (nProcessburst != n){
		//if the burst time of the process > 0, decrease burst time of the process
		if (bt[current_p] > 0 && temp[current_p].at <= curr_time){
			//check if the difference of the burst time and slice >= 0
			difference = bt[current_p] - slice; 
			if(difference >= 0){
				//decrease the burst time of the current process
				curr_time += slice;
				bt[current_p] = difference;
			}
			//else, process is ready to fully burst; minuend = subtrahend
			else{
				curr_time += bt[current_p];
				bt[current_p] -= bt[current_p];
			}
		}
		
		//update the end of the current process 
		end[current_p][pCounter[current_p]] = curr_time;
		pCounter[current_p] += 1;
		
		//check if fully bursted
		//if fully burst, we print start and end time, as well as compute for the waiting time and turnaround time
		//turnaround time formula: tat = curr_time - arrival time
		//wait time formula: wt = tat - bt
		if(bt[current_p] <= 0 && temp[current_p].bursted != 1){
			size = pCounter[current_p];
			temp[current_p].bursted = 1;
			tat[current_p] = curr_time - temp[current_p].at;
			wt[current_p] = tat[current_p] - temp[current_p].bt;
			total_wait += wt[current_p];

			// print values in table
			if(size > 1) {
				cnt++;
				printf("%c  %2d  %c     %3d      %c    %3d     %c    %3d     %c   %3d    %c              %c                 %c\n",
					V, temp[current_p].id, V, temp[current_p].at, V, temp[current_p].bt, V, start[current_p][0], V, end[current_p][0], V, V, V);
			}
			else
				printf("%c  %2d  %c     %3d      %c    %3d     %c    %3d     %c   %3d    %c     %3d      %c       %3d       %c\n",
						V, temp[current_p].id, V, temp[current_p].at, V, temp[current_p].bt, V, start[current_p][0], V, end[current_p][0], V, wt[current_p], V, tat[current_p], V);

			order[k].id = temp[current_p].id;
			order[k].at = start[current_p][0]; // start time
			order[k].bt = end[current_p][0]; // end time
			k++;

			for(i = 1; i < size-1; i++)
				printf("%c      %c              %c            %c    %3d     %c   %3d    %c              %c                 %c\n",
					V, V, V, V, start[current_p][i], V, end[current_p][i], V, V, V);

			if(size > 1) {
				printf("%c      %c              %c            %c    %3d     %c   %3d    %c     %3d      %c       %3d       %c\n",
					V, V, V, V, start[current_p][size-1], V, end[current_p][size-1], V, wt[current_p], V, tat[current_p], V);
				order[k].id = temp[current_p].id;
				order[k].at = start[current_p][i];
				order[k].bt = end[current_p][i];
				k++;
			}

			nProcessburst++;
		}

		//look for next process
		if(current_p == max){
			for (i = 0; i < n; i++){
				if (temp[i].at <= curr_time && temp[i].bursted != 1){
					current_p = i;
					break;
				}
			}
		}
		
		else{
			next_p = current_p + 1;
			if(temp[next_p].at <= curr_time && temp[next_p].bursted != 1){
				current_p = next_p;
			}
				
			else{
				for (i = 0; i < n; i++){
					if (temp[i].at <= curr_time && i != current_p && i != next_p && temp[i].bursted != 1){
						current_p = i;
						break;
					}
				}
				
				if(temp[current_p].bursted == 1){
					//check for blanks
					for(i = 0; i < n; i++){
						if(temp[i].bursted != 1 && temp[i].at > curr_time){
							curr_time = temp[i].at;
							current_p = i;
							blanks = 1;
							break;
						}
					}
				}
			}
		}
		
		//then we add to the start matrix the start time of the process
		start[current_p][pCounter[current_p]] = curr_time;	
	}
	
	// print table's bottom border
	print_bottom();
	
	awt = (float)total_wait/n;
	printf("\nTotal waiting time: %d\n", total_wait);
	printf("Average waiting time: %.2f\n", awt);

	// print gantt chart
	printf("\nGantt Chart (may need to increase terminal width for proper printing)\n");

	sort_arrival(order, cnt);
	
	// top border
    printf("%c", TL);
	for(j = 1; j < order[0].bt-order[0].at; j++) printf("%c%c", H, H);
	if(order[0].bt-order[0].at <= 1) printf("%c%c", H, H);
	printf("%c%c", H, TM);
	for(i = 1; i < cnt; i++) {
		for(j = 0; j < order[i].bt-order[i].at; j++) printf("%c%c", H, H);
		printf("%c", H);
		if(i < cnt-1) printf("%c", TM);
	}
	printf("%c\n", TR);

	// print process IDs
	printf("%c", V);
	for(j = 0; j < order[0].bt-order[0].at-2; j++) printf(" ");
	printf("%2d", order[0].id);
	if(order[0].bt-order[0].at-2 < 0) printf(" ");
	for(j = 0; j < order[0].bt-order[0].at-1; j++) printf(" ");
	printf("%c", V);

	for(i = 1; i < cnt; i++) {
		for(j = 0; j < order[i].bt-order[i].at-1; j++) printf(" ");
		printf("%2d ", order[i].id);
		for(j = 0; j < order[i].bt-order[i].at-1; j++) printf(" ");
		printf("%c", V);
	}
	printf("\n");

	// bottom border
    printf("%c", BL);
	for(j = 0; j < order[0].bt-order[0].at-1; j++) printf("%c%c", H, H);
	if(order[0].bt-order[0].at <= 1) printf("%c%c", H, H);
	printf("%c%c", H, BM);
	for(i = 1; i < cnt; i++) {
		for(j = 0; j < order[i].bt-order[i].at; j++) printf("%c%c", H, H);
		printf("%c", H);
		if(i < cnt-1) printf("%c", BM);
	}
	printf("%c\n", BR);
	
	// print start and end times
	printf("%2d", order[0].at);
	for(j = 0; j < order[0].bt-order[0].at-1; j++) printf("  ");
	for(i = 1; i < cnt; i++) {
		printf("%2d", order[i].at);
		for(j = 0; j < order[i].bt-order[i].at; j++) printf("  ");
	}
	printf("%2d", order[cnt-1].bt);
}

int main() {
	FILE *fp;
	
	int i = 0, arr[MAX], num;
	char filename[25];
	Process p[100];
	
	printf("Filename: ");
	scanf("%s", &filename);
	fp = fopen(filename, "r");
	
	if(fp == NULL) {
		printf("%s not found.", &filename);
		exit(EXIT_FAILURE);
	}

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
	
	int max = 3 + 3*nProcesses;
	
	// store inputs in a Process array
	for(i = 3; i < n; i+=3) {
		p[j].id = arr[i];
		p[j].at = arr[i+1];
		p[j].bt = arr[i+2];
		j++;
	}
	
	int error = 0;
	
	// if the number of inputs does not match the expected # of inputs
	if(n != max) {
		printf("Incomplete input.\n");
		error = 1;
	}
	
	// check for negative inputs
	if(algo < 0 || nProcesses < 0 || tSlice < 0) error = 2;
	for(i = 0; i < nProcesses; i++) {
		if(p[i].id < 0 || p[i].at < 0 || p[i].bt < 0) {
			error = 2;
			break;
		}
	}
	
	if(error == 2) printf("Negative inputs are invalid.\n");
	
	// validate algo input (valid inputs: 0,1,2,3)
	if(algo < 0 || algo > 4) {
		printf("Please input a valid algorithm.\n");
		error = 1;
	}
	
	// validate tSlice (min = 1 || max = 100)
	if(algo == 3) {
		if(tSlice < 1) {
			printf("Time slice should have a minimum value of 1.\n");
			error = 1;
		}
		if(tSlice > 100) {
			printf("Time slice cannot exceed 100.\n");
			error = 1;
		}
	}
	
	// validate nProcs (min = 3 || max = 100)
	if(nProcesses < 3) {
		printf("Please input at least 3 processes.\n");
		error = 1;
	}
	if(nProcesses > 100) {
		printf("There can only be up to 100 processes.\n");
		error = 1;
	}
	
	// check Process IDs
	for(i = 0; i < nProcesses; i++)
		for(j = i + 1; j < nProcesses; j++)
			if(p[i].id == p[j].id) {
				error = 3;
				break;
			}
			
	if(error == 3) printf("Process IDs should be unique.\n");
	
	if(error == 0) {
		switch(algo) {
			case 0:
				printf("\nFirst-Come First-Serve\n");
				fcfs(p, nProcesses);
				break;
			case 1:
				printf("\nNon-preemptive Shortest-Job First\n");
				nsjf(p, nProcesses);
				break;
			case 2:
				printf("\nPreemptive Shortest-Job First\n");
				PSJF(p, nProcesses);
				break;
			 case 3:
			 	printf("\nRound-Robin\n");
			 	RR(p, nProcesses, tSlice);
			 	break;
		}
	}
		
	return 0;
}
