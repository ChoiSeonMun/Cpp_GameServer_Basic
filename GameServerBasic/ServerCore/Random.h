#pragma once

#include <functional>
#include <random>

using namespace std;

class Random
{
public:
    template <typename T = int32_t> requires integral<T>
    static T GetNext(int64_t maxValue)
    {
        return GetNext(0, maxValue);
    }

    template <typename T = int32_t> requires integral<T>
    static T GetNext(int64_t minValue, int64_t maxValue)
    {
        random_device rd;
        mt19937 engine(rd());
        uniform_int_distribution<T> dist(minValue, maxValue);

        return dist(engine);
    }
};