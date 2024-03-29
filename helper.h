#define LENGTH 64
#define PROCESS_SIZE 50
#define TIME_SLICE 5

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

// queues
Process_queue *queue;

// queues for priority RR
Process_queue *high_queue;
Process_queue *med_queue;
Process_queue *low_queue;

// Queue management functions
Process_node *create_process_node(Process *);
Process_queue *initialize_process_queue(Process_queue *);
void enqueue_process(Process_queue *, Process *);
void dequeue_process(Process_queue *);
bool is_empty(Process_queue *);

// Process loading function
void load_processes(char *, Process_queue *, Process_queue *, Process_queue *, Process_queue *);
bool process_line(char *);
bool create_process(Process_queue *, Process_queue *, Process_queue *, Process_queue *);

// scheduler management functions
int generate_random_number();
void process_fcfs(Process_queue *, bool);
void process_sjf(Process_queue *);
void process_srtf(Process_queue *);

// Other helper functions
void define_global_var();
void print_stats_by_priority();
void print_stats_by_type();
bool do_io(int);
int generate_time_slice(int);

void process_priority_round_robin(Process_queue *, Process_queue *, Process_queue *);
void process_high_priority(Process_queue *);

// sorting functions
void insert_min_to_rear(Process_queue *, int);
void sort_queue(Process_queue *);
int min_finder(Process_queue *, int);
