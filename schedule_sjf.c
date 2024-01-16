/**
 * Implementation of various scheduling algorithms.
 *
 * SJF scheduling
 * 
 * I changed schedule_priority.c
 */
 
#include <stdlib.h>
#include <stdio.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

// reference to the head of the list
struct node *head = NULL;

// sequence counter of next available thread identifier
int nextTid = 0;

Task *pickNextTask();

// add a new task to the list of tasks
void add(char *name, int priority, int burst) {
    // first create the new task
    Task *newTask = (Task *) malloc(sizeof(Task));
    
    newTask->name = name;
    newTask->tid = nextTid++;
    newTask->priority = priority;
    newTask->burst = burst;

    // insert the new task into the list of tasks 
    insert(&head, newTask);
}

/**
 * Run the SJF scheduler
 */
void schedule() 
{
    Task *current;

    // sanity checker
    traverse(head);

    while (head != NULL) {
        current = pickNextTask();
        
        run(current, current->burst);

        delete(&head, current);
    }
}

/**
 * Returns the next task selected to run. 
 * 
 * 
 * This is the only place I made changes (HERE)
 *      Instead of chooding the next task based on priority, 
 *      we choose the next task based on burt (shortest job)
 */
Task *pickNextTask()
{
    struct node *temp;
    Task *hp = head->task;
    temp = head->next;

    while (temp != NULL) {
        if (temp->task->burst < hp->burst)
            hp = temp->task;

        temp = temp->next;
    }

    return hp;
}
