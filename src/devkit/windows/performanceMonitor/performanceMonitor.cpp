#include "performanceMonitor.h"

#if defined(_WIN32) || defined(_WIN64)

#include <windows.h>
#include <psapi.h>

#include "TCHAR.h"

static ULARGE_INTEGER lastCPU = {};
static ULARGE_INTEGER lastSysCPU = {};
static ULARGE_INTEGER lastUserCPU = {};
static int numProcessors = 0;
static HANDLE self = nullptr;

std::vector<float> PerformanceMonitor::cpuHistory;
std::vector<float> PerformanceMonitor::memHistory;

void PerformanceMonitor::StartMonitoring()
{
    init(); 
}

//void PerformanceMonitor::StopMonitoring()
//{
//    LogPerformanceData();
//}


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

void PerformanceMonitor::Update() {
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
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
    if (hProcess == NULL) {
        return 0.0f;
    }

    float memoryMB = 0.0f;
    if (GetProcessMemoryInfo(hProcess, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
        memoryMB = static_cast<float>(pmc.WorkingSetSize) / (1024 * 1024);
    }

    CloseHandle(hProcess);
    return memoryMB;
}
float PerformanceMonitor::getPrivateMemoryUsage()
{
    DWORD processID = GetCurrentProcessId();
    PROCESS_MEMORY_COUNTERS_EX pmc;
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
    if (hProcess == NULL) {
        return 0.0f;
    }

    float privateMB = 0.0f;
    if (GetProcessMemoryInfo(hProcess, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
        privateMB = static_cast<float>(pmc.PrivateUsage) / (1024 * 1024);
    }

    CloseHandle(hProcess);
    return privateMB;
}

#endif