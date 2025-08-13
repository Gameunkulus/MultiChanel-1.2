// HomeworkMultiT-1.2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

void sumOfVec(std::vector<int> vecSum, std::vector<int> newVec1, std::vector<int> newVec2, int firNum, int secNum) {
    for (int i = firNum; i < secNum; i++) 
    {
        vecSum.at(i) = newVec1.at(i) + newVec2.at(i);
    }
}

int main()
{
    setlocale(LC_CTYPE, "rus");
    std::cout << "Количество аппаратных ядер: " << std::thread::hardware_concurrency() << std::endl;
    std::cout << "          " << "1000" << "          " << "10'000" << "          " << "100'000" << "          " << "1000'000" << std::endl;
    std::vector<int> vec1;
    std::vector<int> vec2;
    std::vector<int> numOfThreads{ 1,2,4,8,16 };

    std::vector<int> sizeOfVector{ 1000,10000,100000,1000000};

    std::vector<int> vecSum;

    for (auto& countT : numOfThreads) {
        std::cout << " потоков " << countT;

        for (auto& countV : sizeOfVector) {
            vec1.resize(countV, 2);
            vec2.resize(countV, 4);
            std::vector<std::thread> threads;
            vecSum.resize(countV, 0);

            int partOfSize = static_cast<int>(countV / countT);
            auto thrStart = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < countT; i++) 
            {
                int leftBorder = 0;
                int rightBorder = 0;

                if (i != countT - 1) {
                    leftBorder = rightBorder;
                    rightBorder = partOfSize * (i - 1);
                }
                else {
                    leftBorder = rightBorder;
                    rightBorder = countV;
                }

                threads.push_back(std::thread(sumOfVec, vecSum, vec1, vec2, leftBorder,rightBorder));
            }
            for (auto& it : threads)
            {
                it.join();
            }
            
            auto thrStop = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> thrTime = thrStop - thrStart;
            std::cout << "            " << thrTime.count() << "ms";
        }
        std::cout << "\n\n";
    }
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
