#ifndef TERMINAL_H
#define TERMINAL_H
#pragma once
#include "../include/globals.h"
#include "../include/Task.h"
#include "../include/Project.h"

class Terminal {
private:
    static unsigned int toFgCode(const Color &c);
    static unsigned int toBgCode(const Color &c);

    static void moveCursor(const unsigned int &row, const unsigned int &col);


public:
    static void clearScreen();

    static void drawTaskCreateBox(const std::string &title,
        const std::string &desc, const std::string &dueDate,
        const std::string &status, const std::string &priority,
        const std::string &errorMessage);

    static void drawTaskEditBox(Task &task, const std::string &errorMessage);

    static void drawInputBox(const Action &action, const Type &type, Project &project);

    static void createTaskInProject(const std::string &title, const
        std::string &desc, const std::string &dueDate, const Status &status,
        const Priority &priority, Project &project);
    static void editTaskInProject(const std::string &title, const
        std::vector<Task> &tasks);
    static void deleteTaskInProject(const std::string &title,const
        std::vector<Task> &tasks);

    static void drawInfoBox(const Type &type, const std::string &title, const
        std::string &desc, const std::string &dueDate, const Status &status, const Priority &priority, const std::optional<std::vector<Task>> &tasks = std::nullopt);

    static void drawMenu();

    static void print(const std::string &text, const
        std::optional<std::string> &styles = std::nullopt, const std::optional<Color> &fg = std::nullopt, const std::optional<Color> &bg = std::nullopt);

    static std::string colorize(const std::string &text, const
        std::optional<Style> &styles = std::nullopt, const std::optional<Color> &fg = std::nullopt, const std::optional<Color> &bg = std::nullopt);

    static std::string buildStyleCodes(const std::string &styles);



};

#endif // TERMINAL_H
