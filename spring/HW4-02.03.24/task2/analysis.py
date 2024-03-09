import pandas as pd
from matplotlib import pyplot as plt

# Загружаем данные о временной зависимости для всех трёх способов генерации случайных чисел
df_timing = pd.read_csv('timing_data.csv')

# Строим графики для каждого из методов в зависимости от числа итераций
iteration_counts = df_timing['Iterations'].unique()
methods = ['rand', 'mt19937', 'random_device']

plt.figure(figsize=(12, 8))
for method in methods:
    method_times = df_timing[df_timing['Method'] == method]['Time (ms)'].values
    plt.plot(iteration_counts, method_times, label=method, marker='o')

plt.xlabel('Итерации')
plt.ylabel('t, ms')
plt.title('Время Генерации в Зависимости от Количества Итераций')
plt.legend()
#plt.xscale('log')
#plt.yscale('log')
plt.grid(True, which="both", ls="--")
plt.show()

# Теперь переходим к анализ плотностей распределений для каждого из способов в зависимости от числа итераций
for count in iteration_counts:
    for method in methods:
        file_name = f'{method}_numbers_{count}.csv'
        try:
            df_values = pd.read_csv(file_name, header=None, names=['Value'])
            plt.figure(figsize=(12, 6))
            plt.hist(df_values['Value'], bins=251, alpha=0.7, label=f'{method} - {count}')
            
            plt.xlabel('Сгенерированные Числа')
            plt.ylabel('Частота Их Появлений')
            plt.title(f'Распределение Частот для {method} с {count} итераций')
            plt.legend()
            plt.grid(True, which="both", ls="--")

            # plt.yscale('log')
            
            # Сохраняем графики в файлы
            plt.savefig(f'density_{method}_{count}.png')
            plt.close()
        except FileNotFoundError:
            # На всякий случай проверяем, что файл дейсствительно был
            # Мало ли Вы решите изменить названия...
            print(f'File {file_name} not found. Skipping.')


# Очевидным лидером по времени генерации является rand, чего следовало ожидать.
# Также очевидно и то, что Вихрь Мерсена быстре random_device,
# т.к. первый считается более эффективным генератором.
            
# По поводу рапределений можно сказать лишь то, что все они достаточно быстро приходят к равномерному.
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 
# 