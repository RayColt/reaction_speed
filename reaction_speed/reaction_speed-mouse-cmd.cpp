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
    cout << "WAIT FOR THE 'O':" << flush;
    int delay_ms = 2000 + (rand() % 3001);
    this_thread::sleep_for(chrono::milliseconds(delay_ms));
    chrono::high_resolution_clock::time_point start = chrono::steady_clock::now();
    cout << "O" << flush;

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

    chrono::high_resolution_clock::time_point end = chrono::steady_clock::now();
    chrono::duration<double> elapsed = end - start;
    double ms = elapsed.count() * 1000;
    cout << "\n\nYour reaction time: " << ms << " ms\n";
    cout << "Your S Indication: S" << (elapsed.count() * 10) << "\n";

    cout << "\nPress Enter to close program . . .";
    int c = getchar();

    return 0;
}