//Round Robin CPU scheduling
#include <stdio.h>

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
			
			printf("P[%d]\n", temp[current_p].id);
			for(i = 0; i < size; i++)
			{
				printf("Start Time: %d End Time: %d\n", start[current_p][i], end[current_p][i]);
				
			}
			printf("Waiting time: %d\n", wt[current_p]);
			printf("Turnaround time: %d\n", tat[current_p]);
			printf("************************************\n");
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
	
	awt = (float)total_wait/n;
	printf("Average waiting time: %.2f\n", awt);
}

int main(){
	Process test1, test2, test3, test4, test5, test6;
/*
	3 4 20    round robin - 4 processes - 20 splits
	1 0 53
	2 0 17
	3 0 68
	4 0 24
	
	Process		Arrival		Burst
	  P4		   0		  7
 	  P3		   1		  5
	  P1		   4		 24
 	  P5		   5		  2
 	  P2		  18		  4
 	  P6		  33		  6
	
*/

	test1.id = 1;
	test1.at = 0;
	test1.bt = 53;
	
	test2.id = 2;
	test2.at = 0;
	test2.bt = 17;
	
	test3.id = 3;
	test3.at = 0;
	test3.bt = 68;
	
	test4.id = 4;
	test4.at = 0;
	test4.bt = 24;
	
	Process DPROCESS[4] = {test1, test2, test3, test4};
	
	RR(DPROCESS, 4, 20);
	
/*
	test1.id = 4;
	test1.at = 0;
	test1.bt = 7;
	
	test2.id = 3;
	test2.at = 1;
	test2.bt = 5;
	
	test3.id = 1;
	test3.at = 4;
	test3.bt = 24;
	
	test4.id = 5;
	test4.at = 5;
	test4.bt = 2;
	
	test5.id = 2;
	test5.at = 18;
	test5.bt = 4;
	
	test6.id = 6;
	test6.at = 33;
	test6.bt = 6;
	
	Process DPROCESS[6] = {test1, test2, test3, test4, test5, test6};
	
	RR(DPROCESS, 6, 4);
*/	
	return 0;
}


















