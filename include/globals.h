#ifndef GLOBALS_H
#define GLOBALS_H
#pragma once

#include <iostream> // IWYU pragma: keep
#include <string>
#include <optional> // IWYU pragma: keep
#include <map>
#include <vector> // IWYU pragma: keep
#include <fstream>
#include <filesystem> // IWYU pragma: keep
#include <json/json.h>

enum class Color {
    Black, Red, Green, Yellow, Blue, Magenta, Cyan, White,
    BrightRed, BrightGreen, BrightYellow, BrightBlue
};
enum class Style {
    Bold = 1, Dim, Italic, Underline, Strikethrough
};
enum class Type {
    Project, Task
};
enum class Action {
    Create, Edit, Delete
};
enum class Status {
    Todo, InProgress, Completed
};
enum class Priority {
    Low, Medium, High
};

struct ColorPair{
    Color fg;
    Color bg;
};

const std::map<int, std::string> test = {
    {1, "One"},
    {2, "Two"},
    {3, "Three"}
};

const std::map<Priority, ColorPair> priorityColors = {
    {Priority::Low, {Color::Magenta, Color::Green}},
    {Priority::Medium, {Color::Black, Color::Yellow}},
    {Priority::High, {Color::White, Color::Red}}
};
const std::map<Status, ColorPair> statusColor = {
    {Status::Todo, {Color::Black, Color::Yellow}},
    {Status::InProgress, {Color::Cyan, Color::Blue}},
    {Status::Completed, {Color::Magenta, Color::Green}}
};

const std::map<std::string, Priority> strPriority = {
    {"Low", Priority::Low},
    {"Medium", Priority::Medium},
    {"High", Priority::High}
};
const std::map<std::string, Status> strStatus = {
    {"Todo", Status::Todo},
    {"InProgress", Status::InProgress},
    {"Completed", Status::Completed}
};

const std::map<Priority, std::string> priorityStr = {
    {Priority::Low, "Low"},
    {Priority::Medium, "Medium"},
    {Priority::High, "High"}
};
const std::map<Status, std::string> statusStr = {
    {Status::Todo, "Todo"},
    {Status::InProgress, "InProgress"},
    {Status::Completed, "Completed"}
};
const std::map<Type, std::string> typeStr = {
    {Type::Project, "Project"},
    {Type::Task, "Task"}
};

inline Json::Value load_projects() {
    std::ifstream projects_file(DATA_DIR "/projects.json", std::ifstream::binary);
    Json::Value projects(Json::arrayValue);
    if (!projects_file.is_open()) {
        return projects;
    }

    std::string content((std::istreambuf_iterator<char>(projects_file)), std::istreambuf_iterator<char>());
    if (content.find_first_not_of(" \t\r\n") == std::string::npos) {
        return projects;
    }

    Json::CharReaderBuilder readerBuilder;
    readerBuilder["collectComments"] = false;
    std::string errors;
    std::istringstream stream(content);
    if (!Json::parseFromStream(readerBuilder, stream, &projects, &errors) || !projects.isArray()) {
        return Json::Value(Json::arrayValue);
    }

    return projects;
}

inline Json::Value load_tasks() {
    std::ifstream tasks_file(DATA_DIR "/tasks.json", std::ifstream::binary);
    Json::Value tasks(Json::arrayValue);
    if (!tasks_file.is_open()) {
        return tasks;
    }

    std::string content((std::istreambuf_iterator<char>(tasks_file)), std::istreambuf_iterator<char>());
    if (content.find_first_not_of(" \t\r\n") == std::string::npos) {
        return tasks;
    }

    Json::CharReaderBuilder readerBuilder;
    readerBuilder["collectComments"] = false;
    std::string errors;
    std::istringstream stream(content);
    if (!Json::parseFromStream(readerBuilder, stream, &tasks, &errors) || !tasks.isArray()) {
        return Json::Value(Json::arrayValue);
    }

    return tasks;
}
#endif // GLOBALS_H
