#ifndef TASK_H
#define TASK_H
#pragma once
#include "../include/globals.h"

class Task {
private:
    std::string title;
    std::string description;
    std::string dueDate;
    Status status;
    Priority priority; 
    Type type = Type::Task;
public:
    Task(const std::string &title, const std::string &description, const std::string &dueDate, const Status &status, const Priority &priority) :
        title(title), description(description), dueDate(dueDate), status(status), priority(priority) {}

    // Getters
    std::string getTitle() const { return this->title; }
    std::string getDescription() const { return this->description; }
    std::string getDueDate() const { return this->dueDate; }
    Status getStatus() const { return this->status; }
    Priority getPriority() const { return this->priority; }

    // Setters
    void setTitle(const std::string &newTitle) { this->title = newTitle; }
    void setDescription(const std::string &newDescription) { this->description
        = newDescription; }
    void setDueDate(const std::string &newDueDate) { this->dueDate =
         newDueDate; }
    void setStatus(const Status &newStatus) { this->status = newStatus; }
    void setPriority(const Priority &newPriority) { this->priority =
        newPriority; }
};


#endif // TASK_H
