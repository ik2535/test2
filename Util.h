#pragma once
#include <map>
#include <string>
using namespace std;

map<string, string> ProcessConfigData(string config_file);
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
