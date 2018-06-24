#define LENGTH 64
#define PROCESS_SIZE 50 


// Global variables
int _priority;
int _odds_of_IO;
char *_thread_name;
char *_thread_type;
int _thread_length;


// structs
typedef struct process {
	int priority;
	char *thread_name;
	int thread_length;
	char *thread_type;
	int odds_of_IO;	
} Process;


typedef struct process_node {
	struct process *data;
	struct process_node *next;
} Process_node;


typedef struct process_queue{
	int size;
	struct process_node *front;
	struct process_node *back;
} Process_queue;

Process_queue *queue;

// Queue management functions
Process_node *create_process_node(Process *);
Process_queue *initialize_process_queue(Process_queue *);
void enqueue_process(Process_queue *, Process *);
void dequeue_process(Process_queue *);

// Process loading function
void load_processes(char *, Process_queue *);
bool process_line(char *);
bool create_process();

// scheduler management functions
int generate_random_word(int len);
void process_fcfs(Process_queue *);
