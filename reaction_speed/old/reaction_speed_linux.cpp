/* uncommented
 * reaction_speed_linux.cpp
 *
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <termios.h>
#include <unistd.h>

using namespace std;
//
// Test your Reaction Speed / US Army S indication
//

// Read one character without waiting for Enter
int getch()
{
    // Save current terminal settings
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    // Disable canonical mode and echo
    // ICANON off: switches from line-buffered (canonical) input to character-by-character mode
    // ECHO off: prevents the typed character from being printed to the screen
    newt.c_lflag &= ~(ICANON | ECHO);
    // Apply the modified settings immediatel
    // TCSANOW tells the terminal to apply changes without waiting.
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    // Read one character
    int c = getchar();
    // Restore original terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return c;
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    cout << "Get Ready! Wait for the O, then press SPACE as fast as you can.\n";
    this_thread::sleep_for(chrono::seconds(1));

    cout << "WAIT FOR THE 'O':" << flush;
    int delay_ms = 2000 + (rand() % 3001);// rand() % 3001 produces a random integer between 0…3000
    this_thread::sleep_for(chrono::milliseconds(delay_ms));
    auto start = chrono::high_resolution_clock::now();
    cout << "O" << flush;
    while (getch() != ' ') {}

    auto end = chrono::high_resolution_clock::now();
    auto reaction = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    cout << "\nYour reaction time: " << reaction << " ms\n";
    return 0;
}*/