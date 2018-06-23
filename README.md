# Simulator-Scheduler
Simulator that simulates different scheduling algorithms.

The simulator has four different scheduling algorithms.
1. Pure round-robin. A first-come-first-serve queue. This scheduler does not use priority.
2. Priority round-robin. A multi-level queue, where priority 1 tasks run first, in a round-robin fashion...
3. Shortest job first, as described in class, and the textbook. This scheduler does not use priority.
4. Shortest time to completion first, as described in class, and the textbook. This scheduler does not use priority.

The scheduling algorithms are time-sharing algorithms, but will be non-premptive - a running process can not be preempted. The process will run for an entire timeslice, except for the case that it quits early in the case that it ‘yields the processor’ because it is waiting for I/O.
