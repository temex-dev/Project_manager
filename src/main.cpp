#include "../include/Terminal.h"

int main() {
    Terminal::print("Hello, World!", "1", Color::BrightGreen,
        Color::Black);
    Terminal::print("Hello, World~", "13",
        Color::BrightYellow);
    Terminal::print("Hello, World!", "12345");
    Terminal::print("Hellow World!");

    return 0;
}

/*
print whole line with optional parameters - { "text", "styles", fg color, bg color }
Terminal::print("Hello, World!", "1", Color::BrightGreen, Color::Black);
Terminal::print("Hello, World!", "14", Color::BrightYellow);
Terminal::print("Hello, World!", "5");
Terminal::print("Hello, World!");

colorize only part of text(same parameters as print)
cout << "Hello " << Terminal::colorize("World", "1") << "!\n";

----------------------------------------------------------
STYLES
1 - bold
2 - dim
3 - italic
4 - underline
5 - strikethrough
*/
