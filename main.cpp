//
// main.cpp
// 2023-09-01
// Ivan Konishchev
//

#include <iostream>
#include "Sort.h"

int main(int argc, const char *argv[])
{
    srand(0);
    std::cout << "Input threads count: (если '0' то будет использоваться системное количество) : ";
    int countThreads{0};
    std::cin >> countThreads;
    Sort::maxThread = countThreads;
    if (countThreads == 0)
    {
        Sort::maxThread = std::thread::hardware_concurrency();
    }
    std::cout << "Using counts thread: " << Sort::maxThread << "\n";
    long size = 100000000;
    int *array = new int[size];
    for (long i = 0; i < size; i++)
    {
        array[i] = rand() % 500000;
    }

    time_t start, end;
    std::cout << "start\n";
    time(&start);
    Sort::mergeSort(array, size);
    time(&end);

    double seconds = difftime(end, start);
    printf("The time: %f seconds\n", seconds);

    if (!Sort::isSorted(array, size))
    {
        std::cout << "Unsorted" << std::endl;
    }

    for (long i = 0; i < size; i++)
    {
        array[i] = rand() % 500000;
    }
    std::cout << "start one thread:\n";
    // однопоточный запуск
    time(&start);
    Sort::mergeSort(array, size, false);
    time(&end);
    seconds = difftime(end, start);
    printf("The time: %f seconds\n", seconds);

    if (!Sort::isSorted(array, size))
    {
        std::cout << "Unsorted" << std::endl;
    }
    
    delete[] array;

    return 0;
}



