#include <iostream>
#include <utility>


// Вот тут пришлось попотеть, после C C++ выглядит немного удивительно...

template<typename T>
class shared_ptr
{
private:
    // Внутренний struct для управления общими ресурсами и количеством объектов, использующих данный ресурс
    // Для безопасности я обращаюсь к сырому казателю через контрольный блок...
    struct ControlBlock
    {
        T* ptr;         // Указатель на управляемый ресурс
        size_t count;   // Количество объектов, использующих (общий) ресурс

        // Конструктор для инициализации контрольного блока сырым указателем
        ControlBlock(T* p) : ptr(p), count(1) {}
    };

    // Указатель на контрольный блок
    ControlBlock* control_block;

public:
    // Конструктор по умолчанию
    // Инициализирует общий указатель с помощью nullptr
    shared_ptr() : control_block(nullptr) {}

    // Конструктор из сырого указателя
    //Иинициализирует общий указатель с помощью сырого указателя
    // Конструктор из сырого указателя
    explicit shared_ptr(T* ptr) : control_block(nullptr)
    {
        // Проверяем, не равен ли ptr nullptr перед созданием контрольного блока
        if (ptr) { control_block = new ControlBlock(ptr); }
    }

    // Конструктор из unique_ptr
    // Принимает std::unique_ptr<T> и перемещает владение ресурсом,
    // обеспечивая, что unique_ptr больше не управляет объектом.
    explicit shared_ptr(std::unique_ptr<T>&& ptr) : control_block(nullptr)
    {
        // Проверяем, не равен ли unique_ptr nullptr
        if (ptr)
        {
            // 'release' освобождает ресурс из unique_ptr и предотвращает его удаление
            control_block = new ControlBlock(ptr.release());
        }
    }

    // Копирующий конструктор
    // Создаёт shared_ptr, который делит право на ресурс с 'other'
    shared_ptr(const shared_ptr& other) : control_block(other.control_block)
    {
        if (this != &other)
        {
            if (control_block)
            {
                // Увеличиваем счётчик объектов, делящих ресурс...
                control_block->count++;
            }
        }
    }

    // Перемещающий конструктор
    // Создаёт shared_ptr, получая ресурс от 'other'
    shared_ptr(shared_ptr&& other) noexcept : control_block(nullptr)
    {
        if (this != &other)
        {
            // Swap'аем содержимое с 'other'
            swap(other);
        }
    }

    // Копирующий оператор присвоения
    // Назначает совместное владение от 'other' к *этому
    shared_ptr& operator=(const shared_ptr& other)
    {
        // Проверка на самоприсвоение
        if (this != &other)
        {
            // Очищаем текущий ресурс, если таковой имеется
            reset();
            // Копируем данные из 'other'
            control_block = other.control_block;
            if (control_block)
            {
                // Увеличиваем счётчик ссылок
                control_block->count++;
            }
        }
        return *this;
    }


    // Перемещаюзий оператор присвоения
    // Назначает совместное владение путём приобретения ресурса у 'other'
    shared_ptr& operator=(shared_ptr&& other) noexcept
    {
        // Проверка на самоприсвоение
        if (this != &other)
        {
            // Очищаем текущий ресурс
            reset();
            // Перемещаем ресурс 'other' к текущему объекту
            control_block = other.control_block;
            // Обнуляем указатель 'other' для предотвращения двойного освобождения
            other.control_block = nullptr;
        }
        return *this;
    }


    // Деструктор
    // Освобождаем общий ресурс, если это был последний из shared_ptr
    ~shared_ptr()
    {
        reset(); // Reset'им общий указатель...
    }

    // Метод reset
    // Сбрасывает общий указатель, уменьшая количество ссылок и освобождая ресурс при необходимости
    void reset()
    {
        if (control_block)
        {
            control_block->count--; // Уменьшаем счётчик
            if (control_block->count == 0) // Если не осталось обектов, делящих ресурс
            {
                delete control_block->ptr;  // Освобождаем ресурс
                delete control_block;       // Освобождаем контрольный блок
            }
            control_block = nullptr;  // Сбрасываем до nullptr
        }
    }

    // Метод swap
    // Меняет местами содержимое двух объектов shared_ptr
    void swap(shared_ptr& other) noexcept
    {
        std::swap(control_block, other.control_block);
    }

    // Метод get
    // Возвращает сырой указатель на управляемый ресурс
    T* get() const
    {
        return control_block ? control_block->ptr : nullptr; // Возращаем nullptr если контрольный блок -  nullptr
    }

    // Оператор разыменования
    // Предоставляет доступ к управляемому ресурсу
    T& operator*() const
    {
        return *(control_block->ptr);
    }

    // Оператор стрелочка
    // Предоставляет доступ к элементам управляемого ресурса
    T* operator->() const
    {
        return control_block->ptr;  // Возращаем сырой указатель на ресурс
    }

    // Метод use_count
    // Возвращает текущее количество объектов, которые делят данный ресурс
    size_t use_count() const
    {
        return control_block ? control_block->count : 0;  // Возращает значение счётчика или 0, если контрольный блок - nullptr
    }

    // Bool
    // Проверяет, не равен ли общий указатель null
    explicit operator bool() const
    {
        return control_block != nullptr;
    }
};

// Демонстрационный код...
int main()
{
    // Конструктор по умолчанию
    shared_ptr<int> ptr_default;

    // Конструктор из сырого указателя
    shared_ptr<int> ptr_raw(new int(10));
    std::cout << "Use count after raw pointer construction: " << ptr_raw.use_count() << std::endl;

    // Копирующий конструктор
    shared_ptr<int> ptr_copy(ptr_raw);
    std::cout << "Use count after copy constructor: " << ptr_raw.use_count() << std::endl;

    // Перемещающий конструктор
    shared_ptr<int> ptr_move(std::move(ptr_copy));
    std::cout << "Use count after move constructor: " << ptr_move.use_count() << std::endl;

    // Конструктор из unique_ptr
    std::unique_ptr<int> unique_ptr(new int(20));
    shared_ptr<int> ptr_unique(std::move(unique_ptr));
    std::cout << "Use count after unique_ptr constructor: " << ptr_unique.use_count() << std::endl;

    // Метод reset с сырым указателем
    ptr_raw.reset();
    std::cout << "Use count after reset with raw pointer: " << ptr_raw.use_count() << std::endl;

    // Метод reset с shared_ptr
    ptr_move.reset();
    std::cout << "Use count after reset with shared_ptr: " << ptr_move.use_count() << std::endl;

    // Метод swap
    ptr_raw.swap(ptr_unique);
    std::cout << "Use count after swap: " << ptr_raw.use_count() << ", " << ptr_unique.use_count() << std::endl;

    // Метод get
    int* raw_ptr = ptr_raw.get();
    if (raw_ptr)
    {
        std::cout << "Value using get method: " << *raw_ptr << std::endl;
    }

    // Операторы разыменования и стрелочки
    std::cout << "Value using dereference operator: " << *ptr_raw << std::endl;
    std::cout << "Value using arrow operator: " << ptr_raw.use_count() << std::endl;

    // Логический оператор (или bool, как его называл выше...)
    if (ptr_default)
    {
        std::cout << "ptr_default is not null" << std::endl;
    } else
    {
        std::cout << "ptr_default is null" << std::endl;
    }

    return 0;
}
