#include <iostream>

template <class T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
    };
    Node* front;
    Node* rear;
public:
    Queue() : front(nullptr), rear(nullptr) {}
    void push(T data) {
        Node* temp = new Node;
        temp->data = data;
        temp->next = nullptr;
        if (front == nullptr) {
            front = rear = temp;
        } else {
            rear->next = temp;
            rear = temp;
        }
    }
    T front_value() {
        return front->data;
    }
    void pop() {
        Node* temp = front;
        front = front->next;
        delete temp;
    }
    bool empty() {
        return front == nullptr;
    }
};

// Define a Process class to hold information about each process
class Process {
public:
    std::string name;
    int duration;
    int remaining_time;
    Process(std::string name, int duration) : name(name), duration(duration), remaining_time(duration) {}
};

// Define a Round Robin scheduler class to manage the order in which processes are executed
class RoundRobinScheduler {
private:
    int time_quantum;
    Process* current_process;
    Queue<Process*> process_queue;
public:
    RoundRobinScheduler(int time_quantum) : time_quantum(time_quantum), current_process(nullptr) {}
    void add_process(Process* process) {
        process_queue.push(process);
    }
    void run() {
        while (!process_queue.empty() || current_process != nullptr) {
            // If there is no running process, dequeue the next process from the queue and start it
            if (current_process == nullptr) {
                current_process = process_queue.front_value();
                process_queue.pop();
                std::cout << "Starting process: " << current_process->name << std::endl;
            }
           
            // Save the state of the current process before switching to the next one
            current_process->remaining_time = current_process->duration - time_quantum;
           
            // Decrement the duration of the running process by the time quantum
            current_process->duration -= time_quantum;
            std::cout << "Running process: " << current_process->name << " Duration: " << current_process->duration << std::endl;
           
            // If the running process has completed, set the running process to nullptr
            if (current_process->duration <= 0) {
                current_process = nullptr;
                std::cout << "Process complete!" << std::endl;
            }
           
            // If the time quantum has been reached, enqueue the current process and start the next one
            else if (current_process->duration > 0) {
                process_queue.push(current_process);
                current_process = process_queue.front_value();
                process_queue.pop();
                std::cout << "Time quantum reached, switching to next process: " << current_process->name << std::endl;
            }
        }
    }
};

int main() {
    // Create a Round Robin scheduler with a time quantum of 5
    RoundRobinScheduler scheduler(5);
   
    // Add some processes to the scheduler
    scheduler.add_process(new Process("Process 1", 15));
    scheduler.add_process(new Process("Process 2", 10));
    scheduler.add_process(new Process("Process 3", 20));
   
    // Run the scheduler to execute the processes
    scheduler.run();
   
    return 0;
}