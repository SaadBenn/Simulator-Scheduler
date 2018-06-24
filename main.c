#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>
#include "helper.h"

int main(int argc, char const *argv[]) {

	// load the processes first
	char *fileName = "processes.txt";

	initialize_process_queue(queue);
	load_processes(fileName);
	return 0;
} // close main


void load_processes(char *fileName) {
	char *buffer;
	FILE *fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("%s\n", "Error opening the file");
		exit(1);
	} // if

	assert(fp != NULL);
	buffer = (char*) malloc(sizeof(LENGTH));

	while (fgets(buffer, LENGTH, fp)) {
		process_line(buffer);
		create_process();
	}
	printf("%s\n", "Process loading done!");
} // close load processes


bool process_line(char *line) {
	char delim[] = " ";
	_thread_name = strtok(line, delim);
	_thread_type = strtok(NULL, delim);
	_priority = strtok(NULL, delim);
	_thread_length = strtok(NULL, delim);
	_odds_of_IO = strtok(NULL, delim);
	return true;
} // close process_line


bool create_process() {
	Process *process = (Process*) malloc(sizeof(PROCESS_SIZE));
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
	Process_node *node = (Process_node*) malloc(sizeof(Process_node));
	if (node == NULL){
		error("out of memory");
	}

	assert(node != NULL);
	node->data = p;
	node->next = NULL;
	return node;
} // close create_process_node


/**
 * Initializes a process queue. Makes an empty queue
 */
void initialize_process_queue(Process_queue *q) {
	q = (Process_queue*) malloc(sizeof(Process_queue));
	
	assert(q != NULL);
	q->front = q->back = NULL;
	q->size = 0;
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
