#include <stdio.h>
#define MAX_PROCESS 10
typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;
void fcfs(Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    while (completed < n) {
        int min_index = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time == current_time && processes[i].remaining_time > 0) {
                min_index = i;
                break;
            }
        }
        if (min_index == -1) {
            current_time++;
            continue;
        }
        processes[min_index].remaining_time--;
        current_time++;
        if (processes[min_index].remaining_time == 0) {
            completed++;
            processes[min_index].waiting_time = current_time - processes[min_index].arrival_time - processes[min_index].burst_time;
            processes[min_index].turnaround_time = current_time - processes[min_index].arrival_time;
            total_waiting_time += processes[min_index].waiting_time;
            total_turnaround_time += processes[min_index].turnaround_time;
        }
    }
    double average_waiting_time = (double)total_waiting_time / n;
    double average_turnaround_time = (double)total_turnaround_time / n;
    printf("-GANTT CHART-\n");
    for (int i = 0; i < n; i++) {
        printf("p%d ", processes[i].pid);
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < processes[i].burst_time; j++) {
            printf("I ");
        }
        printf("\n");
    }
    printf("Average Waiting Time of Processes : %.4f\n", average_waiting_time);
    printf("Average Turnaround Time of Processes : %.4f\n", average_turnaround_time);
}
int main() {
    Process processes[MAX_PROCESS];
    int n;
    printf("Enter the number of processes : ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time for process p%d : ", i);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter Burst Time for process p%d : ", i);
        scanf("%d", &processes[i].burst_time);
        processes[i].pid = i;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }
    fcfs(processes, n);
    return 0;
}