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
    Project() = default;
    Project(const std::string &title) : title(title) {}

    void addTask(const Task &task) {
        tasks.push_back(task);
    }

    const std::vector<Task> &getTasks() const {
        return this->tasks;
    }

    void clearTasks() {
        tasks.clear();
    }

    void setTitle(const std::string &newTitle) {
        this->title = newTitle;
    }

    static std::string jsonEscape(const std::string &value) {
        std::string escaped;
        escaped.reserve(value.size());
        for (char c : value) {
            switch (c) {
                case '"': escaped += "\\\""; break;
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

    std::string toJson() const {
        return "{\"title\":\"" + jsonEscape(title) + "\"}";
    }

    std::string getTitle() const {
        return this->title;
    }
};

#endif // PROJECT_H
