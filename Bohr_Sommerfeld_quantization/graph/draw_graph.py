import matplotlib.pyplot as plt
import numpy as np
import math

# Загрузка данных
x_values = []
v_values = []
energy_levels = []

# Чтение значений x
with open('X_values.txt', 'r') as f:
    x_values = [float(line.strip()) for line in f]

# Чтение значений V(x)
with open('V_values.txt', 'r') as f:
    v_values = [float(line.strip()) for line in f]

# Чтение уровней энергии
with open('energy_levels.txt', 'r') as f:
    energy_levels = [float(line.strip()) for line in f]


# Построение фазовых траекторий
def plot_phase_trajectories(v_values, x_values, energy_levels):
    plt.figure(figsize=(10, 6))

    for E in energy_levels:
        # Определяем области, где E > V(x), чтобы строить траекторию
        x_allowed = []
        p_vals = []

        for i in range(len(x_values)):
            if E > v_values[i]:  # Только если E > V(x)
                x_allowed.append(x_values[i])
                p_vals.append(math.sqrt(2 * (E - v_values[i])))  # Рассчитываем p

        # Строим фазовую траекторию
        plt.plot(x_allowed, p_vals, '-b')
        plt.plot(x_allowed, [-p for p in p_vals], '-b')  # Отрицательная часть

    plt.xlabel("x")
    plt.ylabel("p")
    plt.title("Фазовые траектории для уровней энергии")
    plt.grid(True)
    plt.show()

# Построение графика
plt.figure(figsize=(10, 6))
plt.plot(x_values, v_values, label="V(x)", color="blue")

# Добавление уровней энергии
for energy in energy_levels:
    plt.axhline(y=energy, color="red", linestyle="--", label=f"Energy level E={energy}")

# Удаление повторяющихся меток в легенде (если уровни энергии одинаковые)
handles, labels = plt.gca().get_legend_handles_labels()
unique_labels = dict(zip(labels, handles))
plt.legend(unique_labels.values(), unique_labels.keys())

# Настройка осей и заголовка
plt.xlabel("x")
plt.ylabel("V(x) / Energy levels")
plt.title("Potential V(x) and Energy Levels")
plt.grid(True)

plot_phase_trajectories(v_values,x_values,energy_levels)

# Показ графика
plt.show()