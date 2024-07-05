# Task Management System

This project implements a task management system with functionalities to manage tasks and their priorities. Tasks can have subtasks, forming a tree structure. The main operations include adding, removing, and changing task priorities, as well as printing tasks in different formats.

## Contributors

- Arman Akhoundy ([ArmanX5](https://www.github.com/ArmanX5))
- Setareh Hashempour ([setarehashempour](https://github.com/setarehashempour))

## Code Overview

The project consists of two main components:

1. **Task**: Represents an individual task.
2. **TaskManager**: Manages a collection of tasks.

### Task Class

The `Task` class represents a task with an ID, priority, and potential subtasks. It includes methods to get and set task properties and manage subtasks.

#### Methods

- **Task(int id, int priority)**:
  Constructor to initialize a task with a given ID and priority.
  
- **int get_priority()**:
  Returns the task's priority.
  - Time complexity: O(1)
  
- **void set_priority(int new_priority)**:
  Sets a new priority for the task.
  - Time complexity: O(1)
  
- **int get_id()**:
  Returns the task's ID.
  - Time complexity: O(1)
  
- **void set_id(int id)**:
  Sets a new ID for the task.
  - Time complexity: O(1)
  
- **Task\* get_right()**:
  Returns the right subtask.
  - Time complexity: O(1)
  
- **void set_right(Task\* right)**:
  Sets the right subtask.
  - Time complexity: O(1)
  
- **Task\* get_left()**:
  Returns the left subtask.
  - Time complexity: O(1)
  
- **void set_left(Task\* left)**:
  Sets the left subtask.
  - Time complexity: O(1)
  
- **Task\* get_parent()**:
  Returns the parent task.
  - Time complexity: O(1)
  
- **void set_parent(Task\* parent)**:
  Sets the parent task.
  - Time complexity: O(1)
  
- **void set_subtask(Task\* subtask)**:
  Adds a subtask to this task. If the subtask is already assigned to another parent, it is first removed from its current parent. The new subtask is assigned to either the left or right position based on existing subtasks and their IDs.
  - Time complexity: O(1)
  
- **void delete_task()**:
  Deletes the task and its subtasks by setting left and right pointers to `nullptr` and then deleting the task itself.
  - Time complexity: O(1)
  
- **void remove_subtask(Task\* subtask)**:
  Removes a specific subtask. If the left subtask is removed and there is a right subtask, the right subtask is moved to the left.
  - Time complexity: O(1)
  
- **void print_task()**:
  Prints the task and its subtasks in a specified format (task ID followed by its subtasks within brackets).
  - Time complexity: O(n), where n is the number of subtasks
  
- **void print_task_in_tree(const string& prefix = "", bool is_left = true)**:
  Prints the task and its subtasks in a tree format using ASCII characters to represent branches.
  - Time complexity: O(n), where n is the number of subtasks

### TaskManager Class

The `TaskManager` class manages a collection of tasks, allowing for operations such as adding, removing, and changing task priorities. Tasks are maintained in a heap to efficiently manage task priorities.

#### Methods

- **void add_task(Task\* task)**:
  Adds a task to the task manager. If the task already exists, it does not add it again. The task is inserted into the heap and the list of root tasks, maintaining heap properties.
  - Time complexity: O(log n), due to heap operations
  
- **Task\* extract_max(vector<Task\*>& heap)**:
  Removes and returns the highest priority task from the heap. The last task in the heap is moved to the root, and the heap is restructured.
  - Time complexity: O(log n), due to heap operations
  
- **Task\* peek_max(vector<Task\*>& heap)**:
  Returns the highest priority task without removing it.
  - Time complexity: O(1)
  
- **bool isEmpty()**:
  Checks if the task queue is empty.
  - Time complexity: O(1)
  
- **void print_tasks_by_priority()**:
  Prints tasks in order of their priority by extracting the max from a temporary heap until it is empty.
  - Time complexity: O(n log n), due to extracting max for all tasks
  
- **void remove_task(int id)**:
  Removes a task and its subtasks from the task manager. It first removes subtasks recursively, then removes the task itself and re-heapifies the remaining tasks.
  - Time complexity: O(n log n), as it may involve heapifying the remaining tasks
  
- **void change_task_priority(int id, int new_priority)**:
  Changes the priority of a task. The task is located and its priority is updated, followed by re-heapifying to maintain heap properties.
  - Time complexity: O(log n), due to re-heapifying
  
- **Task\* get_task(int id)**:
  Returns the task with the given ID.
  - Time complexity: O(n)
  
- **void print_all_tasks()**:
  Prints all tasks and their subtasks.
  - Time complexity: O(n), where n is the number of root tasks
  
- **void print_in_tree_format()**:
  Prints all tasks and their subtasks in a tree format.
  - Time complexity: O(n), where n is the number of root tasks
  
- **void add_subtask(int parent_id, int subtask_id)**:
  Adds a subtask to a parent task. If the parent task already has two subtasks or if the parent and subtask IDs are the same, it does not add the subtask. It also removes the subtask from the root tasks if necessary.
  - Time complexity: O(n log n), due to potential heap operations

## Time Complexity

### Task Class Operations

- **Getters and setters**: O(1)
- **set_subtask**: O(1)
- **delete_task**: O(1)
- **remove_subtask**: O(1)
- **print_task**: O(n), where n is the number of subtasks
- **print_task_in_tree**: O(n), where n is the number of subtasks

### TaskManager Class Operations

- **add_task**: O(log n), due to heap operations
- **extract_max**: O(log n), due to heap operations
- **peek_max**: O(1)
- **isEmpty**: O(1)
- **print_tasks_by_priority**: O(n log n), due to extracting max for all tasks
- **remove_task**: O(n log n), as it may involve heapifying the remaining tasks
- **change_task_priority**: O(log n), due to re-heapifying
- **get_task**: O(n)
- **print_all_tasks**: O(n), where n is the number of root tasks
- **print_in_tree_format**: O(n), where n is the number of root tasks
- **add_subtask**: O(n log n), due to potential heap operations

This project efficiently manages task priorities and relationships using a combination of heap operations and tree structures, ensuring that tasks can be added, removed, and queried effectively.
