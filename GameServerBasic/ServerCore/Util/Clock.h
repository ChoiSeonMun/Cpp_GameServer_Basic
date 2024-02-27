#pragma once

// ---------------------------------------------
// Define
// ---------------------------------------------
#define	CLOCK			Clock::GetInstance()
#define NOW_TICK		CLOCK.GetSystemTick
#define NOW_STRING		CLOCK.GetNowTimeString

#define TICK_MIN		(60)
#define TICK_HOUR		(TICK_MIN * 60)
#define TICK_DAY		(TICK_HOUR * 24)

#define TICK_TO_MIN(x)	(x / TICK_MIN)
#define MIN_TO_TICK(x)	(x * TICK_MIN)

#define TICK_TO_HOUR(x) (x / TICK_HOUR)
#define HOUR_TO_TICK(x) (x * TICK_HOUR)

#define TICK_TO_DAY(x) (x / TICK_DAY)
#define DAY_TO_TICK(x) (x * TICK_DAY)

#define DATETIME_FORMAT L"D%Y-%m-%dT%H:%M:%S"
#define DATE_FORMAT		L"%Y-%m-%d"
#define TIME_FORMAT		L"%H:%M:%S"
#define DB_TIME_FORMAT	L"%4d-%2d-%2d %2d:%2d:%2d"

using namespace std;
using namespace std::chrono;

using TimePoint = system_clock::time_point;

enum class DayOfWeek
{
	Sunday,
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday
};

class Clock : public Singleton<Clock>
{
public:
	Clock();
	
	tick_t	GetServerStartTick();
	tick_t	GetSystemTick();
	tick_t	GetTickFromString(wstr_t str, const wchar_t* format = DB_TIME_FORMAT);

	wstr_t	GetNowTimeString(const wchar_t* format = DATETIME_FORMAT);
	wstr_t	GetNowTimeStringWithMilliSec(const wchar_t* format = DATETIME_FORMAT);

	wstr_t	GetTodayString();
	wstr_t	GetTomorrowString();
	wstr_t	GetYesterdayString();

	DayOfWeek GetTodayOfWeek();

private:
	wstr_t	getTickString(tick_t tick, const wchar_t* format = DATETIME_FORMAT);
private:
	tick_t	_serverStartTick;
};
