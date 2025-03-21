# 100191_Viraktitya_Panha_CPU_Scheduling
# CPU Scheduling Simulator

## Overview
This project is a CPU Scheduling Simulator implemented in C++. It supports four scheduling algorithms:
- First-Come, First-Served (FCFS)
- Shortest-Job-First (SJF)
- Shortest-Remaining-Time (SRT)
- Round Robin (RR)

The program provides a menu-driven interface to select an algorithm, enter process details, and display results including a Gantt chart, waiting times, turnaround times, and averages.

## Features
- Menu-based selection of scheduling algorithms
- Input validation for process details
- Gantt chart display
- Calculation of waiting and turnaround times
- Average waiting and turnaround time computation

## Installation & Compilation
### Prerequisites
- A C++ compiler (e.g., g++, clang++)

### Compilation
```sh
 g++ cpu_scheduling.cpp -o scheduler
```

### Running the Program
```sh
 ./scheduler
```

## Usage
1. Enter the number of processes.
2. Provide process details (ID, Arrival Time, Burst Time).
3. Choose a scheduling algorithm from the menu.
4. For Round Robin, enter the time quantum.
5. View the Gantt chart and performance metrics.

## Example Output
```
CPU Scheduling Algorithms:
1. FCFS
2. SJF
3. SRT
4. RR
5. Exit
Choose an option: 1

Gantt Chart: P1 P2 P3 P4
Process    Arrival    Burst    Completion    Waiting    Turnaround
P1        0         5       5             0         5
P2        2         3       8             3         6
P3        3         8       16            5         13
P4        5         6       22            11        17

Average Waiting Time: 4.75
Average Turnaround Time: 10.25
```

## Repository Structure
```
📂 CPU-Scheduling-Simulator
 ├── 📄 cpu_scheduling.cpp  # Source code
 ├── 📄 README.md           # Documentation
 ├── 📄 report.pdf          # Project report
```

## License
This project is open-source and licensed under the MIT License.