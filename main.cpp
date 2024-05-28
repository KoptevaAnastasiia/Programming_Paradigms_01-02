#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256
#define FILENAME_SIZE 100  // Визначення константи

void add_text(char *input, size_t bufferSize);
void start_newline(char *input);
void file_name_save_and_save_text(char *input);
void save_to_file(const char *filename, const char *text);
void load_from_file(char *input, size_t bufferSize);






void add_text(char *input, size_t bufferSize) {
    printf("Введіть рядок: ");


    fflush(stdout);  // Примусово виводимо буфер printf
    char buffer[BUFFER_SIZE];


    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        // Читання рядка з введення
        printf("Помилка читання рядка.\n");
        return;
    }

        strncat(input, buffer, bufferSize - strlen(input) - 1);

    }




void start_newline(char *input) {
    printf("\n");
    printf("New line is started\n");

    }

// void save_to_file( ) {
//
// }

void file_name_save_and_save_text(char *input) {
    char filename[FILENAME_SIZE];
    printf("Введіть назву файлу для збереження: ");
    scanf("%99s", filename); // Читаємо назву файлу, враховуючи межу 99 символів
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Помилка відкриття файлу для запису.\n");

    }
    fprintf(file, "%s", input);


    fclose(file);

    // Повідомлення про успішний запис
    printf("Текст було записано у файл успішно.\n");


}

void load_from_file(char *input, size_t bufferSize) {
    char filename[FILENAME_SIZE];
    printf("Введіть назву файлу для завантаження: ");
    if (scanf("%99s", filename) != 1) {
        printf("Помилка читання назви файлу.\n");
        return;
    }
    getchar();  // Споживання символу нового рядка, залишеного scanf

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Помилка відкриття файлу для читання.\n");
        return;
    }

    input[0] = '\0';  // Очищення існуючого тексту
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        strncat(input, buffer, bufferSize - strlen(input) - 1);
    }

    fclose(file);
    printf("Текст успішно завантажено з файлу.\n");
}

int main() {
    char *input = (char *)malloc(BUFFER_SIZE * sizeof(char));
    if (input == NULL) {
        printf("Помилка виділення пам'яті.\n");
        return 1;
    }
    input[0] = '\0';  // Ініціалізація рядка як порожнього

    int choice;

    do {
        printf("\nChoose the command::\n");
        printf("Enter text to append: 1 \n");
        printf("New line is started: 2 \n");
        printf("Enter the file name for saving: 3 \n");
        printf("Enter the file name for loading: 4 \n");
        printf("Print the current text to console: 5 \n");
        printf("Введіть свій вибір: ");
        scanf("%d", &choice);

        getchar();  // Споживання символу нового рядка, залишеного scanf

        switch (choice) {
            case 1: {
                add_text(input, BUFFER_SIZE);
                break;
            }
            case 2: {
                start_newline(input);
                break;
            }
            case 3: {
                file_name_save_and_save_text(input);
                break ;
            }
            // case 4: {
            //     load_from_file(input,  );
            //     break ;
            // }
            case 5: {
                printf("Current text: %s\n", input);
                break;
            }









            default: {
                printf("Невірний вибір. Спробуйте ще раз.\n");
                break;
            }
        }
    } while (choice != 0);

    free(input);
    return 0;  // Завершення програми з кодом успішного виконання
}
