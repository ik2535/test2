#include <stdio.h>
#include <json/json.h>
#include <curl/curl.h>
#include <sqlite3.h>
#include <fstream>

#include "Stock.h"
#include "Util.h"
#include "MarketData.h"

int main(void)
{
	string sConfigFile = "config.csv";
	map<string, string> configMap = ProcessConfigData(sConfigFile);
	string url_common = configMap["url_common"];
	string api_token = configMap["api_token"];
	string symbol = configMap["symbol"];

	string urlRequest = url_common + "intraday/" + symbol + ".US?" + "api_token=" + api_token + "&interval=5m&fmt=json";
	cout << urlRequest << endl;

	string readBuffer;
	int runStatus = RetrieveMarketData(urlRequest, readBuffer);
	if (runStatus != 0)
	{
		cout << "Failed in retrieving market data!" << endl;
		return -1;
	}

	Stock myStock(symbol);
	runStatus = PopulateIntradayTrades(readBuffer, myStock);
	if (runStatus != 0)
	{
		cout << "Failed in parsing market data!" << endl;
		return -1;
	}

	// Create and open a text file for output
	ofstream outputFile("Results.txt");
	
	if (!outputFile.is_open()) {
		cout << "Failed to open Results.txt for writing!" << endl;
		return -1;
	}
	
	// Redirect stock output to the file
	outputFile << myStock;
	
	// Close the file
	outputFile.close();
	
	cout << "Results successfully written to Results.txt" << endl;
	
	return 0;
}