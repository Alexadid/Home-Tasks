import pandas as pd
from matplotlib import pyplot as plt

# Загружаем данные из CSV файла
df = pd.read_csv('hash_collision_analysis.csv')

# Хэш-функции для легенды
hash_functions = ['RSHash', 'JSHash', 'PJWHash', 'ELFHash', 'BKDRHash', 'SDBMHash', 'DJBHash', 'DEKHash', 'APHash']

# Выставляем размеры
plt.figure(figsize=(12, 8))

# Строим графики для каждой хэш-функции
for hash_function in hash_functions:
    # Будем исопльзовать логарифмический масштаб, так что прибавляем 1, чтобы избежать проблем с log(0)
    adjusted_collisions = df[hash_function] + 1
    plt.plot(df['NumberOfStrings'], adjusted_collisions, label=hash_function, marker='o')

plt.xlabel('Количество Строк')
plt.ylabel('Количество Коллизий + 1')
plt.title('Анализ Колизий Хэш-функций в Логарифмическом Масштабе')
plt.legend()

# Логарифмический масштаб
plt.yscale('log')

# Отображаем линии сетки для большей наглядности 
plt.grid(True, which="both", ls="--")

plt.show()
