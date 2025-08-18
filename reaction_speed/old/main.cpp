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
    cout << "WAIT FOR THE 'O':" << flush;
    int delay_ms = 2000 + (rand() % 3001);// rand() % 3001 produces a random integer between 0…3000
    this_thread::sleep_for(chrono::milliseconds(delay_ms));
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    cout << "O" << flush;
    while (_getch() != ' ') {}
    /*
        TODO: with MOUSE CLICK :: AI?
        while (true)
        {
            if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) { break; }
	    }
    */


    cout << endl;

    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_ms_seconds = end - start;
    cout << "\nYour reaction time: " << elapsed_ms_seconds.count() * 1000 << " ms\n";
    cout << "\nYour S Indication: S" << elapsed_ms_seconds.count() * 10 << "\n";

    return 0;
}