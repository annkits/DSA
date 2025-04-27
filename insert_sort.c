#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define N1 100
#define N2 200
#define N3 300
#define N4 400
#define N5 500

// заполнение массива возрастающими числами
void FillInc(int A[], int n){
    for (int i = 0; i < n; i++){
        A[i] = i + 1; 
    }
}

// заполнение массива убывающими числами
void FillDec(int A[], int n){
    for (int i = 0; i < n; i++){
        A[i] = n - i;
    }
}

// заполнение массива случайными числами
void FillRand(int A[], int n){
    for (int i = 0; i < n; i++){
        A[i] = rand() % 10000;
    }
}

//подсчёт контрольной суммы элементов массива А
unsigned long long int CheckSum(int A[], int n){
    unsigned long long int sum = 0;
    for (int i = 0; i < n; i++){
        sum += A[i];
    }
    return sum;
}

//подсчёт серий в массиве А
int RunNumber(int A[], int n){
    if (n == 0) return 0;
    int cnt = 1;
    for (int i = 1; i < n; i++){
        if (A[i] < A[i - 1]){
            cnt++;
        }
    }
    return cnt;
}

//вывод массива на экран
void PrintMas(int A[], int n){
    for (int i = 0; i < n; i++){
        printf("%d ", A[i]);
    }
    printf("\n");
}

//средняя длина серий в массиве
float AverageSeriesLenght(int A[], int n){
    if (n == 0) return 0;
    int series_count = RunNumber(A, n);
    return (float)n / series_count;
}

//расчёт теоретических сравнений
int CTheoretical(int n){
    int c_theoretical = ((int)(n * n - n) / 4);
    return c_theoretical;
}

//расчёт теоретических пересылок
int MTheoretical(int n){
    int m_theoretical = ((int)(((n * n - n) / 4)) + n - 1);
    return m_theoretical;
}

//расчёт отношений факт. сравн. и перест. к теоретическим
void CMComparison(int c_fact, int m_fact, int *c_theoretical, int *m_theoretical){
    float c_diff = (float)c_fact / *c_theoretical;
    printf("Отношение фактического количества сравнений с теоретическим: %.3f\n", c_diff);
    float m_diff = (float)m_fact / *m_theoretical;
    printf("Отношение фактического количества пересылок с теоретическим: %.3f\n", m_diff);
}

//функция метода SelectSort + фактические сравнения и перестановки
void selectSort(int A[], int n, int *c_fact, int *m_fact){
    *c_fact = 0;
    *m_fact = 0;
    for (int i = 0; i < n - 1; i++){
        int j_min = i;
        for (int j = i + 1; j < n; j++){
            (*c_fact)++;
            if (A[j] < A[j_min]){
                j_min = j;
            }
        }
            int temp = A[i];
            (*m_fact)++;
            A[i] = A[j_min];
            (*m_fact)++;
            A[j_min] = temp;
            (*m_fact)++;
    }
}

void bubbleSort(int A[], int n, int *c_fact, int *m_fact){
    *c_fact = 0;
    *m_fact = 0;
    for (int i = 0; i < n - 1; i++){
        for (int j = 1; j < n - i; j++){
            (*c_fact)++;
            if (A[j] < A[j - 1]){
                int temp = A[j];
                (*m_fact)++;
                A[j] = A[j - 1];
                (*m_fact)++;
                A[j - 1] = temp;
                (*m_fact)++;
            }
        }
    }
    // printf("Массив после сортировки: \n");
    // PrintMas(A, n);
    // printf("Количество сделанных сравнений: %d\n", *c_fact);
    // printf("Количество сделанных пересылок: %d\n", *m_fact);
}

void shakerSort(int A[], int n, int *c_fact, int *m_fact){
    *c_fact = 0;
    *m_fact = 0;

    int l = 0;
    int r = n - 1;
    int k = n;

    while (l < r){
        for (int j = r; j > l; j--){
            (*c_fact)++;
            if (A[j] < A[j - 1]){
                int temp = A[j];
                (*m_fact)++;
                A[j] = A[j - 1];
                (*m_fact)++;
                A[j - 1] = temp;
                (*m_fact)++;
                k = j;
            }
        }
        l = k;

        for (int j = l; j < r; j++){
            (*c_fact)++;
            if (A[j] > A[j + 1]){
                int temp = A[j];
                (*m_fact)++;
                A[j] = A[j + 1];
                (*m_fact)++;
                A[j + 1] = temp;
                (*m_fact)++;
                k = j;
            }
        }
        r = k;
    }
}

void insertSort(int A[], int n, int *c_fact, int *m_fact){
    *c_fact = 0;
    *m_fact = 0;

    for (int i = 1; i < n; ++i){
        int t = A[i];
        (*m_fact)++;
        int j = i - 1;

        while (j >= 0){
            (*c_fact)++;
            if (t < A[j]){
                A[j + 1] = A[j];
                (*m_fact)++;
                j = j - 1;
            } else break;
        }
        A[j + 1] = t;
        (*m_fact)++;
    }
}

void output(int A[], int n, int *c_theoretical, int *m_theoretical){
    int c_fact = 0;
    int m_fact = 0;

    FillDec(A, n);
    // PrintMas(A, n);
    printf("Контрольная сумма: %lld\n", CheckSum(A, n));
    printf("Количество серий: %d\n", RunNumber(A, n));
    printf("\n");

    int *copyA = (int *)malloc(n * sizeof(int));
    memcpy(copyA, A, n * sizeof(int));
    insertSort(copyA, n, &c_fact, &m_fact);
    printf("Контрольная сумма: %lld\n", CheckSum(copyA, n));
    printf("Количество серий: %d\n", RunNumber(copyA, n));
    CMComparison(c_fact, m_fact, c_theoretical, m_theoretical);
    printf("\n");
    free(copyA);

    FillRand(A, n);
    // PrintMas(A, n);
    printf("Контрольная сумма: %lld\n", CheckSum(A, n));
    printf("Количество серий: %d\n", RunNumber(A, n));
    printf("\n");

    copyA = (int *)malloc(n * sizeof(int));
    memcpy(copyA, A, n * sizeof(int));
    insertSort(copyA, n, &c_fact, &m_fact);
    printf("Контрольная сумма: %lld\n", CheckSum(copyA, n));
    printf("Количество серий: %d\n", RunNumber(copyA, n));
    CMComparison(c_fact, m_fact, c_theoretical, m_theoretical);
    printf("\n");
    free(copyA);

    FillInc(A, n);
    // PrintMas(A, n);
    printf("Контрольная сумма: %lld\n", CheckSum(A, n));
    printf("Количество серий: %d\n", RunNumber(A, n));
    printf("\n");

    copyA = (int *)malloc(n * sizeof(int));
    memcpy(copyA, A, n * sizeof(int));
    insertSort(copyA, n, &c_fact, &m_fact);
    printf("Контрольная сумма: %lld\n", CheckSum(copyA, n));
    printf("Количество серий: %d\n", RunNumber(copyA, n));
    CMComparison(c_fact, m_fact, c_theoretical, m_theoretical);
    printf("\n");
    free(copyA);
}

void RunTests0(int n, int *results) {
    int A[n], B[n];
    int c_fact, m_fact;
    
    FillDec(A, n);
    memcpy(B, A, n * sizeof(int));
    insertSort(B, n, &c_fact, &m_fact);
    results[0] = c_fact + m_fact;

    FillRand(A, n);
    memcpy(B, A, n * sizeof(int));
    insertSort(B, n, &c_fact, &m_fact);
    results[1] = c_fact + m_fact;

    FillInc(A, n);
    memcpy(B, A, n * sizeof(int));
    insertSort(B, n, &c_fact, &m_fact);
    results[2] = c_fact + m_fact;
}

void PrintTableRow(int N, int M_C_teor, int *results) {
    printf("| %-3d | %-13d | %-8d | %-8d | %-8d |\n", N, M_C_teor, results[0], results[1], results[2]);
}

//массивы случайных чисел
void RunTests2(int n, int *select_results, int *bubble_results, int *shaker_results, int *insert_results) {
    int A[n], B[n];
    int c_fact, m_fact;

    // Тест для сортировки выбором
    FillRand(A, n);
    memcpy(B, A, n * sizeof(int));
    selectSort(B, n, &c_fact, &m_fact);
    select_results[0] = c_fact + m_fact;

    // Тест для пузырьковой сортировки
    FillRand(A, n);
    memcpy(B, A, n * sizeof(int));
    bubbleSort(B, n, &c_fact, &m_fact);
    bubble_results[0] = c_fact + m_fact;

    //Тест для шейкер сортировки
    FillRand(A, n);
    memcpy(B, A, n * sizeof(int));
    shakerSort(B, n, &c_fact, &m_fact);
    shaker_results[0] = c_fact + m_fact;

    //Тест для сортировки вставками
    FillRand(A, n);
    memcpy(B, A, n * sizeof(int));
    insertSort(B, n, &c_fact, &m_fact);
    insert_results[0] = c_fact + m_fact;
}

//для сводной таблицы
void PrintTableRow2(int N, int *select_results, int *bubble_results, int *shaker_results, int *insert_results) {
    printf("| %-3d | %-12d | %-12d | %-12d | %-12d |\n", N, *select_results, *bubble_results, *shaker_results, *insert_results);
}

void PlotGraph(int *sizes, int *select_results, int *bubble_results, int *shaker_results, int *insert_results, int count) {
    FILE *gp = popen("gnuplot -persistent", "w");
    if (gp == NULL) {
        printf("Ошибка при запуске Gnuplot!\n");
        return;
    }

    fprintf(gp, "set title 'Сравнение алгоритмов сортировки'\n");
    fprintf(gp, "set xlabel 'Размер массива n'\n");
    fprintf(gp, "set ylabel 'Mф + Cф'\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "set key left top\n"); // Легенда в верхнем левом углу
    fprintf(gp, "set autoscale xy\n");
    fprintf(gp, "set style line 1 lc rgb '#245E20' lt 1 lw 2 pt 7\n"); // Зеленый для SelectSort
    fprintf(gp, "set style line 2 lc rgb '#FFA500' lt 1 lw 2 pt 7\n"); // Оранжевый для BubbleSort
    fprintf(gp, "set style line 3 lc rgb '#0000FF' lt 1 lw 2 pt 7\n"); // Синий для ShakerSort
    fprintf(gp, "set style line 4 lc rgb '#FF0000' lt 1 lw 2 pt 7\n"); // Красный для InsertSort

    // Построение графиков
    fprintf(gp, "plot '-' with lines ls 1 title 'Select Sort', ");
    fprintf(gp, "'-' with lines ls 2 title 'Bubble Sort', ");
    fprintf(gp, "'-' with lines ls 3 title 'Shaker Sort', ");
    fprintf(gp, "'-' with lines ls 4 title 'Insert Sort'\n");

    for (int i = 0; i < count; i++) {
        fprintf(gp, "%d %d\n", sizes[i], select_results[i]);
    }
    fprintf(gp, "e\n");

    for (int i = 0; i < count; i++) {
        fprintf(gp, "%d %d\n", sizes[i], bubble_results[i]);
    }
    fprintf(gp, "e\n");

    for (int i = 0; i < count; i++) {
        fprintf(gp, "%d %d\n", sizes[i], shaker_results[i]);
    }
    fprintf(gp, "e\n");

    for (int i = 0; i < count; i++) {
        fprintf(gp, "%d %d\n", sizes[i], insert_results[i]);
    }
    fprintf(gp, "e\n");

    pclose(gp);
}

void PlotTableGnuplot1(int *sizes, int *c_theoretical, int *m_theoretical, int results[][6], int count) {
    FILE *gp = popen("gnuplot -persistent", "w");
    if (gp == NULL) {
        printf("Ошибка при запуске Gnuplot!\n");
        return;
    }

    fprintf(gp, "set title 'Трудоемкость метода прямого включения InsertSort'\n");
    fprintf(gp, "unset key\n");
    fprintf(gp, "unset border\n");
    fprintf(gp, "unset tics\n");
    fprintf(gp, "set xrange [0:5]\n");
    fprintf(gp, "set yrange [%d:-1]\n", count);

    // *** Заголовки ***
    fprintf(gp, "set label 1 'n' at 0.5,-0.5 center\n");
    fprintf(gp, "set label 2 'Mф+Cф' at 4,-0.5 center\n");
    fprintf(gp, "set label 4 'М+С теор.' at 1.5,-0.5 center\n");
    fprintf(gp, "set label 5 'Убыв' at 2.5,-0.2 center\n");
    fprintf(gp, "set label 6 'Случ' at 3.5,-0.2 center\n");
    fprintf(gp, "set label 7 'Возр' at 4.5,-0.2 center\n");

    // *** Данные в ячейках ***
    for (int i = 0; i < count; i++) {
        double y = i + 0.5;  // Центр строки

        fprintf(gp, "set label '%d' at 0.5,%f center\n", sizes[i], y);
        fprintf(gp, "set label '%d' at 1.5,%f center\n", c_theoretical[i] + m_theoretical[i], y);
        fprintf(gp, "set label '%d' at 2.5,%f center\n", results[i][0], y);
        fprintf(gp, "set label '%d' at 3.5,%f center\n", results[i][1], y);
        fprintf(gp, "set label '%d' at 4.5,%f center\n", results[i][2], y);
    }

    // *** Линии таблицы ***
    for (int i = 0; i <= count; i++) {
        fprintf(gp, "set arrow from 0,%d to 5,%d nohead lt 1 lw 1\n", i, i);
    }
    for (int j = 0; j <= 7; j++) {
        fprintf(gp, "set arrow from %d,0 to %d,%d nohead lt 1 lw 1\n", j, j, count);
    }

    fprintf(gp, "plot NaN\n");
    pclose(gp);
}

void PlotTableGnuplot2(int *sizes, int *select_results, int *bubble_results, int *shaker_results, int *insert_results, int count) {
    FILE *gp = popen("gnuplot -persistent", "w");
    if (gp == NULL) {
        printf("Ошибка при запуске Gnuplot!\n");
        return;
    }

    fprintf(gp, "set title 'Трудоемкость квадратичных методов сортировки'\n");
    fprintf(gp, "unset key\n");
    fprintf(gp, "unset border\n");
    fprintf(gp, "unset tics\n");
    fprintf(gp, "set xrange [0:5]\n");
    fprintf(gp, "set yrange [%d:-1]\n", count);

    // *** Заголовки ***
    fprintf(gp, "set label 1 'n' at 0.5,-0.5 center\n");
    fprintf(gp, "set label 2 'Mф+Cф' at 4,-0.5 center\n");
    fprintf(gp, "set label 4 'Select' at 1.5,-0.2 center\n");
    fprintf(gp, "set label 5 'Bubble' at 2.5,-0.2 center\n");
    fprintf(gp, "set label 6 'Shaker' at 3.5,-0.2 center\n");
    fprintf(gp, "set label 7 'Insert' at 4.5,-0.2 center\n");

    // *** Данные в ячейках ***
    for (int i = 0; i < count; i++) {
        double y = i + 0.5;  // Центр строки

        fprintf(gp, "set label '%d' at 0.5,%f center\n", sizes[i], y);
        fprintf(gp, "set label '%d' at 1.5,%f center\n", select_results[i], y);
        fprintf(gp, "set label '%d' at 2.5,%f center\n", bubble_results[i], y);
        fprintf(gp, "set label '%d' at 3.5,%f center\n", shaker_results[i], y);
        fprintf(gp, "set label '%d' at 4.5,%f center\n", insert_results[i], y);
    }

    // *** Линии таблицы ***
    for (int i = 0; i <= count; i++) {
        fprintf(gp, "set arrow from 0,%d to 5,%d nohead lt 1 lw 1\n", i, i);
    }
    for (int j = 0; j <= 7; j++) {
        fprintf(gp, "set arrow from %d,0 to %d,%d nohead lt 1 lw 1\n", j, j, count);
    }

    fprintf(gp, "plot NaN\n");
    pclose(gp);
}

int main(){
    srand(time(NULL));

    int A[N1];
    int B[N2];
    int C[N3];
    int D[N4];
    int E[N5];
    int sizes[] = {N1, N2, N3, N4, N5};

    int c_theoretical[5];
    int m_theoretical[5];
    for (int i = 0; i < 5; i++){
        c_theoretical[i] = CTheoretical(sizes[i]);
        m_theoretical[i] = MTheoretical(sizes[i]);
    }

    for (int i = 0; i < 5; i++){
        printf("Теоретическое количество сравнений N = %d: %d\n", sizes[i], c_theoretical[i]);
        printf("Теоретическое количество пересылок N = %d: %d\n", sizes[i], m_theoretical[i]);

    }

    printf("\n");

    for (int i = 0; i < 5; i++){
        output(A, sizes[i], &c_theoretical[i], &m_theoretical[i]);
    }

    int results[5][6];
    for (int i = 0; i < 5; i++){
        RunTests0(sizes[i], results[i]);
    }

    printf("     Трудоемкость метода прямого включения InsertSort\n");
    printf("----------------------------------------------------------------------\n");
    printf("| N   | M+C теоретич. |          M_факт+C_факт         |\n");
    printf("|     |               | Убыв.    | Случ.    | Возр.    |\n");
    printf("----------------------------------------------------------------------\n");

    for (int i = 0; i < 5; i++){
        PrintTableRow(sizes[i], c_theoretical[i] + m_theoretical[i], results[i]);
    }
    printf("\n");


    printf("           Трудоемкость квадратичных методов сортировки\n");
    printf("----------------------------------------------------------------------\n");
    printf("| N   |                        M_факт+C_факт                      |\n");
    printf("|     | Select       | Bubble       | Shaker       | Insert       |\n");
    printf("----------------------------------------------------------------------\n");

    int select_results[5], bubble_results[5], shaker_results[5], insert_results[5];
    for (int i = 0; i < 5; i++) {
        RunTests2(sizes[i], &select_results[i], &bubble_results[i], &shaker_results[i], &insert_results[i]);
        PrintTableRow2(sizes[i], &select_results[i], &bubble_results[i], &shaker_results[i], &insert_results[i]);
    }

    PlotTableGnuplot1(sizes, c_theoretical, m_theoretical, results, 5);
    PlotTableGnuplot2(sizes, select_results, bubble_results, shaker_results, insert_results, 5);

    PlotGraph(sizes, select_results, bubble_results, shaker_results, insert_results, 5);
}