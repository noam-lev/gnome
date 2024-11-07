#include <windows.h>
#include <process.h>
#include <Tlhelp32.h>
#include <winbase.h>
#include <string>
using namespace std;

std::string fromWcharToString(std::wstring wstr)
{
    // Calculating the length of the multibyte string
    size_t len = wcstombs(nullptr, wstr.c_str(), 0) + 1;

    // Creating a buffer to hold the multibyte string
    char* buffer = new char[len];

    // Converting wstring to string
    wcstombs(buffer, wstr.c_str(), len);

    // Creating std::string from char buffer
    std::string str(buffer);

    // Cleaning up the buffer
    delete[] buffer;
    return str;
}

std::string GetAppPath() {
    WCHAR path[MAX_PATH];  // Use WCHAR for wide character array
    GetModuleFileNameW(NULL, path, MAX_PATH);  // Retrieves the full path of the executable in wide characters
    std::wstring wpath = std::wstring(path);
    // convert to string
    return fromWcharToString(wpath);  // Return as std::wstring (wide string)
}

std::string makePurePath(std::string pre_path)
{
    string pure_path;
    int len = strlen(pre_path.c_str()) - 24;
    pure_path = pre_path.substr(0, len);
    return pure_path;
}

bool ifProcessIsAwake(const wchar_t* filename)
{
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(pEntry);
    BOOL hRes = Process32First(hSnapShot, &pEntry);
    while (hRes)
    {
        if (wcscmp(pEntry.szExeFile, filename) == 0)
        {
            CloseHandle(hSnapShot);
            return true;
        }
        hRes = Process32Next(hSnapShot, &pEntry);
    }
    CloseHandle(hSnapShot);
    return false;
}

int makeProcess(PROCESS_INFORMATION* pi, const char* exe_path)
{
    int id = 8200;
    STARTUPINFOA si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(pi, sizeof(pi));
    int len = strlen(exe_path) + 3;
    char* my_exe = (char*)malloc(len * sizeof(CHAR));
    sprintf_s(my_exe, len, "%s %c", exe_path, id);


    CreateProcessA(
        NULL,
        my_exe, // Command line : exe path + arg 
        NULL, // Process handle not inheritable
        NULL, // Thread handle not inheritable
        FALSE, // Set handle inheritance to FALSE
        0, // No creation flags
        NULL, // Use parent's environment block
        NULL, // Use parent's starting directory
        &si, // Pointer to STARTUPINFO structure
        pi); // Pointer to PROCESS_INFORMATION structure
    printf("process is running.\n");  //, id - '0'


    free(my_exe);
    return 0;
}

bool wakeProcessByName()
{
    const wchar_t* name = L"security launcher.exe";
    bool ans = ifProcessIsAwake(name);
    if (ans == false)
    {
        return false;
    }
    return true;
}


//int main()
INT WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    string my_path = GetAppPath();
    string pure_path = makePurePath(my_path);
    string sec_launcher_path = pure_path + "security launcher.exe";
    PROCESS_INFORMATION sec_launcher;
    // makeProcess(&trivia_launcher, sec_launcher_path.c_str());
    while (true)
    {
        if (wakeProcessByName() == false)
            makeProcess(&sec_launcher, sec_launcher_path.c_str());
    }
}