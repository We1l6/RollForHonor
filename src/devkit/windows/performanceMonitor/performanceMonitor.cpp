#include "performanceMonitor.h"
#include <string>

#if defined(_WIN32) || defined(_WIN64)

#include <psapi.h>
#include <windows.h>

#include "TCHAR.h"

static ULARGE_INTEGER lastCPU = {};
static ULARGE_INTEGER lastSysCPU = {};
static ULARGE_INTEGER lastUserCPU = {};
static int numProcessors = 0;
static HANDLE self = nullptr;

std::vector<float> PerformanceMonitor::cpuHistory;
std::vector<float> PerformanceMonitor::memHistory;

void PerformanceMonitor::StartMonitoring() { init(); }

// void PerformanceMonitor::StopMonitoring()
//{
//     LogPerformanceData();
// }


void PerformanceMonitor::LogPerformanceData()
{
    float cpuUsage = getCurrentCPUUsage();
    float workingMemMB = getMemoryUsage();
    float privateMemMB = getPrivateMemoryUsage();

    std::cout << std::fixed;
    std::cout << "CPU Usage: " << cpuUsage << "%\t"
              << "Working Set: " << workingMemMB << " MB\t"
              << "Private Memory: " << privateMemMB << " MB\n";
}

void PerformanceMonitor::Update()
{
    float cpu = getCurrentCPUUsage();
    float mem = getMemoryUsage();

    if (cpuHistory.size() >= MAX_HISTORY_SIZE)
        cpuHistory.erase(cpuHistory.begin());
    if (memHistory.size() >= MAX_HISTORY_SIZE)
        memHistory.erase(memHistory.begin());

    cpuHistory.push_back(cpu);
    memHistory.push_back(mem);
}

void PerformanceMonitor::init()
{
    SYSTEM_INFO sysInfo;
    FILETIME ftime, fsys, fuser;

    GetSystemInfo(&sysInfo);
    numProcessors = sysInfo.dwNumberOfProcessors;

    GetSystemTimeAsFileTime(&ftime);
    memcpy(&lastCPU, &ftime, sizeof(FILETIME));

    self = GetCurrentProcess();
    GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
    memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
    memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));
}

float PerformanceMonitor::getCurrentCPUUsage()
{
    FILETIME ftime, fsys, fuser;
    ULARGE_INTEGER now, sys, user;
    double percent;

    GetSystemTimeAsFileTime(&ftime);
    memcpy(&now, &ftime, sizeof(FILETIME));

    GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
    memcpy(&sys, &fsys, sizeof(FILETIME));
    memcpy(&user, &fuser, sizeof(FILETIME));
    percent = (sys.QuadPart - lastSysCPU.QuadPart) +
              (user.QuadPart - lastUserCPU.QuadPart);
    percent /= (now.QuadPart - lastCPU.QuadPart);
    percent /= numProcessors;
    lastCPU = now;
    lastUserCPU = user;
    lastSysCPU = sys;

    return percent * 100;
}

float PerformanceMonitor::getMemoryUsage()
{
    DWORD processID = GetCurrentProcessId();
    PROCESS_MEMORY_COUNTERS_EX pmc;
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                                  FALSE, processID);
    if (hProcess == NULL)
    {
        return 0.0f;
    }

    float memoryMB = 0.0f;
    if (GetProcessMemoryInfo(hProcess, (PROCESS_MEMORY_COUNTERS *)&pmc,
                             sizeof(pmc)))
    {
        memoryMB = static_cast<float>(pmc.WorkingSetSize) / (1024 * 1024);
    }

    CloseHandle(hProcess);
    return memoryMB;
}
float PerformanceMonitor::getPrivateMemoryUsage()
{
    DWORD processID = GetCurrentProcessId();
    PROCESS_MEMORY_COUNTERS_EX pmc;
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                                  FALSE, processID);
    if (hProcess == NULL)
    {
        return 0.0f;
    }

    float privateMB = 0.0f;
    if (GetProcessMemoryInfo(hProcess, (PROCESS_MEMORY_COUNTERS *)&pmc,
                             sizeof(pmc)))
    {
        privateMB = static_cast<float>(pmc.PrivateUsage) / (1024 * 1024);
    }

    CloseHandle(hProcess);
    return privateMB;
}

void PerformanceMonitor::Render()
{
    static bool initialized = false;
    static bool paused = false;

    if (!initialized)
    {
        PerformanceMonitor::StartMonitoring();
        initialized = true;
    }
    if (ImGui::Button(paused ? "Resume" : "Pause"))
    {
        paused = !paused;
    }

    ImGui::SameLine();
    ImGui::Text(paused ? "Paused" : "Running");

    if (!paused)
    {
        PerformanceMonitor::Update();
    }

    // --- CPU Usage ---
    const auto &cpuHistory = PerformanceMonitor::GetCpuHistory();
    ImGui::Text("CPU Usage:");
    if (!cpuHistory.empty())
    {
        float maxCpu = *std::max_element(cpuHistory.begin(), cpuHistory.end());
        float minCpu = *std::min_element(cpuHistory.begin(), cpuHistory.end());
        float avgCpu =
            std::accumulate(cpuHistory.begin(), cpuHistory.end(), 0.0f) /
            cpuHistory.size();
        float y_min = minCpu;
        float y_max = maxCpu;

        if (y_min == y_max)
        {
            y_max = y_min + 1.0f;
        }

        ImGui::PlotLines("##cpu", cpuHistory.data(), (int)cpuHistory.size(), 0,
                         nullptr, 0.0f, y_max * PLOT_SCALE_PADDING,
                         ImVec2(0, PLOT_HEIGHT));

        ImGui::SameLine();
        ImGui::SetCursorPosX(PLOT_STATISTICS_POSITION);
        ImGui::Text("Min: %.1f%%", minCpu);
        ImGui::SameLine();
        ImGui::Text("Avg: %.1f%%", avgCpu);
        ImGui::SameLine();
        ImGui::Text("Max: %.1f%%", maxCpu);
    }

    ImGui::Separator();

    // --- Memory Usage ---
    const auto &memHistory = PerformanceMonitor::GetMemHistory();
    ImGui::Text("Memory Usage (MB):");

    if (!memHistory.empty())
    {
        float avgMem =
            std::accumulate(memHistory.begin(), memHistory.end(), 0.0f) /
            memHistory.size();
        float minMem = *std::min_element(memHistory.begin(), memHistory.end());
        float maxMem = *std::max_element(memHistory.begin(), memHistory.end());

        ImGui::PlotLines("##mem", memHistory.data(),
                         static_cast<int>(memHistory.size()), 0, nullptr, 0.0f,
                         maxMem * PLOT_SCALE_PADDING, ImVec2(0, PLOT_HEIGHT));

        ImGui::SameLine();
        ImGui::SetCursorPosX(PLOT_STATISTICS_POSITION);
        ImGui::Text("Min: %.1f MB", minMem);
        ImGui::SameLine();
        ImGui::Text("Avg: %.1f MB", avgMem);
        ImGui::SameLine();
        ImGui::Text("Max: %.1f MB", maxMem);
    }
}

#elif defined(__linux__)

/*
cpu  user nice system idle iowait irq softirq steal guest guest_nice

*/
#include <fstream>
#include <sstream>
void PerformanceMonitor::StartMonitoring() { init(); }

// void PerformanceMonitor::StopMonitoring()
//{
//     LogPerformanceData();
// }

#include "imgui.h"
#include <sys/sysinfo.h>
void PerformanceMonitor::LogPerformanceData() {}

void PerformanceMonitor::Update() {}

void PerformanceMonitor::init() {}

float PerformanceMonitor::getCurrentCPUUsage() {}

float PerformanceMonitor::getMemoryUsage() {}
float PerformanceMonitor::getPrivateMemoryUsage() {}

void PerformanceMonitor::Render()
{
    struct sysinfo info;
    sysinfo(&info);

    double load_1min =
        static_cast<double>(info.loads[0]) / (1 << SI_LOAD_SHIFT);
    double load_5min =
        static_cast<double>(info.loads[1]) / (1 << SI_LOAD_SHIFT);
    double load_15min =
        static_cast<double>(info.loads[2]) / (1 << SI_LOAD_SHIFT);

    std::string str =
        "CPU load (1 min avg):\t" + std::to_string(load_1min) + "\n" +
        "CPU load (5 min avg):\t" + std::to_string(load_5min) + "\n" +
        "CPU load (15 min avg):\t" + std::to_string(load_15min) + "\n" +
        "Uptime: " + std::to_string(info.uptime) + " seconds\n" +
        "Total RAM: " + std::to_string(info.totalram / 1024 / 1024) + " MB\n" +
        "Free RAM: " + std::to_string(info.freeram / 1024 / 1024) + " MB\n" +
        "Load Average: " + std::to_string(info.loads[0]) + "\n" +
        "Processes: " + std::to_string(info.procs) + "\n";

    ImGui::Text("%s", str.c_str());
}

#endif