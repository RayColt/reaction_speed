#include <chrono>
#include <thread>
#include <iostream>
#include <conio.h> 
#include <windows.h>

using namespace std;

int main()
{
    srand(time(nullptr));
    cout << "Get Ready! Wait for the O, then press SPACE as fast as you can.\n";
    this_thread::sleep_for(chrono::seconds(1));

    const char spinner[] = { '/', '-', '\\', '|' };
    const int numFrames = sizeof(spinner) / sizeof(spinner[0]);
    // Spin for ~5 seconds
    int delay_ms = 100 + (rand() % 251);
    for (int i = 0; i < 20; ++i) 
    {
        cout << "\r" << "WAIT FOR THE 'O': "  << spinner[i % numFrames] << flush;
        this_thread::sleep_for(chrono::milliseconds(delay_ms));
    }
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    //cout << "\b" << "O" << flush;
    cout << "O";
    while (_getch() != ' ') {}
    /* MOUSE KEY DowN
    while (true) 
    {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {break;}
    }*/


    cout << endl;
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_ms_seconds = end - start;
    cout << "\nYour reaction time: " << elapsed_ms_seconds.count() * 1000 << " ms\n";
    cout << "\nYour S Indication: S" << elapsed_ms_seconds.count() * 10 << "\n";

    return 0;
}