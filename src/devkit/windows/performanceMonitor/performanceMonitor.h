#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <numeric>
#include <string>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include <cstdio>
#include "imgui.h"

class PerformanceMonitor
{
public:
    //Lifecycle
    static void StartMonitoring();
    static void StopMonitoring();

    //GPU monitoring control
    static void StartGPUMonitoring();
    static void StopGPUMonitoring();

    //Data getters
    static float GetCurrentGPUUsage();
    static float GetCurrentVRAMUsage();
    static float GetAverageCPU();
    static float GetAverageGPU();
    static float GetAverageVRAM();
    static float GetAverageMemory();
    static float GetFPS();

    //History getters
    static const std::vector<float>& GetCpuHistory() { return cpuHistory; }
    static const std::vector<float>& GetGPUHistory() { return gpuHistory; }
    static const std::vector<float>& GetVRAMHistory() { return vramHistory; }
    static const std::vector<float>& GetMemHistory() { return memHistory; }
    static const std::vector<float>& GetFPSHistory() { return fpsHistory; }

    //Toggles for plots
    static void ToggleCPUPlot() { cpuMonitorEnabled = !cpuMonitorEnabled; }
    static void ToggleGPUPlot() { gpuMonitorEnabled = !gpuMonitorEnabled; }
    static void ToggleRAMPlot() { ramMonitorEnabled = !ramMonitorEnabled; }
    static void ToggleFPSPlot() { fpsMonitorEnabled = !fpsMonitorEnabled; }

    //Core updates and rendering
    static void Update();
    static void Render();
    static void LogPerformanceData();

private:
    //Initialization
    static void init();

    // Internal data retrieval
    static float getCurrentCPUUsage();
    static float getPrivateMemoryUsage();
    static float getMemoryUsage();

    // GPU monitoring thread and queries
    static void GPUMonitorLoop();
    static float QueryGPUUsage();
    static float QueryVRAMUsage();
    static std::string getNvidiaGPUName();

    // Threading & synchronization
    static std::thread gpuThread;
    static std::atomic<bool> monitoringActive;
    static std::mutex dataMutex;

    //Cached GPU data to avoid blocking calls in main thread
    static float cachedGPUUsage;
    static float cachedVRAMUsage;

    //Histories
    static inline std::vector<float> cpuHistory;
    static inline std::vector<float> memHistory;
    static inline std::vector<float> gpuHistory;
    static inline std::vector<float> vramHistory;
    static inline std::vector<float> fpsHistory;

    //Enable flags for each monitor
    static inline bool cpuMonitorEnabled = true;
    static inline bool gpuMonitorEnabled = true;
    static inline bool ramMonitorEnabled = true;
    static inline bool fpsMonitorEnabled = true;

    //GPU name cache
    static inline std::string nvidiaGPUName;

    //Constants
    static constexpr int MAX_HISTORY_SIZE = 100;

    static constexpr float PLOT_HEIGHT = 100.0f;
    static constexpr float PLOT_STATISTICS_POSITION = 15.0f;
    static constexpr float PLOT_SCALE_PADDING = 1.2f;
};
