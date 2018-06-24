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
    // initialize the gloabl vars
    define_global_var();
    
    load_processes(fileName, queue);
    
    int scheduler = atoi(argv[1]);
    
    switch (scheduler) {
        case 0:
            process_fcfs(queue);
            break;
        default:
            break;
    } // switch
    
    print_stats_by_priority();
    print_stats_by_type();
    printf("\n%s\n", "Scheduling done!");
    return 0;
} // close main


void define_global_var() {
    NUMBER_OF_PROCESSES = 0;
    // avergaing time
    total_time_for_short = 0;
    total_time_for_med = 0;
    total_time_for_long = 0;
    total_time_for_io = 0;
    
    // type counter
    count_short = 0;
    count_med = 0;
    count_long = 0;
    count_io = 0;
    
    // priority counter
    count_high_priority = 0;
    count_med_priority = 0;
    count_low_priority = 0;
    
    // time for priorities
    time_high = 0;
    time_med = 0;
    time_low = 0;
} // close define_global_var


void process_fcfs(Process_queue *queue) {
    
    printf("%s\n", "Using First Come First Served Scheduling algorithm.");
    int i;
    int time_slice_for_io = 0;
    int wait_time = 0;
    //int len = queue->size;
    for (i = 0; i < NUMBER_OF_PROCESSES; i++) {
        // not checking for empty queue - bad porgramming
        Process *process = queue->front->data;
        char first_letter = process->thread_name[0];
        
        switch (first_letter) {
            case 's':
                if (process->priority == 0) {
                    count_high_priority += 1;
                    time_high = wait_time + process->thread_length;
                    wait_time += process->thread_length;
                } else if (process->priority == 1) {
                    count_med_priority += 1;
                    time_med = wait_time + process->thread_length;
                    wait_time += process->thread_length;
                } else {
                    count_low_priority += 1;
                    time_low = wait_time + process->thread_length;
                    wait_time += process->thread_length;
                }
                count_short += 1;
                total_time_for_short = wait_time;
                break;
            case 'm':
                if (process->priority == 0) {
                    count_high_priority += 1;
                    time_high = wait_time + process->thread_length;
                    wait_time += process->thread_length;
                } else if (process->priority == 1) {
                    count_med_priority += 1;
                    time_med = wait_time + process->thread_length;
                    wait_time += process->thread_length;
                } else {
                    count_low_priority += 1;
                    time_low = wait_time + process->thread_length;
                    wait_time += process->thread_length;
                }
                count_med += 1;
                total_time_for_med = wait_time;
                break;
            
            case 'l':
                if (process->priority == 0) {
                    count_high_priority += 1;
                    time_high = wait_time + process->thread_length;
                    wait_time += process->thread_length;
                } else if (process->priority == 1) {
                    count_med_priority += 1;
                    time_med = wait_time + process->thread_length;
                    wait_time += process->thread_length;
                } else {
                    count_low_priority += 1;
                    time_low = wait_time + process->thread_length;
                    wait_time += process->thread_length;
                }
                count_long += 1;
                total_time_for_long = wait_time;
                break;
            
            case 'i':
                time_slice_for_io = generate_random_word(process->thread_length);
                
                if (process->priority == 0) {
                    count_high_priority += 1;
                    time_high = wait_time + time_slice_for_io;
                    wait_time += time_slice_for_io;
                } else if (process->priority == 1) {
                    count_med_priority += 1;
                    time_med = wait_time + time_slice_for_io;
                    wait_time += time_slice_for_io;
                } else {
                    count_low_priority += 1;
                    time_low = wait_time + time_slice_for_io;
                    wait_time += time_slice_for_io;
                }
                count_io += 1;
                total_time_for_io = wait_time;
                break;
            default:
                break;
        } // switch - case
        
        dequeue_process(queue);
    } // for loop
} // close process_fcfs


void print_stats_by_priority() {
    printf("\n------------------------------------------------------------------\n");
    printf("%s\n", "Average run time per priority:");
    printf("Priority 0 average run time: %d\n", time_high/count_high_priority);
    printf("Priority 1 average run time: %d\n", time_med/count_med_priority);
    printf("Priority 2 average run time: %d\n", time_low/count_low_priority);
} // close print_stats_priority


void print_stats_by_type() {
    printf("\n------------------------------------------------------------------\n");
    printf("%s\n", "Average run time per type:");
    printf("Type 0 average run time: %d\n", total_time_for_short/count_short);
    printf("Type 1 average run time: %d\n", total_time_for_med/count_med);
    printf("Type 2 average run time: %d\n", total_time_for_long/count_long);
    printf("Type 3 average run time: %d\n", total_time_for_io/count_io);
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
    NUMBER_OF_PROCESSES++;
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
