#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
    cout << " Press Any Key:" << endl;
    while (true) {
        // Iterate through all possible key codes (0 to 255)
        for (int keyCode = 0; keyCode < 256; ++keyCode) {
            // Check if the key with keyCode is currently
            // pressed
            if (GetAsyncKeyState(keyCode) & 0x8000) {
                // Convert the key code to ASCII character
                char keyChar = static_cast<char>(keyCode);
                cout << "Pressed Key: " << keyChar
                     << " (ASCII value: " << keyCode << ")"
                     << endl;
            }
        }

        // Add a small delay to avoid high CPU usage
        Sleep(100);
    }

    return 0;
}