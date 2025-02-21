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
    srand(time(NULL));
    for (int i = 0; i < n; i++){
        A[i] = rand();
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
    int c_theoretical = ((int)(n * n - n) / 2);
    return c_theoretical;
}

//расчёт теоретических пересылок
int MTheoretical(int n){
    int m_theoretical = ((int)(3 * (n * n - n)) / 4);
    return m_theoretical;
}

//расчёт отношений факт. сравн. и перест. к теоретическим
void CMComparison(int c_fact, int m_fact, int *c_theoretical, int *m_theoretical){
    float c_diff = (float)c_fact / *c_theoretical;
    printf("Отношение фактического количества сравнений с теоретическим: %.3f\n", c_diff);
    float m_diff = (float)m_fact / *m_theoretical;
    printf("Отношение фактического количества пересылок с теоретическим: %.3f\n", m_diff);
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

void output(int A[], int n, int *c_theoretical, int *m_theoretical){
    int c_fact = 0;
    int m_fact = 0;

    FillDec(A, n);
    PrintMas(A, n);
    printf("Контрольная сумма: %lld\n", CheckSum(A, n));
    printf("Количество серий: %d\n", RunNumber(A, n));
    printf("\n");

    int *copyA = (int *)malloc(n * sizeof(int));
    memcpy(copyA, A, n * sizeof(int));
    bubbleSort(copyA, n, &c_fact, &m_fact);
    printf("Контрольная сумма: %lld\n", CheckSum(copyA, n));
    printf("Количество серий: %d\n", RunNumber(copyA, n));
    CMComparison(c_fact, m_fact, c_theoretical, m_theoretical);
    printf("\n");
    free(copyA);

    FillRand(A, n);
    PrintMas(A, n);
    printf("Контрольная сумма: %lld\n", CheckSum(A, n));
    printf("Количество серий: %d\n", RunNumber(A, n));
    printf("\n");

    copyA = (int *)malloc(n * sizeof(int));
    memcpy(copyA, A, n * sizeof(int));
    bubbleSort(copyA, n, &c_fact, &m_fact);
    printf("Контрольная сумма: %lld\n", CheckSum(copyA, n));
    printf("Количество серий: %d\n", RunNumber(copyA, n));
    CMComparison(c_fact, m_fact, c_theoretical, m_theoretical);
    printf("\n");
    free(copyA);

    FillInc(A, n);
    PrintMas(A, n);
    printf("Контрольная сумма: %lld\n", CheckSum(A, n));
    printf("Количество серий: %d\n", RunNumber(A, n));
    printf("\n");

    copyA = (int *)malloc(n * sizeof(int));
    memcpy(copyA, A, n * sizeof(int));
    bubbleSort(copyA, n, &c_fact, &m_fact);
    printf("Контрольная сумма: %lld\n", CheckSum(copyA, n));
    printf("Количество серий: %d\n", RunNumber(copyA, n));
    CMComparison(c_fact, m_fact, c_theoretical, m_theoretical);
    printf("\n");
    free(copyA);
}

void RunTests(int n, int *results) {
    int A[n], B[n];
    int c_fact, m_fact;

    FillDec(A, n);
    memcpy(B, A, n * sizeof(int));
    bubbleSort(B, n, &c_fact, &m_fact);
    results[0] = c_fact + m_fact;

    FillRand(A, n);
    memcpy(B, A, n * sizeof(int));
    bubbleSort(B, n, &c_fact, &m_fact);
    results[1] = c_fact + m_fact;

    FillInc(A, n);
    memcpy(B, A, n * sizeof(int));
    bubbleSort(B, n, &c_fact, &m_fact);
    results[2] = c_fact + m_fact;
}

void PrintTableRow(int N, int M_C_teor, int *results) {
    printf("| %-3d | %-13d | %-8d | %-8d | %-8d |\n", N, M_C_teor, results[0], results[1], results[2]);
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

void RunTests2(int n, int *bubble_results, int *select_results) {
    int A[n], B[n];
    int c_fact, m_fact;

    // Тест для пузырьковой сортировки
    FillRand(A, n);
    memcpy(B, A, n * sizeof(int));
    bubbleSort(B, n, &c_fact, &m_fact);
    bubble_results[0] = c_fact + m_fact;

    // Тест для сортировки выбором
    FillRand(A, n);
    memcpy(B, A, n * sizeof(int));
    selectSort(B, n, &c_fact, &m_fact);
    select_results[0] = c_fact + m_fact;
}

void PlotGraph(int *sizes, int *bubble_results, int *select_results, int count) {
    FILE *gp = popen("gnuplot -persistent", "w");
    if (gp == NULL) {
        printf("Ошибка при запуске Gnuplot!\n");
        return;
    }

    fprintf(gp, "set title 'Сравнение алгоритмов сортировки'\n");
    fprintf(gp, "set xlabel 'Размер массива n'\n");
    fprintf(gp, "set ylabel 'Mф + Cф'\n");
    fprintf(gp, "plot '-' with lines title 'Bubble Sort', '-' with lines title 'Select Sort'\n");

    for (int i = 0; i < count; i++) {
        fprintf(gp, "%d %d\n", sizes[i], bubble_results[i]);
    }
    fprintf(gp, "e\n");

    for (int i = 0; i < count; i++) {
        fprintf(gp, "%d %d\n", sizes[i], select_results[i]);
    }
    fprintf(gp, "e\n");

    pclose(gp);
}

void PlotTableGnuplot(int *sizes, int *theor, int results[][3], int count) {
    FILE *gp = popen("gnuplot -persistent", "w");
    if (gp == NULL) {
        printf("Ошибка при запуске Gnuplot!\n");
        return;
    }

    fprintf(gp, "set title 'Трудоемкость пузырьковой сортировки'\n");
    fprintf(gp, "unset key\n");
    fprintf(gp, "unset border\n");
    fprintf(gp, "unset tics\n");
    fprintf(gp, "set xrange [0:5]\n");
    fprintf(gp, "set yrange [%d:-1]\n", count);

    // *** Заголовки ***
    fprintf(gp, "set label 1 'N' at 0.5,-0.5 center\n");
    fprintf(gp, "set label 2 'M+C\\nтеоретич.' at 1.5,-0.5 center\n");
    fprintf(gp, "set label 3 'Mфакт+Cфакт' at 3.5,-0.7 center\n");
    fprintf(gp, "set label 4 'Убыв.' at 2.5,-0.2 center\n");
    fprintf(gp, "set label 5 'Случ.' at 3.5,-0.2 center\n");
    fprintf(gp, "set label 6 'Возр.' at 4.5,-0.2 center\n");

    // *** Данные в ячейках ***
    for (int i = 0; i < count; i++) {
        double y = i + 0.5;  // Центр строки

        fprintf(gp, "set label '%d' at 0.5,%f center\n", sizes[i], y);
        fprintf(gp, "set label '%d' at 1.5,%f center\n", theor[i], y);
        fprintf(gp, "set label '%d' at 2.5,%f center\n", results[i][0], y);
        fprintf(gp, "set label '%d' at 3.5,%f center\n", results[i][1], y);
        fprintf(gp, "set label '%d' at 4.5,%f center\n", results[i][2], y);
    }

    // *** Линии таблицы ***
    for (int i = 0; i <= count; i++) {
        fprintf(gp, "set arrow from 0,%d to 5,%d nohead lt 1 lw 1\n", i, i);
    }
    for (int j = 0; j <= 5; j++) {
        fprintf(gp, "set arrow from %d,0 to %d,%d nohead lt 1 lw 1\n", j, j, count);
    }

    fprintf(gp, "plot NaN\n");
    pclose(gp);
}

int main(){
    int A[N1];
    int B[N2];
    int C[N3];
    int D[N4];
    int E[N5];

    int c1_theoretical = CTheoretical(N1);
    int c2_theoretical = CTheoretical(N2);
    int c3_theoretical = CTheoretical(N3);
    int c4_theoretical = CTheoretical(N4);
    int c5_theoretical = CTheoretical(N5);

    printf("Теоретическое количество сравнений N = 100: %d\n", c1_theoretical);
    printf("Теоретическое количество сравнений N = 200: %d\n", c2_theoretical);
    printf("Теоретическое количество сравнений N = 300: %d\n", c3_theoretical);
    printf("Теоретическое количество сравнений N = 400: %d\n", c4_theoretical);
    printf("Теоретическое количество сравнений N = 500: %d\n", c5_theoretical);

    int m1_theoretical = MTheoretical(N1);
    int m2_theoretical = MTheoretical(N2);
    int m3_theoretical = MTheoretical(N3);
    int m4_theoretical = MTheoretical(N4);
    int m5_theoretical = MTheoretical(N5);

    printf("Теоретическое количество сравнений N = 100: %d\n", m1_theoretical);
    printf("Теоретическое количество сравнений N = 200: %d\n", m2_theoretical);
    printf("Теоретическое количество сравнений N = 300: %d\n", m3_theoretical);
    printf("Теоретическое количество сравнений N = 400: %d\n", m4_theoretical);
    printf("Теоретическое количество сравнений N = 500: %d\n", m5_theoretical);

    printf("\n");

    output(A, N1, &c1_theoretical, &m1_theoretical);
    output(A, N2, &c1_theoretical, &m1_theoretical);
    output(A, N3, &c1_theoretical, &m1_theoretical);
    output(A, N4, &c1_theoretical, &m1_theoretical);
    output(A, N5, &c1_theoretical, &m1_theoretical);

    int results1[6], results2[6], results3[6], results4[6], results5[6];

    RunTests(N1, results1);
    RunTests(N2, results2);
    RunTests(N3, results3);
    RunTests(N4, results4);
    RunTests(N5, results5);

    printf("----------------------------------------------------------------------\n");
    printf("| N   | M+C теоретич. |          M_факт+C_факт         |\n");
    printf("|     |               | Убыв.    | Случ.    | Возр.    |\n");
    printf("----------------------------------------------------------------------\n");

    PrintTableRow(N1, CTheoretical(N1) + MTheoretical(N1), results1);
    PrintTableRow(N2, CTheoretical(N2) + MTheoretical(N2), results2);
    PrintTableRow(N3, CTheoretical(N3) + MTheoretical(N3), results3);
    PrintTableRow(N4, CTheoretical(N4) + MTheoretical(N4), results4);
    PrintTableRow(N5, CTheoretical(N5) + MTheoretical(N5), results5);

    int sizes[] = {N1, N2, N3, N4, N5};
    int bubble_results[5], select_results[5];
    for (int i = 0; i < 5; i++) {
        RunTests2(sizes[i], &bubble_results[i], &select_results[i]);
    }
    PlotGraph(sizes, bubble_results, select_results, 5);

    int sizes2[] = {100, 200, 300, 400, 500};
    int theor[] = {CTheoretical(100) + MTheoretical(100), 
        CTheoretical(200) + MTheoretical(200), 
        CTheoretical(300) + MTheoretical(300), 
        CTheoretical(400) + MTheoretical(400), 
        CTheoretical(500) + MTheoretical(500)};
    
    int results[5][3];
    RunTests(100, results[0]);
    RunTests(200, results[1]);
    RunTests(300, results[2]);
    RunTests(400, results[3]);
    RunTests(500, results[4]);

    PlotTableGnuplot(sizes2, theor, results, 5);
}