#include <stdio.h>

#define MAX 400

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

void nsjf(Process p[], int n) {
	Process temp;
	int twt = 0, tbt = 0;
	int st[MAX] = {0}, wt[MAX] = {0}, tat[MAX] = {0};
	float awt = 0;
	
	int i, j, k;
	
	// sort by arrival time
	for(i = 0; i < n; i++)
		for(j = 0; j < n-i-1; j++)
			if(p[j].at > p[j+1].at) {
				temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
			
	// sort by burst time for (arrival < burst)
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

	// compute for start and waiting time
    for(i = 1; i < n; i++) {
        st[i] = st[i-1] + p[i-1].bt;
        wt[i] = st[i] - p[i].at;
    }

	// compute for turnaround time
    tat[0] += p[0].bt;
	for(i = 1; i < n; i++)
		tat[i] = tat[i-1] + p[i].bt;
	
	for(i = 0; i < n; i++) {
		// total waiting time
		twt += wt[i];
		
		printf("P[%d]\n", p[i].id);
		printf("Start Time: %d End Time: %d\n", st[i], tat[i]);
		printf("Waiting time: %d\n", wt[i]);
		printf("Turnaround time: %d\n", tat[i]);
		printf("************************************\n");
	}
	
	awt = (float)twt/n;
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
//		case 2:
//			psjf();
//			break;
//		case 3:
//			rr();
//			break;
	}
		
	return 0;
}