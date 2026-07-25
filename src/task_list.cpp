#include "task_list.hpp"
#include <iostream>

using namespace std;

bool isValidPriority(int priority) {
    // Return true when priority is from 1 to 5.
    return (priority >= 1 && priority <= 5);
}

Task createTask(string description, int priority) {
    Task task;
    // Store the description.
    // Store the priority if valid; otherwise store 1.
    // New tasks should start as not completed.
    task.description = description;
    task.priority = isValidPriority(priority) ? priority: 1;
    task.completed = false;
    return task;
}

void insertFront(TaskNode*& head, Task task) {
    // Dynamically allocate a new TaskNode.
    // Store task in the node.
    // Point the new node to the old head.
    // Update head.
    TaskNode* newNode = new TaskNode;
    newNode->data = task;
    newNode->next = head;
    head = newNode;
}

int countTasks(const TaskNode* head) {
    // Traverse the list and count nodes.
    int count = 0;
    const TaskNode* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

TaskNode* findTask(TaskNode* head, string description) {
    // Traverse the list.
    // Return the first node whose task description matches.
    // Return nullptr if not found.
    TaskNode* current = head;
    while(current != nullptr) {
        if(current->data.description == description) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

bool markTaskComplete(TaskNode* head, string description) {
    // Find the task.
    // If found, set completed to true and return true.
    // Otherwise return false.
    TaskNode* found = findTask(head, description);
    if(found != nullptr) {
        found->data.completed = true;
        return true;
    }
    return false;
}

int removeCompletedTasks(TaskNode*& head) {
    // Remove all completed tasks.
    // Return the number of removed nodes.
    // Be sure to handle completed tasks at the head of the list.
    int removedCount = 0;
    while(head != nullptr && head->data.completed) {
        TaskNode* toDelete = head;
        head = head->next;
        delete toDelete;
        removedCount++;
    }

    TaskNode* current = head;
    while(current != nullptr && current->next != nullptr) {
        if(current->next->data.completed) {
            TaskNode* toDelete = current->next;
            current->next = toDelete->next;
            delete toDelete;
            removedCount++;
        }
        else {
            current = current->next;
        }
    }

    return removedCount;
}

void clearTasks(TaskNode*& head) {
    // Delete every node in the list.
    // Set head to nullptr.
    while(head != nullptr) {
        TaskNode* toDelete = head;
        head = head->next;
        delete toDelete;
    }
}

void printTask(const Task& task) {
    cout << task.description
         << " | priority " << task.priority
         << " | " << (task.completed ? "complete" : "not complete")
         << endl;
}

void printTasks(const TaskNode* head) {
    if (head == nullptr) {
        cout << "No tasks." << endl;
        return;
    }

    const TaskNode* current = head;

    while (current != nullptr) {
        printTask(current->data);
        current = current->next;
    }
}
