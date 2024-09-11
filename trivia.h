#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <random>

#pragma comment(lib, "wininet.lib")

// Function to make HTTP GET request
std::string HttpGet(const std::string& url) {
    std::string response;
    HINTERNET hInternet = InternetOpenA("TriviaBotAgent", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL) {
        std::cerr << "Failed to open WinINet" << std::endl;
        return response;
    }

    HINTERNET hConnect = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (hConnect == NULL) {
        std::cerr << "Failed to open URL" << std::endl;
        InternetCloseHandle(hInternet);
        return response;
    }

    char buffer[1024];
    DWORD bytesRead;
    while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        response.append(buffer, bytesRead);
    }

    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);
    return response;
}

// Function to decode HTML entities
std::string DecodeHtmlEntities(const std::string& input) {
    std::string output = input;
    size_t pos = 0;
    while ((pos = output.find("&quot;", pos)) != std::string::npos) {
        output.replace(pos, 6, "\"");
        pos += 1;
    }
    while ((pos = output.find("&#039;", pos)) != std::string::npos) {
        output.replace(pos, 6, "'");
        pos += 1;
    }
    while ((pos = output.find("&amp;", pos)) != std::string::npos) {
        output.replace(pos, 5, "&");
        pos += 1;
    }
    // Add more entity replacements as needed
    return output;
}

// Simple JSON parsing (Note: This is a very basic parser and not suitable for complex JSON)
std::string GetJsonValue(const std::string& json, const std::string& key) {
    size_t pos = json.find("\"" + key + "\":");
    if (pos == std::string::npos) return "";
    pos = json.find("\"", pos + key.length() + 2);
    if (pos == std::string::npos) return "";
    size_t end = json.find("\"", pos + 1);
    if (end == std::string::npos) return "";
    return DecodeHtmlEntities(json.substr(pos + 1, end - pos - 1));
}

std::vector<std::string> GetJsonArray(const std::string& json, const std::string& key) {
    std::vector<std::string> result;
    size_t pos = json.find("\"" + key + "\":");
    if (pos == std::string::npos) return result;
    pos = json.find("[", pos);
    if (pos == std::string::npos) return result;
    size_t end = json.find("]", pos);
    if (end == std::string::npos) return result;

    std::string arrayContent = json.substr(pos + 1, end - pos - 1);
    std::istringstream iss(arrayContent);
    std::string item;
    while (std::getline(iss, item, ',')) {
        item = item.substr(item.find("\"") + 1);
        item = item.substr(0, item.rfind("\""));
        result.push_back(DecodeHtmlEntities(item));
    }
    return result;
}

// Function to generate trivia questions
void GenerateTriviaQuestions(int amount = 5) {
    std::string url = "https://opentdb.com/api.php?amount=" + std::to_string(amount);
    std::string response = HttpGet(url);

    if (response.empty()) {
        std::cout << "Failed to get trivia questions." << std::endl;
        return;
    }

    std::istringstream responseStream(response);
    std::string line;
    while (std::getline(responseStream, line)) {
        if (line.find("\"question\":") != std::string::npos) {
            std::string question = GetJsonValue(line, "question");
            std::string correctAnswer = GetJsonValue(line, "correct_answer");
            std::vector<std::string> incorrectAnswers = GetJsonArray(line, "incorrect_answers");

            std::cout << "Question: " << question << std::endl;

            std::vector<std::string> allAnswers = incorrectAnswers;
            allAnswers.push_back(correctAnswer);

            // Shuffle the answers
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(allAnswers.begin(), allAnswers.end(), g);

            char option = 'A';
            for (const auto& answer : allAnswers) {
                std::cout << option << ") " << answer << std::endl;
                option++;
            }

            // Get user input
            std::cout << "Your answer (A, B, C, etc.): ";
            char userAnswer;
            std::cin >> userAnswer;

            // Check if the answer is correct
            if (toupper(userAnswer) - 'A' >= 0 && toupper(userAnswer) - 'A' < allAnswers.size()) {
                std::string selectedAnswer = allAnswers[toupper(userAnswer) - 'A'];
                if (selectedAnswer == correctAnswer) {
                    std::cout << "Correct!" << std::endl;
                }
                else {
                    std::cout << "Wrong! The correct answer was: " << correctAnswer << std::endl;
                }
            }
            else {
                std::cout << "Invalid answer!" << std::endl;
            }

            std::cout << std::endl; // Print a new line for better readability
        }
    }
}

int main() {
    GenerateTriviaQuestions(3);  // Generate 3 trivia questions
    system("pause");
    return 0;
}