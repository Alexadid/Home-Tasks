import pandas as pd
from matplotlib import pyplot as plt

# Загружаем данные из CSV файла для анализа коллизий
df = pd.read_csv('hash_collision_analysis.csv')

# Хэш-функции для легенды
hash_functions = ['RSHash', 'JSHash', 'PJWHash', 'ELFHash', 'BKDRHash', 'SDBMHash', 'DJBHash', 'DEKHash', 'APHash']

# Анализ коллизий
plt.figure(figsize=(12, 8))

# Строим графики для каждой хэш-функции
for hash_function in hash_functions:
    adjusted_collisions = df[hash_function] + 1
    plt.plot(df['NumberOfStrings'], adjusted_collisions, label=hash_function, marker='o')

plt.xlabel('Количество Строк')
plt.ylabel('Количество Коллизий + 1')
plt.title('Анализ Колизий Хэш-функций в Логарифмическом Масштабе')
plt.legend()
plt.yscale('log')
plt.grid(True, which="both", ls="--")
plt.show()

# Анализ плотности распределения
for i, hash_function in enumerate(hash_functions):
    # Загружаем данные из CSV файла для каждой хэш-функции
    df_hash_values = pd.read_csv(f'hash_values_{i}.csv', header=None, names=['HashValue'])
    
    plt.figure(figsize=(12, 6))
    plt.hist(df_hash_values['HashValue'], bins=50, alpha=0.7, label=hash_function)
    
    plt.xlabel('Значение Хэша')
    plt.ylabel('Частота')
    plt.title(f'Плотность Распределения для {hash_function}')
    plt.legend()
    plt.grid(True, which="both", ls="--")
    
    # Сохраняем графики в файлы для каждой хэш-функции
    plt.savefig(f'density_{hash_function}.png')
    
    plt.show()


# Стоит сказать пару слов о распределениях:
# 1) относительно равномерно рспределены APHash, RSHash, SDBMHash;
# 2) BKDRHash распределён менее равномерно, очевиден провал по частотам;
# 3) DEKHash, ELFHash и PJWHash распределены скорее как нечтно среднее
# между равномерным и нормальным распредлением;
# 4) DJBHash, JSHash распредлены неочевидным образом, возможно дело в том,
# что было сгенерировано недостаточно хэшей;