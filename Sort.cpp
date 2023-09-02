//
// Sort.cpp
// 2023-09-01
// Ivan Konishchev
//

#include "Sort.h"

int Sort::threads = 0;
int Sort::maxThread = std::thread::hardware_concurrency();
std::mutex Sort::mutex_threads;

void Sort::mergeSort(int *arr, long size, bool isMultitraiding)
{
    if (isMultitraiding)
    {
        sortWithThreads(arr, 0, size - 1);
        return;
    }
    sortWithOutThreads(arr, 0, size - 1);
}

void Sort::sortWithThreads(int *arr, long start, long end)
{
    if (start >= end)
    {
        return;
    }

    int mid = (start + end) / 2;
    Sort::mutex_threads.lock();
    int thrcount = threads;
    Sort::mutex_threads.unlock();
    if (Sort::threads >= (Sort::maxThread - 1) || (end - start) < 10000)
    {

        Sort::sortWithOutThreads(arr, start, end);
        return;
    }
    auto f = std::async(std::launch::async, [&]()
                        { 
								Sort::mutex_threads.lock();
								threads++;
								Sort::mutex_threads.unlock();
								Sort::sortWithThreads(arr, start, mid);
								Sort::mutex_threads.lock();
								threads--;
								Sort::mutex_threads.unlock(); });
    Sort::sortWithThreads(arr, mid + 1, end);
    f.wait();
    merge(arr, start, mid, end);
}

void Sort::sortWithOutThreads(int *arr, long start, long end)
{
    if (start >= end)
        return;

    long midle = (start + end - 1) / 2;

    sortWithOutThreads(arr, start, midle);
    sortWithOutThreads(arr, midle + 1, end);

    merge(arr, start, midle, end);
}

void Sort::merge(int *arr, long start, long midle, long end)
{
    int left = midle - start + 1;
    int right = end - midle;

    int *Left_arr = new int[left];
    int *Right_arr = new int[right];

    for (int i = 0; i < left; ++i)
        Left_arr[i] = arr[start + i];

    for (int j = 0; j < right; ++j)
        Right_arr[j] = arr[midle + 1 + j];

    int i = 0, j = 0;
    int k = start;
    while (i < left && j < right)
    {
        if (Left_arr[i] <= Right_arr[j])
        {
            arr[k] = Left_arr[i];
            i++;
        }
        else
        {
            arr[k] = Right_arr[j];
            j++;
        }
        k++;
    }
    while (i < left)
    {
        arr[k] = Left_arr[i];
        i++;
        k++;
    }
    while (j < right)
    {
        arr[k] = Right_arr[j];
        j++;
        k++;
    }
}

bool Sort::isSorted(int *arr, long size)
{
    for (long i = 0; i < size - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            return false;
        }
    }
    return true;
}