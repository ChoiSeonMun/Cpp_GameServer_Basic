#include "stdafx.h"
#include "Clock.h"

Clock::Clock()
{
	_serverStartTick = GetSystemTick();
}

tick_t Clock::GetServerStartTick()
{
	return _serverStartTick;
}

tick_t Clock::GetSystemTick()
{
	return system_clock::to_time_t(system_clock::now());
}

tick_t Clock::GetTickFromString(wstr_t str, const wchar_t* format)
{
	int year = 0;
	int month = 0;
	int day = 0;
	int hour = 0;
	int minute = 0;
	int second = 0;

	swscanf_s(str.c_str(), format, &year, &month, &day, &hour, &minute, &second);

	// NOTE : month는 0부터 year는 1900년부터 시작한다.
	tm time = { second, minute, hour, day, month - 1, year - 1900 };

	return mktime(&time);
}

wstr_t Clock::GetNowTimeString(const wchar_t* format)
{
	tick_t systemTick = GetSystemTick();

	return getTickString(systemTick, format);
}

wstr_t Clock::GetNowTimeStringWithMilliSec(const wchar_t* format)
{
#if 0
	TimePoint now = system_clock::now();
	TimePoint oldSecond = system_clock::from_time_t(GetSystemTick());

	duration<double> milliSecond = now - oldSecond;
	array<wchar_t, SIZE_8> milliStr;
	snwprintf(milliStr, L"%03d", static_cast<int>(milliSecond.count() * 1000));
#else
	auto point = high_resolution_clock::now();
	auto ms = duration_cast<milliseconds>(point.time_since_epoch());

	auto sec = duration_cast<seconds>(ms);
	tick_t tick = sec.count();
	std::size_t fractionalSeconds = ms.count() % 1000;
	array<wchar_t, SIZE_8> milliStr;
	snwprintf(milliStr, L"%03d", static_cast<int>(fractionalSeconds));
#endif
	wstringstream timeStrStream;
	timeStrStream << getTickString(GetSystemTick(), format);
	timeStrStream << L".";
	timeStrStream << milliStr.data();
	
	return timeStrStream.str();
}

wstr_t Clock::GetTodayString()
{
	return getTickString(GetSystemTick(), DATE_FORMAT);
}

wstr_t Clock::GetTomorrowString()
{
	return getTickString(GetSystemTick() + DAY_TO_TICK(1), DATE_FORMAT);
}

wstr_t Clock::GetYesterdayString()
{
	return getTickString(GetSystemTick() - DAY_TO_TICK(1), DATE_FORMAT);
}

DayOfWeek Clock::GetTodayOfWeek()
{
	tm time;
	tick_t tick = GetSystemTick();
	localtime_s(&time, &tick);

	return DayOfWeek(time.tm_wday);
}

wstr_t Clock::getTickString(tick_t tick, const wchar_t* format)
{
	array<wchar_t, SIZE_128> timeStr;

	tm time;
	localtime_s(&time, &tick);
	wcsftime(timeStr.data(), timeStr.size(), format, &time);

	return timeStr.data();
}
