#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <chrono>
#include <iostream>
#include <vector>
#include <algorithm>

// Объявление класса Stopwatch
class Stopwatch
{
public:
    // Конструктор секундомера
    Stopwatch();

    // Метод запуска отсчёта секундомера
    void start();

    // Метод для постановки секундомера на паузу
    void pause();

    // Сброс времени секундомера
    void reset();

    // Метод-шаблон для получения времени, прошедшего с начала отсчёта,
    // в указанных единицах измерения
    template<typename DurationType>
    auto elapsed() const
    {
        if (m_isRunning)
        {
            return std::chrono::duration_cast<DurationType>(std::chrono::steady_clock::now() - m_startTime - m_pauseTime).count();
        }
        else if (m_isPaused)
        {
            return std::chrono::duration_cast<DurationType>(m_pauseTime).count();
        }

        return DurationType::zero().count();
    }

private:
    std::chrono::steady_clock::time_point m_startTime;  // Время начала отсчёта
    std::chrono::steady_clock::duration m_pauseTime;    // Время постановки секундомера на паузу
    bool m_isRunning = false;
    bool m_isPaused = false;
};

#endif // STOPWATCH_HPP
