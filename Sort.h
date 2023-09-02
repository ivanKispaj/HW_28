//
// Sort.h
// 2023-09-01
// Ivan Konishchev
//

#pragma once
#include <iostream>
#include <future>
#include <thread>
#include <mutex>

class Sort
{
private:
    Sort() = default;
    static int threads;
    static std::mutex mutex_threads;

    static void sortWithThreads(int *arr, long start, long end, int currThread = 1);
    static void sortWithOutThreads(int *arr, long start, long end);
    static void merge(int *arr, long start, long midle, long end);

public:
    ~Sort() = default;

    static int maxThread;
    static void mergeSort(int *arr, long size, bool isMultitreading = true);
    static bool isSorted(int *arr, long size);
};
