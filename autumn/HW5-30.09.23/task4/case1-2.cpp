int someVariableX = 20;

int main()
{
    // Ошибка линковщика - someVariableX определён и в файле case1-1.cpp, и case1-2.cpp
    int sum = someVariableX;
    return 0;
}
