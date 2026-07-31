#include "../include/Terminal.h"
#include "../include/Task.h"
#include "../include/Project.h"

int main() {
// set terminal title
    system("echo -ne '\033]0;Todo App\a'");

    Terminal::clearScreen();

    Project project;

    Terminal::drawMenu(project);

    // Terminal::drawInputBox(Action::Create, Type::Task, project);
    // Terminal::drawInputBox(Action::Create, Type::Task, project);

    Terminal::drawInputBox(Action::Create, Type::Project, project);
    std::vector<Task> projects = project.getTasks();
    for (const auto &p : projects) {
        Terminal::drawInfoBox(p.getType(), p.getTitle(),
            p.getDescription(), p.getDueDate(), p.getStatus(), p.getPriority());
    }

    return 0;
}
