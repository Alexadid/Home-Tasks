#include "../include/stopwatch.hpp"

// Определение методов класса Stopwatch

// Конструктор класса Stopwatch
// Отсчёт начинается с момента создания объекта
Stopwatch::Stopwatch()
{
    reset();
    start();
}

// Метод для начала отсчёта времени секундомером
// Применяется как при создании секундомера,
// так и в случае необходимости возобновить его работу после паузы
void Stopwatch::start()
{
    if (!m_isRunning)
    {
        m_startTime = std::chrono::steady_clock::now() - m_pauseTime;
        m_isRunning = true;
        m_isPaused = false;
        m_pauseTime = std::chrono::steady_clock::duration::zero();
    }
}

// Метод для постановки секундомера на паузу
void Stopwatch::pause()
{
    if (m_isRunning && !m_isPaused)
    {
        auto pauseTime = std::chrono::steady_clock::now();
        m_pauseTime += pauseTime - m_startTime;
        m_isPaused = true;
        m_isRunning = false;
    }
}

// Метод для сброса времени, отсчитанного секундомером
// Для удобства отсчёт не начнётся без дополнительного использования метода start()
void Stopwatch::reset()
{
    m_isRunning = false;
    m_isPaused = false;
    m_startTime = std::chrono::steady_clock::time_point();
    m_pauseTime = std::chrono::steady_clock::duration::zero();
}
