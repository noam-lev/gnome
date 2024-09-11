#include <windows.h>
#include <physicalmonitorenumerationapi.h>
#include <highlevelmonitorconfigurationapi.h>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#pragma comment(lib, "Dxva2.lib")

// Function to rotate the screen
bool RotateScreen(DWORD displayIndex, DWORD orientation) {
    DISPLAY_DEVICE dd = { sizeof(dd), 0 };
    DEVMODE dm = { 0 };
    dm.dmSize = sizeof(dm);

    if (!EnumDisplayDevices(NULL, displayIndex, &dd, 0)) {
        std::cout << "Failed to enumerate display devices." << std::endl;
        return false;
    }

    if (!EnumDisplaySettings(dd.DeviceName, ENUM_CURRENT_SETTINGS, &dm)) {
        std::cout << "Failed to get display settings." << std::endl;
        return false;
    }

    if (dm.dmDisplayOrientation == orientation) {
        std::cout << "Screen is already in the desired orientation." << std::endl;
        return true;
    }

    DWORD oldWidth = dm.dmPelsWidth;
    DWORD oldHeight = dm.dmPelsHeight;

    switch (orientation) {
    case DMDO_DEFAULT:
    case DMDO_180:
        dm.dmPelsWidth = oldWidth;
        dm.dmPelsHeight = oldHeight;
        break;
    case DMDO_90:
    case DMDO_270:
        dm.dmPelsWidth = oldHeight;
        dm.dmPelsHeight = oldWidth;
        break;
    }

    dm.dmDisplayOrientation = orientation;
    dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYORIENTATION;

    LONG result = ChangeDisplaySettingsEx(dd.DeviceName, &dm, NULL, CDS_UPDATEREGISTRY, NULL);
    if (result != DISP_CHANGE_SUCCESSFUL) {
        std::cout << "Failed to change display settings. Error code: " << result << std::endl;
        return false;
    }

    std::cout << "Screen rotated successfully." << std::endl;
    return true;
}

// Function to rotate screen for a specified duration
void RotateScreenForDuration(int milliseconds) {
    // Rotate screen 90 degrees
    if (RotateScreen(0, DMDO_180)) {
        // Wait for specified duration
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));

        // Rotate screen back to original position
        RotateScreen(0, DMDO_DEFAULT);
    }
}

int main() {
    int duration;
    std::cout << "Enter duration to rotate screen (in milliseconds): ";
    std::cin >> duration;

    RotateScreenForDuration(duration);

    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.ignore();
    std::cin.get();

    return 0;
}