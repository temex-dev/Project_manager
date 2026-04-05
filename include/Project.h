#ifndef PROJECT_H
#define PROJECT_H
#pragma once
#include "../include/globals.h"
#include "../include/Task.h"

class Project {
private:
    std::string title;
    std::vector<Task> tasks;
    Type type = Type::Project;
public:
    void addTask(const Task &task) {
        tasks.push_back(task);
    }

    const std::vector<Task> &getTasks() const {
        return this->tasks;
    }

    void clearTasks() {
        tasks.clear();
    }

    std::string getTitle() const {
        return this->title;
    }
};

#endif // PROJECT_H
