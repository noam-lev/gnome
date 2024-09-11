#pragma once
#include <random>
#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#pragma comment(lib, "wininet.lib")

// Function to make HTTP GET request
std::string HttpGet(const std::string& url);

   

// Function to decode HTML entities
std::string DecodeHtmlEntities(const std::string& input);

// Simple JSON parsing (Note: This is a very basic parser and not suitable for complex JSON)
std::string GetJsonValue(const std::string& json, const std::string& key);

std::vector<std::string> GetJsonArray(const std::string& json, const std::string& key);

// Function to generate trivia questions
int GenerateTriviaQuestions(int amount = 5);
