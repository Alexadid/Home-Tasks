import pandas as pd
from matplotlib import pyplot as plt



# Закгружаем данные из CSV файла
df = pd.read_csv('timing_results.csv')

# Пока не известно, есть ли зависимость
# Рассчитаем значение константы, а также построим графики
# По этому можно будет судить о резльутатах...

# Рассматриваем следующие данные
set_insertion_times = df['Set Insertion Time (μs)']
vector_sort_times = df['Vector Insert + Sort Time (μs)']

# Рассчитываем отношение времени вставко для set и времени на вставку и сортировку в vector для каждого N
ratios = set_insertion_times / vector_sort_times

# Наконец, рассчитаем значение константы усреднением
average_ratio = ratios.mean()

# Строим графики, подписываем оси и т.д.
plt.figure(figsize=(10, 6))
plt.plot(df['N'], df['Set Insertion Time (μs)'], label='std::Время вставок для set', marker='o')
plt.plot(df['N'], df['Vector Insert + Sort Time (μs)'], label='время std::vector + std::sort', marker='x')
plt.xlabel('Количество элементов N')
plt.ylabel('Время, μs')
#plt.yscale('log')
#plt.xscale('log')
plt.title('Опыт: время вставок и сортировок')
plt.legend()
plt.grid(True)

# И напишем внизу примерное значение константы
plt.figtext(0.5, 0.01, f'Среднее значение отношения времени вставки в set к времени сортировки в vector: {average_ratio:.2f}x', 
            fontsize=12, ha='center')

plt.show()
