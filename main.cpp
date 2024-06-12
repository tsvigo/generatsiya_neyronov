//#include <QCoreApplication>

//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);

//    return a.exec();
//}
//###########################################################################
#include <QCoreApplication>
#include <QDataStream>
#include <QFile>
#include <QRandomGenerator>
#include <iostream>
#include <vector>

// Функция для генерации случайных чисел
std::vector<long long> generateRandomNumbers(size_t count)
{
    std::vector<long long> numbers;
    numbers.reserve(count);

    for (size_t i = 0; i < count; ++i) {
        numbers.push_back(QRandomGenerator::global()->generate64());
    }

    return numbers;
}

// Функция для записи чисел в файл в двоичном виде
bool writeNumbersToFile(const std::vector<long long> &numbers, const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    QDataStream out(&file);
    for (const auto &number : numbers) {
        out << number;
    }

    file.close();
    return true;
}

// Функция для чтения чисел из файла в двоичном виде
std::vector<long long> readNumbersFromFile(const QString &fileName)
{
    std::vector<long long> numbers;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return numbers;
    }

    QDataStream in(&file);
    long long number;
    while (!in.atEnd()) {
        in >> number;
        numbers.push_back(number);
    }

    file.close();
    return numbers;
}

// Главная функция
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    const size_t numberCount = 205;
    const QString fileName
        = "/home/viktor/my_projects_qt_2/generatsiya_neyronov/random_numbers.bin";

    // Генерация случайных чисел
    std::vector<long long> generatedNumbers = generateRandomNumbers(numberCount);

    // Запись чисел в файл
    if (!writeNumbersToFile(generatedNumbers, fileName)) {
        std::cerr << "Failed to write numbers to file." << std::endl;
        return 1;
    }

    // Чтение чисел из файла
    std::vector<long long> readNumbers = readNumbersFromFile(fileName);

    // Проверка правильности записи
    if (generatedNumbers == readNumbers) {
        std::cout << "Numbers were written and read correctly." << std::endl;
    } else {
        std::cerr << "Numbers were not written or read correctly." << std::endl;
        return 1;
    }

    return 0;
}
