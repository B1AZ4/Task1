# Замена байтовых последовательностей

Программа для замены одной последовательности байт на другую в файле.
Автор:Смоликов Роман
Группа:МК-101

## Требования
- CMake 3.15 или выше
# Клонирование репозитория
git clone https://github.com/B1AZ4/Task1.git
cd Task1

# Создание папки для сборки
mkdir build
cd build

# Настройка проекта
cmake -S .. -G "Visual Studio 17 2022" -A Win32

# Сборка
cmake --build . --config Release

# Запуск
cd Release
replace_app.exe input.txt output.txt "Pattern_hex" "replacement_hex"
