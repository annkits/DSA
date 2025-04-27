#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функция для генерации отсортированного массива
int* generateSortedArray(int size) {
    int* arr = (int*)malloc(size * sizeof(int));
    arr[0] = rand() % 100;
    for (int i = 1; i < size; i++) {
        arr[i] = arr[i-1] + (rand() % 10) + 1; // Гарантируем возрастающий массив
    }
    return arr;
}

// Первая версия бинарного поиска (BSsearchAll I)
int binarySearchAll1(int* arr, int size, int target, int* comparisons) {
    int left = 0, right = size - 1;
    *comparisons = 0;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        (*comparisons)++;
        if (arr[mid] == target) {
            return mid;
        }
        (*comparisons)++;
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

// Вторая версия бинарного поиска (BSsearchAll II)
int binarySearchAll2(int* arr, int size, int target, int* comparisons) {
    int left = 0, right = size - 1;
    *comparisons = 0;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        (*comparisons)++;
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    (*comparisons)++;
    if (arr[right] == target) {
        return right;
    }
    return -1;
}

void plotTableGnuplot(int* sizes, double* results1, double* results2, int count, const char* title, int window) {
    char command[50];
    sprintf(command, "gnuplot -persistent");
    FILE* gp = popen(command, "w");
    if (gp == NULL) {
        printf("Ошибка при запуске Gnuplot для окна %d!\n", window);
        return;
    }

    fprintf(gp, "set terminal wxt %d size 400,400\n", window);
    fprintf(gp, "set title '%s'\n", title);
    fprintf(gp, "unset key\n");
    fprintf(gp, "unset border\n");
    fprintf(gp, "unset tics\n");
    fprintf(gp, "set xrange [0:3]\n");
    fprintf(gp, "set yrange [%d:-1]\n", count);

    // Заголовки
    fprintf(gp, "set label 'N' at 0.5,-0.5 center\n");
    fprintf(gp, "set label 'C_в I' at 1.5,-0.5 center\n");
    fprintf(gp, "set label 'C_в II' at 2.5,-0.5 center\n");

    // Данные в ячейках
    for (int i = 0; i < count; i++) {
        double y = i + 0.5;
        fprintf(gp, "set label '%d' at 0.5,%f center\n", sizes[i], y);
        fprintf(gp, "set label '%.2f' at 1.5,%f center\n", results1[i], y);
        fprintf(gp, "set label '%.2f' at 2.5,%f center\n", results2[i], y);
    }

    // Линии таблицы
    for (int i = 0; i <= count; i++) {
        fprintf(gp, "set arrow from 0,%d to 3,%d nohead lt 1 lw 1\n", i, i);
    }
    for (int j = 0; j <= 3; j++) {
        fprintf(gp, "set arrow from %d,0 to %d,%d nohead lt 1 lw 1\n", j, j, count);
    }

    fprintf(gp, "plot NaN\n");
    pclose(gp);
}

int main() {
    srand(time(NULL));
    int sizes[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    int num_sizes = 10;
    int num_trials = 1000;
    
    double avg_comparisons1[10], avg_comparisons2[10];
    double avg_all_comparisons1[10], avg_all_comparisons2[10];
    
    for (int s = 0; s < num_sizes; s++) {
        int size = sizes[s];
        avg_comparisons1[s] = 0;
        avg_comparisons2[s] = 0;
        avg_all_comparisons1[s] = 0;
        avg_all_comparisons2[s] = 0;
        
        for (int trial = 0; trial < num_trials; trial++) {
            int* arr = generateSortedArray(size);
            int target = arr[rand() % size];
            
            int comparisons1, comparisons2;
            binarySearchAll1(arr, size, target, &comparisons1);
            binarySearchAll2(arr, size, target, &comparisons2);
            
            avg_comparisons1[s] += comparisons1;
            avg_comparisons2[s] += comparisons2;
            
            int total_comparisons1 = 0, total_comparisons2 = 0;
            for (int i = 0; i < size; i++) {
                int comp1, comp2;
                binarySearchAll1(arr, size, arr[i], &comp1);
                binarySearchAll2(arr, size, arr[i], &comp2);
                total_comparisons1 += comp1;
                total_comparisons2 += comp2;
            }
            
            avg_all_comparisons1[s] += (double)total_comparisons1 / size;
            avg_all_comparisons2[s] += (double)total_comparisons2 / size;
            
            free(arr);
        }
        
        avg_comparisons1[s] /= num_trials;
        avg_comparisons2[s] /= num_trials;
        avg_all_comparisons1[s] /= num_trials;
        avg_all_comparisons2[s] /= num_trials;
    }
    
    // // Создаем временный файл для данных графика
    // FILE* temp_data1 = fopen("temp_data1.dat", "w");
    // if (temp_data1 == NULL) {
    //     printf("Ошибка при создании temp_data1.dat\n");
    //     return 1;
    // }
    // for (int s = 0; s < num_sizes; s++) {
    //     fprintf(temp_data1, "%d %f %f\n", sizes[s], avg_comparisons1[s], avg_comparisons2[s]);
    // }
    // fclose(temp_data1);
    
    // // Создаем скрипт для графика (окно 0)
    // FILE* gp_graph = fopen("plot_graph.gp", "w");
    // if (gp_graph == NULL) {
    //     printf("Ошибка при создании plot_graph.gp\n");
    //     remove("temp_data1.dat");
    //     return 1;
    // }
    // fprintf(gp_graph, "set terminal wxt 0 size 600,400\n");
    // fprintf(gp_graph, "set title 'Трудоемкость поиска одного элемента'\n");
    // fprintf(gp_graph, "set xlabel 'Размер массива'\n");
    // fprintf(gp_graph, "set ylabel 'Среднее число сравнений'\n");
    // fprintf(gp_graph, "set key bottom right\n");
    // fprintf(gp_graph, "plot 'temp_data1.dat' using 1:2 with linespoints title 'BSsearchAll I', \
    //       'temp_data1.dat' using 1:3 with linespoints title 'BSsearchAll II'\n");
    // fclose(gp_graph);
    
    // // Создаем скрипт для первой таблицы (окно 1)
    // FILE* gp_table1 = fopen("plot_table1.gp", "w");
    // if (gp_table1 == NULL) {
    //     printf("Ошибка при создании plot_table1.gp\n");
    //     remove("temp_data1.dat");
    //     remove("plot_graph.gp");
    //     return 1;
    // }
    // fprintf(gp_table1, "set terminal wxt 1 size 400,400\n");
    // fprintf(gp_table1, "unset key\n");
    // fprintf(gp_table1, "unset border\n");
    // fprintf(gp_table1, "unset tics\n");
    // fprintf(gp_table1, "set xrange [0:3]\n");
    // fprintf(gp_table1, "set yrange [%d:-1]\n", num_sizes);
    // fprintf(gp_table1, "set title 'Трудоемкость поиска одного элемента'\n");
    
    // fprintf(gp_table1, "set label 'N' at 0.5,-0.5 center\n");
    // fprintf(gp_table1, "set label 'C_в I' at 1.5,-0.5 center\n");
    // fprintf(gp_table1, "set label 'C_в II' at 2.5,-0.5 center\n");
    
    // for (int i = 0; i < num_sizes; i++) {
    //     double y = i + 0.5;
    //     fprintf(gp_table1, "set label '%d' at 0.5,%f center\n", sizes[i], y);
    //     fprintf(gp_table1, "set label '%.2f' at 1.5,%f center\n", avg_comparisons1[i], y);
    //     fprintf(gp_table1, "set label '%.2f' at 2.5,%f center\n", avg_comparisons2[i], y);
    // }
    
    // for (int i = 0; i <= num_sizes; i++) {
    //     fprintf(gp_table1, "set arrow from 0,%d to 3,%d nohead lt 1 lw 1\n", i, i);
    // }
    // for (int j = 0; j <= 3; j++) {
    //     fprintf(gp_table1, "set arrow from %d,0 to %d,%d nohead lt 1 lw 1\n", j, j, num_sizes);
    // }
    // fprintf(gp_table1, "plot NaN\n");
    // fclose(gp_table1);
    
    // // Создаем скрипт для второй таблицы (окно 2)
    // FILE* gp_table2 = fopen("plot_table2.gp", "w");
    // if (gp_table2 == NULL) {
    //     printf("Ошибка при создании plot_table2.gp\n");
    //     remove("temp_data1.dat");
    //     remove("plot_graph.gp");
    //     remove("plot_table1.gp");
    //     return 1;
    // }
    // fprintf(gp_table2, "set terminal wxt 2 size 400,400\n");
    // fprintf(gp_table2, "unset key\n");
    // fprintf(gp_table2, "unset border\n");
    // fprintf(gp_table2, "unset tics\n");
    // fprintf(gp_table2, "set xrange [0:3]\n");
    // fprintf(gp_table2, "set yrange [%d:-1]\n", num_sizes);
    // fprintf(gp_table2, "set title 'Трудоемкость поиска всех элементов'\n");
    
    // fprintf(gp_table2, "set label 'N' at 0.5,-0.5 center\n");
    // fprintf(gp_table2, "set label 'C_в I' at 1.5,-0.5 center\n");
    // fprintf(gp_table2, "set label 'C_в II' at 2.5,-0.5 center\n");
    
    // for (int i = 0; i < num_sizes; i++) {
    //     double y = i + 0.5;
    //     fprintf(gp_table2, "set label '%d' at 0.5,%f center\n", sizes[i], y);
    //     fprintf(gp_table2, "set label '%.2f' at 1.5,%f center\n", avg_all_comparisons1[i], y);
    //     fprintf(gp_table2, "set label '%.2f' at 2.5,%f center\n", avg_all_comparisons2[i], y);
    // }
    
    // for (int i = 0; i <= num_sizes; i++) {
    //     fprintf(gp_table2, "set arrow from 0,%d to 3,%d nohead lt 1 lw 1\n", i, i);
    // }
    // for (int j = 0; j <= 3; j++) {
    //     fprintf(gp_table2, "set arrow from %d,0 to %d,%d nohead lt 1 lw 1\n", j, j, num_sizes);
    // }
    // fprintf(gp_table2, "plot NaN\n");
    // fclose(gp_table2);
    
    // // Запускаем gnuplot для каждого окна в фоновом режиме
    // int ret1 = system("gnuplot -persistent plot_graph.gp &");
    // if (ret1 != 0) {
    //     printf("Ошибка при запуске gnuplot для графика\n");
    // }
    
    // int ret2 = system("gnuplot -persistent plot_table1.gp &");
    // if (ret2 != 0) {
    //     printf("Ошибка при запуске gnuplot для первой таблицы\n");
    // }
    
    // int ret3 = system("gnuplot -persistent plot_table2.gp &");
    // if (ret3 != 0) {
    //     printf("Ошибка при запуске gnuplot для второй таблицы\n");
    // }
    
    // // Удаляем временные файлы
    // remove("temp_data1.dat");
    // remove("plot_graph.gp");
    // remove("plot_table1.gp");
    // remove("plot_table2.gp");

    // Вывод графика (оставляем как есть)
    FILE* temp_data1 = fopen("temp_data1.dat", "w");
    if (temp_data1 == NULL) {
        printf("Ошибка при создании temp_data1.dat\n");
        return 1;
    }
    for (int s = 0; s < num_sizes; s++) {
        fprintf(temp_data1, "%d %f %f\n", sizes[s], avg_comparisons1[s], avg_comparisons2[s]);
    }
    fclose(temp_data1);

    FILE* gp_graph = fopen("plot_graph.gp", "w");
    if (gp_graph == NULL) {
        printf("Ошибка при создании plot_graph.gp\n");
        remove("temp_data1.dat");
        return 1;
    }
    fprintf(gp_graph, "set terminal wxt 0 size 600,400\n");
    fprintf(gp_graph, "set title 'Трудоемкость поиска одного элемента'\n");
    fprintf(gp_graph, "set xlabel 'Размер массива'\n");
    fprintf(gp_graph, "set ylabel 'Среднее число сравнений'\n");
    fprintf(gp_graph, "set key bottom right\n");
    fprintf(gp_graph, "plot 'temp_data1.dat' using 1:2 with linespoints title 'BSsearchAll I', \
          'temp_data1.dat' using 1:3 with linespoints title 'BSsearchAll II'\n");
    fclose(gp_graph);
    
    // Запуск графика
    int ret1 = system("gnuplot -persistent plot_graph.gp &");
    if (ret1 != 0) {
        printf("Ошибка при запуске gnuplot для графика\n");
    }

    // Вывод таблиц с помощью новой функции
    plotTableGnuplot(sizes, avg_comparisons1, avg_comparisons2, num_sizes, 
                    "Трудоемкость поиска одного элемента", 1);
    plotTableGnuplot(sizes, avg_all_comparisons1, avg_all_comparisons2, num_sizes, 
                    "Трудоемкость поиска всех элементов", 2);

    // Удаление временных файлов
    remove("temp_data1.dat");
    remove("plot_graph.gp");

    printf("\nПрограмма завершена.\n");

    return 0;
}