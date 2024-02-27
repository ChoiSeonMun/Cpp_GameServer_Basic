#include "stdafx.h"


int main()
{
	printf("yesterday %ws\n", CLOCK.GetYesterdayString().c_str());
	printf("today %ws\n", CLOCK.GetTodayString().c_str());
	printf("tomorrow %ws\n", CLOCK.GetTomorrowString().c_str());
	printf("today is [%d] week of the day\n", static_cast<int>(CLOCK.GetTodayOfWeek()));

	printf("system = %llu\n", NOW_TICK());
	for (int counter = 1; counter < 10; ++counter)
	{
		printf("%ws\n", CLOCK.GetNowTimeStringWithMilliSec().c_str());
	}

	return 0;
}