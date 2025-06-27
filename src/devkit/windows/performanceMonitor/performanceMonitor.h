#pragma once

#if defined(_WIN32) || defined(_WIN64)

#include <iostream>
#include <vector>
class PerformanceMonitor
{
public:
	static void StartMonitoring();
	//static void StopMonitoring();
    static void LogPerformanceData();

    static void Update();

    static const std::vector<float>& GetCpuHistory() { return cpuHistory; }
    static const std::vector<float>& GetMemHistory() { return memHistory; }
private:
    static std::vector<float> cpuHistory;
    static std::vector<float> memHistory;


    static void init();
    static float getCurrentCPUUsage();
	static float getPrivateMemoryUsage();
	static float getMemoryUsage();

    static constexpr int MAX_HISTORY_SIZE = 100;
};
#endif
//#if defined(__linux__)
//
//#elif defined(__APPLE__) || defined(__MACH__)