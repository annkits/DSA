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

// Функция сравнения по сложному ключу (фамилия + имя)
int compareSubscribers(Subscriber* sub1, Subscriber* sub2) {
    int cmp = strcmp(sub1->surname, sub2->surname);
    if (cmp != 0) {
        return cmp * sortDirection;
    }
    return strcmp(sub1->name, sub2->name) * sortDirection;
}

// Функция сравнения по альтернативному ключу (возраст + фамилия)
int compareSubscribersAlt(Subscriber* sub1, Subscriber* sub2) {
    if (sub1->age != sub2->age) {
        return (sub1->age - sub2->age) * sortDirection;
    }
    return strcmp(sub1->surname, sub2->surname) * sortDirection;
}

// Сортировка вставками
void insertSort(Subscriber A[], int n, int* c_fact, int* m_fact, int (*compare)(Subscriber*, Subscriber*)) {
    *c_fact = 0;
    *m_fact = 0;

    for (int i = 1; i < n; ++i) {
        Subscriber t = A[i];
        (*m_fact)++;
        int j = i - 1;

        while (j >= 0) {
            (*c_fact)++;
            if (compare(&t, &A[j]) < 0) {
                A[j + 1] = A[j];
                (*m_fact)++;
                j = j - 1;
            } else break;
        }
        A[j + 1] = t;
        (*m_fact)++;
    }
}

// Функция вывода справочника
void printDirectory(Subscriber* directory, int size) {
    printf("\nТелефонный справочник:\n");
    printf("----------------------------------------\n");
    printf("| Фамилия | Имя      | Телефон     | Возраст |\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("| %-8s | %-8s   | %-11s | %7d |\n", 
               directory[i].surname, 
               directory[i].name, 
               directory[i].phone, 
               directory[i].age);
    }
    printf("----------------------------------------\n");
}

// Функция двоичного поиска по фамилии
void findAllBySurname(Subscriber* directory, int size, char* searchSurname) {
    int found = 0;
    int left = 0;
    int right = size - 1;
    int firstIndex = -1;
    
    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = strcmp(directory[mid].surname, searchSurname);
        
        if (cmp == 0) {
            firstIndex = mid;
            right = mid - 1;
        }
        else if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    
    if (firstIndex == -1) {
        printf("\nАбоненты с фамилией '%s' не найдены\n", searchSurname);
        return;
    }
    
    printf("\nНайденные абоненты с фамилией '%s':\n", searchSurname);
    printf("----------------------------------------\n");
    printf("| Фамилия | Имя      | Телефон     | Возраст |\n");
    printf("----------------------------------------\n");
    
    for (int i = firstIndex; i >= 0 && strcmp(directory[i].surname, searchSurname) == 0; i--) {
        printf("| %-7s | %-8s | %-11s | %7d |\n", 
               directory[i].surname, 
               directory[i].name, 
               directory[i].phone, 
               directory[i].age);
        found++;
    }
    
    for (int i = firstIndex + 1; i < size && strcmp(directory[i].surname, searchSurname) == 0; i++) {
        printf("| %-7s | %-8s | %-11s | %7d |\n", 
               directory[i].surname, 
               directory[i].name, 
               directory[i].phone, 
               directory[i].age);
        found++;
    }
    printf("----------------------------------------\n");
    printf("Найдено записей: %d\n", found);
}

int main() {
    Subscriber directory[] = {
        {"Иванов", "Петр", "+79123456789", 25},
        {"Петров", "Иван", "+79234567890", 30},
        {"Иванов", "Алексей", "+79345678901", 22},
        {"Сидоров", "Николай", "+79456789012", 28},
        {"Козлов", "Дмитрий", "+79567890123", 35}
    };
    int size = sizeof(directory) / sizeof(directory[0]);
    
    // Вывод исходного справочника
    printf("Исходный справочник:\n");
    printDirectory(directory, size);
    
    // Сортировка по фамилии и имени (по возрастанию)
    sortDirection = 1;
    insertSort(directory, size, &comparisons, &moves, compareSubscribers);
    printf("\nОтсортировано по фамилии и имени (по возрастанию):");
    printDirectory(directory, size);
    printf("Количество сравнений: %d, перемещений: %d\n", comparisons, moves);
    
    // Пример двоичного поиска
    // Ввод фамилии для поиска
    char searchSurname[20];
    printf("\nВведите фамилию для поиска: ");
    scanf("%19s", searchSurname); // Ограничение на длину ввода
    findAllBySurname(directory, size, searchSurname);
    
    // Сортировка по возрасту и фамилии (по убыванию)
    sortDirection = -1;
    insertSort(directory, size, &comparisons, &moves, compareSubscribersAlt);
    printf("\nОтсортировано по возрасту и фамилии (по убыванию):");
    printDirectory(directory, size);
    printf("Количество сравнений: %d, перемещений: %d\n", comparisons, moves);
    
    return 0;
}