#include <algorithm>
#include <bitset>
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#define TASKLIMIT 100

enum {
    NOT_COMPLETED,
    COMPLETED,
};

struct task {
    std::string taskName;
    int id;
    int progress;
};

std::vector<struct task *> TaskList(TASKLIMIT);
std::bitset<TASKLIMIT> IdRecords{0};

int add(std::string desc, int status) {
    if (IdRecords.all()) {
        std::cerr << "Task Limit Reached" << std::endl;
        return -1;
    }
    int id;
    for (int i = 0; i < TASKLIMIT; i++) {
        if (!IdRecords[i]) {
            id = i;
            break;
        }
    }
    IdRecords.set(size_t(id), true);
    struct task *newTask = (struct task *)malloc(sizeof(struct task));
    if (newTask == NULL) {
        std::cerr << "Error creating new task" << std::endl;
        return -1;
    }
    newTask->id = id;
    newTask->taskName = desc;
    newTask->progress = status;
    TaskList[id] = newTask;
    std::cout << "Created Task with\nID: " << id << "\nName: " << desc
              << "\nStatus: " << status << std::endl;
    return id;
}

int update(int id, std::string newDesc) {
    if (!IdRecords[id]) {
        std::cerr << "Task does not exist with ID " << id << std::endl;
        return -1;
    }
    TaskList[id]->taskName = newDesc;
    return id;
}

int update(int id, int status) {
    if (!IdRecords[id]) {
        std::cerr << "Task does not exist with ID " << id << std::endl;
        return -1;
    }
    TaskList[id]->progress = id;
    return id;
}

int deleteTask(int id) {
    if (!IdRecords[id]) {
        std::cerr << "Task does not exist with ID " << id << std::endl;
        return -1;
    }
    free(TaskList[id]);
    TaskList[id] = NULL;
    IdRecords.set(size_t(id), false);
    return id;
}

void list() {
    if (IdRecords.none()) {
        std::cout << "There are no tasks currently" << std::endl;
        return;
    }
    std::cout << "ID\t\tNAME\t\tPROGRESS\n";
    for (int i = 0; i < TASKLIMIT; i++) {
        if (IdRecords[i]) {
            std::cout << TaskList[i]->id << "\t\t" << TaskList[i]->taskName
                      << "\t\t"
                      << ((TaskList[i]->progress == NOT_COMPLETED)
                              ? "Not Completed"
                              : "Completed")
                      << "\n";
        }
    }
    std::cout << std::flush;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        // replace with help
        std::cerr << "Pass arguments" << std::endl;
        return 1;
    }
    if (argc == 2) {
        if (argv[1] == std::string("list")) {
            // list
            list();
            return 1;
        } else {
            // replace with help
            std::cerr << "wrong arguments\n";
            return 1;
        }
    }
    if (argc > 2) {
        if (argv[1] == std::string("add")) {
            std::string desc(argv[2]);
            int status = 0;
            if (argc == 4) {
                std::string str_status(argv[3]);
                if (str_status.length() == 1 && isdigit(str_status[0])) {
                    status = str_status[0] - '0';
                }
            }
            return (add(desc, status) == -1) ? 1 : 0;
        } else if (argv[1] == std::string("update")) {
            if (argc == 4) {
                std::string str_id(argv[2]);
                if (!std::all_of(str_id.begin(), str_id.end(), ::isdigit)) {
                    // error wrong format
                    std::cerr << "wrong format\n";
                    return 1;
                }
                int id = std::stoi(str_id);
                std::string desc(argv[3]);
                return (update(id, desc) == -1) ? 1 : 0;
            } else {
                // error wrong format
                std::cerr << "wrong format\n";
                return 1;
            }
        } else if (argv[1] == std::string("delete")) {
            std::string str_id(argv[2]);
            if (!std::all_of(str_id.begin(), str_id.end(), ::isdigit)) {
                // error wrong format
                std::cerr << "wrong format\n";
                return 1;
            }
            int id = std::stoi(str_id);
            return (deleteTask(id) == -1) ? 1 : 0;
        }
    }
    return 0;
}
