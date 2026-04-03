#ifndef PROJECT_H
#define PROJECT_H
#pragma once
#include "../include/globals.h"
#include "../include/Task.h"

class Project {
private:
    std::vector<Task> tasks;

public:
    void addTask(const Task &task) {
        tasks.push_back(task);
    }

    const std::vector<Task> &getTasks() const {
        return tasks;
    }

    void clearTasks() {
        tasks.clear();
    }
};

#endif // PROJECT_H
