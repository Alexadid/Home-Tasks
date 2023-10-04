// Пример I: ошибка линковщика с обнаружением многократно определённого внешнего символа
// Для проверки созданы 2 файла, которые можно скомпилировать для проверки моделирования
// Это файлы case1-1.cpp, case1-2.cpp

// case1-1.cpp

int someVariableX = 10;


// case1-2.cpp

int someVariableX = 20;

int main()
{
    // Ошибка линковщика - someVariableX определён и в файле case1-1.cpp, и case1-2.cpp
    // Таким образом, линковщик не может установить, какое определение использовать...
    int sum = someVariableX;
    return 0;
}

/*
duplicate symbol '_someVariableX' in:
    /var/folders/wj/bxj04vcj105bpjp9q7tb9nvr0000gn/T/case1-1-beb44e.o
    /var/folders/wj/bxj04vcj105bpjp9q7tb9nvr0000gn/T/case1-2-307e7c.o
ld: 1 duplicate symbol for architecture arm64
*/

// Способы устранения:
// 1) можно удалить одно из определений;
// 2) использовать ключевое слово extern в одном файле для объявления x и определения его в другом.



// Пример II: ошибка линковщика с неразрешённым внешним символом

// case2.cpp

// Объявление без определения
extern int someVariableY;

int main()
{
    // Ошибка линковщика - someVariableY объявлен, но не определён
    // При компиляции линковщик будет искать определение someVariableY, но не найдёт его
    int result = someVariableY;
    return 0;
}

/*
Undefined symbols for architecture arm64:
  "_someVariableY", referenced from:
      _main in case2-ea8952.o
ld: symbol(s) not found for architecture arm64
*/

// Способы устранения:
// он только один - переменная должна быть определена в одно из компилируемых файлов
