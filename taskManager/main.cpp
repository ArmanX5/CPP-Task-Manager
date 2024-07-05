// A Data Structure and Algorithm Project
// Contributors: Arman Akhoundy, Setareh Hashempour

#include <iostream>
#include <vector>
using namespace std;

struct Task {
    int id;
    int priority;
    Task* right;
    Task* left;
    Task* parent;

    // Constructor
    Task(int id, int priority) {
        this->id = id;
        this->priority = priority;
        this->right = nullptr;
        this->left = nullptr;
        this->parent = nullptr;
    }

    // Get priority
    int get_priority() { return this->priority; }

    // Set priority
    void set_priority(int new_priority) { this->priority = new_priority; }

    // Get id
    int get_id() { return this->id; }

    // Set id
    void set_id(int id) { this->id = id; }

    // Get right subtask
    Task* get_right() { return this->right; }

    // Set right subtask
    void set_right(Task* right) { this->right = right; }

    // Get left subtask
    Task* get_left() { return this->left; }

    // Set left subtask
    void set_left(Task* left) { this->left = left; }

    // Get parent task
    Task* get_parent() { return this->parent; }

    // Set parent task
    void set_parent(Task* parent) { this->parent = parent; }

    // Add subtask
    void set_subtask(Task* subtask) {
        if (subtask->get_parent() != nullptr) {
            subtask->get_parent()->remove_subtask(subtask);
        }

        if (this->get_left() == nullptr) {
            this->set_left(subtask);
        }
        else if (this->get_right() == nullptr) {
            if (subtask->get_id() < this->get_left()->get_id()) {
                this->set_right(this->get_left());
                this->set_left(subtask);
            } else {
                this->set_right(subtask);
            }
        }
        subtask->set_parent(this);
    }

    // Delete task
    void delete_task() {
        this->set_left(nullptr);
        this->set_right(nullptr);
        delete this;
    }

    // Remove a specific subtask
    void remove_subtask(Task* subtask) {
        if (this->get_left() == subtask) {
            if (this->get_right() == nullptr) {
                this->set_left(nullptr);
            } else {
                this->set_left(this->get_right());
                this->get_right()->set_parent(this->get_parent());
                this->set_right(nullptr);
            }
        } else if (this->get_right() == subtask) {
            this->set_right(nullptr);
        }
        subtask->set_parent(nullptr);
    }

    // Print task with its subtasks in the specified format
    void print_task() {
        cout << this->id;
        if (left != nullptr || right != nullptr) {
            cout << " [";
            if (left != nullptr) left->print_task();
            if (right != nullptr) {
                if (left != nullptr) cout << " ";
                right->print_task();
            }
            cout << "]";
        }
    }
    
    // Print task with its subtasks in tree format
    void print_task_in_tree(const string& prefix = "", bool is_left = true) {
        cout << prefix;

        cout << (is_left ? "├──" : "└──" );

        cout << this->id << endl;

        if (left && right) {
            left->print_task_in_tree(prefix + (is_left ? "│   " : "    "), true);
            right->print_task_in_tree(prefix + (is_left ? "│   " : "    "), false);
        } else if (left) {
            left->print_task_in_tree(prefix + (is_left ? "│   " : "    "), false);
        }
    }
};

class TaskManager {
private:
    vector<Task*> tasks;
    vector<Task*> rootTasks;

    // Helper function to swap two tasks in the heap
    void swap(vector<Task*>& heap, int i, int j) {
        Task* temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    // Helper functions for heap operations
    void heapify_up(vector<Task*>& heap, int index) {
        if (index == 0) return; // If at root, done
        int parent = (index - 1) / 2;
        if (heap[index]->get_priority() > heap[parent]->get_priority() ||
            (heap[index]->get_priority() == heap[parent]->get_priority() && heap[index]->get_id() < heap[parent]->get_id())) {
            swap(heap, index, parent);
            heapify_up(heap, parent);
        }
    }

    void heapify_down(vector<Task*>& heap, int index) {
        int size = heap.size();
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && (heap[left]->get_priority() > heap[largest]->get_priority() ||
                            (heap[left]->get_priority() == heap[largest]->get_priority() && heap[left]->get_id() < heap[largest]->get_id()))) {
            largest = left;
        }
        if (right < size && (heap[right]->get_priority() > heap[largest]->get_priority() ||
                             (heap[right]->get_priority() == heap[largest]->get_priority() && heap[right]->get_id() < heap[largest]->get_id()))) {
            largest = right;
        }
        if (largest != index) {
            swap(heap, index, largest);
            heapify_down(heap, largest);
        }
    }

    // Helper function to find the insertion index for a new task
    int findInsertionIndex(vector<Task*>& vec, Task* task) {
        int low = 0;
        int high = vec.size();

        while (low < high) {
            int mid = (low + high) / 2;
            if (vec[mid]->id < task->id) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }

        return low;
    }

public:
    // Insert task into the heap
    void add_task(Task* task) {
        // if the task is already in tasks, don't add it again
        for (int i = 0; i < tasks.size(); i++) {
            if (tasks[i]->get_id() == task->get_id()) {
                cout << "Task " << task->get_id() << " already exists." << endl;
                return;
            }
        }
        tasks.push_back(task);
        rootTasks.insert(rootTasks.begin() + findInsertionIndex(rootTasks, task), task);
        heapify_up(tasks, tasks.size() - 1);
    }

    // Get and remove the highest priority task
    Task* extract_max(vector<Task*>& heap) {
        if (heap.empty()) {return nullptr;}

        Task* max_task = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            heapify_down(heap, 0);
        }

        return max_task;
    }

    // Get the highest priority task without removing it
    Task* peek_max(vector<Task*>& heap) {
        if (heap.empty()) {return nullptr;}
        return heap[0];
    }

    // Check if the queue is empty
    bool isEmpty() {
        return tasks.empty();
    }

    // Print tasks according to their priority
    void print_tasks_by_priority() {
        vector<Task*> temp_heap = tasks;

        while (!temp_heap.empty()) {
            cout << extract_max(temp_heap)->id << " ";
        }
        cout << endl;
    }

    // Remove task with given id and all of its subtasks from the queue
    void remove_task(int id) {
        for (int i = 0; i < tasks.size(); i++) {
            if (tasks[i]->get_id() == id) {
                // Remove subtasks first
                if (tasks[i]->get_left() != nullptr) {
                    remove_task(tasks[i]->get_left()->get_id());
                }
                if (tasks[i]->get_right() != nullptr) {
                    remove_task(tasks[i]->get_right()->get_id());
                }

                // Find and remove the task from its parent's children in Tasks
                for (int j = 0; j < tasks.size(); j++) {
                    if ((tasks[j]->get_left() != nullptr) && (tasks[j]->get_left()->get_id() == id)) {
                        tasks[j]->remove_subtask(tasks[j]->get_left());
                        break;
                    }
                    else if ((tasks[j]->get_right() != nullptr) && (tasks[j]->get_right()->get_id() == id)){
                        tasks[j]->remove_subtask(tasks[j]->get_right());
                        break;
                    }
                }

                // Delete the task
                tasks[i]->delete_task();
                tasks.erase(tasks.begin() + i);
                break;
            }
        }

        // Find and remove the task from RootTasks
        for (int i = 0; i < rootTasks.size(); i++) {
            if (rootTasks[i]->get_id() == id) {
                rootTasks.erase(rootTasks.begin() + i);
                break;
            }
        }

        // Heapify all tasks after removal to maintain the heap property
        for (int i = tasks.size() / 2 - 1; i >= 0; i--) {
            heapify_down(tasks, i);
        }
    }

    // Change task priority in the queue
    void change_task_priority(int id, int new_priority) {
        if (get_task(id) == nullptr) {
            cout << "Task " << id << " does not exist." << endl;
            return;
        }
        for (int i = 0; i < tasks.size(); i++) {
            if (tasks[i]->get_id() == id) {
                tasks[i]->set_priority(new_priority);
                // Re-heapify to maintain the heap property
                heapify_up(tasks, i);
                heapify_down(tasks, i);
                break;
            }
        }
    }

    // Get task
    Task* get_task(int id) {
        for (int i = 0; i < tasks.size(); i++) {
            if (tasks[i]->get_id() == id) {
                return tasks[i];
            }
        }
        return nullptr;
    }

    // Print all tasks and their subtasks
    void print_all_tasks() {
        for(int i = 0; i < rootTasks.size(); i++){
            rootTasks[i]->print_task();
            cout << " ";
        }
        cout << endl;
    }

    // Print all tasks and their subtasks in tree shape
    void print_in_tree_format() {
        for(int i = 0; i < rootTasks.size(); i++){
            rootTasks[i]->print_task_in_tree();
            cout << endl;
        }
    }

    // Add subtask and remove from rootTasks if necessary
    void add_subtask(int parent_id, int subtask_id) {
        Task* parent_task = get_task(parent_id);
        Task* subtask = get_task(subtask_id);

        if (parent_id == subtask_id) {
            cout << "Parent and subtask cannot be the same." << endl;
            return;
        }
        if ((parent_task->get_left() != nullptr) && (parent_task->get_right() != nullptr)) {
            cout << "Parent " << parent_id << " already has two subtasks." << endl;
            return;
        }

        // Add the subtask to the parent
        parent_task->set_subtask(subtask);
        // Remove the subtask from rootTasks if it exists there
        for (int i = 0; i < rootTasks.size(); i++) {
            if (rootTasks[i]->get_id() == subtask_id) {
                rootTasks.erase(rootTasks.begin() + i);
                break;
            }
        }
    }
};


int main() {
    int opt;
    int input_1;
    int input_2;

    TaskManager tm;
    Task* task = nullptr;

    while (1) {
        cin >> opt;
        switch (opt) {
        case 0: // End of program
            break;

        case 1: // Add new task
            cin >> input_1 >> input_2; // id, priority
            if (input_2 < 0) {
                cout << "Priority cannot be negative." << endl;
                break;
            }
            task = new Task(input_1, input_2);
            tm.add_task(task);
            break;

        case 2: // Add new child
            cin >> input_1 >> input_2; // parent id, child id
            tm.add_subtask(input_1, input_2);
            break;

        case 3: // Delete task and all its children
            cin >> input_1; // id
            tm.remove_task(input_1);
            break;

        case 4: // Change priority of task
            cin >> input_1 >> input_2; // id, new priority
            if (input_2 < 0) {
                cout << "Priority cannot be negative." << endl;
                break;
            }
            tm.change_task_priority(input_1, input_2);
            break;

        case 5: // Print all tasks and all its children
            tm.print_all_tasks();
            break;

        case 6: // Print all tasks according to their priority
            tm.print_tasks_by_priority();
            break;

        case 7: // Print all tasks and all its children in tree shape
            tm.print_in_tree_format();
            break;

        default:
            cout << "Invalid Option";
            break;
        }
        if (opt == 0) break;
    }

    return 0;
}
