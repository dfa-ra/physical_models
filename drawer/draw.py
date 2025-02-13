import matplotlib.pyplot as plt

print("start drawer")

# Считываем данные из файла
data_sets = []
current_set = []
labels = []

with open("/media/ra/_work/ra/ITMO/PHISICS/physical_models/drawer/data.txt", "r") as file:
    label = None
    for line in file:
        line = line.strip()
        if line == "-":  # Если встретили разделитель, сохраняем текущий набор
            if current_set:  # Проверяем, что набор не пустой
                data_sets.append(current_set)
                labels.append(label)
                current_set = []  # Очищаем временный список
                label = None
        elif label is None:  # Если ещё не прочитано название графика
            label = line
        elif line:  # Если строка содержит данные
            try:
                x, y, z = map(float, line.split())  # Преобразуем строки в числа
                current_set.append((x, y))  # Сохраняем только x и y (z игнорируется)
            except ValueError:
                print(f"Ошибка чтения строки: {line}")

    # Добавляем последний набор, если он есть
    if current_set and label:
        data_sets.append(current_set)
        labels.append(label)

# Создаём график
plt.figure(figsize=(10, 10))

# Для каждого набора данных строим линию
for i, (data_set, label) in enumerate(zip(data_sets, labels)):
    x_values = [point[0] for point in data_set]
    y_values = [point[1] for point in data_set]
    plt.plot(x_values, y_values, label=label, linestyle='-')

# Настройка графика
plt.title("Графики по точкам")
plt.axhline(0, color='black', linewidth=0.5, ls="--")  # Линия X=0
plt.axvline(0, color='black', linewidth=0.5, ls="--")  # Линия Y=0
plt.legend()  # Отображаем легенду с номерами графиков
plt.grid(True)  # Включаем сетку
plt.xlabel("X")
plt.ylabel("Y")

# Показываем график
plt.show()