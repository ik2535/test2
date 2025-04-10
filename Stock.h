#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class IntradayTrade
{
private:
	long timestamp;
	string datetime;
	float open;
	float high;
	float low;
	float close;
	int volume;

public:
	IntradayTrade(long timestamp_, string datetime_, float open_, float high_, float low_, float close_, int volume_) :
		timestamp(timestamp_), datetime(datetime_), open(open_), high(high_), low(low_), close(close_), volume(volume_)
	{}

	~IntradayTrade() {}

	friend ostream& operator<<(ostream& out, const IntradayTrade& t)
	{
		out << " Datetime: " << t.datetime << " Open: " << t.open
			<< " High: " << t.high << " Low: " << t.low
			<< " Close: " << t.close << " Volume: " << t.volume << endl;
		return out;
	}
};

class Stock
{
private:
	string symbol;
	vector<IntradayTrade> trades;

public:
	Stock(string symbol_) : symbol(symbol_) {}

	~Stock() {}

	void addIntradayTrade(IntradayTrade aTrade)
	{
		trades.push_back(aTrade);
	}

	friend ostream& operator<<(ostream& out, const Stock& s)
	{
		out << "Symbol: " << s.symbol << endl;
		for (const auto& trade : s.trades)
			out << trade;
		return out;
	}
};
