#include "performanceMonitor.h"

auto lastFrameTime = std::chrono::high_resolution_clock::now();
std::thread PerformanceMonitor::gpuThread;
std::atomic<bool> PerformanceMonitor::monitoringActive(false);
float PerformanceMonitor::cachedGPUUsage = -1.0f;
float PerformanceMonitor::cachedVRAMUsage = -1.0f;
std::mutex PerformanceMonitor::dataMutex;
#if defined(_WIN32) || defined(_WIN64)

#include <windows.h>
#include <tchar.h>  
#include <psapi.h>

static ULARGE_INTEGER lastCPU = {};
static ULARGE_INTEGER lastSysCPU = {};
static ULARGE_INTEGER lastUserCPU = {};
static int numProcessors = 0;
static HANDLE self = nullptr;

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

float PerformanceMonitor::GetAverageCPU()
{
	if (cpuHistory.empty())
		return 0.0f;
	float sum = std::accumulate(cpuHistory.begin(), cpuHistory.end(), 0.0f);
	return sum / cpuHistory.size();
}

float PerformanceMonitor::GetAverageMemory()
{
	if (memHistory.empty())
		return 0.0f;
	float sum = std::accumulate(memHistory.begin(), memHistory.end(), 0.0f);
	return sum / memHistory.size();
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

	// Get NVIDIA GPU name
	nvidiaGPUName = getNvidiaGPUName();
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

float PerformanceMonitor::GetFPS()
{
    auto now = std::chrono::high_resolution_clock::now();
    float frameTime = std::chrono::duration<float>(now - lastFrameTime).count();
    lastFrameTime = now;
    if (frameTime > 0)
        return 1.0f / frameTime;
    else
        return 0.0f;
}

std::string PerformanceMonitor::getNvidiaGPUName()
{
    const char* command = "nvidia-smi --query-gpu=name --format=csv,noheader";
    std::array<char, 128> buffer;
    std::string result;

    FILE* pipe = _popen(command, "r");
    if (!pipe) return "";

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr)
        result += buffer.data();

    _pclose(pipe);

    size_t end = result.find_last_not_of(" \n\r\t");
    if (end != std::string::npos)
        result = result.substr(0, end + 1);
    else
        result.clear();

    return result;
}

float PerformanceMonitor::GetAverageGPU()
{
    if (gpuHistory.empty()) return 0.0f;

    float sum = std::accumulate(gpuHistory.begin(), gpuHistory.end(), 0.0f);
    return sum / gpuHistory.size();
}

float PerformanceMonitor::GetAverageVRAM()
{
    if (vramHistory.empty()) return 0.0f;

    float sum = std::accumulate(vramHistory.begin(), vramHistory.end(), 0.0f);
    return sum / vramHistory.size();
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


void PerformanceMonitor::StartGPUMonitoring()
{
    if (monitoringActive.load()) return;

    monitoringActive = true;
    gpuThread = std::thread(&PerformanceMonitor::GPUMonitorLoop);
}

void PerformanceMonitor::StopGPUMonitoring()
{
    if (!monitoringActive.load()) return;

    monitoringActive = false;
    if (gpuThread.joinable())
        gpuThread.join();
}

float PerformanceMonitor::GetCurrentGPUUsage()
{
    std::lock_guard<std::mutex> lock(dataMutex);
    return cachedGPUUsage;
}

float PerformanceMonitor::GetCurrentVRAMUsage()
{
    std::lock_guard<std::mutex> lock(dataMutex);
    return cachedVRAMUsage;
}

void PerformanceMonitor::GPUMonitorLoop()
{
    while (monitoringActive.load())
    {
        float gpuUsage = QueryGPUUsage();
        float vramUsage = QueryVRAMUsage();

        {
            std::lock_guard<std::mutex> lock(dataMutex);
            cachedGPUUsage = gpuUsage;
            cachedVRAMUsage = vramUsage;

            gpuHistory.push_back(gpuUsage);
            vramHistory.push_back(vramUsage);

            if (gpuHistory.size() > MAX_HISTORY_SIZE)
                gpuHistory.erase(gpuHistory.begin());
            if (vramHistory.size() > MAX_HISTORY_SIZE)
                vramHistory.erase(vramHistory.begin());
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

float PerformanceMonitor::QueryGPUUsage()
{
    const char* cmd = "nvidia-smi --query-gpu=utilization.gpu --format=csv,noheader,nounits";
    std::array<char, 64> buffer;
    std::string result;
    FILE* pipe = _popen(cmd, "r");
    if (!pipe) return -1.0f;

    if (fgets(buffer.data(), buffer.size(), pipe) != nullptr)
        result = buffer.data();

    _pclose(pipe);

    try {
        return std::stof(result);
    }
    catch (...) {
        return -1.0f;
    }
}

float PerformanceMonitor::QueryVRAMUsage()
{
    const char* cmd = "nvidia-smi --query-gpu=memory.used --format=csv,noheader,nounits";
    std::array<char, 64> buffer;
    std::string result;
    FILE* pipe = _popen(cmd, "r");
    if (!pipe) return -1.0f;

    if (fgets(buffer.data(), buffer.size(), pipe) != nullptr)
        result = buffer.data();

    _pclose(pipe);

    try {
        return std::stof(result);
    }
    catch (...) {
        return -1.0f;
    }
}

void PerformanceMonitor::Render()
{
    static bool initialized = false;
    static bool paused = false;

    if (!initialized)
    {
        StartMonitoring();
        initialized = true;
    }

    //Pause/Resume button
    if (ImGui::Button(paused ? "Resume" : "Pause"))
    {
        paused = !paused;
    }
    ImGui::SameLine();
    ImGui::Text(paused ? "Paused" : "Running");

    //Checkboxes
    ImGui::Checkbox("CPU Usage", &cpuMonitorEnabled);
    ImGui::SameLine();
    if (ImGui::Checkbox("GPU Usage", &gpuMonitorEnabled))
    {
        if (gpuMonitorEnabled)
            StartGPUMonitoring();
        else
            StopGPUMonitoring();
    }
    ImGui::SameLine();
    ImGui::Checkbox("RAM Usage", &ramMonitorEnabled);
    ImGui::SameLine();
    ImGui::Checkbox("FPS", &fpsMonitorEnabled);

    ImGui::Separator();

    if (!paused)
    {
        Update(); 
    }

    //--- CPU Usage ---
    if (cpuMonitorEnabled)
    {
        const auto& cpuHistory = GetCpuHistory();
        ImGui::Text("CPU Usage:");
        if (!cpuHistory.empty())
        {
            float minCpu = *std::min_element(cpuHistory.begin(), cpuHistory.end());
            float maxCpu = *std::max_element(cpuHistory.begin(), cpuHistory.end());
            float avgCpu = GetAverageCPU();

            if (minCpu == maxCpu) maxCpu = minCpu + 1.0f;

            ImGui::PlotLines("##cpuPlot", cpuHistory.data(), (int)cpuHistory.size(), 0, nullptr,
                0.0f, maxCpu * PLOT_SCALE_PADDING, ImVec2(0, PLOT_HEIGHT));

            ImGui::SameLine();
            ImGui::SetCursorPosX(PLOT_STATISTICS_POSITION);
            ImGui::Text("Min: %.1f%%", minCpu);
            ImGui::SameLine();
            ImGui::Text("Avg: %.1f%%", avgCpu);
            ImGui::SameLine();
            ImGui::Text("Max: %.1f%%", maxCpu);
        }
        else
        {
            ImGui::Text("No CPU data yet.");
        }
        ImGui::Separator();
    }

    //--- GPU Usage ---
    if (gpuMonitorEnabled)
    {
        ImGui::Text("GPU Usage: %s", nvidiaGPUName.empty() ? "NVIDIA GPU" : nvidiaGPUName.c_str());

        const auto& gpuHist = GetGPUHistory();
        const auto& vramHist = GetVRAMHistory();

        if (!gpuHist.empty() && !vramHist.empty())
        {
            float minGPU = *std::min_element(gpuHist.begin(), gpuHist.end());
            float maxGPU = *std::max_element(gpuHist.begin(), gpuHist.end());
            float avgGPU = GetAverageGPU();

            float minVRAM = *std::min_element(vramHist.begin(), vramHist.end());
            float maxVRAM = *std::max_element(vramHist.begin(), vramHist.end());
            float avgVRAM = GetAverageVRAM();

            if (minGPU == maxGPU) maxGPU = minGPU + 1.0f;
            if (minVRAM == maxVRAM) maxVRAM = minVRAM + 1.0f;

            ImGui::PlotLines("##gpuPlot", gpuHist.data(), (int)gpuHist.size(), 0, nullptr,
                0.0f, 100.0f, ImVec2(0, PLOT_HEIGHT));
            ImGui::SameLine();
            ImGui::SetCursorPosX(PLOT_STATISTICS_POSITION);
            ImGui::Text("Min: %.1f%%", minGPU);
            ImGui::SameLine();
            ImGui::Text("Avg: %.1f%%", avgGPU);
            ImGui::SameLine();
            ImGui::Text("Max: %.1f%%", maxGPU);

            ImGui::Text("VRAM Usage (MB):");
            ImGui::PlotLines("##vramPlot", vramHist.data(), (int)vramHist.size(), 0, nullptr,
                0.0f, maxVRAM * PLOT_SCALE_PADDING, ImVec2(0, PLOT_HEIGHT));
            ImGui::SameLine();
            ImGui::SetCursorPosX(PLOT_STATISTICS_POSITION);
            ImGui::Text("Min: %.1f MB", minVRAM);
            ImGui::SameLine();
            ImGui::Text("Avg: %.1f MB", avgVRAM);
            ImGui::SameLine();
            ImGui::Text("Max: %.1f MB", maxVRAM);
        }
        else
        {
            ImGui::Text("GPU data not available.");
        }
        ImGui::Separator();
    }

    //--- RAM Usage ---
    if (ramMonitorEnabled)
    {
        const auto& memHistory = GetMemHistory();
        ImGui::Text("Memory Usage (MB):");
        if (!memHistory.empty())
        {
            float minMem = *std::min_element(memHistory.begin(), memHistory.end());
            float maxMem = *std::max_element(memHistory.begin(), memHistory.end());
            float avgMem = GetAverageMemory();

            if (minMem == maxMem) maxMem = minMem + 1.0f;

            ImGui::PlotLines("##ramPlot", memHistory.data(), (int)memHistory.size(), 0, nullptr,
                0.0f, maxMem * PLOT_SCALE_PADDING, ImVec2(0, PLOT_HEIGHT));

            ImGui::SameLine();
            ImGui::SetCursorPosX(PLOT_STATISTICS_POSITION);
            ImGui::Text("Min: %.1f MB", minMem);
            ImGui::SameLine();
            ImGui::Text("Avg: %.1f MB", avgMem);
            ImGui::SameLine();
            ImGui::Text("Max: %.1f MB", maxMem);
        }
        else
        {
            ImGui::Text("No memory data yet.");
        }
        ImGui::Separator();
    }

    //--- FPS ---
    if (fpsMonitorEnabled)
    {
        const auto& fpsHist = GetFPSHistory();
        float currentFPS = GetFPS();

        if (currentFPS > 0.0f)
        {
            if (!paused)
            {
                fpsHistory.push_back(currentFPS);
                if (fpsHistory.size() > MAX_HISTORY_SIZE)
                    fpsHistory.erase(fpsHistory.begin());
            }
        }

        ImGui::Text("FPS: %.0f", currentFPS);
        if (!fpsHist.empty())
        {
            float minFPS = *std::min_element(fpsHist.begin(), fpsHist.end());
            float maxFPS = *std::max_element(fpsHist.begin(), fpsHist.end());
            float avgFPS = std::accumulate(fpsHist.begin(), fpsHist.end(), 0.0f) / fpsHist.size();

            if (minFPS == maxFPS) maxFPS = minFPS + 1.0f;

            ImGui::PlotLines("##fpsPlot", fpsHist.data(), (int)fpsHist.size(), 0, nullptr,
                0.0f, maxFPS * PLOT_SCALE_PADDING, ImVec2(0, 80));

            ImGui::SameLine();
            ImGui::SetCursorPosX(PLOT_STATISTICS_POSITION);
            ImGui::Text("Min: %.0f", minFPS);
            ImGui::SameLine();
            ImGui::Text("Avg: %.0f", avgFPS);
            ImGui::SameLine();
            ImGui::Text("Max: %.0f", maxFPS);
        }
        else
        {
            ImGui::Text("No FPS data yet.");
        }
    }
}