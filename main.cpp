#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256
#define FILENAME_SIZE 100

char *result_copy = NULL;

class Program {
public:
    char *input;

    Program() {
        input = (char *)malloc(BUFFER_SIZE * sizeof(char));
        if (input == NULL) {
            printf("Помилка виділення пам'яті.\n");
            exit(1);
        }
        input[0] = '\0';
    }

    ~Program() {
        free(input);
        if (result_copy != NULL) {
            free(result_copy);
        }
    }

    void add_text();
    void start_newline();
    void search_substring();
    void insert_text();
    void save_to_file(char *input);
    void free_input();
    void delete_command(int line, int index, int len);
    void copy(int line, int index, int len);
    void cut(int line, int index, int len);
};

void Program::add_text() {
    printf("Enter the text: ");
    fflush(stdout);

    char text[BUFFER_SIZE];

    if (fgets(text, BUFFER_SIZE, stdin) == NULL) {
        printf("Помилка читання рядка.\n");
        return;
    }
    strncat(input, text, BUFFER_SIZE - strlen(input) - 1);
}

void Program::start_newline() {
    strncat(input, "\n", BUFFER_SIZE - strlen(input) - 1);
    printf("New line is started\n");
}

void Program::search_substring() {
    char substring[BUFFER_SIZE];
    printf("Enter the substring to search: ");
    fgets(substring, BUFFER_SIZE, stdin);



    int line = 0;
    int column = 0;
    int num_matches = 0 ;



    int o = 0 ;
    int p = 0;

    int l = 0 ;

    while (l- 1 != strlen(input) ) {
        if (input[p] == '\n') {
            line++;
            column = 0;
        }else {
            column++;
        }

        if (substring[o] != input[p]) {
            p++;
            column++;
            num_matches = 0;
            o = 0;
        }
        else {
            p++;
            o++;
            num_matches++;
        }

        if (num_matches == strlen(substring)) {
            printf(" ( %d,%d )", line, column );
            num_matches = 0;
            o = 0;
        }
        l++;
    }

}

void Program::insert_text() {

    char substring[BUFFER_SIZE];
    int line, index;
    printf("Enter the line and index: ");


    scanf("%d %d", &line, &index);
    getchar();

    // після scanf, коли користувач натискає клавішу "Enter", символ нового рядка (\n) залишається у буфері вводу.
    //  getchar видаляє символ нововго рядка з буфету

    printf("Enter text to insert: ");
    fgets(substring, BUFFER_SIZE, stdin);


    if (substring[strlen(substring) - 1] == '\n') {
        substring[strlen(substring)- 1] = '\0';

    }

    int current_line = 0;
    int current_index = 0;


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

            char result[BUFFER_SIZE];
            char input_00[BUFFER_SIZE];
            char input_01[BUFFER_SIZE];

            snprintf(input_00, position - input + 1 , "%s", input);
            input_00[position - input] = '\0';


            snprintf(input_01, sizeof(input_01), "%s", position);



            snprintf(result, sizeof(result), "%s%s%s", input_00, substring , input_01);

            printf("Result :  %s", result);


            snprintf(input, BUFFER_SIZE, "%s", result);



        }
    }


}

void Program::save_to_file(char *input) {
    char filename[FILENAME_SIZE];
    printf("Введіть назву файлу для збереження: ");
    if ( fgets     (filename,   sizeof(filename),    stdin) != NULL) {
        filename[strlen(filename) - 1] = '\0';
    }

    FILE* file = fopen64(filename, "w+x");

    if (file == NULL) {
        printf("Помилка відкриття файлу для запису.\n");
        return;
    }
    else {
        fprintf(file, "%s", input);  // for save input in fille
        //Функція fprintf () записує вихідні дані в потік, визначений fp , під керуванням специфікатора формату

        fclose(file);
        printf("Текст було записано у файл успішно.\n");
    }

}


void Program::free_input() {
    free(input);
}

void Program::delete_command(int line, int index, int len) {
    int current_line = 0, current_index = 0;
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

        char result[BUFFER_SIZE];
        strncpy(result, input, position - input);
        result[position - input] = '\0';

        strncat(result, position + len, BUFFER_SIZE);
        strncpy(input, result, BUFFER_SIZE);

    }
}

void Program::copy( int line, int index, int len) {
        int current_line = 0, current_index = 0;
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

            if (result_copy != NULL) {
                free(result_copy);
            }

            result_copy = (char *)malloc((len + 1) * sizeof(char));
            if (result_copy == NULL) {
                printf("Memory allocation error.\n");
                return;
            }

            strncpy(result_copy, position, len); // copy by len
            result_copy[len] = '\0';

            printf("Copied text: %s\n", result_copy);
        } else {
            printf("Line %d not found.\n", line);
        }
}

    void Program::cut(int line, int index, int len) {
        copy(line, index, len);
        if (result_copy != NULL) {
            delete_command(line, index, len);
        }
        printf("Copied text: %s\n", result_copy);

    }

    int main() {
        Program program;
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
            printf("8. Delete\n");
            printf("11. Cut\n");
            printf("13. Copy\n");
            printf("0. Stop\n");
            printf("==============================\n");
            printf("Enter your choice: ");
            char choice_str[3];
            fgets(choice_str, sizeof(choice_str), stdin);

            choice = atoi(choice_str); // Перетворення строкового вводу в число

            switch (choice) {
                case 1:
                    program.add_text();
                break;
                case 2:
                    program.start_newline();
                break;
                case 3:
                    program.save_to_file(program.input);
                break;
                case 4:

                    break;
                case 5:
                    printf("Поточний текст: %s\n", program.input);
                break;
                case 6:
                    program.insert_text();
                break;
                case 7:
                    program.search_substring();
                break;
                case 8: {
                    int line, index, len;
                    printf("Enter the line, index, and length: ");
                    scanf("%d %d %d", &line, &index, &len);
                    getchar();
                    program.delete_command(line, index, len);
                    break;
                }
                case 11: {
                    int line, index, len;
                    printf("Enter the line, index, and length: ");
                    scanf("%d %d %d", &line, &index, &len);
                    getchar();
                    program.cut(line, index, len);
                    break;
                }
                case 13: {
                    int line, index, len;
                    printf("Enter the line, index, and length: ");
                    scanf("%d %d %d", &line, &index, &len);
                    getchar();
                    program.copy(line, index, len);
                    break;
                }
                case 0:
                    program.free_input();
                break;
                default:
                    printf("Неправильний вибір.\n");
                break;
            }
        } while (choice != 0);


    }
