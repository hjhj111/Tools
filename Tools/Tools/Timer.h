/*
 * @Author: your name
 * @Date: 2022-01-05 09:44:41
 * @LastEditTime: 2022-01-05 10:16:11
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \Tools\Timer.h
 */
#pragma once
#include <chrono>
#include <mutex>
#include <future>
#include <condition_variable>

class Timer
{
public:
    Timer()
    {
    }

    Timer(const Timer& timer)
    {
        m_stop = timer.m_stop;
    }

    ~Timer()
    {
        stop();
    }

    void start(int interval, std::function<void()> task)
    {
        if (!m_stop)
            return;
        m_stop = false;

        m_future = std::async(std::launch::async, [this, interval, task]()
        {
            while (true)
            {
                std::unique_lock<std::mutex> lock(m_mutex);
                const auto status = m_cv.wait_for(lock, std::chrono::milliseconds(interval));
                if(status == std::cv_status::timeout)
                    task();
                else if(m_stop)
                    break;
            }
        });
    }

    void stop()
    {
        if (m_stop)
            return;

        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_stop = true;
        }
        m_cv.notify_one();
        m_future.wait();
    }

private:
    bool m_stop{ true };
    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::future<void> m_future;
};

