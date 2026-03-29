#include "../include/Terminal.h"


int Terminal::toFgCode(const Color &c) {
    switch (c) {
        case Color::Black:         return 30;
        case Color::Red:           return 31;
        case Color::Green:         return 32;
        case Color::Yellow:        return 33;
        case Color::Blue:          return 34;
        case Color::Magenta:       return 35;
        case Color::Cyan:          return 36;
        case Color::White:         return 37;
        case Color::BrightRed:     return 91;
        case Color::BrightGreen:   return 92;
        case Color::BrightYellow:  return 93;
        case Color::BrightBlue:    return 94;
        default:                   return 37;
    }
}
int Terminal::toBgCode(const Color &c) {
    switch (c) {
        case Color::Black:         return 40;
        case Color::Red:           return 41;
        case Color::Green:         return 42;
        case Color::Yellow:        return 43;
        case Color::Blue:          return 44;
        case Color::Magenta:       return 45;
        case Color::Cyan:          return 46;
        case Color::White:         return 47;
        case Color::BrightRed:     return 101;
        case Color::BrightGreen:   return 102;
        case Color::BrightYellow:  return 103;
        case Color::BrightBlue:    return 104;
        default:                   return 40;
    }
}
void Terminal::clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

std::string Terminal::buildStyleCodes(const std::string &styles) {
    std::string codes = "";
    for (const char &s : styles) {
        switch (s) {
            case '1': codes += "1;"; break;  // bold
            case '2': codes += "2;"; break;  // dim
            case '3': codes += "3;"; break;  // italic
            case '4': codes += "4;"; break;  // underline
            case '5': codes += "9;"; break;  // strikethrough
        }
    }
    return codes;
}
void Terminal::print(const std::string &text, const std::optional<std::string> &
    styles, const std::optional<Color> &fg, const std::optional<Color> &bg) {

    Color fgColor = fg.value_or(Color::White);
    Color bgColor = bg.value_or(Color::Black);

//start ANSI code
    std::string code = "\033[";

//add ANSI codes for styles
    if (styles.has_value()) code += buildStyleCodes(styles.value());

//add colors in format 'fg;bg'
    code += std::to_string(toFgCode(fgColor)) + ";" + std::to_string
        (toBgCode(bgColor)) + "m";

//display with ANSI code
    std::cout << code << text << "\033[0m\n";
}

std::string Terminal::colorize(const std::string &text, const
    std::optional<std::string> &styles, const std::optional<Color> &fg, const std::optional<Color> &bg) {

    Color fgColor = fg.value_or(Color::White);
    Color bgColor = bg.value_or(Color::Black);

    std::string code = "\033[";
    if (styles.has_value()) code += buildStyleCodes(styles.value());
    code += std::to_string(toFgCode(fgColor)) + "m";
    return code + text + "\033[0m";
}
