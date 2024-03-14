#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <iostream>
#include <string>



// Структура, хранящая запись о студенте (кусок базы данных, в общем)
struct StudentRecord
{
    std::string name;
    int groupNumber;
    // GPA - Grade Point Average --- Средний Балл
    double gpa;

    StudentRecord(std::string name, int groupNumber, double gpa)
        : name(std::move(name)), groupNumber(groupNumber), gpa(gpa) {}
};

// Тэги для доступа по каждому из индексов
struct by_name{};
struct by_gpa{};
struct random_access{};

// Великий и ужасный Мульти-индекс Контейнер
typedef boost::multi_index::multi_index_container<
    StudentRecord,
    boost::multi_index::indexed_by<
        // Сортируем по среднему баллу
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<by_gpa>, boost::multi_index::member<StudentRecord, double, &StudentRecord::gpa>,
            std::greater<double> // Стоит отметить, что это сортирует средний балл в убывающем порядке
        >,
        // Хэшированный индекс по фамилии
        boost::multi_index::hashed_non_unique<
            boost::multi_index::tag<by_name>, boost::multi_index::member<StudentRecord, std::string, &StudentRecord::name>
        >,
        // Random access теперь есть!
        boost::multi_index::random_access<
            boost::multi_index::tag<random_access>
        >
    >
> StudentRecords;

int main() 
{
    // А вот теперь переходим к демонстрации...

    // Создаём экземпляр контайнера
    StudentRecords records;

    // Вставим немного записей
    // В этот раз, пожалуй, обойдёмся без случайной генерации
    records.insert(StudentRecord("John Doe", 1, 3.5));
    records.insert(StudentRecord("Alice Johnson", 1, 3.9));
    records.insert(StudentRecord("Jane Smith", 2, 3.7));

    // Демонстрируем random access
    std::cout << "Random access to the second student record:" << std::endl;
    const auto& ra_index = records.get<random_access>();
    // Стоит удостовериться, что записей хотя бы 2
    if(ra_index.size() > 1)
    {
        // Попробуем получить доступ ко второй записи
        const auto& record = ra_index[1];
        std::cout << record.name << " - GPA: " << record.gpa << std::endl;
    } else 
    {
        std::cout << "Insufficient records for random access." << std::endl;
    }

    // Доступ по среднему баллу
    std::cout << "Students sorted by GPA (descending):" << std::endl;
    const auto& gpa_index = records.get<by_gpa>();
    for(const auto& record : gpa_index)
    {
        std::cout << record.name << " - GPA: " << record.gpa << std::endl;
    }

    // Находим запись по фамилии
    std::cout << "\nLookup by last name:" << std::endl;
    const auto& name_index = records.get<by_name>();
    auto it = name_index.find("Jane Smith");
    if(it != name_index.end())
    {
        std::cout << it->name << " - GPA: " << it->gpa << std::endl;
    } else
    {
        std::cout << "Student not found." << std::endl;
    }

    return 0;
}
