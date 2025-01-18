#pragma once
#include <string> //biblioteka, która jest mi potrzebna do zrobienia reaktywnego wyboru w menu, i obsługi napisów w menu
#include <nlohmann/json.hpp> //biblioteka nlohmanna dodaję obsługę plików json
#include <unordered_map>
#include <iostream>

using json = nlohmann::json;

void LoadTranslations(const std::string& language);

std::string T(const std::string& key);

extern std::unordered_map<std::string, std::string> translations;