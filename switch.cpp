#include <iostream>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;
};

void push_process(queue<Process>& process_queue, int pid, int arrival_time, int burst_time, int priority = 0) {
    Process new_process = {pid, arrival_time, burst_time, burst_time, priority};
    process_queue.push(new_process);
}

void fcfs_scheduling(queue<Process>& process_queue) {
    while (!process_queue.empty()) {
        Process current_process = process_queue.front();
        process_queue.pop();
        
        cout << "Process " << current_process.pid << " executed for " << current_process.burst_time << " units." << endl;
    }
}

void sjf_scheduling(queue<Process>& process_queue) {
    priority_queue<Process, vector<Process>, function<bool(Process, Process)>> pq([](Process a, Process b) {
        return a.burst_time > b.burst_time;
    });
    
    while (!process_queue.empty()) {
        pq.push(process_queue.front());
        process_queue.pop();
    }
    
    while (!pq.empty()) {
        Process current_process = pq.top();
        pq.pop();
        
        cout << "Process " << current_process.pid << " executed for " << current_process.burst_time << " units." << endl;
    }
}

void priority_scheduling(queue<Process>& process_queue) {
    priority_queue<Process, vector<Process>, function<bool(Process, Process)>> pq([](Process a, Process b) {
        return a.priority > b.priority;
    });
    
    while (!process_queue.empty()) {
        pq.push(process_queue.front());
        process_queue.pop();
    }
    
    while (!pq.empty()) {
        Process current_process = pq.top();
        pq.pop();
        
        cout << "Process " << current_process.pid << " executed for " << current_process.burst_time << " units." << endl;
    }
}

void round_robin_scheduling(queue<Process>& process_queue, int time_slice) {
    while (!process_queue.empty()) {
        Process current_process = process_queue.front();
        process_queue.pop();
        
        if (current_process.remaining_time <= time_slice) {
            // Process completes within time slice
            cout << "Process " << current_process.pid << " executed for " << current_process.remaining_time << " units." << endl;
        } else {
            // Process does not complete within time slice
            current_process.remaining_time -= time_slice;
            cout << "Process " << current_process.pid << " executed for " << time_slice << " units." << endl;
            process_queue.push(current_process);
        }
    }
}

int main() {
    // Get process information from the user
    int num_processes;
    cout << "Enter the number of processes: ";
    cin >> num_processes;
    
    queue<Process> process_queue;
    for (int i = 1; i <= num_processes; i++) {
        int arrival_time, burst_time, priority;
        cout << "Enter arrival time and burst time of process " << i << ": ";
        cin >> arrival_time >> burst_time;
        cout << "Enter priority of process " << i << " (default is 0): ";
        cin >> priority;
        push_process(process_queue, i, arrival_time, burst_time, priority);
    }
    
    // Prompt the user to choose a scheduling algorithm
   

int choice;
    cout << "Choose a scheduling algorithm: " << endl;
    cout << "1. FCFS" << endl;
    cout << "2. SJF" << endl;
    cout << "3. Priority" << endl;
    cout << "4. Round-robin" << endl;
    cin >> choice;
    
    // Run the chosen scheduling algorithm on the process queue
    switch (choice) {
        case 1:
            fcfs_scheduling(process_queue);
            break;
        case 2:
            sjf_scheduling(process_queue);
            break;
        case 3:
            priority_scheduling(process_queue);
            break;
        case 4:
            int time_slice;
            cout << "Enter time slice for round-robin scheduling: ";
            cin >> time_slice;
            round_robin_scheduling(process_queue, time_slice);
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
    }
    

   return 0;

}

