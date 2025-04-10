[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/IUq-ozRz)
# Homework_Assignment_1
Modify our class example, FRE7831_MarketData_JSON, to pull and parse all the available intraday trading data. Then populate the data into an object of the class IntradayTrade.
Convert the timestamp to NY local time:

		time_t t = timestamp;
		struct tm* tm = localtime(&t);
		sprintf(datetime, "%s", asctime(tm));
  
Redirect the output of your program to Results.txt.

Submit your project source cpp and header files and Results.txt.

