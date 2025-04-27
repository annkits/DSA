#include <stdio.h>
#include <string.h>

// Структура записи телефонного справочника
typedef struct {
    char surname[20];    // Фамилия
    char name[20];       // Имя
    char phone[15];      // Номер телефона
    int age;            // Возраст
} Subscriber;

// Глобальные переменные для подсчета операций
int sortDirection = 1; // 1 - по возрастанию, -1 - по убыванию
int comparisons = 0;   // Счетчик сравнений
int moves = 0;         // Счетчик перемещений
int sortKey = 0;       // 0 - по фамилии и имени, 1 - по возрасту и фамилии

// Логическая функция less для сравнения двух абонентов
int less(Subscriber* x, Subscriber* y) {
    if (sortKey == 0) { // Сравнение по фамилии и имени
        int cmp = strcmp(x->surname, y->surname);
        if (cmp != 0) {
            return cmp < 0;
        }
        return strcmp(x->name, y->name) < 0;
    } else { // Сравнение по возрасту и фамилии
        if (x->age != y->age) {
            return x->age < y->age;
        }
        return strcmp(x->surname, y->surname) < 0;
    }
}

// Сортировка вставками с использованием функции less и индексного массива
void insertSort(Subscriber A[], int indices[], int n, int* c_fact, int* m_fact) {
    *c_fact = 0;
    *m_fact = 0;

    // Инициализация индексного массива
    for (int i = 0; i < n; i++) {
        indices[i] = i;
    }

    for (int i = 1; i < n; ++i) {
        Subscriber t = A[i];
        int t_index = indices[i];
        (*m_fact)++;
        int j = i - 1;

        while (j >= 0) {
            (*c_fact)++;
            if ((sortDirection == 1 && less(&t, &A[j])) || 
                (sortDirection == -1 && !less(&t, &A[j]) && less(&A[j], &t))) {
                A[j + 1] = A[j];
                indices[j + 1] = indices[j];
                (*m_fact)++;
                j = j - 1;
            } else break;
        }
        A[j + 1] = t;
        indices[j + 1] = t_index;
        (*m_fact)++;
    }
}

// Функция вывода справочника с индексами
void printDirectory(Subscriber* directory, int indices[], int size) {
    printf("\nТелефонный справочник:\n");
    printf("------------------------------------------------\n");
    printf("| Индекс | Фамилия | Имя      | Телефон     | Возраст |\n");
    printf("------------------------------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("| %6d | %-7s | %-8s | %-11s | %7d |\n", 
               indices[i],
               directory[i].surname, 
               directory[i].name, 
               directory[i].phone, 
               directory[i].age);
    }
    printf("------------------------------------------------\n");
}

// Функция поиска и вывода всех абонентов с заданной фамилией
void findAllBySurname(Subscriber* directory, int indices[], int size, char* searchSurname) {
    int found = 0;
    // Сначала находим первый элемент с помощью бинарного поиска
    int left = 0;
    int right = size - 1;
    int firstIndex = -1;
    
    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = strcmp(directory[mid].surname, searchSurname);
        
        if (cmp == 0) {
            firstIndex = mid;
            right = mid - 1; // Ищем самый левый элемент
        }
        else if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    
    if (firstIndex == -1) {
        printf("\nАбоненты с фамилией '%s' не найдены\n", searchSurname);
        return;
    }
    
    // Выводим все элементы с совпадающей фамилией
    printf("\nНайденные абоненты с фамилией '%s':\n", searchSurname);
    printf("------------------------------------------------\n");
    printf("| Индекс | Фамилия | Имя      | Телефон     | Возраст |\n");
    printf("------------------------------------------------\n");
    
    // Идем влево от найденного индекса
    for (int i = firstIndex; i >= 0 && strcmp(directory[i].surname, searchSurname) == 0; i--) {
        printf("| %6d | %-7s | %-8s | %-11s | %7d |\n", 
               indices[i],
               directory[i].surname, 
               directory[i].name, 
               directory[i].phone, 
               directory[i].age);
        found++;
    }
    
    // Идем вправо от найденного индекса
    for (int i = firstIndex + 1; i < size && strcmp(directory[i].surname, searchSurname) == 0; i++) {
        printf("| %6d | %-7s | %-8s | %-11s | %7d |\n", 
               indices[i],
               directory[i].surname, 
               directory[i].name, 
               directory[i].phone, 
               directory[i].age);
        found++;
    }
    printf("------------------------------------------------\n");
    printf("Найдено записей: %d\n", found);
}

int main() {
    Subscriber directory[] = {
        {"Иванов", "Петр", "+79123456789", 25},
        {"Петров", "Иван", "+79234567890", 30},
        {"Иванов", "Алексей", "+79345678901", 22},
        {"Сидоров", "Николай", "+79456789012", 28},
        {"Козлов", "Дмитрий", "+79567890123", 30}
    };
    int size = sizeof(directory) / sizeof(directory[0]);
    int indices[size]; // Индексный массив
    
    // Вывод исходного справочника
    for (int i = 0; i < size; i++) indices[i] = i; // Инициализация индексов
    printf("Исходный справочник:\n");
    printDirectory(directory, indices, size);
    
    // Сортировка по фамилии и имени (по возрастанию)
    sortDirection = 1;
    sortKey = 0;
    insertSort(directory, indices, size, &comparisons, &moves);
    printf("\nОтсортировано по фамилии и имени (по возрастанию):");
    printDirectory(directory, indices, size);
    printf("Количество сравнений: %d, перемещений: %d\n", comparisons, moves);
    
    // Ввод фамилии для поиска
    char searchSurname[20];
    printf("\nВведите фамилию для поиска: ");
    scanf("%19s", searchSurname);
    
    // Поиск и вывод всех совпадений
    findAllBySurname(directory, indices, size, searchSurname);
    
    // Сортировка по возрасту и фамилии (по убыванию)
    sortDirection = -1;
    sortKey = 1;
    insertSort(directory, indices, size, &comparisons, &moves);
    printf("\nОтсортировано по возрасту и фамилии (по убыванию):");
    printDirectory(directory, indices, size);
    printf("Количество сравнений: %d, перемещений: %d\n", comparisons, moves);
    
    return 0;
}