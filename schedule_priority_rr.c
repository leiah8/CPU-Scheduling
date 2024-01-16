/**
 * Implementation of various scheduling algorithms.
 * Priority Round-robin scheduling
 * 
 * I slightly changed schedule_rr.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

struct node *head = NULL;

// pointer to the struct containing the next task
struct node *tmp;

Task *pickNextTask1();
Task *pickNextTask2();


// add a new task to the list of tasks
void add(char *name, int priority, int burst) {
    // first create the new task
    Task *newTask = (Task *) malloc(sizeof(Task));

    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;

    // insert the new task into the list of tasks 
    insert(&head, newTask);
}

/**
 * Run the priority scheduler
 */
void schedule() 
{
    
    Task *current;

    tmp = head;

    while (head != NULL) {
        current = pickNextTask1();

        if (current->burst > QUANTUM) {
            run(current, QUANTUM);

            current->burst -= QUANTUM;
        }
        else {
            run(current, current->burst);
            
            current->burst = 0;

            printf("Task %s finished.\n",current->name);        
            delete(&head, current);
        }

    }
}


//this is the only place I changed

/**
 * Returns the next task selected to run.
 * 
 * I select the next task based on priority
 *      But instead of starting the loop from the head each time, 
 *      I start at the current task 
 * 
 */
Task *pickNextTask1()
{
    
    struct node *temp;
    Task *hp = tmp->task;

    if (tmp->next == NULL)
        temp = head;
    else
        temp = tmp->next;

    struct node *hold = tmp;

    while (temp != tmp) {
        if (temp->task->priority >= hp->priority) {
            hp = temp->task;
            hold = temp;
        }

        if (tmp->next == NULL)
            tmp = head;
        else
            tmp = tmp->next;

    }

    Task *nextTask = hp;
    tmp = hold;
    return nextTask;
}


//this is the only place I changed

/**
 * Returns the next task selected to run.
 * 
 * I select the next task based on priority
 * 
 */
Task *pickNextTask2()
{
struct node *temp;
Task *hp = head->task;
temp = head->next;

    while (temp != NULL) {
        if (temp->task->priority >= hp->priority)
            hp = temp->task;

        temp = temp->next;
    }

    return hp;
}