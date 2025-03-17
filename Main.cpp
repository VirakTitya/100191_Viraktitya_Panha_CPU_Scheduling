#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Process {
    int id, arrivalTime, burstTime, remainingTime, completionTime, waitingTime, turnaroundTime;
};

void fcfs(vector<Process>& processes);
void sjf(vector<Process>& processes);
void srt(vector<Process>& processes);
void rr(vector<Process>& processes, int quantum);
void displayResults(vector<Process>& processes);
void displayGanttChart(vector<int>& gantt);

int main() {
    int choice, n, quantum;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> processes(n);
    
    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time and burst time for P" << i+1 << ": ";
        processes[i].id = i+1;
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    while (true) {
        cout << "\nCPU Scheduling Algorithms:\n";
        cout << "1. FCFS\n2. SJF\n3. SRT\n4. RR\n5. Exit\nChoose an option: ";
        cin >> choice;

        if (choice == 5) break;
        if (choice == 4) {
            cout << "Enter time quantum: ";
            cin >> quantum;
        }
        
        vector<Process> tempProcesses = processes;
        switch (choice) {
            case 1: fcfs(tempProcesses); break;
            case 2: sjf(tempProcesses); break;
            case 3: srt(tempProcesses); break;
            case 4: rr(tempProcesses, quantum); break;
            default: cout << "Invalid option! Try again.\n";
        }
    }
    return 0;
}

void fcfs(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrivalTime < b.arrivalTime;
    });
    
    int time = 0;
    vector<int> gantt;
    for (auto& p : processes) {
        if (time < p.arrivalTime) time = p.arrivalTime;
        gantt.push_back(p.id);
        p.completionTime = time + p.burstTime;
        p.turnaroundTime = p.completionTime - p.arrivalTime;
        p.waitingTime = p.turnaroundTime - p.burstTime;
        time += p.burstTime;
    }
    displayGanttChart(gantt);
    displayResults(processes);
}

void sjf(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.burstTime < b.burstTime;
    });
    
    int time = 0;
    vector<int> gantt;
    for (auto& p : processes) {
        if (time < p.arrivalTime) time = p.arrivalTime;
        gantt.push_back(p.id);
        p.completionTime = time + p.burstTime;
        p.turnaroundTime = p.completionTime - p.arrivalTime;
        p.waitingTime = p.turnaroundTime - p.burstTime;
        time += p.burstTime;
    }
    displayGanttChart(gantt);
    displayResults(processes);
}

void srt(vector<Process>& processes) {
    int time = 0, completed = 0, n = processes.size();
    vector<int> gantt;
    
    while (completed < n) {
        int idx = -1, minTime = 1e9;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= time && processes[i].remainingTime > 0 && processes[i].remainingTime < minTime) {
                minTime = processes[i].remainingTime;
                idx = i;
            }
        }
        
        if (idx == -1) {
            time++;
            continue;
        }
        
        gantt.push_back(processes[idx].id);
        processes[idx].remainingTime--;
        if (processes[idx].remainingTime == 0) {
            processes[idx].completionTime = time + 1;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
            completed++;
        }
        time++;
    }
    displayGanttChart(gantt);
    displayResults(processes);
}

void rr(vector<Process>& processes, int quantum) {
    queue<int> q;
    int time = 0, n = processes.size(), completed = 0;
    vector<int> gantt;
    
    for (int i = 0; i < n; i++) q.push(i);
    
    while (!q.empty()) {
        int i = q.front(); q.pop();
        gantt.push_back(processes[i].id);
        
        int execTime = min(quantum, processes[i].remainingTime);
        time += execTime;
        processes[i].remainingTime -= execTime;
        
        if (processes[i].remainingTime == 0) {
            processes[i].completionTime = time;
            processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
            processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
            completed++;
        } else {
            q.push(i);
        }
    }
    displayGanttChart(gantt);
    displayResults(processes);
}

void displayResults(vector<Process>& processes) {
    double totalWT = 0, totalTAT = 0;
    cout << "\nProcess\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n";
    for (auto& p : processes) {
        cout << "P" << p.id << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t" << p.completionTime << "\t" << p.waitingTime << "\t" << p.turnaroundTime << "\n";
        totalWT += p.waitingTime;
        totalTAT += p.turnaroundTime;
    }
    cout << "\nAverage Waiting Time: " << totalWT / processes.size() << "\n";
    cout << "Average Turnaround Time: " << totalTAT / processes.size() << "\n";
}

void displayGanttChart(vector<int>& gantt) {
    cout << "\nGantt Chart: ";
    for (int p : gantt) cout << "P" << p << " ";
    cout << "\n";
}
