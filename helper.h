#define LENGTH 15
#define PROCESS_SIZE 50 


// Global variables
int _priority;
int _odds_of_IO;
char _thread_name[20];
char _thread_type[15];
int _thread_length;
Process_queue queue;


// structs
typedef struct process {
	int priority;
	char thread_name[20];
	int thread_length;
	char thread_type[15];
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


// Queue management functions
Process_node *create_process_node(Process *);
void initialize_process_queue(Process_queue *);
void enqueue_process(Process_queue *, Process *);


// Process loading function
void load_processes(char *);
bool process_line(char *);
bool create_process();