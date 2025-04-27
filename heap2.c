#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int M = 0, C = 0;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    M++;
}

void heapify(int arr[], int L, int R) {
    int x = arr[L];
    int i = L;
    while (1) {
        int j = 2 * i + 1;
        if (j > R) break;
        if (j < R) {
            if (arr[j + 1] > arr[j]) {
                C++;
                j = j + 1;
            }
        }
        if (x >= arr[j]) {
            C++;
            break;
        }
        M++;
        arr[i] = arr[j];
        i = j;
    }
    if (i != L) {
        M++;
    }
    M++;
    arr[i] = x;
}

void buildHeap(int arr[], int n) {
    for (int start = n / 2 - 1; start >= 0; start--) {
        heapify(arr, start, n - 1);
    }
}

void generateBestCase(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = i + 1;
}

void generateAverageCase(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = rand() % (2 * n);
}

void generateWorstCase(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = n - i;
}

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

void plotTableGnuplot(int* sizes, double* theor, double* best, double* avg, double* worst, int count, const char* title, int window) {
    char command[50];
    sprintf(command, "gnuplot -persistent");
    FILE* gp = popen(command, "w");
    if (gp == NULL) {
        printf("Ошибка при запуске Gnuplot для окна %d!\n", window);
        return;
    }

    fprintf(gp, "set terminal wxt %d size 600,400\n", window);
    fprintf(gp, "set title '%s'\n", title);
    fprintf(gp, "unset key\n");
    fprintf(gp, "unset border\n");
    fprintf(gp, "unset tics\n");
    fprintf(gp, "set xrange [0:5]\n");
    fprintf(gp, "set yrange [%d:-1]\n", count);

    fprintf(gp, "set label 'N' at 0.5,-0.5 center\n");
    fprintf(gp, "set label 'M+C теор.' at 1.5,-0.5 center\n");
    fprintf(gp, "set label 'Убыв.' at 2.5,-0.5 center\n");
    fprintf(gp, "set label 'Случ.' at 3.5,-0.5 center\n");
    fprintf(gp, "set label 'Возр.' at 4.5,-0.5 center\n");

    for (int i = 0; i < count; i++) {
        double y = i + 0.5;
        fprintf(gp, "set label '%d' at 0.5,%f center\n", sizes[i], y);
        fprintf(gp, "set label '%.0f' at 1.5,%f center\n", theor[i], y);
        fprintf(gp, "set label '%.0f' at 2.5,%f center\n", best[i], y);
        fprintf(gp, "set label '%.0f' at 3.5,%f center\n", avg[i], y);
        fprintf(gp, "set label '%.0f' at 4.5,%f center\n", worst[i], y);
    }

    for (int i = 0; i <= count; i++) {
        fprintf(gp, "set arrow from 0,%d to 5,%d nohead lt 1 lw 1\n", i, i);
    }
    for (int j = 0; j <= 5; j++) {
        fprintf(gp, "set arrow from %d,0 to %d,%d nohead lt 1 lw 1\n", j, j, count);
    }

    fprintf(gp, "plot NaN\n");
    pclose(gp);
}

void plotTableGnuplotSort(int* sizes, double* best, double* avg, double* worst, int count, const char* title, int window) {
    char command[50];
    sprintf(command, "gnuplot -persistent");
    FILE* gp = popen(command, "w");
    if (gp == NULL) {
        printf("Ошибка при запуске Gnuplot для окна %d!\n", window);
        return;
    }

    fprintf(gp, "set terminal wxt %d size 600,400\n", window);
    fprintf(gp, "set title '%s'\n", title);
    fprintf(gp, "unset key\n");
    fprintf(gp, "unset border\n");
    fprintf(gp, "unset tics\n");
    fprintf(gp, "set xrange [0:4]\n");
    fprintf(gp, "set yrange [%d:-1]\n", count);

    fprintf(gp, "set label 'N' at 0.5,-0.5 center\n");
    fprintf(gp, "set label 'Убыв.' at 1.5,-0.5 center\n");
    fprintf(gp, "set label 'Случ.' at 2.5,-0.5 center\n");
    fprintf(gp, "set label 'Возр.' at 3.5,-0.5 center\n");

    for (int i = 0; i < count; i++) {
        double y = i + 0.5;
        fprintf(gp, "set label '%d' at 0.5,%f center\n", sizes[i], y);
        fprintf(gp, "set label '%.0f' at 1.5,%f center\n", best[i], y);
        fprintf(gp, "set label '%.0f' at 2.5,%f center\n", avg[i], y);
        fprintf(gp, "set label '%.0f' at 3.5,%f center\n", worst[i], y);
    }

    for (int i = 0; i <= count; i++) {
        fprintf(gp, "set arrow from 0,%d to 4,%d nohead lt 1 lw 1\n", i, i);
    }
    for (int j = 0; j <= 4; j++) {
        fprintf(gp, "set arrow from %d,0 to %d,%d nohead lt 1 lw 1\n", j, j, count);
    }

    fprintf(gp, "plot NaN\n");
    pclose(gp);
}

void plotComparisonGraph(int *sizes, int *heap_results, int *shell_results, int count) {
    FILE *gp = popen("gnuplot -persistent", "w");
    if (gp == NULL) {
        printf("Ошибка при запуске Gnuplot!\n");
        return;
    }

    fprintf(gp, "set terminal wxt 4 size 600,400\n");
    fprintf(gp, "set title 'Сравнение HeapSort и ShellSort (случайный массив)'\n");
    fprintf(gp, "set xlabel 'Размер массива n'\n");
    fprintf(gp, "set ylabel 'Mф + Cф'\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "set key left top\n");
    fprintf(gp, "set autoscale xy\n");
    fprintf(gp, "set style line 1 lc rgb '#FF0000' lt 1 lw 2 pt 7\n");
    fprintf(gp, "set style line 2 lc rgb '#0000FF' lt 1 lw 2 pt 7\n");

    fprintf(gp, "plot '-' with lines ls 1 title 'HeapSort', ");
    fprintf(gp, "'-' with lines ls 2 title 'ShellSort'\n");

    for (int i = 0; i < count; i++) {
        fprintf(gp, "%d %d\n", sizes[i], heap_results[i]);
    }
    fprintf(gp, "e\n");

    for (int i = 0; i < count; i++) {
        fprintf(gp, "%d %d\n", sizes[i], shell_results[i]);
    }
    fprintf(gp, "e\n");

    pclose(gp);
}

void runTests(int n, int *heap_result, int *shell_result) {
    int arr[n], temp[n];
    int c_fact, m_fact, stepCount;

    // HeapSort
    generateAverageCase(arr, n);
    for (int i = 0; i < n; i++) temp[i] = arr[i];
    heapSort(temp, n);
    *heap_result = M + C;

    // ShellSort
    generateAverageCase(arr, n);
    for (int i = 0; i < n; i++) temp[i] = arr[i];
    shellSort(temp, n, &c_fact, &m_fact, &stepCount);
    *shell_result = c_fact + m_fact;
}

int main() {
    srand(time(NULL));

    int sizes1[] = {100, 200, 300, 400, 500};
    int sizes2[] = {100, 200, 300, 400, 500};
    int count1 = 5, count2 = 5;

    double theor1[5], best1[5], avg1[5], worst1[5];
    double best2[5], avg2[5], worst2[5];

    // Трудоемкость построения пирамиды
    for (int i = 0; i < count1; i++) {
        int n = sizes1[i];
        int arr[n];

        theor1[i] = 2 * log2(n) + log2(n) + 2;

        M = 0; C = 0;
        generateWorstCase(arr, n);
        heapify(arr, 1, n);
        best1[i] = M + C;

        M = 0; C = 0;
        generateAverageCase(arr, n);
        heapify(arr, 1, n);
        avg1[i] = M + C;

        M = 0; C = 0;
        generateBestCase(arr, n);
        heapify(arr, 1, n);
        worst1[i] = M + C;
    }

    // Трудоемкость пирамидальной сортировки
    for (int i = 0; i < count2; i++) {
        int n = sizes2[i];
        int arr[n];

        M = 0; C = 0;
        generateWorstCase(arr, n);
        heapSort(arr, n);
        best2[i] = M + C;

        M = 0; C = 0;
        generateAverageCase(arr, n);
        heapSort(arr, n);
        avg2[i] = M + C;

        M = 0; C = 0;
        generateBestCase(arr, n);
        heapSort(arr, n);
        worst2[i] = M + C;
    }

    // Тестирование для графиков (HeapSort и ShellSort, случайный массив)
    int heap_results[5], shell_results[5];
    for (int i = 0; i < 5; i++) {
        runTests(sizes2[i], &heap_results[i], &shell_results[i]);
    }

    // Построение таблиц
    plotTableGnuplot(sizes1, theor1, best1, avg1, worst1, count1, "Трудоемкость построения пирамиды", 1);
    plotTableGnuplotSort(sizes2, best2, avg2, worst2, count2, "Трудоемкость пирамидальной сортировки", 2);

    // Построение графика
    plotComparisonGraph(sizes2, heap_results, shell_results, 5);

    return 0;
}