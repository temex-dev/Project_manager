#ifndef TERMINAL_H
#define TERMINAL_H
#pragma once
#include "../include/globals.h"

class Terminal {
private:
    static unsigned int toFgCode(const Color &c);
    static unsigned int toBgCode(const Color &c);

    static void moveCursor(const unsigned int &row, const unsigned int &col);

public:
    static void clearScreen();

    static void drawInputBox(const Type &type, const Action &action, const
        std::string &title, std::string &desc, std::string &dueDate, const Status &status, const Priority &priority);

    static void drawInfoBox(const Type &type, const std::string &title, const
        std::string &desc, const std::string &dueDate, const Status &status, const Priority &priority);

    static void drawMenu();

    static void print(const std::string &text, const
        std::optional<std::string> &styles = std::nullopt, const std::optional<Color> &fg = std::nullopt, const std::optional<Color> &bg = std::nullopt);

    static std::string colorize(const std::string &text, const
        std::optional<Style> &styles = std::nullopt, const std::optional<Color> &fg = std::nullopt, const std::optional<Color> &bg = std::nullopt);

    static std::string buildStyleCodes(const std::string &styles);



};

#endif // TERMINAL_H
