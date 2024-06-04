#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256
#define FILENAME_SIZE 100

void add_text(char *input, size_t bufferSize);
void start_newline(char *input);
void file_name_save_and_save_text(char *input);
void load_from_file(char *input, size_t bufferSize);
void search_substring(char *input);
void insert_text(char *input );
void delete_file();




void add_text(char *input, size_t bufferSize) {
    printf("Enter the text : ");
    fflush(stdout);   // оч буфету обміну

    char text[BUFFER_SIZE];

    if (fgets(text, BUFFER_SIZE, stdin) == NULL) {
         printf("Помилка читання рядка.\n");
        return;
    }
    strncat(input, text, bufferSize - strlen(input) - 1);  // Додаємо новий рядок до існуючого тексту
}
void start_newline(char *input) {
    strncat(input, "\n", BUFFER_SIZE - strlen(input) - 1);
    printf("New line is started\n");
}
void file_name_save_and_save_text(char *input) {
    char filename[FILENAME_SIZE]; // масив символів який буде містити назву файлу
    printf("Введіть назву файлу для збереження: ");




    // scanf("%99s", filename);   // функція fgets() не читає певну частину вхідних даних, оскільки функція scanf() залишає символ нового рядка в буфері
                                 // Функція scanf() зазвичай вважається небезпечною для обробки рядків; безпечніше використовувати fgets() для отримання рядка введення, а потім використовувати sscanf() для обробки введення.





    //                 buf            n                    fp
    if ( fgets     (filename,   sizeof(filename),    stdin) != NULL) {
        filename[strlen(filename) - 1] = '\0';
    }


    FILE *file = fopen64(filename, "w+x");  // 64 for big filles  and add +x

    if (file == NULL) {
        printf("Помилка відкриття файлу для запису.\n");
        return;
    }
    else {

        fprintf(file, "%s", input);  // for save input in fille

        //Функція fprintf () записує вихідні дані в потік, визначений fp , під керуванням специфікатора формату
        // %s тому що стрінг


        fclose(file);   // звільняє ресурси
        printf("Текст було записано у файл успішно.\n");
    }

}








void load_from_file(char *input, size_t bufferSize) {
    char filename[FILENAME_SIZE];

    printf("Enter the file name for loading: ");
    if (scanf("%99s", filename) != 1) {
        printf("Error reading file name.\n");
        return;
    }

    getchar();


    FILE *file = fopen(filename, "r");  // mayabe r++
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    input[0] = '\0';

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) { ///
        strncat(input, buffer, bufferSize - strlen(input) - 1);
    }

    fclose(file);
    printf("Text has been loaded successfully.\n");
}







void search_substring(char *input) {
    char substring[BUFFER_SIZE];
    printf("Enter the substring to search: ");
    fgets(substring, BUFFER_SIZE, stdin);

   // substring[strcspn(substring, "\n")] = '\0';  // Видалення символу нового рядка
// що це таке


    int i = 0;
    for(i ; substring[i] != '/0' ; i++) {
        if (substring[i] == '\n') {
            substring[i] = '\0';
            break;
        }
    }

    int line = 0;
    int column = 0;
    int num_matches = 0 ;



    int o = 0 ;
    int p = 0;


    while (p != strlen(input)) {
        if (input[p] == '\n') {
            line++;
            column = 0;
            p++;
            continue;
        }

        if (substring[o] != input[p] ){
            p++;
            column++;
            num_matches = 0;
            o = 0;
        }
        else{
            p++;
            o++;

            num_matches++;
        }

        if (num_matches == strlen(substring)) {
            printf( "%d , %d", line, column);
            num_matches = 0;
            o = 0 ;
        }
    }


    }






void insert_text(char *input) {

    char substring[BUFFER_SIZE];
    int line, index;

    printf("Enter the line and index: ");
    scanf("%d %d", &line, &index);

    getchar();                 // видалення символу нового рядка для коректного зчитування


    printf("Enter text to insert: ");
    fgets(substring, BUFFER_SIZE, stdin);



    int current_line = 0;
    int current_index = 0;

    int input_len = strlen(input);
    int insert_len = strlen(substring);
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
    memmove(input  , substring,  strlen(substring) +1 + strlen(input));



}


void delete_file() {
    char filename[FILENAME_SIZE];
    printf("Enter the file name to delete: ");
    if (scanf("%99s", filename) != 1) {
        printf("Error reading file name.\n");
        return;
    }
    getchar();

    if (remove(filename) == 0) {
        printf("File deleted successfully.\n");
    } else {
        printf("Error deleting file.\n");
    }
}









int main() {
    char *input = (char *)
    malloc(BUFFER_SIZE * sizeof(char));

    if (input == NULL) {
        printf("Помилка виділення пам'яті.\n");
        return 1;
    }

    input[0] = '\0';

    int choice;

    do {
        printf("\n==============================\n");
        printf(" Choose the command:\n");
        printf(" \n");
        printf("1. Enter text to append\n");
        printf("2. Start new line\n");
        printf("3. Enter the file name for saving\n");
        printf("4. Enter the file name for loading\n");
        printf("5. Print the current text to console\n");
        printf("6. Insert substring \n");
        printf("7. Position search  \n");
        printf("8. Delete file\n");
        printf("==============================\n");
        printf("Enter your choice: ");
        char choice_str[3];


        fgets(choice_str, sizeof(choice_str), stdin);


        if (  choice_str[1] != '\n') {
            printf("Invalid choice(.\n");
            break;

        }

        choice = choice_str[0] - '0';  // нуль віднімаємо щоб прирівняти до числа

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
            case 4: {

                load_from_file(input, BUFFER_SIZE);
                break;
            }
            case 5: {

                printf("Current text: %s\n", input);
                break;
            }

            case 6: {

                insert_text(input );
                break;
            }
            case 7: {

                search_substring(input);
                break;
            }
            case 8 : {

                delete_file();
                break ;
            }
            default: {

                break;
            }
        }
    } while (choice != 0);

    free(input);
    return 0;
}
