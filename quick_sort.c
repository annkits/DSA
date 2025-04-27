#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define N1 100
#define N2 200
#define N3 300
#define N4 400
#define N5 500

// Глобальные счетчики для операций сравнения (C) и перестановок (M)
int M = 0, C = 0;

// Глобальные счетчики для глубины рекурсии
int current_depth1 = 0, max_depth1 = 0; // Для QuickSort1
int current_depth2 = 0, max_depth2 = 0; // Для QuickSort2

// Функции для заполнения массивов
void FillInc(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = i + 1;
    }
}

void FillDec(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = n - i;
    }
}

void FillRand(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 10000;
    }
}

// Функция для обмена элементов
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    M++;
}

// Функция разбиения для QuickSort
int partition(int a[], int L, int R) {
    int i = L, j = R;
    int x = a[L]; // Опорный элемент (pivot)

    while (i <= j) {
        while (a[i] < x) {
            C++;
            i++;
        }
        C++;

        while (a[j] > x) {
            C++;
            j--;
        }
        C++;

        if (i <= j) {
            swap(&a[i], &a[j]);
            i++;
            j--;
        }
    }
    return i;
}

// QuickSort1 с подсчётом глубины рекурсии
void quickSort1(int a[], int L, int R) {
    current_depth1++;
    if (current_depth1 > max_depth1) {
        max_depth1 = current_depth1;
    }

    int i = L, j = R;
    int x = a[L];

    while (i <= j) {
        while (a[i] < x) {
            C++;
            i++;
        }
        C++;

        while (a[j] > x) {
            C++;
            j--;
        }
        C++;

        if (i <= j) {
            swap(&a[i], &a[j]);
            i++;
            j--;
        }
    }

    if (L < j) {
        quickSort1(a, L, j);
    }
    if (i < R) {
        quickSort1(a, i, R);
    }

    current_depth1--;
}

// QuickSort2 с подсчётом глубины рекурсии
void quickSort2(int a[], int L, int R) {
    current_depth2++;
    if (current_depth2 > max_depth2) {
        max_depth2 = current_depth2;
    }

    while (L < R) {
        int i = partition(a, L, R);
        int j = i - 1;

        if (j - L < R - i) {
            quickSort2(a, L, j);
            L = i;
        } else {
            quickSort2(a, i, R);
            R = j;
        }
    }

    current_depth2--;
}

// Реализация HeapSort
void siftDown(int arr[], int start, int end) {
    int root = start;

    while (2 * root + 1 <= end) {
        int child = 2 * root + 1;
        int swapIdx = root;

        C++;
        if (arr[swapIdx] < arr[child]) {
            swapIdx = child;
        }

        if (child + 1 <= end) {
            C++;
            if (arr[swapIdx] < arr[child + 1]) {
                swapIdx = child + 1;
            }
        }

        if (swapIdx == root) {
            return;
        } else {
            M++;
            int temp = arr[root];
            arr[root] = arr[swapIdx];
            arr[swapIdx] = temp;
            root = swapIdx;
        }
    }
}

void heapSort(int arr[], int n) {
    C = 0;
    M = 0;

    for (int start = n / 2 - 1; start >= 0; start--) {
        siftDown(arr, start, n - 1);
    }

    for (int end = n - 1; end > 0; end--) {
        M++;
        int temp = arr[0];
        arr[0] = arr[end];
        arr[end] = temp;

        siftDown(arr, 0, end - 1);
    }
}

// Реализация ShellSort
int calculateStep(int i, int prev_h) {
    return 3 * prev_h + 1;
}

void generateSteps(int steps[], int *stepCount, int n) {
    int m = (int)(log2(n)) - 1;
    if (m < 0) m = 0;

    int h = 1;
    steps[0] = h;
    int count = 1;

    for (int i = 2; i <= m && h < n; i++) {
        h = calculateStep(i, h);
        if (h < n) {
            steps[count] = h;
            count++;
        }
    }
    *stepCount = count;
}

void shellSort(int A[], int n, int *c_fact, int *m_fact, int *stepCount) {
    *c_fact = 0;
    *m_fact = 0;

    int steps[100];
    generateSteps(steps, stepCount, n);

    for (int s = *stepCount - 1; s >= 0; s--) {
        int k = steps[s];
        for (int i = k; i < n; i++) {
            int t = A[i];
            (*m_fact)++;
            int j = i - k;

            while (j >= 0) {
                (*c_fact)++;
                if (t < A[j]) {
                    A[j + k] = A[j];
                    (*m_fact)++;
                    j = j - k;
                } else break;
            }
            A[j + k] = t;
            (*m_fact)++;
        }
    }
}

// Функция для вывода таблицы трудоёмкости для QuickSort1 и QuickSort2
void plotTableGnuplotSort(int* sizes, double* best1, double* avg1, double* worst1, 
                          double* best2, double* avg2, double* worst2, int count, 
                          const char* title, int window) {
    char command[50];
    sprintf(command, "gnuplot -persistent");
    FILE* gp = popen(command, "w");
    if (gp == NULL) {
        printf("Ошибка при запуске Gnuplot для окна %d!\n", window);
        return;
    }

    fprintf(gp, "set terminal wxt %d size 800,400\n", window);
    fprintf(gp, "set title '%s'\n", title);
    fprintf(gp, "unset key\n");
    fprintf(gp, "unset border\n");
    fprintf(gp, "unset tics\n");
    fprintf(gp, "set xrange [0:7]\n");
    fprintf(gp, "set yrange [%d:-1]\n", count);

    fprintf(gp, "set label 'N' at 0.5,-0.5 center\n");
    fprintf(gp, "set label 'QuickSort1' at 2,-0.5 center\n");
    fprintf(gp, "set label 'QuickSort2' at 5,-0.5 center\n");
    fprintf(gp, "set label 'Убыв.' at 1.5,-0.5 center\n");
    fprintf(gp, "set label 'Случ.' at 2.5,-0.5 center\n");
    fprintf(gp, "set label 'Возр.' at 3.5,-0.5 center\n");
    fprintf(gp, "set label 'Убыв.' at 4.5,-0.5 center\n");
    fprintf(gp, "set label 'Случ.' at 5.5,-0.5 center\n");
    fprintf(gp, "set label 'Возр.' at 6.5,-0.5 center\n");

    for (int i = 0; i < count; i++) {
        double y = i + 0.5;
        fprintf(gp, "set label '%d' at 0.5,%f center\n", sizes[i], y);
        fprintf(gp, "set label '%.0f' at 1.5,%f center\n", worst1[i], y); // QuickSort1 Убыв.
        fprintf(gp, "set label '%.0f' at 2.5,%f center\n", avg1[i], y);   // QuickSort1 Случ.
        fprintf(gp, "set label '%.0f' at 3.5,%f center\n", best1[i], y);  // QuickSort1 Возр.
        fprintf(gp, "set label '%.0f' at 4.5,%f center\n", worst2[i], y); // QuickSort2 Убыв.
        fprintf(gp, "set label '%.0f' at 5.5,%f center\n", avg2[i], y);   // QuickSort2 Случ.
        fprintf(gp, "set label '%.0f' at 6.5,%f center\n", best2[i], y);  // QuickSort2 Возр.
    }

    for (int i = 0; i <= count; i++) {
        fprintf(gp, "set arrow from 0,%d to 7,%d nohead lt 1 lw 1\n", i, i);
    }
    for (int j = 0; j <= 7; j++) {
        fprintf(gp, "set arrow from %d,0 to %d,%d nohead lt 1 lw 1\n", j, j, count);
    }

    fprintf(gp, "plot NaN\n");
    pclose(gp);
}

// Функция для вывода таблицы глубины рекурсии для QuickSort1 и QuickSort2
void plotTableGnuplotSortDepth(int* sizes, double* best1, double* avg1, double* worst1, 
                               double* best2, double* avg2, double* worst2, int count, 
                               const char* title, int window) {
    char command[50];
    sprintf(command, "gnuplot -persistent");
    FILE* gp = popen(command, "w");
    if (gp == NULL) {
        printf("Ошибка при запуске Gnuplot для окна %d!\n", window);
        return;
    }

    fprintf(gp, "set terminal wxt %d size 800,400\n", window);
    fprintf(gp, "set title '%s'\n", title);
    fprintf(gp, "unset key\n");
    fprintf(gp, "unset border\n");
    fprintf(gp, "unset tics\n");
    fprintf(gp, "set xrange [0:7]\n");
    fprintf(gp, "set yrange [%d:-1]\n", count);

    fprintf(gp, "set label 'n' at 0.5,-0.5 center\n");
    fprintf(gp, "set label 'QuickSort1' at 2,-0.5 center\n");
    fprintf(gp, "set label 'QuickSort2' at 5,-0.5 center\n");
    fprintf(gp, "set label 'Убыв.' at 1.5,-0.5 center\n");
    fprintf(gp, "set label 'Случ.' at 2.5,-0.5 center\n");
    fprintf(gp, "set label 'Возр.' at 3.5,-0.5 center\n");
    fprintf(gp, "set label 'Убыв.' at 4.5,-0.5 center\n");
    fprintf(gp, "set label 'Случ.' at 5.5,-0.5 center\n");
    fprintf(gp, "set label 'Возр.' at 6.5,-0.5 center\n");

    for (int i = 0; i < count; i++) {
        double y = i + 0.5;
        fprintf(gp, "set label '%d' at 0.5,%f center\n", sizes[i], y);
        fprintf(gp, "set label '%.0f' at 1.5,%f center\n", worst1[i], y);
        fprintf(gp, "set label '%.0f' at 2.5,%f center\n", avg1[i], y);
        fprintf(gp, "set label '%.0f' at 3.5,%f center\n", best1[i], y);
        fprintf(gp, "set label '%.0f' at 4.5,%f center\n", worst2[i], y);
        fprintf(gp, "set label '%.0f' at 5.5,%f center\n", avg2[i], y);
        fprintf(gp, "set label '%.0f' at 6.5,%f center\n", best2[i], y);
    }

    for (int i = 0; i <= count; i++) {
        fprintf(gp, "set arrow from 0,%d to 7,%d nohead lt 1 lw 1\n", i, i);
    }
    for (int j = 0; j <= 7; j++) {
        fprintf(gp, "set arrow from %d,0 to %d,%d nohead lt 1 lw 1\n", j, j, count);
    }

    fprintf(gp, "plot NaN\n");
    pclose(gp);
}

// Функция для построения графиков зависимости M+C от n
void PlotGraphComparison(int *sizes, int *heap_results, int *shell_results, int *quick_results, int count) {
    FILE *gp = popen("gnuplot -persistent", "w");
    if (gp == NULL) {
        printf("Ошибка при запуска Gnuplot!\n");
        return;
    }

    fprintf(gp, "set terminal wxt 3 size 600,400\n");
    fprintf(gp, "set title 'Сравнение HeapSort, ShellSort и QuickSort (случайный массив)'\n");
    fprintf(gp, "set xlabel 'Размер массива n'\n");
    fprintf(gp, "set ylabel 'Mф + Cф'\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "set key left top\n");
    fprintf(gp, "set autoscale xy\n");
    fprintf(gp, "set style line 1 lc rgb '#FF0000' lt 1 lw 2 pt 7\n"); // Красный для HeapSort
    fprintf(gp, "set style line 2 lc rgb '#0000FF' lt 1 lw 2 pt 7\n"); // Синий для ShellSort
    fprintf(gp, "set style line 3 lc rgb '#008000' lt 1 lw 2 pt 7\n"); // Зелёный для QuickSort

    fprintf(gp, "plot '-' with lines ls 1 title 'HeapSort', ");
    fprintf(gp, "'-' with lines ls 2 title 'ShellSort', ");
    fprintf(gp, "'-' with lines ls 3 title 'QuickSort'\n");

    for (int i = 0; i < count; i++) {
        fprintf(gp, "%d %d\n", sizes[i], heap_results[i]);
    }
    fprintf(gp, "e\n");

    for (int i = 0; i < count; i++) {
        fprintf(gp, "%d %d\n", sizes[i], shell_results[i]);
    }
    fprintf(gp, "e\n");

    for (int i = 0; i < count; i++) {
        fprintf(gp, "%d %d\n", sizes[i], quick_results[i]);
    }
    fprintf(gp, "e\n");

    pclose(gp);
}

// Тесты для сравнения трёх алгоритмов (случайный массив)
void RunTestsComparison(int n, int *heap_result, int *shell_result, int *quick_result) {
    int arr[n], temp[n];
    int c_fact, m_fact, stepCount;

    // HeapSort
    FillRand(arr, n);
    for (int i = 0; i < n; i++) temp[i] = arr[i];
    heapSort(temp, n);
    *heap_result = M + C;

    // ShellSort
    FillRand(arr, n);
    for (int i = 0; i < n; i++) temp[i] = arr[i];
    shellSort(temp, n, &c_fact, &m_fact, &stepCount);
    *shell_result = c_fact + m_fact;

    // QuickSort1
    FillRand(arr, n);
    for (int i = 0; i < n; i++) temp[i] = arr[i];
    M = 0; C = 0;
    quickSort1(temp, 0, n - 1);
    *quick_result = M + C;
}

// Основная программа
int main() {
    srand(time(NULL));

    int sizes[] = {N1, N2, N3, N4, N5};
    int count = 5;

    // Массивы для хранения результатов трудоёмкости
    double best1_mc[5], avg1_mc[5], worst1_mc[5]; // QuickSort1
    double best2_mc[5], avg2_mc[5], worst2_mc[5]; // QuickSort2
    // Массивы для хранения результатов глубины рекурсии
    double best1_depth[5], avg1_depth[5], worst1_depth[5]; // QuickSort1
    double best2_depth[5], avg2_depth[5], worst2_depth[5]; // QuickSort2

    // Трудоёмкость и глубина рекурсии для QuickSort1 и QuickSort2
    for (int i = 0; i < count; i++) {
        int n = sizes[i];
        int arr[n];

        // QuickSort1: Худший случай (убывающий порядок)
        FillDec(arr, n);
        M = 0; C = 0;
        max_depth1 = 0; current_depth1 = 0;
        quickSort1(arr, 0, n - 1);
        worst1_mc[i] = (double)(M + C);
        worst1_depth[i] = (double)max_depth1;

        // QuickSort1: Средний случай (случайный порядок)
        FillRand(arr, n);
        M = 0; C = 0;
        max_depth1 = 0; current_depth1 = 0;
        quickSort1(arr, 0, n - 1);
        avg1_mc[i] = (double)(M + C);
        avg1_depth[i] = (double)max_depth1;

        // QuickSort1: Лучший случай (возрастающий порядок)
        FillInc(arr, n);
        M = 0; C = 0;
        max_depth1 = 0; current_depth1 = 0;
        quickSort1(arr, 0, n - 1);
        best1_mc[i] = (double)(M + C);
        best1_depth[i] = (double)max_depth1;

        // QuickSort2: Худший случай (убывающий порядок)
        FillDec(arr, n);
        M = 0; C = 0;
        max_depth2 = 0; current_depth2 = 0;
        quickSort2(arr, 0, n - 1);
        worst2_mc[i] = (double)(M + C);
        worst2_depth[i] = (double)max_depth2;

        // QuickSort2: Средний случай (случайный порядок)
        FillRand(arr, n);
        M = 0; C = 0;
        max_depth2 = 0; current_depth2 = 0;
        quickSort2(arr, 0, n - 1);
        avg2_mc[i] = (double)(M + C);
        avg2_depth[i] = (double)max_depth2;

        // QuickSort2: Лучший случай (возрастающий порядок)
        FillInc(arr, n);
        M = 0; C = 0;
        max_depth2 = 0; current_depth2 = 0;
        quickSort2(arr, 0, n - 1);
        best2_mc[i] = (double)(M + C);
        best2_depth[i] = (double)max_depth2;
    }

    // Тестирование для графиков (HeapSort, ShellSort, QuickSort1, случайный массив)
    int heap_results[5], shell_results[5], quick_results[5];
    for (int i = 0; i < 5; i++) {
        RunTestsComparison(sizes[i], &heap_results[i], &shell_results[i], &quick_results[i]);
    }

    // Построение таблиц
    plotTableGnuplotSort(sizes, best1_mc, avg1_mc, worst1_mc, best2_mc, avg2_mc, worst2_mc, count, 
                         "Трудоемкость метода Хоара: QuickSort1 и QuickSort2 (M+C)", 1);
    plotTableGnuplotSortDepth(sizes, best1_depth, avg1_depth, worst1_depth, best2_depth, avg2_depth, worst2_depth, count, 
                              "Глубина рекурсии сортировки методом Хоара: QuickSort1 и QuickSort2", 2);

    // Построение графика (задание 5*)
    PlotGraphComparison(sizes, heap_results, shell_results, quick_results, 5);

    return 0;
}