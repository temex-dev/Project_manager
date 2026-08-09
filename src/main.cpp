#include "../include/Terminal.h"
#include "../include/Task.h"
#include "../include/Project.h"

int main() {
// set terminal title
    system("echo -ne '\033]0;Todo App\a'");

    Terminal::clearScreen();

    Project project;

    Terminal::drawMenu(project);

    return 0;
}
