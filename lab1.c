#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int main(){
    int n;

    printf("Введите длину массива: ");
    scanf("%d", &n);

    int A[n];

    FillInc(A, n);
    printf("Массив с возрастающими числами:\n");
    PrintMas(A, n);
    printf("Контрольная сумма: %lld\n", CheckSum(A, n));

    FillDec(A, n);
    printf("Массив с убывающими числами:\n");
    PrintMas(A, n);
    printf("Контрольная сумма: %lld\n", CheckSum(A, n));

    FillRand(A, n);
    printf("Массив с рандомными числами:\n");
    PrintMas(A, n);

    printf("Контрольная сумма: %lld\n", CheckSum(A, n));
    printf("Количество серий: %d\n", RunNumber(A, n));

    FillInc(A, n);
    int inc_ser = RunNumber(A, n);
    printf("Количество серий в возрастающем массиве: %d\n", inc_ser);

    FillDec(A, n);
    int dec_ser = RunNumber(A, n);
    printf("Количество серий в убывающем массиве: %d\n", dec_ser);

}