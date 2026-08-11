#ifndef TIMER_H
#define TIMER_H

#include <chrono>

using namespace std;

class Timer
{
private:
    chrono::high_resolution_clock::time_point startTime;
    chrono::high_resolution_clock::time_point endTime;

public:

    // Start the timer
    void start()
    {
        startTime = chrono::high_resolution_clock::now();
    }

    // Stop the timer
    void stop()
    {
        endTime = chrono::high_resolution_clock::now();
    }


    double elapsedMilliseconds() const
    {
        return chrono::duration<double, milli>(endTime - startTime).count();
    }
};

#endif