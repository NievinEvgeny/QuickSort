#include <cstdlib>
#include <iostream>
#include <omp.h>
#include <sys/time.h>

const int size = 10000000;
const int threshold = 2500000;

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void partition(int* v, int& i, int& j, int low, int high)
{
    i = low;
    j = high;
    int pivot = v[(low + high) / 2];
    do
    {
        while (v[i] < pivot)
            i++;
        while (v[j] > pivot)
            j--;
        if (i <= j)
        {
            std::swap(v[i], v[j]);
            i++;
            j--;
        }
    } while (i <= j);
}

void serial_quicksort(int* v, int low, int high)
{
    int i, j;
    partition(v, i, j, low, high);
    if (low < j)
        serial_quicksort(v, low, j);
    if (i < high)
        serial_quicksort(v, i, high);
}

void quicksort_tasks(int* v, int low, int high)
{
    int i, j;
    partition(v, i, j, low, high);
    if (high - low < threshold || (j - low < threshold || high - i < threshold))
    {
        if (low < j)
            quicksort_tasks(v, low, j);
        if (i < high)
            quicksort_tasks(v, i, high);
    }
    else
    {
#pragma omp task untied // Открепить задачу от потока (задачу может выполнять любой поток)
        {
            quicksort_tasks(v, low, j);
        }
        quicksort_tasks(v, i, high);
    }
}

void parallel_quicksort(int* v, int low, int high)
{
#pragma omp parallel num_threads(8)
    {
#pragma omp single
        quicksort_tasks(v, low, high);
    }
}

int main()
{
    int* arr = new int[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand();
    }
    double t = wtime();
    // serial_quicksort(arr, 0, size - 1);
    parallel_quicksort(arr, 0, size - 1);
    t = wtime() - t;
    printf("Elapsed time (sec.): %.6f\n", t);
}