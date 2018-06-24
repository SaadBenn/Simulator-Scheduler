#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>
#include "helper.h"

int main(int argc, char const *argv[]) {
    
    // load the processes first
    char *fileName = "processes.txt";
    
    queue = initialize_process_queue(queue);
    load_processes(fileName, queue);
    int scheduler = 1;
    
    switch (scheduler) {
        case 1:
            process_fcfs(queue);
            break;
        default:
            break;
    } // switch
    
    //dequeue_process(queue);
    return 0;
} // close main


void process_fcfs(Process_queue *queue) {
    
    int i;
    for (i = 0; i < queue->size; i++) {
        Process *process = queue->front->data;
        if (process->thread_name[0] == 's' || process->thread_name[0] == 'm' || process->thread_name[0] == 'l') {
            int rand_num = generate_random_word(2);
            if (rand_num == 0) {
                
            }
            printf("YES");
        }
    }
}


void load_processes(char *fileName, Process_queue *queue) {
    char *buffer;
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("%s\n", "Error opening the file");
        exit(1);
    } // if
    
    assert(fp != NULL);
    buffer = (char*) malloc(sizeof(LENGTH));
    
    while (fgets(buffer, LENGTH, fp) != NULL) {
        process_line(buffer);
        create_process(queue);
    }
    printf("%s\n", "Process loading done!");
} // close load processes


bool process_line(char *line) {
    size_t len = strlen(line);
    line[len -1] = '\0';
    
    char delim[] = " ";
    _thread_name = strdup(strtok(line, delim));
    _thread_type = strdup(strtok(NULL, delim));
    _priority = atoi(strtok(NULL, delim));
    _thread_length = atoi(strtok(NULL, delim));
    char *i =strtok(NULL, delim);
    _odds_of_IO = atoi(i);
    return true;
} // close process_line


bool create_process(Process_queue *queue) {
    Process *process = (Process*) malloc(sizeof(PROCESS_SIZE) * 10);
    assert(process != NULL);
    
    process->thread_name = _thread_name;
    process->thread_type = _thread_type;
    process->priority = _priority;
    process->thread_length = _thread_length;
    process->odds_of_IO = _odds_of_IO;
    
    // enqueue the process
    enqueue_process(queue, process);
    return true;
} // close create_process


/**
 * Creates a single process node with pointer to data and next
 */
Process_node *create_process_node(Process *p) {
    Process_node *node = (Process_node*) malloc(sizeof(Process_node) * 50);
    if (node == NULL) {
        perror("out of memory\n");
    } // if
    
    assert(node != NULL);
    node->data = p;
    node->next = NULL;
    return node;
} // close create_process_node


/**
 * Initializes a process queue. Makes an empty queue
 */
Process_queue *initialize_process_queue(Process_queue *q) {
    q = (Process_queue*) malloc(sizeof(Process_queue));
    
    assert(q != NULL);
    q->front = q->back = NULL;
    q->size = 0;
    return q;
} // close initialize_process_queue


/**
 * Equeues a process
 */
void enqueue_process(Process_queue *q, Process *p) {
    Process_node *node = create_process_node(p);
    
    if (q->front == NULL) {
        assert(q->back == NULL);
        q->front = q->back = node;
    } else {
        assert(q->back != NULL);
        q->back->next = node;
        q->back = node;
    }
    q->size++;
} // close enqueue_process


/**
 * Dequeues a process
 */
void dequeue_process(Process_queue *q) {
    Process_node *deleted = q->front;
    assert(q->size > 0);
    if (q->size == 1) {
        q->front = NULL;
        q->back = NULL;
    } else {
        assert(q->front->next != NULL);
        q->front = q->front->next;
    }
    free(deleted);
    q->size--;
} // close dequeue_process


int generate_random_word(int len) {
    srand(time(NULL));
    int rand_num = rand() % len;
    return rand_num;
} // close generate_random_word
