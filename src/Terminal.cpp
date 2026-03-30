#include "../include/Terminal.h"


unsigned int Terminal::toFgCode(const Color &c) {
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
unsigned int Terminal::toBgCode(const Color &c) {
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
    std::cout << "\033[3J\033[2J\033[1;1H";
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
    std::optional<Style> &styles, const std::optional<Color> &fg, const std::optional<Color> &bg) {

    Color fgColor = fg.value_or(Color::White);
    Color bgColor = bg.value_or(Color::Black);

    std::string code = "\033[";
    if (styles.has_value()) {
        switch(styles.value()) {
            case Style::Bold:          code += "1;"; break;
            case Style::Dim:           code += "2;"; break;
            case Style::Italic:        code += "3;"; break;
            case Style::Underline:     code += "4;"; break;
            case Style::Strikethrough: code += "9;"; break;
        }
    }
    code += std::to_string(toFgCode(fgColor)) + ";" + std::to_string(toBgCode(bgColor)) + "m";
    return code + text + "\033[0m";
}

void Terminal::moveCursor(const unsigned int &row, const unsigned int &col) {
    std::cout << "\033[" << row << ";" << col << "H";
}

// ===== NOT FINISHED =====
void Terminal::drawInfoBox(const Type &type, const std::string &title, const
    std::string &desc, const std::string &dueDate, const Status &status, const Priority &priority) {


        class Task {
            private:
                std::string title;
                public:
                Task(const std::string &t) : title(t) {}
                std::string getTitle() const { return title; }
        };
    struct Tasks {
        Task *task;
    };
    Task test1("Task 1");
    Task test2("Task 2");

    Tasks testTask1 = {&test1};
    Tasks testTask2 = {&test2};
    std::vector<Tasks> tasks = {testTask1, testTask2};

    const std::string typeStr = (type == Type::Project) ? "Project" : "Task";

    std::cout << "      ┌───────────────────────────────┐\n";
    std::cout << "      │ "
        << Terminal::colorize(typeStr, Style::Bold, Color::BrightBlue)
        << "\033[21G: "
        << Terminal::colorize(title, Style::Bold) << "\n";
    std::cout << "      ├───────────────────────────────┤\n";
    std::cout << "      │ "
        << Terminal::colorize("Description : ", Style::Bold)
        << Terminal::colorize(desc, Style::Italic) << "\n";
    if (type == Type::Project) {

        std::cout << "      │ "
            << Terminal::colorize("Tasks       : ", Style::Bold);
            for (const auto &t : tasks) {
            std::cout << Terminal::colorize(t.task->getTitle(), Style::Italic) << ", ";
        }
        std::cout << "\b\b " << std::endl;
    }
    std::cout << "      │ "
        << Terminal::colorize("Due Date    : ", Style::Bold)
        << Terminal::colorize(dueDate, Style::Underline) << "\n";
    std::cout << "      │ "
        << Terminal::colorize("Status      : ", Style::Bold)
        << Terminal::colorize(statusStr.at(status), std::nullopt, statusColor.at(status).fg, statusColor.at(status).bg) << "\n";
    std::cout << "      │ "
        << Terminal::colorize("Priority    : ", Style::Bold)
        << Terminal::colorize(priorityStr.at(priority), std::nullopt, priorityColors.at(priority).fg, priorityColors.at(priority).bg) << "\n";
    std::cout << "      └───────────────────────────────┘\n";
}

void Terminal::drawMenu() {
    char input;
    std::cout << "      ┌───────────────────────────────┐\n";
    std::cout << "      │ "
        << Terminal::colorize("Menu", Style::Bold, Color::BrightBlue)
        << "\033[15G: "
        << Terminal::colorize("Select an option", Style::Bold) << "      │\n";
    std::cout << "      ├───────────────────────────────┤\n";
    std::cout << "      │ "
        << Terminal::colorize("1. Create Task", Style::Bold) << "                │\n";
    std::cout << "      │ "
        << Terminal::colorize("2. Create Project", Style::Bold) << "             │\n";
    std::cout << "      │ "
        << Terminal::colorize("3. View Tasks/Projects", Style::Bold) << "        │\n";
    std::cout << "      │ "
        << Terminal::colorize("4. Edit Task/Project", Style::Bold) << "          │\n";
    std::cout << "      │ "
        << Terminal::colorize("5. Delete Task/Project", Style::Bold) << "        │\n";
    std::cout << "      │ "
        << Terminal::colorize("6. Help", Style::Bold) << "                       │\n";
    std::cout << "      │ "
        << Terminal::colorize("7. Exit", Style::Bold) << "                       │\n";
    std::cout << "      ├───────────────────────────────┤\n";
    std::cout << "      │ #\n";
    std::cout << "      └───────────────────────────────┘\n";
    Terminal::moveCursor(12, 11);
    std::cin >> input;
    Terminal::clearScreen();
}
