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

// Функция для вычисления шага h_i по заданной формуле
int calculateStep(int i, int prev_h) {
    return 3 * prev_h + 1;
}

// Функция для генерации последовательности шагов
void generateSteps(int steps[], int *stepCount, int n) {
    int m = (int)(log2(n)) - 1; // m = floor(log2(n)) - 1
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

void shellSort(int A[], int n, int *c_fact, int *m_fact, int *stepCount){
    *c_fact = 0;
    *m_fact = 0;

    int steps[100];

    generateSteps(steps, stepCount, n);

    for (int s = *stepCount - 1; s >= 0; s--){
        int k = steps[s];
        for(int i = k; i < n; i++){
            int t = A[i];
            (*m_fact)++;
            int j = i - k;
            
            while (j >= 0){
                (*c_fact)++;
                if (t < A[j]){
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

// Функция для генерирования последовательности шагов Чиперфилда
void generateChipperfieldSequence(int steps2[], int *stepCount2, int n) {
    int chipperfield[] = {1, 4, 10, 23, 57, 132, 301, 701};
    int max_steps = sizeof(chipperfield) / sizeof(chipperfield[0]);
    *stepCount2 = 0;

    for (int i = 0; i < max_steps; i++) {
        if (chipperfield[i] >= n) break;
        steps2[i] = chipperfield[i];
        (*stepCount2)++;
    }
}

// Основная функция сортировки Шелла с использованием последовательности Чиперфилда
void shellSort2(int A[], int n, int *c_fact, int *m_fact, int *stepCount2) {
    *c_fact = 0;
    *m_fact = 0;
    int steps2[20];
    generateChipperfieldSequence(steps2, stepCount2, n);

    for (int i = *stepCount2 - 1; i >= 0; i--) {
        int k = steps2[i];
        for(int i = k; i < n; i++){
            int t = A[i];
            (*m_fact)++;
            int j = i - k;
            
            while (j >= 0){
                (*c_fact)++;
                if (t < A[j]){
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

void output(int A[], int n, int *c_theoretical, int *m_theoretical, int *stepCount){
    int c_fact = 0;
    int m_fact = 0;

    FillDec(A, n);
    // PrintMas(A, n);
    printf("Контрольная сумма: %lld\n", CheckSum(A, n));
    printf("Количество серий: %d\n", RunNumber(A, n));
    printf("\n");

    int *copyA = (int *)malloc(n * sizeof(int));
    memcpy(copyA, A, n * sizeof(int));
    shellSort(copyA, n, &c_fact, &m_fact, stepCount);
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
    shellSort(copyA, n, &c_fact, &m_fact, stepCount);
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
    shellSort(copyA, n, &c_fact, &m_fact, stepCount);
    printf("Контрольная сумма: %lld\n", CheckSum(copyA, n));
    printf("Количество серий: %d\n", RunNumber(copyA, n));
    CMComparison(c_fact, m_fact, c_theoretical, m_theoretical);
    printf("\n");
    free(copyA);
}

void RunTests0(int n, int *results, int *stepCount) {
    int A[n], B[n];
    int c_fact, m_fact;

    FillRand(A, n);
    memcpy(B, A, n * sizeof(int));
    insertSort(B, n, &c_fact, &m_fact);
    results[0] = c_fact + m_fact;

    FillRand(A, n);
    memcpy(B, A, n * sizeof(int));
    shellSort(B, n, &c_fact, &m_fact, stepCount);
    results[1] = c_fact + m_fact;
}

void RunTests1(int n, int *results2, int *stepCount, int *stepCount2) {
    int A[n], B[n];
    int c_fact, m_fact;

    // Для последовательности Кнута
    FillRand(A, n);
    memcpy(B, A, n * sizeof(int));
    shellSort(B, n, &c_fact, &m_fact, stepCount);
    results2[0] = c_fact + m_fact;

    // Для последовательности Чиперфилда
    FillRand(A, n);
    memcpy(B, A, n * sizeof(int));
    shellSort2(B, n, &c_fact, &m_fact, stepCount2);
    results2[1] = c_fact + m_fact;
}

void PrintTableRow(int N, int *steps, int stepCount, int *results) {
    printf("| %-3d | ", N);
    
    for (int i = 0; i < stepCount; i++) {
        printf("%-4d ", steps[i]);
    }

    for (int i = stepCount; i < 10; i++) {
        printf("     ");
    }

    printf("| %-20d | %-20d |\n", results[0], results[1]);
}

//массивы случайных чисел
void RunTests2(int n, int *select_results, int *bubble_results, int *shaker_results, int *insert_results, int *shell_results, int *stepCount) {
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

    //Тест для сортировки вставками
    FillRand(A, n);
    memcpy(B, A, n * sizeof(int));
    shellSort(B, n, &c_fact, &m_fact, stepCount);
    shell_results[0] = c_fact + m_fact;
}

//для второй таблицы
void PrintTableRow2(int N, int *steps, int stepCount, int *steps2, int stepCount2, int *results2) {
    printf("| %-3d | ", N);
    
    // Выводим шаги Кнута (в порядке возрастания)
    for (int i = 0; i < stepCount; i++) {
        printf("%-3d ", steps[i]);
    }
    for (int i = stepCount; i < 8; i++) {
        printf("    ");
    }
    printf("| %-14d | ", results2[0]);

    // Выводим шаги Чиперфилда (в порядке возрастания)
    for (int i = 0; i < stepCount2; i++) {
        printf("%-3d ", steps2[i]);
    }
    for (int i = stepCount2; i < 8; i++) {
        printf("    ");
    }
    printf("| %-14d |\n", results2[1]);
}

void PlotGraph(int *sizes, int *select_results, int *bubble_results, int *shaker_results, int *insert_results, int *shell_results, int count) {
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
    fprintf(gp, "set style line 5 lc rgb '#800080' lt 1 lw 2 pt 7\n"); // Фиолетовый для ShellSort

    // Построение графиков
    fprintf(gp, "plot '-' with lines ls 1 title 'Select Sort', ");
    fprintf(gp, "'-' with lines ls 2 title 'Bubble Sort', ");
    fprintf(gp, "'-' with lines ls 3 title 'Shaker Sort', ");
    fprintf(gp, "'-' with lines ls 4 title 'Insert Sort', ");
    fprintf(gp, "'-' with lines ls 5 title 'Shell Sort'\n");

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

    for (int i = 0; i < count; i++) {
        fprintf(gp, "%d %d\n", sizes[i], shell_results[i]);
    }
    fprintf(gp, "e\n");

    pclose(gp);
}

void PlotTableGnuplot1(int *sizes, int *insert_results, int *shell_results, int count) {
    FILE *gp = popen("gnuplot -persistent", "w");
    if (gp == NULL) {
        printf("Ошибка при запуске Gnuplot!\n");
        return;
    }

    fprintf(gp, "set title 'Трудоемкость метода Шелла'\n");
    fprintf(gp, "unset key\n");
    fprintf(gp, "unset border\n");
    fprintf(gp, "unset tics\n");
    fprintf(gp, "set xrange [0:4]\n"); // 4 столбца: n, шаги, Insert, Shell
    fprintf(gp, "set yrange [%d:-1]\n", count);

    // *** Заголовки ***
    fprintf(gp, "set label 1 'N' at 0.5,-0.5 center\n");
    fprintf(gp, "set label 2 'h1 … hm Д.Кнута' at 1.5,-0.5 center\n");
    fprintf(gp, "set label 3 'Insert M_факт+C_факт' at 2.5,-0.5 center\n");
    fprintf(gp, "set label 4 'Shell M_факт+C_факт' at 3.5,-0.5 center\n");

    // *** Данные в ячейках ***
    for (int i = 0; i < count; i++) {
        double y = i + 0.5; // Центр строки
        int steps[10];
        int stepCount;
        generateSteps(steps, &stepCount, sizes[i]);

        fprintf(gp, "set label '%d' at 0.5,%f center\n", sizes[i], y);

        // Вывод шагов Кнута (в порядке возрастания)
        char steps_str[50] = "";
        for (int j = 0; j < stepCount; j++) {
            char temp[10];
            sprintf(temp, "%d ", steps[j]);
            strcat(steps_str, temp);
        }
        fprintf(gp, "set label '%s' at 1.5,%f center\n", steps_str, y);

        fprintf(gp, "set label '%d' at 2.5,%f center\n", insert_results[i], y);
        fprintf(gp, "set label '%d' at 3.5,%f center\n", shell_results[i], y);
    }

    // *** Линии таблицы ***
    for (int i = 0; i <= count; i++) {
        fprintf(gp, "set arrow from 0,%d to 4,%d nohead lt 1 lw 1\n", i, i);
    }
    for (int j = 0; j <= 4; j++) {
        fprintf(gp, "set arrow from %d,0 to %d,%d nohead lt 1 lw 1\n", j, j, count);
    }

    fprintf(gp, "plot NaN\n");
    pclose(gp);
}

void PlotTableGnuplot2(int *sizes, int results2[][2], int count) {
    FILE *gp = popen("gnuplot -persistent", "w");
    if (gp == NULL) {
        printf("Ошибка при запуске Gnuplot!\n");
        return;
    }

    fprintf(gp, "set title 'Исследование трудоемкости метода Шелла'\n");
    fprintf(gp, "unset key\n");
    fprintf(gp, "unset border\n");
    fprintf(gp, "unset tics\n");
    fprintf(gp, "set xrange [0:5]\n"); // 5 столбцов: n, шаги Кнута, Shell (Кнут), шаги Чиперфилда, Shell (Чиперфилд)
    fprintf(gp, "set yrange [%d:-1]\n", count);

    // *** Заголовки ***
    fprintf(gp, "set label 1 'N' at 0.5,-0.5 center\n");
    fprintf(gp, "set label 2 'h1 … hm Д.Кнута' at 1.5,-0.5 center\n");
    fprintf(gp, "set label 3 'Shell' at 2.5,-0.5 center\n");
    fprintf(gp, "set label 4 'h1 … hm Чиперфилда' at 3.5,-0.5 center\n");
    fprintf(gp, "set label 5 'Shell' at 4.5,-0.5 center\n");
    fprintf(gp, "set label 6 'M_факт+C_факт' at 2.5,-0.2 center\n");
    fprintf(gp, "set label 7 'M_факт+C_факт' at 4.5,-0.2 center\n");

    // *** Данные в ячейках ***
    for (int i = 0; i < count; i++) {
        double y = i + 0.5; // Центр строки
        int steps[10];
        int stepCount;
        int steps2[10];
        int stepCount2;
        generateSteps(steps, &stepCount, sizes[i]);
        generateChipperfieldSequence(steps2, &stepCount2, sizes[i]);

        fprintf(gp, "set label '%d' at 0.5,%f center\n", sizes[i], y);

        // Вывод шагов Кнута (в порядке возрастания)
        char steps_str[50] = "";
        for (int j = 0; j < stepCount; j++) {
            char temp[10];
            sprintf(temp, "%d ", steps[j]);
            strcat(steps_str, temp);
        }
        fprintf(gp, "set label '%s' at 1.5,%f center\n", steps_str, y);

        fprintf(gp, "set label '%d' at 2.5,%f center\n", results2[i][0], y);

        // Вывод шагов Чиперфилда (в порядке убывания)
        char steps2_str[50] = "";
        for (int j = 0; j < stepCount2; j++) {
            char temp[10];
            sprintf(temp, "%d ", steps2[j]);
            strcat(steps2_str, temp);
        }
        fprintf(gp, "set label '%s' at 3.5,%f center\n", steps2_str, y);

        fprintf(gp, "set label '%d' at 4.5,%f center\n", results2[i][1], y);
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
    srand(time(NULL));

    int A[N1];
    int B[N2];
    int C[N3];
    int D[N4];
    int E[N5];
    int sizes[] = {N1, N2, N3, N4, N5};
    int stepCount;
    int stepCount2;
    int steps[10]; // Массив для хранения шагов
    int steps2[10];

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
        output(A, sizes[i], &c_theoretical[i], &m_theoretical[i], &stepCount);
    }

    int results[5][2];
    for (int i = 0; i < 5; i++){
        RunTests0(sizes[i], results[i], &stepCount);
    }

    printf("     Трудоемкость метода Шелла\n");
    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("| N   | h1 … hm по формуле                                | Insert M_факт+C_факт | Shell M_факт+C_факт  |\n");
    printf("|     | Д.Кнута                                           |                      |                      |\n");
    printf("---------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < 5; i++){
        generateSteps(steps, &stepCount, sizes[i]);
        PrintTableRow(sizes[i], steps, stepCount, results[i]);
    }
    printf("\n");


    printf("     Исследование трудоемкости метода Шелла\n");
    printf("-------------------------------------------------------------------------------------------------------------\n");
    printf("| N   | h1 … hm по формуле              | Shell          | h1 … hm по формуле              | Shell          |\n");
    printf("|     | Д.Кнута                         | M_факт+C_факт  | по формуле Чиперфилда           | M_факт+C_факт  |\n");
    printf("-------------------------------------------------------------------------------------------------------------\n");

    int results2[5][2];
    for (int i = 0; i < 5; i++){
        RunTests1(sizes[i], results2[i], &stepCount, &stepCount2);
    }
    for (int i = 0; i < 5; i++) {
        generateSteps(steps, &stepCount, sizes[i]);
        generateChipperfieldSequence(steps2, &stepCount2, sizes[i]);
        PrintTableRow2(sizes[i], steps, stepCount, steps2, stepCount2, results2[i]);
    }
    printf("\n");

    int select_results[5], bubble_results[5], shaker_results[5], insert_results[5], shell_results[5];
    for (int i = 0; i < 5; i++) {
        RunTests2(sizes[i], &select_results[i], &bubble_results[i], &shaker_results[i], &insert_results[i], &shell_results[i], &stepCount);
    }

    PlotTableGnuplot1(sizes, insert_results, shell_results, 5);
    PlotTableGnuplot2(sizes, results2, 5);

    PlotGraph(sizes, select_results, bubble_results, shaker_results, insert_results, shell_results, 5);
}