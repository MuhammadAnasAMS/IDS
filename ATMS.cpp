#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// Structure for Passenger
struct Passenger {
    string name;
    string ticketType; // Economy, Business, First Class
    int priority;      // Determined based on ticket type
    int processingTime; // Time required for handling (e.g., check-in)

    Passenger(string n, string type, int time) 
        : name(n), ticketType(type), processingTime(time) {
        if (type == "First Class") priority = 1;
        else if (type == "Business") priority = 2;
        else priority = 3; // Economy
    }
};

// Comparator for Priority Queue
struct ComparePriority {
    bool operator()(const Passenger &p1, const Passenger &p2) {
        return p1.priority > p2.priority; // Higher priority comes first
    }
};

// Class for Plane Ticket Management System
class PlaneTicketSystem {
private:
    queue<Passenger> roundRobinQueue; // Round-robin queue
    priority_queue<Passenger, vector<Passenger>, ComparePriority> priorityQueue; // Priority queue
    int timeQuantum; // Time slice for round-robin processing

public:
    // Constructor
    PlaneTicketSystem(int quantum) : timeQuantum(quantum) {}

    // Add passenger to the priority queue
    void addPassenger(string name, string ticketType, int processingTime) {
        Passenger newPassenger(name, ticketType, processingTime);
        priorityQueue.push(newPassenger);
        cout << "Added Passenger: " << name << " | Ticket Type: " << ticketType 
             << " | Processing Time: " << processingTime << " units\n";
    }

    // Load passengers into the round-robin queue based on priority
    void loadRoundRobinQueue() {
        while (!priorityQueue.empty()) {
            roundRobinQueue.push(priorityQueue.top());
            priorityQueue.pop();
        }
        cout << "\nAll passengers loaded into round-robin queue based on priority.\n";
    }

    // Process passengers using round-robin scheduling
    void processPassengers() {
        cout << "\nStarting passenger processing...\n";
        while (!roundRobinQueue.empty()) {
            Passenger current = roundRobinQueue.front();
            roundRobinQueue.pop();

            cout << "Processing Passenger: " << current.name 
                 << " | Ticket Type: " << current.ticketType 
                 << " | Priority: " << current.priority 
                 << " | Remaining Time: " << current.processingTime << " units\n";

            if (current.processingTime > timeQuantum) {
                current.processingTime -= timeQuantum;
                roundRobinQueue.push(current); // Requeue if processing is not complete
                cout << "Requeueing Passenger: " << current.name 
                     << " | Remaining Time: " << current.processingTime << " units\n";
            } else {
                cout << "Passenger " << current.name << " has completed processing.\n";
            }
        }
        cout << "\nAll passengers have been processed.\n";
    }

    // Display all passengers in priority order
    void displayPassengers() {
        cout << "\nPassengers in Priority Order:\n";
        priority_queue<Passenger, vector<Passenger>, ComparePriority> tempQueue = priorityQueue;
        while (!tempQueue.empty()) {
            Passenger p = tempQueue.top();
            tempQueue.pop();
            cout << "Name: " << p.name 
                 << " | Ticket Type: " << p.ticketType 
                 << " | Priority: " << p.priority 
                 << " | Processing Time: " << p.processingTime << " units\n";
        }
    }
};

int main() {
    // Initialize system with time quantum
    PlaneTicketSystem system(3);

    // Adding passengers
    system.addPassenger("Alice", "First Class", 5);
    system.addPassenger("Bob", "Economy", 6);
    system.addPassenger("Charlie", "Business", 4);
    system.addPassenger("Diana", "First Class", 7);
    system.addPassenger("Edward", "Economy", 3);
    system.addPassenger("Fiona", "Business", 8);

    // Display passengers in priority order
    system.displayPassengers();

    // Load passengers into round-robin queue based on priority
    system.loadRoundRobinQueue();

    // Process passengers
    system.processPassengers();

    return 0;
}
