# C++ Task Manager

This code implements a task manager that allows you to manage tasks with priorities and subtasks.

## Features

* Add new tasks with priorities (priority cannot be negative)
* Add subtasks to existing tasks (a task can only have up to two subtasks)
* Delete tasks and all of its subtasks
* Change the priority of an existing task
* Print all tasks and their subtasks (flat format)
* Print all tasks according to their priority (highest to lowest)
* Print all tasks and their subtasks in a tree format

## Usage

1. Compile the code using a C++11 compiler (e.g., g++).
2. Run the executable.
3. The program will prompt you to enter commands. Valid commands are:

* `0`: Exit the program
* `1`: Add a new task (format: `1 id priority`)
* `2`: Add a subtask to an existing task (format: `2 parent_id child_id`)
* `3`: Delete a task and all its subtasks (format: `3 id`)
* `4`: Change the priority of a task (format: `4 id new_priority`)
* `5`: Print all tasks and their subtasks (flat format)
* `6`: Print all tasks according to their priority (highest to lowest)
* `7`: Print all tasks and their subtasks in a tree format

### Example

```
1 100 1   // Add a task with id 100 and priority 1
2 100 200 // Add a subtask with id 200 to task 100
3 200     // Delete task 200 and its subtasks
5         // Print all tasks
1 300 2   // Add another task with id 300 and priority 2
6         // Print all tasks by priority
7         // Print all tasks in tree format
0         // Exit the program
```

## Note

* The program uses a min-heap to store tasks for efficient priority retrieval.
* Tasks are identified by their unique IDs.

## Contributors

* Arman Akhoundy ([ArmanX5](https://github.com/ArmanX5))
* Setareh Hashempour ([setarehashempour](https://github.com/setarehashempour))
