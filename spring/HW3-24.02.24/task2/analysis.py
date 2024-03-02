import pandas as pd
from matplotlib import pyplot as plt

# Загружаем данные из CSV файла для анализа коллизий
df = pd.read_csv('hash_collision_analysis.csv')

# Подготавливаем все поля графика
plt.figure(figsize=(12, 8))
plt.plot(df['NumberOfStructs'], df['BoostHash'] + 1, label='BoostHash', marker='o')

plt.xlabel('Количество структур')
plt.ylabel('Количество Коллизий + 1')
plt.title('Анализ Колизий Хэш-функции из Библиотеки Boost')
plt.legend()
plt.yscale('log')
plt.grid(True, which="both", ls="--")
plt.show()

# Загружаем хэши для анализа распределения
df_hash_values = pd.read_csv('hash_values.csv', header=None, names=['HashValue'])

# Поступаем также, как и с коллизиями...
plt.figure(figsize=(12, 6))
plt.hist(df_hash_values['HashValue'], bins=50, alpha=0.7, label='BoostHash')

plt.xlabel('Hash Value')
plt.ylabel('Frequency')
plt.title('Density Distribution for BoostHash')
plt.legend()
plt.grid(True, which="both", ls="--")

# Полученный график сохраняем
plt.savefig('density_BoostHash.png')

plt.show()

# Буду честным, очень странно, что даже 10^6 объектов не дали хоть одну коллизию.
# Полагаю, что я недооцениваю возможности Boost...
# Также отмечу, что распределение является практически идеально равномерным