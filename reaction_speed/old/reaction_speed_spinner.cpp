/* uncommented
 * reaction_speed_spinner.cpp
 * 
 * This program measures the user's reaction time by displaying a spinner
 * for a random duration before showing an 'O'. The user must click the left
 * mouse button as fast as possible after seeing the 'O'.
 *
 * It uses Windows API for console input and output.
 * It is aprximately 1 ms slower but has a spinner animation that creates the maybe realistic slowdown.
 * 
#include <windows.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <cstdlib>  // for srand, rand
#include <ctime>    // for time(nullptr)

using namespace std;

// Disable Quick Edit and mouse-selection in the console
void disableQuickEdit()
{
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hIn, &mode);
    mode &= ~(ENABLE_QUICK_EDIT_MODE | ENABLE_MOUSE_INPUT);
    SetConsoleMode(hIn, mode);
}

int main()
{
    // Seed RNG and disable console Quick Edit
    srand(static_cast<unsigned>(time(nullptr)));
    disableQuickEdit();
    cout << "Get Ready! Wait for the O, then click \nthe LEFT mouse button as fast as you can.\n";
    this_thread::sleep_for(chrono::seconds(1));
    cout << "WAIT FOR THE 'O'::" << flush;
    int delay_ms = 2000 + (rand() % 3001);

    // Rotating indicator characters
    const char spinner[] = { '/', '-', '\\', '|' };
    int spinner_len = sizeof(spinner) / sizeof(spinner[0]);
    int spinner_pos = 0;

    // Show rotating spinner for the random delay
    auto spin_start = chrono::steady_clock::now();
    while (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - spin_start).count() < delay_ms)
    {
        cout << "\b" << spinner[spinner_pos] << flush;
        spinner_pos = (spinner_pos + 1) % spinner_len;
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    cout << "\bO" << flush; // Replace spinner with 'O'

    // Poll for left-button down
    while (true)
    {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
        {
            break;
        }
        // Avoid CPU at 100%
        this_thread::sleep_for(chrono::milliseconds(5));
    }

    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    chrono::duration<double> elapsed = end - start;
    double ms = elapsed.count() * 1000;
    cout << "\n\nYour reaction time: " << ms << " ms\n";
    cout << "Your S Indication: S" << (elapsed.count() * 10) << "\n";

    return 0;
}*/