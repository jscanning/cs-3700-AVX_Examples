
#include "stdafx.h"
#include <chrono>
#include <utility>

using namespace std;
using namespace std::chrono;

template<typename F, typename... Args>
double funcTime(F func, Args&&... args) {
#define duration(a) duration_cast<nanoseconds>(a).count()
#define timeNow() high_resolution_clock::now()
	typedef high_resolution_clock::time_point TimeVar;
	TimeVar t1 = timeNow();
	func(forward<Args>(args)...);
	return duration(timeNow() - t1);
}
