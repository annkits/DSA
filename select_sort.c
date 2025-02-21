#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N1 10
#define N2 100

//заполнение массива случайными числами
void FillRand(int A[], int n){
    srand(time(NULL));
    for (int i = 0; i < n; i++){
        A[i] = rand()%101;
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

//функция метода SelectSort + фактические сравнения и перестановки
void SelectSort(int A[], int n, int *c_fact, int *m_fact){
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
    printf("Обычный SelectSort:\n");
    PrintMas(A, n);
    printf("Количество сделанных сравнений: %d\n", *c_fact);
    printf("Количество сделанных пересылок: %d\n", *m_fact);
}

void GoodSelectSort(int A[], int n, int *c_fact, int *m_fact){
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
        if (j_min != i){
            int temp = A[i];
            (*m_fact)++;
            A[i] = A[j_min];
            (*m_fact)++;
            A[j_min] = temp;
            (*m_fact)++;
        }
    }
    printf("Улучшенный SelectSort:\n");
    PrintMas(A, n);
    printf("Количество сделанных сравнений: %d\n", *c_fact);
    printf("Количество сделанных пересылок: %d\n", *m_fact);
}

//расчёт теоретических сравнений
int CTheoretical(int n){
    int c_theoretical = ((int)(n * n - n) / 2);
    return c_theoretical;
}

//расчёт теоретических перестановок
int MTheoretical(int n){
    int m_theoretical = 3 * (n - 1);
    return m_theoretical;
}

//расчёт отношений факт. сравн. и перест. к теоретическим
void CMComparison(int c_fact, int m_fact, int *c_theoretical, int *m_theoretical){
    float c_diff = (float)c_fact / *c_theoretical;
    printf("Отношение фактического количества сравнений с теоретическим: %.3f\n", c_diff);
    float m_diff = (float)m_fact / *m_theoretical;
    printf("Отношение фактического количества пересылок с теоретическим: %.3f\n", m_diff);
}

//заполнение массива убывающими числами
void FillDec(int A[], int n){
    for (int i = 0; i < n; i++){
        A[i] = n - i;
    }
}

//заполнение массива возрастающими числами
void FillInc(int A[], int n){
    for (int i = 0; i < n; i++){
        A[i] = i + 1; 
    }
}

void Output(int A[], int n, int *c_theoretical, int *m_theoretical){
    int c_fact = 0;
    int m_fact = 0;

    PrintMas(A, n);
    printf("Контрольная сумма: %lld\n", CheckSum(A, n));
    printf("Количество серий: %d\n", RunNumber(A, n));
    printf("\n");

    int *copyA = malloc(n * sizeof(int));
    memcpy(copyA, A, n * sizeof(int));
    SelectSort(copyA, n, &c_fact, &m_fact);
    printf("Контрольная сумма: %lld\n", CheckSum(copyA, n));
    printf("Количество серий: %d\n", RunNumber(copyA, n));
    CMComparison(c_fact, m_fact, c_theoretical, m_theoretical);
    printf("\n");
    free(copyA);

    copyA = malloc(n * sizeof(int));
    memcpy(copyA, A, n * sizeof(int));
    GoodSelectSort(copyA, n, &c_fact, &m_fact);
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
    SelectSort(B, n, &c_fact, &m_fact);
    results[0] = c_fact + m_fact;
    
    memcpy(B, A, n * sizeof(int));
    GoodSelectSort(B, n, &c_fact, &m_fact);
    results[1] = c_fact + m_fact;

    FillRand(A, n);
    memcpy(B, A, n * sizeof(int));
    SelectSort(B, n, &c_fact, &m_fact);
    results[2] = c_fact + m_fact;

    memcpy(B, A, n * sizeof(int));
    GoodSelectSort(B, n, &c_fact, &m_fact);
    results[3] = c_fact + m_fact;

    FillInc(A, n);
    memcpy(B, A, n * sizeof(int));
    SelectSort(B, n, &c_fact, &m_fact);
    results[4] = c_fact + m_fact;

    memcpy(B, A, n * sizeof(int));
    GoodSelectSort(B, n, &c_fact, &m_fact);
    results[5] = c_fact + m_fact;
}

void PrintTableRow(int N, int M_C_teor, int *results) {
    printf("| %-3d | %-13d | %-8d | %-8d | %-8d | %-8d | %-8d | %-8d |\n",
           N, M_C_teor, results[0], results[2], results[4], results[1], results[3], results[5]);
}

int main(){
    int A[N1];
    int B[N2];

    int c1_theoretical = CTheoretical(N1);
    int c2_theoretical = CTheoretical(N2);

    int m1_theoretical = MTheoretical(N1);
    int m2_theoretical = MTheoretical(N2);

    printf("Теоретическое количество сравнений N = 10: %d\n", c1_theoretical);
    printf("Теоретическое количество сравнений N = 100: %d\n", c2_theoretical);

    printf("Теоретическое количество пересылок N = 10: %d\n", m1_theoretical);
    printf("Теоретическое количество пересылок N = 100: %d\n", m2_theoretical);

    printf("\n");

    FillRand(A, N1);
    printf("Массив случайных чисел:\n");
    Output(A, N1, &c1_theoretical, &m1_theoretical);

    FillRand(A, N2);
    printf("Массив случайных чисел:\n");
    Output(A, N2, &c2_theoretical, &m2_theoretical);

    FillDec(A, N1);
    printf("Массив убывающих чисел:\n");
    Output(A, N1, &c1_theoretical, &m2_theoretical);

    FillDec(A, N2);
    printf("Массив убывающих чисел:\n");
    Output(A, N2, &c1_theoretical, &m2_theoretical);

    FillInc(A, N1);
    printf("Массив возрастающих чисел:\n");
    Output(A, N1, &c1_theoretical, &m2_theoretical);

    FillInc(A, N2);
    printf("Массив возрастающих чисел:\n");
    Output(A, N2, &c1_theoretical, &m2_theoretical);

    printf("Вывод: не улучшенный метод SelectSort не зависит от исходной упорядоченности массива.\n");
    printf("Улучшенный метод влияет на количество перестановок - отсутствие фиктивных перестановок уменьшает их общее количество.\n");

    int results1[6], results2[6];

    RunTests(N1, results1);
    RunTests(N2, results2);

    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("| N   | M+C теоретич. | Исходный M_факт+C_факт         | Улучшенный M_факт+C_факт       |\n");
    printf("|     |               | Убыв.    | Случ.    | Возр.    | Убыв.    | Случ.    | Возр.    |\n");
    printf("-------------------------------------------------------------------------------------------------------\n");

    PrintTableRow(N1, CTheoretical(N1) + MTheoretical(N1), results1);
    PrintTableRow(N2, CTheoretical(N2) + MTheoretical(N2), results2);

}