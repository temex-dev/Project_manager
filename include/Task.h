#ifndef TASK_H
#define TASK_H
#pragma once
#include "../include/globals.h"

class Task {
private:
    std::string title;
    std::string description;
    std::string dueDate;
    std::string projectTitle;
    Status status;
    Priority priority;
    Type type = Type::Task;
public:
    Task(const std::string &title, const std::string &description, const std::string &dueDate, const Status &status, const Priority &priority, const std::string &projectTitle = "") :
        title(title), description(description), dueDate(dueDate), projectTitle(projectTitle), status(status), priority(priority) {}

// Getters
    std::string getTitle() const { return this->title; }
    std::string getDescription() const { return this->description; }
    std::string getDueDate() const { return this->dueDate; }
    std::string getProjectTitle() const { return this->projectTitle; }
    Status getStatus() const { return this->status; }
    Priority getPriority() const { return this->priority; }
    Type getType() const { return this->type; }

// Setters
    void setTitle(const std::string &newTitle) { this->title = newTitle; }
    void setDescription(const std::string &newDescription) { this->description
        = newDescription; }
    void setDueDate(const std::string &newDueDate) { this->dueDate =
         newDueDate; }
    void setProjectTitle(const std::string &newProjectTitle) { this->projectTitle = newProjectTitle; };
    void setStatus(const Status &newStatus) { this->status = newStatus; }
    void setPriority(const Priority &newPriority) { this->priority =
        newPriority; }

    static std::string jsonEscape(const std::string &value) {
        std::string escaped;
        escaped.reserve(value.size());
        for (char c : value) {
            switch (c) {
                case '\"': escaped += "\\\""; break;
                case '\\': escaped += "\\\\"; break;
                case '\b': escaped += "\\b"; break;
                case '\f': escaped += "\\f"; break;
                case '\n': escaped += "\\n"; break;
                case '\r': escaped += "\\r"; break;
                case '\t': escaped += "\\t"; break;
                default: escaped += c; break;
            }
        }
        return escaped;
    }

    std::string toJson(const std::optional<std::string> &projectTitle = std::nullopt) const {
        std::string json = "{";
        json += "\"title\":\"" + jsonEscape(title) + "\",";
        json += "\"description\":\"" + jsonEscape(description) + "\",";
        json += "\"dueDate\":\"" + jsonEscape(dueDate) + "\",";
        json += "\"status\":\"" + statusStr.at(status) + "\",";
        json += "\"priority\":\"" + priorityStr.at(priority) + "\"";
        if (projectTitle.has_value()) {
            json += ",\"projectTitle\":\"" + jsonEscape(projectTitle.value()) + "\"";
        }
        json += "}";
        return json;
    }

};


#endif // TASK_H
