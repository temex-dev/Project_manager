#include "../include/Terminal.h"
#include "../include/Task.h"
#include "../include/Project.h"

int main() {
    Terminal::clearScreen();

    Project project;

    // project.addTask(Task("Task 1", "This is a sample task description.", "2024-12-31", Status::InProgress, Priority::High));

    // project.addTask(Task("Task 2", "Second task in project.", "2024-12-31", Status::Todo, Priority::Medium));

    // Terminal::drawMenu();

    // Terminal::drawInfoBox(Type::Task, "Task 1", "This is a sample task description.", "2024-12-31", Status::InProgress, Priority::High);

    // Terminal::drawInfoBox(Type::Project, "New Project", "Project description goes here.", "2024-12-31", Status::Todo, Priority::Medium, project.getTasks());

    // Terminal::drawInfoBox(Type::Task, "Completed Task", "This task is completed.", "2024-12-31", Status::Completed, Priority::Low);

    Terminal::drawInputBox(Action::Create, Type::Task, project);

    Terminal::drawInputBox(Action::Create, Type::Project, project);
    std::vector<Task> tasks = project.getTasks();
    for (const auto &t : tasks) {
        Terminal::drawInfoBox(t.getType(), t.getTitle(),
            t.getDescription(), t.getDueDate(), t.getStatus(), t.getPriority());
    }

    return 0;
}
