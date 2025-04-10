#pragma once
#include <string>

class Stock;

int RetrieveMarketData(const std::string& url_request, std::string& read_buffer);
int PopulateIntradayTrades(const std::string& read_buffer, Stock& stock);
