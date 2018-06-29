/******************************************************************************
Saad Mushtaq
Assignment 3
Operating System - COMP 3430
Robert "the Goat" Guderian <3
Simulating Scheduling algorithms
/******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>
#include "helper.h"


// Global variables
int NUMBER_OF_PROCESSES;
int _priority;
int _odds_of_IO;
char *_thread_name;
char *_thread_type;
int _thread_length;

// avergaing time
int total_time_for_short;
int total_time_for_med;
int total_time_for_long;
int total_time_for_io;

// type counter
int count_short;
int count_med;
int count_long;
int count_io;

// priority counter
int count_high_priority;
int count_med_priority;
int count_low_priority;

// time for priorities
int time_high;
int time_med;
int time_low;

// time tracker
int wait_time = 0;

// Do sorting for SJB
const bool FALSE = false;
const bool TRUE = true;

// counters for the different priorities
int counter_p0 = 0;
int counter_p1 = 0;
int counter_p2 = 0;


/******************************************************************************/
int main(int argc, char const *argv[]) {
    
    // load the processes first
    char *fileName = "processes.txt";
    
    queue = initialize_process_queue(queue);
    high_queue = initialize_process_queue(high_queue);
    med_queue = initialize_process_queue(med_queue);
    low_queue = initialize_process_queue(low_queue);
    
    // initialize the gloabl vars
    define_global_var();
    
    load_processes(fileName, queue, high_queue, med_queue, low_queue);
    
    int scheduler = atoi(argv[1]);
    
    switch (scheduler) {
        case 1:
            printf("%s\n", "Using Pure Round Robin Scheduling algorithm.");
            process_fcfs(queue, FALSE);
            break;
        case 2:
            printf("%s\n", "Using Priority Round Robin algorithm.");
            process_priority_round_robin(high_queue, med_queue, low_queue);
            break;
        case 3:
            printf("%s\n", "Using Shortest Job First Scheduling algorithm.");
            process_sjf(queue);
            break;
        case 4:
            printf("%s\n", "Using Shortest Time To Completion Scheduling algorithm.");
            process_srtf(queue);
            break;
        default:
            printf("%s\n", "Valid arguments are from -> 1.....4, only.");
            break;
    } // switch
    
    printf("------------------------------------------------------------------\n");
    print_stats_by_priority();
    print_stats_by_type();
    printf("------------------------------------------------------------------\n");
    printf("\n%s\n", "Scheduling done!");
    return 0;
} // close main


/******************************************************************************
process all the shortest remaining time jobs first by sorting them
******************************************************************************/
void process_srtf(Process_queue *queue) {
    process_fcfs(queue, TRUE);
} // close process_srtf


/******************************************************************************
Initialise all the global variables
******************************************************************************/
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


/******************************************************************************
Process the highest priority first then the second one and then the lowest priority
******************************************************************************/
void process_priority_round_robin(Process_queue *queue_high, Process_queue *queue_med, Process_queue *queue_low) {
    process_fcfs(queue_high, FALSE);
    process_fcfs(queue_med, FALSE);
    process_fcfs(queue_low, FALSE);
} // close process_priority_round_robin


/******************************************************************************
The heart of the simulator, this process will sdo sorting if it is SJF/SRTF otherwise it 
will generate a quantum and use that until a job is completely dequed
/******************************************************************************/
void process_fcfs(Process_queue *queue, bool do_sort) {
    
    int i;
    int quantum;
    bool result_io;
    int n;
    // check if we need to rerun the processes
    while (is_empty(queue)) {
        
        if (do_sort) {
            sort_queue(queue);
        }
        
        n = queue->size;
        for (i = 0; i < n; i++) {
            
            Process *process = queue->front->data;
            char first_letter = process->thread_name[0];
            
            // io interruption?
            result_io = do_io(process->odds_of_IO);
            
            switch (first_letter) {
                case 's':
                    if (process->priority == 0) {
                        if (result_io) {
                            // io expected
                            quantum = generate_time_slice(TIME_SLICE);
                            
                            // if time remaining is less than the quantum
                            if (process->thread_length < quantum) {
                                wait_time += process->thread_length;
                                
                            // thread length is > than the quantum
                            } else {
                                wait_time += quantum;
                            }
                        // no io expected, use full time slice of 5
                        } else {
                            quantum = TIME_SLICE;
                            if (process->thread_length < quantum) {
                                wait_time += process->thread_length;
                            } else {
                                wait_time += TIME_SLICE;
                            }
                        }
                        
                        // check if the process has completed
                        if (process->thread_length - quantum <= 0) {
                            count_high_priority += 1;
                            counter_p0++;
                            count_short += 1;
                            total_time_for_short += wait_time;
                            time_high += wait_time;
                        } else {
                            int quantum_left = process->thread_length - quantum;
                            process->thread_length = quantum_left;
                            enqueue_process(queue, process);
                        }
                        
                    } else if (process->priority == 1) {
                        
                        if (result_io) {
                            quantum = generate_time_slice(TIME_SLICE);
                            if (process->thread_length < quantum) {
                                wait_time += process->thread_length;
                            } else {
                                wait_time += quantum;
                            }
                        } else {
                            quantum = TIME_SLICE;
                            if (process->thread_length < quantum) {
                                wait_time += process->thread_length;
                            } else {
                                wait_time += TIME_SLICE;
                            }
                        }
                        
                        if (process->thread_length - quantum <= 0) {
                            count_med_priority += 1;
                            counter_p1++;
                            count_short += 1;
                            time_med += wait_time;
                            total_time_for_short += wait_time;
                        } else {
                            int quantum_left = process->thread_length - quantum;
                            process->thread_length = quantum_left;
                            enqueue_process(queue, process);
                        }
                        
                        
                    } else {
                        // priority 2 - low priority
                        
                        if (result_io) {
                            quantum = generate_time_slice(TIME_SLICE);
                            if (process->thread_length < quantum) {
                                wait_time += process->thread_length;
                            } else {
                                wait_time += quantum;
                            }
                            
                        } else {
                            quantum = TIME_SLICE;
                            if (process->thread_length < quantum) {
                                wait_time += process->thread_length;
                            } else {
                                wait_time += TIME_SLICE;
                            }
                        }
                        
                        if (process->thread_length - quantum <= 0) {
                            count_low_priority += 1;
                            counter_p2++;
                            time_low += wait_time;
                            count_short += 1;
                            total_time_for_short += wait_time;
                        } else {
                            int quantum_left = process->thread_length - quantum;
                            process->thread_length = quantum_left;
                            enqueue_process(queue, process);
                        }
                    } // else
                    
                    break;
                    
                case 'm':
                    if (process->priority == 0) {
                        
                        if (result_io) {
                            quantum = generate_time_slice(TIME_SLICE);
                            if (process->thread_length < quantum) {
                                wait_time += process->thread_length;
                            } else {
                                wait_time += quantum;
                            }
                            
                        } else {
                            quantum = TIME_SLICE;
                            if (process->thread_length < quantum) {
                                wait_time += process->thread_length;
                            } else {
                                // use the full time slice
                                wait_time += TIME_SLICE;
                            }
                        }
                        
                        // check if we have more time remaining
                        if (process->thread_length - quantum <= 0) {
                            count_med_priority += 1;
                            counter_p0++;
                            time_high += wait_time;
                            count_med += 1;
                            total_time_for_med += wait_time;
                        
                        } else {
                            // enqueue the process again with the updated time
                            int quantum_left = process->thread_length - quantum;
                            process->thread_length = quantum_left;
                            enqueue_process(queue, process);
                        }
                        
                        
                    } else if (process->priority == 1) {
                        
                        if (result_io) {
                            quantum = generate_time_slice(TIME_SLICE);
                            if (process->thread_length < quantum) {
                                wait_time += process->thread_length;
                            } else {
                                wait_time += quantum;
                            }
                            
                        } else {
                            quantum = TIME_SLICE;
                            if (process->thread_length < quantum) {
                                wait_time += process->thread_length;
                            } else {
                                wait_time += TIME_SLICE;
                            }
                        }
                        
                        // check if we have more time remaining
                        if (process->thread_length - quantum <= 0) {
                            count_med_priority += 1;
                            time_med += wait_time;
                            counter_p1++;
                            count_med += 1;
                            total_time_for_med += wait_time;
                            
                        } else {
                            // enqueue the process again with the updated time
                            int quantum_left = process->thread_length - quantum;
                            process->thread_length = quantum_left;
                            enqueue_process(queue, process);
                        }
                        
                        
                    } else {
                        
                        // low priority
                        if (result_io) {
                            quantum = generate_time_slice(TIME_SLICE);
                            if (process->thread_length < quantum) {
                                wait_time += process->thread_length;
                            } else {
                                wait_time += quantum;
                            }
                            
                        } else {
                            quantum = TIME_SLICE;
                            if (process->thread_length < quantum) {
                                wait_time += process->thread_length;
                            } else {
                                wait_time += TIME_SLICE;
                            }
                        }
                        
                        // check if we have more time remaining
                        if (process->thread_length - quantum <= 0) {
                            count_low_priority += 1;
                            time_low += wait_time;
                            counter_p2++;
                            count_med += 1;
                            total_time_for_med += wait_time;
                            
                        } else {
                            // enqueue the process again with the updated time
                            int quantum_left = process->thread_length - quantum;
                            process->thread_length = quantum_left;
                            enqueue_process(queue, process);
                        }
                        
                    } // else
                    break;
                
                case 'l':
                    if (process->priority == 0) {
                        if (result_io) {
                            quantum = generate_time_slice(TIME_SLICE);
                            if (process->thread_length < quantum) {
                                wait_time += process->thread_length;
                            } else {
                                wait_time += quantum;
                            }
                            
                        
                        } else {
                            quantum = TIME_SLICE;
                            if (process->thread_length < quantum) {
                                wait_time += process->thread_length;
                            } else {
                                wait_time += TIME_SLICE;
                            }
                        }
                        
                        // check if we have more time remaining
                        if (process->thread_length - quantum <= 0) {
                            count_high_priority += 1;
                            counter_p0++;
                            time_high += wait_time;
                            count_long += 1;
                            total_time_for_long += wait_time;
                            
                        } else {
                            // enqueue the process again with the updated time
                            int quantum_left = process->thread_length - quantum;
                            process->thread_length = quantum_left;
                            enqueue_process(queue, process);
                        }
                        
                    } else if (process->priority == 1) {
                        
                        if (result_io) {
                            quantum = generate_time_slice(TIME_SLICE);
                            if (process->thread_length < quantum) {
                                wait_time += process->thread_length;
                            } else {
                                wait_time += quantum;
                            }

                        } else {
                            quantum = TIME_SLICE;
                            if (process->thread_length < quantum) {
                                wait_time += process->thread_length;
                            } else {
                                wait_time += TIME_SLICE;
                            }
                        }
                        
                        // check if we have more time remaining
                        if (process->thread_length - quantum <= 0) {
                            count_med_priority += 1;
                            time_med += wait_time;
                            counter_p1++;
                            count_long += 1;
                            total_time_for_long += wait_time;
                            
                        } else {
                            // enqueue the process again with the updated time
                            int quantum_left = process->thread_length - quantum;
                            process->thread_length = quantum_left;
                            enqueue_process(queue, process);
                        }
                        
                    } else {
                        
                        if (result_io) {
                            quantum = generate_time_slice(TIME_SLICE);
                            if (process->thread_length < quantum) {
                                wait_time += process->thread_length;
                            } else {
                                wait_time += quantum;
                            }
                        
                        } else {
                            quantum = TIME_SLICE;
                            if (process->thread_length < quantum) {
                                wait_time += process->thread_length;
                            } else {
                                wait_time += TIME_SLICE;
                            }
                        }
                        
                        // check if we have more time remaining
                        if (process->thread_length - quantum <= 0) {
                            count_low_priority += 1;
                            time_low += wait_time;
                            counter_p2++;
                            count_long += 1;
                            total_time_for_long += wait_time;
                            
                        } else {
                            // enqueue the process again with the updated time
                            int quantum_left = process->thread_length - quantum;
                            process->thread_length = quantum_left;
                            enqueue_process(queue, process);
                        }
                        
                    }
                    break;
                
                case 'i':
                    
                    if (process->priority == 0) {
                        
                        if (result_io) {
                            quantum = generate_time_slice(TIME_SLICE);
                            if (process->thread_length < quantum) {
                                wait_time += process->thread_length;
                            } else {
                                wait_time += quantum;
                            }
                            
                        } else {
                            quantum = TIME_SLICE;
                            if (process->thread_length < quantum) {
                                wait_time += process->thread_length;
                            } else {
                                wait_time += TIME_SLICE;
                            }
                        }
                        
                        // check if we have more time remaining
                        if (process->thread_length - quantum <= 0) {
                            count_high_priority += 1;
                            time_high += wait_time;
                            counter_p0++;
                            count_io += 1;
                            total_time_for_io += wait_time;
                            
                        } else {
                            // enqueue the process again with the updated time
                            int quantum_left = process->thread_length - quantum;
                            process->thread_length = quantum_left;
                            enqueue_process(queue, process);
                        }
                        
                    } else if (process->priority == 1) {
                        
                        if (result_io) {
                            quantum = generate_time_slice(TIME_SLICE);
                            if (process->thread_length < quantum) {
                                wait_time += process->thread_length;
                            } else {
                                wait_time += quantum;
                            }
                        
                        } else {
                            quantum = TIME_SLICE;
                            if (process->thread_length < quantum) {
                                wait_time += process->thread_length;
                            } else {
                                wait_time += TIME_SLICE;
                            }
                        }
                        
                        // check if we have more time remaining
                        if (process->thread_length - quantum <= 0) {
                            count_med_priority += 1;
                            time_med += wait_time;
                            counter_p1++;
                            count_io += 1;
                            total_time_for_io += wait_time;
                            
                        } else {
                            // enqueue the process again with the updated time
                            int quantum_left = process->thread_length - quantum;
                            process->thread_length = quantum_left;
                            enqueue_process(queue, process);
                        }
                        
                    } else {
                        
                        if (result_io) {
                            quantum = generate_time_slice(TIME_SLICE);
                            if (process->thread_length < quantum) {
                                wait_time += process->thread_length;
                            } else {
                                wait_time += quantum;
                            }
                        } else {
                            quantum = TIME_SLICE;
                            if (process->thread_length < quantum) {
                                wait_time += process->thread_length;
                            } else {
                                wait_time += TIME_SLICE;
                            }
                        }
                        
                        // check if we have more time remaining
                        if (process->thread_length - quantum <= 0) {
                            count_low_priority += 1;
                            time_low += wait_time;
                            counter_p2++;
                            count_io += 1;
                            total_time_for_io += wait_time;
                            
                        } else {
                            // enqueue the process again with the updated time
                            int quantum_left = process->thread_length - quantum;
                            process->thread_length = quantum_left;
                            enqueue_process(queue, process);
                        }
                    }
                    break;
                    
                default:
                    break;
            } // switch - case
            dequeue_process(queue);
        } // for loop
    } // while loop
} // close process_fcfs


/******************************************************************************
Queue Management function, check if the queue is empty
/******************************************************************************/
bool is_empty(Process_queue *queue) {
    if (queue == NULL) {
        return true;
    } else {
        return queue->size > 0;
    }
} // close is_empty


/******************************************************************************
Process all the shortest jobs first by sorting them first
/******************************************************************************/
void process_sjf(Process_queue *queue) {
    // sort the queue by shortest jobs first
    process_fcfs(queue, TRUE);
} // close process_sjf


/******************************************************************************
Goes through the queue by using in line sort w/o creating a new queue O(n) time
/******************************************************************************/
void sort_queue(Process_queue *queue) {
    int i;
    int n = queue->size;
    for (i = 1; i <= n; i++) {
        int min_index = min_finder(queue, queue->size - i);
        insert_min_to_rear(queue, min_index);
    }
} // close sort_queue


/****************************************************************************** 
Moves given minimum element to rear of queue
/******************************************************************************/
void insert_min_to_rear(Process_queue *queue, int min_index) {
    Process *min_val_process = NULL;
    int n = queue->size;
    int i;
    for (i = 0; i < n; i++) {
        Process *process = (Process*) malloc(sizeof(PROCESS_SIZE) * 10);
        // deep copy before de-queueing
        process->thread_name = strdup(queue->front->data->thread_name);
        process->thread_type = strdup(queue->front->data->thread_type);
        process->priority = queue->front->data->priority;
        process->thread_length = queue->front->data->thread_length;
        process->odds_of_IO = queue->front->data->odds_of_IO;
        //Process *process = curr->data;
        dequeue_process(queue);
        if (i != min_index) {
            enqueue_process(queue, process);
        } else {
            min_val_process = process;
        }
    }
    enqueue_process(queue, min_val_process);
} // close insert_min_to_rear


/****************************************************************************** 
Queue elements after sortedIndex are
already sorted. This function returns
index of minimum element from front to
sortedIndex
******************************************************************************/
int min_finder(Process_queue *queue, int sorted_index) {
    int min_index = -1;
    int min_val = INT_MAX;
    int n = queue->size;
    int i;
    for (i = 0; i < n; i++) {
        Process_node *curr = (Process_node*) malloc(sizeof(Process_node) * 50);
        Process *process = (Process*) malloc(sizeof(PROCESS_SIZE) * 10);
        curr = queue->front;
        
        // deep copy before de-queueing
        if (queue->front->data != NULL) {
            process->thread_name = strdup(queue->front->data->thread_name);
            process->thread_type = strdup(queue->front->data->thread_type);
            process->priority = queue->front->data->priority;
            process->thread_length = queue->front->data->thread_length;
            process->odds_of_IO = queue->front->data->odds_of_IO;
            
            curr->data = process;
        }
        dequeue_process(queue);
        
        // we add the condition i <= sortedIndex
        // because we don't want to traverse
        // on the sorted part of the queue,
        // which is the right part.
        if (process->thread_length <= min_val && i <= sorted_index) {
            min_index = i;
            min_val = process->thread_length;
        }
        enqueue_process(queue, process);
    }
    return min_index;
} // close min_finder


/******************************************************************************
Print the stats by priority
/******************************************************************************/
void print_stats_by_priority() {
    printf("\n%s\n", "Average run time per priority:");
    printf("Priority 0 average run time: %d\n", time_high/counter_p0);
    printf("Priority 1 average run time: %d\n", time_med/counter_p1);
    printf("Priority 2 average run time: %d\n", time_low/counter_p2);
} // close print_stats_priority


/******************************************************************************
print stats by type
/******************************************************************************/
void print_stats_by_type() {
    printf("\n\n%s\n", "Average run time per type:");
    printf("Type 0 average run time: %d\n", total_time_for_short/count_short);
    printf("Type 1 average run time: %d\n", total_time_for_med/count_med);
    printf("Type 2 average run time: %d\n", total_time_for_long/count_long);
    printf("Type 3 average run time: %d\n", total_time_for_io/count_io);
} // close print_stats_by_type


/******************************************************************************
Read the job from the file and create the job
/******************************************************************************/
void load_processes(char *fileName, Process_queue *queue, Process_queue *high_queue, Process_queue *med_queue, Process_queue *low_queue) {
    char *buffer;
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("%s\n", "Error opening the file");
        exit(1);
    } // if
    
    assert(fp != NULL);
    buffer = (char*) malloc(sizeof(LENGTH));
    
    while (fgets(buffer, LENGTH, fp) != NULL) {
        bool result = process_line(buffer);
        if (result) {
            create_process(queue, high_queue, med_queue, low_queue);
        }
    }
    printf("%s\n\n", "Process loading done!");
} // close load processes


/******************************************************************************
does string parsing
/******************************************************************************/
bool process_line(char *line) {
    size_t len = strlen(line);
    line[len -1] = '\0';
    bool result = false;
    if (line[0] != '\0') {
        char delim[] = " ";
        _thread_name = strdup(strtok(line, delim));
        _thread_type = strdup(strtok(NULL, delim));
        _priority = atoi(strtok(NULL, delim));
        _thread_length = atoi(strtok(NULL, delim));
        char *i =strtok(NULL, delim);
        _odds_of_IO = atoi(i);
        result = true;
    }
    return result;
} // close process_line


/******************************************************************************
Creates a new process
/******************************************************************************/
bool create_process(Process_queue *queue, Process_queue *high_queue, Process_queue *med_queue, Process_queue *low_queue) {
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
    
    // For Priority RR
    if (process->priority == 0) {
        enqueue_process(high_queue, process);
    } else if (process->priority == 1) {
        enqueue_process(med_queue, process);
    } else {
        enqueue_process(low_queue, process);
    }
    
    return true;
} // close create_process


/******************************************************************************
 Creates a single process node with pointer to data and next
******************************************************************************/
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


/******************************************************************************
 Initializes a process queue. Makes an empty queue
 ******************************************************************************/
Process_queue *initialize_process_queue(Process_queue *q) {
    q = (Process_queue*) malloc(sizeof(Process_queue));
    
    assert(q != NULL);
    q->front = q->back = NULL;
    q->size = 0;
    return q;
} // close initialize_process_queue


/******************************************************************************
 Equeues a process
/******************************************************************************/
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


/******************************************************************************
 Dequeues a process
 ******************************************************************************/
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


/******************************************************************************
Generate a time slice using the given parameter
/******************************************************************************/
int generate_time_slice(int len) {
    return rand() % len + 1;
} // close generate_time_slice


/******************************************************************************
generate a random number to check for IO interruptions
/******************************************************************************/
int generate_random_number() {
    srand(time(NULL));
    return rand() % 110;
} // close generate_random_word


/******************************************************************************
Helper function that does the checking by returning whether there is IO or nah
/******************************************************************************/
bool do_io(int io_odds) {
    int rand_num = generate_random_number();
    return rand_num > io_odds;
} // close do_io

