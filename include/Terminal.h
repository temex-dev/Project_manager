#pragma once
#ifndef TERMINAL_H
#define TERMINAL_H

#include "../include/globals.h"


enum class Color {
    Black, Red, Green, Yellow, Blue, Magenta, Cyan, White,
    BrightRed, BrightGreen, BrightYellow, BrightBlue
};

enum class Style {
    Bold, Dim, Italic, Underline, Strikethrough
};

class Terminal {
private:
    static int toFgCode(const Color &c);
    static int toBgCode(const Color &c);
public:
    static void clearScreen();

    static void print(const std::string &text, const
        std::optional<std::string> &styles = std::nullopt, const std::optional<Color> &fg = std::nullopt, const std::optional<Color> &bg = std::nullopt);

    static std::string colorize(const std::string &text, const
        std::optional<std::string> &styles = std::nullopt, const std::optional<Color> &fg = std::nullopt, const std::optional<Color> &bg = std::nullopt);

    static std::string buildStyleCodes(const std::string &styles);

};

#endif // TERMINAL_H
