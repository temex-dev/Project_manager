#include "../include/Terminal.h"

int main() {
    Terminal::clearScreen();

    Terminal::drawMenu();


    Terminal::drawInfoBox(Type::Task, "Task 1", "This is a sample task description.", "2024-12-31", Status::InProgress, Priority::High);

    Terminal::drawInfoBox(Type::Project, "New Project", "Project description goes here.", "2024-12-31", Status::Todo, Priority::Medium);

    Terminal::drawInfoBox(Type::Task, "Completed Task", "This task is completed.", "2024-12-31", Status::Completed, Priority::Low);

    std::cout << "end";
    return 0;
}
