#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <thread>

/// <summary>
/// 函数测量结果
/// </summary>
struct ProfileResult
{
    std::string Name;
    long long Start, End;//开始时间，结束时间
    uint32_t ThreadID;//线程id
};

/// <summary>
/// 插桩会话
/// </summary>
struct InstrumentationSession
{
    std::string Name;
};


/// <summary>
/// 插桩（单例）
/// </summary>
class Instrumentor
{
private:
    InstrumentationSession* m_CurrentSession;
    std::ofstream m_OutputStream;               //文件流
    int m_ProfileCount;                         //输出计数
public:
    Instrumentor()
        : m_CurrentSession(nullptr), m_ProfileCount(0)
    {
    }

    void BeginSession(const std::string& name, const std::string& filepath = "results.json")
    {
        m_OutputStream.open(filepath);
        WriteHeader();
        m_CurrentSession = new InstrumentationSession{ name };
    }

    void EndSession()
    {
        WriteFooter();
        m_OutputStream.close();
        delete m_CurrentSession;
        m_CurrentSession = nullptr;
        m_ProfileCount = 0;
    }

    void WriteProfile(const ProfileResult& result)
    {
        if (m_ProfileCount++ > 0)
            m_OutputStream << ",";

        std::string name = result.Name;
        std::replace(name.begin(), name.end(), '"', '\'');//范围内查找与替换

        m_OutputStream << "{";
        m_OutputStream << "\"cat\":\"function\",\n";
        m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',' << "\n";
        m_OutputStream << "\"name\":\"" << name << "\",\n";
        m_OutputStream << "\"ph\":\"X\",\n";
        m_OutputStream << "\"pid\":0,\n";
        m_OutputStream << "\"tid\":" << result.ThreadID << ",\n";
        m_OutputStream << "\"ts\":" << result.Start << "\n";
        m_OutputStream << "}";
        m_OutputStream << "\n";

        m_OutputStream.flush();//输出缓冲
    }

    //json文件头部
    void WriteHeader()
    {
        m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
        m_OutputStream.flush();//输出缓冲
    }

    //json文件尾部
    void WriteFooter()
    {
        m_OutputStream << "]}";
        m_OutputStream.flush();//输出缓冲
    }

    static Instrumentor& Get()//单例
    {
        static Instrumentor instance;
        return instance;
    }
};




//计时器

/// <summary>
/// 插桩计时器
/// </summary>
class InstrumentationTimer
{
public:
    InstrumentationTimer(const char* name, int minTime = 0, int offsetTime = 0)
        : m_Name(name), m_Stopped(false), m_minTime(minTime), m_offsetTime(offsetTime)
    {
        m_StartTimepoint = std::chrono::high_resolution_clock::now();
    }

    ~InstrumentationTimer()
    {
        if (!m_Stopped)
            Stop();
    }

    void Stop()
    {
        auto endTimepoint = std::chrono::high_resolution_clock::now();

        long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count() + m_offsetTime;
        long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count() + m_offsetTime;

        end = (end - start) < m_minTime ? start + m_minTime : end;

        uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());//函数对象
        Instrumentor::Get().WriteProfile({ m_Name, start, end, threadID });//输出文件

        m_Stopped = true;
    }
private:
    const char* m_Name;                                                             //函数名称
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;   //开始时间
    bool m_Stopped;                                                                 //是否停止计时
    int m_minTime;
    int m_offsetTime;
};


#define PROFLING 0
#if PROFLING
#define PROFILE_SCOPE(name, minTime, offsetTime) InstrumentationTimer time##__LINE__(name, minTime, offsetTime)
#define PROFILE_FUNCTION(minTime, offsetTime) PROFILE_SCOPE(__FUNCSIG__ , minTime, offsetTime)
#else
#define PROFILE_SCOPE(name, minTime, offsetTime)
#define PROFILE_FUNCTION(minTime, offsetTime)
#endif