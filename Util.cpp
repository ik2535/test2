#include <fstream>
#include <sstream>
#include "Util.h"

map<string, string> ProcessConfigData(string config_file)
{
	map<string, string> config_map;
	ifstream fin(config_file);
	string line, name, value;
	while (getline(fin, line))
	{
		stringstream sin(line);
		getline(sin, name, ',');
		getline(sin, value);
		config_map[name] = value;
	}
	return config_map;
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	((string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}
