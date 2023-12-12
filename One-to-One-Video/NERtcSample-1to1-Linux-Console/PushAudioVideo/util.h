#ifndef UTIL_H
#define UTIL_H

#include <sys/timeb.h>
#include <time.h>

static uint64_t get_time_ms()
{
    timeb time_now;
    ftime(&time_now); // 秒数
    uint64_t time_cur = time_now.time * 1000 + time_now.millitm; // 毫秒
    return time_cur;
}

static int64_t SystemTimeNanos() {
  int64_t ticks;
  struct timespec ts;
  // TODO(deadbeef): Do we need to handle the case when CLOCK_MONOTONIC is not
  // supported?
  clock_gettime(CLOCK_MONOTONIC, &ts);
  ticks = 1000000000 * static_cast<int64_t>(ts.tv_sec) +
          static_cast<int64_t>(ts.tv_nsec);
  return ticks;
}

static int64_t TimeMicros() {
  return SystemTimeNanos() / 1000;
}

#endif