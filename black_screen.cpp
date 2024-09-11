#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>

// Function to set brightness
void SetBrightness(int brightness) {
    std::string command = "powershell.exe (Get-WmiObject -Namespace root/WMI -Class WmiMonitorBrightnessMethods).WmiSetBrightness(1," + std::to_string(brightness) + ")";

    int result = system(command.c_str());

    if (result == 0) {
        std::cout << "Brightness set to " << brightness << "%" << std::endl;
    }
    else {
        std::cout << "Failed to set brightness. Error code: " << result << std::endl;
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
    int currentBrightness = GetCurrentBrightness();
    if (currentBrightness == -1) {
        std::cout << "Failed to get current brightness" << std::endl;
        return;
    }

    std::cout << "Current brightness: " << currentBrightness << "%" << std::endl;

    // Set brightness to 0%
    SetBrightness(0);

    // Wait for specified duration
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));

    // Restore original brightness
    SetBrightness(currentBrightness);
}

int main() {
    int duration;
    std::cout << "Enter duration to turn off screen (in milliseconds): ";
    std::cin >> duration;

    TurnOffScreenForDuration(duration);

    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.ignore();
    std::cin.get();

    return 0;
}