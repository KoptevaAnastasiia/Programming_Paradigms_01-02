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
 void insert_text(char *input, const char *text_to_insert, int line, int index);

void add_text(char *input, size_t bufferSize) {
    printf("Введіть рядок: ");
    fflush(stdout);  // Примусово виводимо буфер printf
    char buffer[BUFFER_SIZE];
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        printf("Помилка читання рядка.\n");
        return;
    }
    strncat(input, buffer, bufferSize - strlen(input) - 1);  // Додаємо новий рядок до існуючого тексту
}

void start_newline(char *input) {
    printf("\n");
    printf("New line is started\n");
}

void file_name_save_and_save_text(char *input) {
    char filename[FILENAME_SIZE];
    printf("Введіть назву файлу для збереження: ");
    scanf("%99s", filename);
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Помилка відкриття файлу для запису.\n");
        return;
    }
    fprintf(file, "%s", input);
    fclose(file);
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

    input[0] = '\0';
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        strncat(input, buffer, bufferSize - strlen(input) - 1);
    }

    fclose(file);
    printf("Текст успішно завантажено з файлу.\n");
}


void insert_text(char *input, const char *text_to_insert, int line, int index) {
    int current_line = 0;
    int current_index = 0;    // дл я відстеження позиції

    int input_len = strlen(input);
    int insert_len = strlen(text_to_insert);
    char *position = input;



     while (current_line < line && *position != '\0') {
        if (*position == '\n') {
            current_line++;
        }
        position++;
    }

     if (current_line == line) {
        while (current_index < index && *position != '\n' && *position != '\0') {
            position++;
            current_index++;
        }
    }



    memmove(position + insert_len, position, input_len - (position - input) + 1);


     memcpy(position, text_to_insert, insert_len); // вставка

}

int main() {
    char *input = (char *)malloc(BUFFER_SIZE * sizeof(char));
    if (input == NULL) {
        printf("Помилка виділення пам'яті.\n");
        return 1;
    }
    input[0] = '\0';

    int choice;

    do {
        printf("\nChoose the command:\n");
        printf("1. Enter text to append\n");
        printf("2. Start new line\n");
        printf("3. Enter the file name for saving\n");
        printf("4. Enter the file name for loading\n");
        printf("5. Print the current text to console\n");
        printf("6. Implement substring insertion mechanism\n");
        printf("7. Implement substring search mechanism\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        getchar();

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
                break;
            }
            // case 4: {
            //     load_from_file(input, BUFFER_SIZE);
            //     break;
            // }
            case 5: {
                printf("Current text: %s\n", input);
                break;
            }
            case 6: {
                char text_to_insert[BUFFER_SIZE];
                int line, index;


                printf("Enter the line and index: ");
                scanf("%d %d", &line, &index);

                getchar();


                printf("Enter text to insert: ");
                fgets(text_to_insert, BUFFER_SIZE, stdin);   



                text_to_insert[strcspn(text_to_insert, "\n")] = '\0';  // Видалення символу нового рядка ('\n') з кінця введеного тексту. strcspn повертає індекс першого входження '\n'.

                insert_text(input, text_to_insert, line, index);
                break;
            }
            case 7: {
                break;
            }
            default: {
                printf(" error.\n");
                break;
            }
        }
    } while (choice != 0);

    free(input);
    return 0;
}
