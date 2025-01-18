#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <unordered_map>

//używanie aliasu json, aby nie musieć za każdym razem zapiswać nazwy nlohmann::json 
using json = nlohmann::json;

//wczytuje tłumaczenia z pliku JSON dla określonego języka
void loadTranslations(const std::string& language);

//szuka tłumaczenia w pliku JSON dla danego słowa kluczowego
std::string T(const std::string& key);

//globalna mapa tłumaczeń, która przechowuje słowa kluczowe oraz ich tłumaczenia
extern std::unordered_map<std::string, std::string> translations;