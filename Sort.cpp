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

void Sort::sortWithThreads(int *arr, long start, long end, int currThread)
{
    if (start >= end)
    {
        return;
    }

    int mid = (start + end) / 2;

    if (currThread >= Sort::maxThread)
    {

        Sort::sortWithThreads(arr, start, mid, currThread);
        Sort::sortWithThreads(arr,mid + 1, end, currThread);
    }
    else
    {
        auto f = std::async(std::launch::async, [&]()
                            { 
								Sort::sortWithThreads(arr, start, mid, currThread + 2);
                                 });
         auto f1 = std::async(std::launch::async, [&]()
                            { 
								Sort::sortWithThreads(arr, mid + 1, end, currThread + 2);
                                 });
        f.wait();
        f1.wait();
    }
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

    int *leftArr = new int[left];
    int *rightArr = new int[right];

    for (int i = 0; i < left; ++i)
        leftArr[i] = arr[start + i];

    for (int j = 0; j < right; ++j)
        rightArr[j] = arr[midle + 1 + j];

    int i = 0, j = 0;
    int k = start;
    while (i < left && j < right)
    {
        if (leftArr[i] <= rightArr[j])
        {
            arr[k] = leftArr[i];
            i++;
        }
        else
        {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    while (i < left)
    {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    while (j < right)
    {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
    delete[] leftArr;
    delete[] rightArr;
}

bool Sort::isSorted(const int *arr, long size)
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