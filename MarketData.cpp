#include "json/json.h"
#include "curl/curl.h"

#include "Stock.h"
#include "MarketData.h"
#include "Util.h"

int RetrieveMarketData(const string& url_request, string& read_buffer)
{
	curl_global_init(CURL_GLOBAL_ALL);

	CURL* handle;
	CURLcode status;

	handle = curl_easy_init();
	if (!handle)
	{
		cout << "curl_easy_init failed" << endl;
		return -1;
	}

	curl_easy_setopt(handle, CURLOPT_URL, url_request.c_str());
	curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64)");
	curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
	curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, &read_buffer);

	status = curl_easy_perform(handle);
	if (status != CURLE_OK) {
		cout << "curl_easy_perform() failed: " << curl_easy_strerror(status) << endl;
		return -1;
	}

	curl_easy_cleanup(handle);
	return 0;
}

int PopulateIntradayTrades(const string& read_buffer, Stock& stock)
{
	Json::Reader reader;
	Json::Value root;

	if (!reader.parse(read_buffer, root))
	{
		cout << "Failed to parse JSON: " << reader.getFormattedErrorMessages();
		return -1;
	}

	cout << "\nSuccessfully parsed JSON data\n";

	long timestamp;
	char datetime[30];
	float open, high, low, close;
	int volume;

	for (const auto& trade : root)
	{
		timestamp = trade["timestamp"].asInt64();
		time_t t = timestamp;
		struct tm* tm = localtime(&t);
		strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", tm);

		open = trade["open"].asFloat();
		high = trade["high"].asFloat();
		low = trade["low"].asFloat();
		close = trade["close"].asFloat();
		volume = trade["volume"].asInt();

		IntradayTrade aTrade(timestamp, datetime, open, high, low, close, volume);
		stock.addIntradayTrade(aTrade);
	}

	return 0;
}
