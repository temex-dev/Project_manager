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

void Terminal::drawInfoBox(const Type &type, const std::string &title, const
    std::string &desc, const std::string &dueDate, const Status &status, const Priority &priority, const std::optional<std::vector<Task>> &tasks) {

    const std::string typeLabel = typeStr.at(type);

    std::cout << "      ┌───────────────────────────────┐\n";
    std::cout << "      │ "
        << Terminal::colorize(typeLabel, Style::Bold, Color::BrightBlue)
        << "\033[21G: "
        << Terminal::colorize(title, Style::Bold) << "\n";
    std::cout << "      ├───────────────────────────────┤\n";
    std::cout << "      │ "
        << Terminal::colorize("Description : ", Style::Bold)
        << Terminal::colorize(desc, Style::Italic) << "\n";

    if (type == Type::Project && tasks.has_value()) {
        std::cout << "      │ "
            << Terminal::colorize("Tasks       : ", Style::Bold);
        for (const auto &t : tasks.value()) {
            std::cout << Terminal::colorize(t.getTitle(), Style::Italic);
            if (&t != &tasks.value().back()) {
                std::cout << ", ";
            }
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

void Terminal::drawTaskCreateBox(const std::string &title, const
    std::string &desc, const std::string &dueDate, const std::string &status,
    const std::string &priority, const std::string &errorMessage) {

    std::cout << "      ┌───────────────────────────────┐\n";
    std::cout << "      │ "
        << Terminal::colorize("Task", Style::Bold, Color::BrightBlue)
        << "\033[21G: " << title << "\n";
    std::cout << "      ├───────────────────────────────┤\n";
    std::cout << "      │ "
        << Terminal::colorize("Description : ", Style::Bold)
        << desc << "\n";
    std::cout << "      │ "
        << Terminal::colorize("Due Date    : ", Style::Bold)
        << dueDate << "\n";
    std::cout << "      │ "
        << Terminal::colorize("Status      : ", Style::Bold);
    if (strStatus.count(status)) {
        std::cout<< Terminal::colorize(status, std::nullopt,
            statusColor.at(strStatus.at(status)).fg, statusColor.at(strStatus.at(status)).bg) << "\n";
    }
    else { std::cout << status << std::endl; }

    std::cout << "      │ "
        << Terminal::colorize("Priority    : ", Style::Bold);
    if (strPriority.count(priority)) {
        std::cout << Terminal::colorize(priority, std::nullopt,
            priorityColors.at(strPriority.at(priority)).fg, priorityColors.at(strPriority.at(priority)).bg) << "\n";
    }
    else { std::cout << priority << std::endl; }
    std::cout << "      └───────────────────────────────┘\n";

    if (!errorMessage.empty()) {
        std::cout << "\n      "
            << Terminal::colorize("Error: " + errorMessage, std::nullopt, Color::White, Color::Red)
            << "\n";
    }
}

void Terminal::drawTaskEditBox(Task &task, const std::string &errorMessage) {
    Terminal::drawInfoBox(task.getType(), task.getTitle(), task.getDescription(), task.getDueDate(), task.getStatus(), task.getPriority());

}

void Terminal::drawInputBox(const Action &action, const Type &type, Project &
    project) {
    const std::string typeLabel = typeStr.at(type);
    std::string title, desc, dueDate, status, priority;
    std::string errorMessage;
    if (typeLabel == "Task") {
        switch(action) {
            case Action::Create:
                while(true) {
                    Terminal::clearScreen();
                    Terminal::drawTaskCreateBox(title, desc, dueDate, status, priority, errorMessage);
                    errorMessage.clear();

                    if (title.empty()) {
                        Terminal::moveCursor(2, 23);
                        std::getline(std::cin, title);
                        continue;
                    }
                    if (desc.empty()) {
                        Terminal::moveCursor(4, 23);
                        std::getline(std::cin, desc);
                        continue;
                    }
                    if (dueDate.empty()) {
                        Terminal::moveCursor(5, 23);
                        std::getline(std::cin, dueDate);
                        continue;
                    }
                    if (status.empty()) {
                        Terminal::moveCursor(6, 23);
                        std::getline(std::cin, status);
                        if (status != "Todo" && status != "InProgress" && status != "Completed") {
                            status.clear();
                            errorMessage = "Invalid status. Use Todo, InProgress, or Completed.";
                            continue;
                        }
                        continue;
                    }
                    if (priority.empty()) {
                        Terminal::moveCursor(7, 23);
                        std::getline(std::cin, priority);
                        if (priority != "Low" && priority != "Medium" && priority != "High") {
                            priority.clear();
                            errorMessage = "Invalid priority. Use Low, Medium, or High.";
                            continue;
                        }
                        continue;
                    }
                    Terminal::createTaskInProject(title, desc, dueDate,
                        strStatus.at(status), strPriority.at(priority), project);
                    break;
                }
                break;
            case Action::Edit:

            // case Action::Delete:

            default:
            std::cout << "\n      "
                << Terminal::colorize("This isn't a valid action for input.", std::nullopt, Color::White, Color::Red) << "\n";
        }
    }
    std::cout << "\n      "
        << Terminal::colorize("Can't create Project inside another Project '" + project.getTitle() + "'", std::nullopt, Color::White, Color::Red)
        << "\n";
}

void Terminal::createTaskInProject(const std::string &title, const
    std::string &desc, const std::string &dueDate, const Status &status,
        const Priority &priority, Project &project) {
            project.addTask(Task(title, desc, dueDate, status, priority));
}

void Terminal::editTaskInProject(const std::string &title, const
    std::vector<Task> &tasks) {
    // TODO: Implement task edit input box
}

void Terminal::deleteTaskInProject(const std::string &title, const
    std::vector<Task> &tasks) {
    // TODO: Implement task delete input box
}

void Terminal::drawMenu() {
    std::string errorMsg;
    unsigned int input;

    while (true) {
        Terminal::clearScreen();

        std::cout << "      ┌───────────────────────────────┐\n";
        std::cout << "      │ "
            << Terminal::colorize("Menu", Style::Bold, Color::BrightBlue)
            << "\033[15G: "
            << Terminal::colorize("Select an option", Style::Bold) << "      │\n";
        std::cout << "      ├───────────────────────────────┤\n";
        std::cout << "      │ "
            << Terminal::colorize("1. Create Task/Project", Style::Bold) << "        │\n";
        std::cout << "      │ "
            << Terminal::colorize("2. View Tasks/Projects", Style::Bold) << "        │\n";
        std::cout << "      │ "
            << Terminal::colorize("3. Edit Task/Project", Style::Bold) << "          │\n";
        std::cout << "      │ "
            << Terminal::colorize("4. Delete Task/Project", Style::Bold) << "        │\n";
        std::cout << "      │ "
            << Terminal::colorize("5. Help", Style::Bold) << "                       │\n";
        std::cout << "      │ "
            << Terminal::colorize("6. Exit", Style::Bold) << "                       │\n";
        std::cout << "      ├───────────────────────────────┤\n";
        std::cout << "      │ # " << Terminal::colorize("Enter number", Style::Dim) << "\n";
        std::cout << "      └───────────────────────────────┘\n";

        if (!errorMsg.empty()) {
            std::cout << "\n      "
                << Terminal::colorize(errorMsg, std::nullopt, Color::White, Color::Red) << "\n";
        }

        Terminal::moveCursor(11, 11);
        std::cin >> input;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore();
            errorMsg = "Invalid input — please enter a number.";
            continue;
        }

        if (input >= 1 && input <= 6) {
            Terminal::clearScreen();
            std::string errorMsg2;
            unsigned int input2;
            switch (input) {
                case 1:
                    while(true) {
                        Terminal::clearScreen();
                        std::cout << "      ┌───────────────────────────────┐\n";
                        std::cout << "      │ "
                            << Terminal::colorize("Submenu", Style::Bold, Color::BrightBlue)
                            << "\033[16G: "
                            << Terminal::colorize("Select an option", Style::Bold) << "     │\n";
                        std::cout << "      ├───────────────────────────────┤\n";
                        std::cout << "      │ "
                            << Terminal::colorize("1. Create Project", Style::Bold) << "             │\n";
                        std::cout << "      │ "
                            << Terminal::colorize("2. Create Task", Style::Bold) << "                │\n";
                        std::cout << "      ├───────────────────────────────┤\n";
                        std::cout << "      │ # " << Terminal::colorize("Enter number", Style::Dim) << "\n";
                        std::cout << "      └───────────────────────────────┘\n";

                        if (!errorMsg.empty()) {
                            std::cout << "\n      "
                                << Terminal::colorize(errorMsg, std::nullopt, Color::White, Color::Red) << "\n";
                        }

                        Terminal::moveCursor(7, 11);
                        std::cin >> input;

                        if (std::cin.fail()) {
                            std::cin.clear();
                            std::cin.ignore();
                            errorMsg = "Invalid input — please enter a number.";
                            continue;
                        }

                        if (input2 <= 0 || input2 > 2) {
                            errorMsg = "This isn't a valid action for input.";
                            continue;
                        }

                        switch(input2) {
                            case 1:
                                Terminal::drawInputBox(Action::Create, Type::Project);
                                break;
                            case 2:
                                std::cout << "jakej project vis co\n";
                                Terminal::drawInputBox(Action::Create, Type::Task, &project);
                                break;
                        }
                    }
                    break;
                case 2:

                    break;
                case 3:

                    break;
                case 4:

                    break;
                case 5:

                    break;
                case 6:
                    std::cout << "Exiting...\nTemex na to uz nema...\n";
                    exit(0);
            }
        } else {
            errorMsg = "This isn't a valid action for input.";
        }
    }
}
