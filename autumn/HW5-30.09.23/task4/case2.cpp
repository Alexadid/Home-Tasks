// Объявление без определения
extern int someVariableY;

int main()
{
    // Ошибка линковщика - someVariableY объявлен, но не определён
    int result = someVariableY;
    return 0;
}