#include <stdio.h>  // Підключення стандартної бібліотеки вводу/виводу
#include <stdlib.h>  //  робота з динамічною пам'яттю та інших утиліт
#include <string.h>  // робота з рядками

#define BUFFER_SIZE 256  // Визначення константи для розміру буфера
#define FILENAME_SIZE 100  // Визначення константи для розміру масиву для назви файлу
// Буфер (buffer) в програмуванні – це область пам'яті, яка використовується для тимчасового зберігання даних, перш ніж ці дані будуть оброблені або передані іншим компонентам системи.


void add_text ();

void insert_text(char *input, size_t bufferSize, int line, int symbolIndex, const char *text);

void start_newline(char *input);

// void append_text(char *input, size_t bufferSize, const char *text);


void file_name(char *filename);






// Функція для вставки тексту в рядок за вказаною позицією
void insert_text(char *input, size_t bufferSize, int line, int symbolIndex, const char *text) {
    size_t input_len = strlen(input);
    size_t text_len = strlen(text);

    size_t index = 0;
    int current_line = 1;
    int i = 0;
    while (i < input_len && current_line < line) {
        if (input[i] == '\n') {
            current_line++;
        }
        i++;
    }

    index = i + symbolIndex;

    if (current_line < line || (current_line == line && symbolIndex > strlen(input))) {
        printf("Invalid line or symbol index.\n");
        return;
    }

    char *new_input = (char *)malloc((input_len + text_len + 1) * sizeof(char));
    if (new_input == NULL) {
        printf("Memory allocation error.\n");
        return;
    }

    strncpy(new_input, input, index);
    strcpy(new_input + index, text);
    strcpy(new_input + index + text_len, input + index);

    strncpy(input, new_input, bufferSize - 1);
    input[bufferSize - 1] = '\0';

    free(new_input);
}




// Функція для видалення символу нового рядка з кінця рядка
void start_newline(char *input) {
    char *newline_position = strchr(input, '\n');  // Знаходження символу нового рядка    // Функція strchr знаходиться в стандартній бібліотеці C (<string.h>) і використовується для пошуку першого входження символу в рядку
    if (newline_position != NULL) {
        *newline_position = '\0';  // Заміна символу нового рядка на нульовий символ
        printf("New line is started");
    }


}



void add_text() {
    char*  input;  // Оголошення змінної для зберігання введеного рядка
    size_t bufferSize = BUFFER_SIZE; // Початковий розмір буфера
    char FileName[FILENAME_SIZE]; // Масив для зберігання назви файлу

    // Виділення динамічної пам'яті для буфера введення
    input = (char* ) malloc(bufferSize * sizeof(char));                     // В C розмір char завжди дорівнює 1 байту, тому sizeof(char) дорівнює 1.
    if (input == NULL) {  // Перевірка на успішність виділення пам'яті
        printf("Помилка виділення пам'яті. Вихід...\n");
      //  return 1;
    }
    // Введення рядка користувачем
    printf("Введіть рядок: ");
    if (getline(&input, &bufferSize, stdin) == -1) {  // Читання рядка з введення         // stdin (скорочено від "standard input", стандартний вхідний потік) – це місце, звідки ваша програма зазвичай отримує введені дані. Зазвичай це означає введення з клавіатури.
        printf("Помилка читання рядка.\n");
        free(input);  // Звільнення пам'яті у випадку помилки
        //return 1;
    }
    // if (... == -1):
    // Перевірка, чи функція getline повернула -1.
    // Це означає, що сталася помилка при читанні або було досягнуто кінець файлу(EOF).




}




void file_name(char *filename) {
        // Введення назви файлу для збереження
        printf("Введіть назву файлу для збереження: ");
        if (scanf("%99s", filename) != 1) {
            printf("Помилка читання назви файлу.\n");
            // free(input);  // Звільнення пам'яті у випадку помилки
            // return 1;

    }



 //    // Введення назви файлу для збереження
 //    printf("Введіть назву файлу для збереження: ");
 //    if (scanf("%99s", filename) != 1) {
 // // Читання назви файлу з введення
 //        printf("Помилка читання назви файлу.\n");
 //        free(input);  // Звільнення пам'яті у випадку помилки
 //       // return 1;
 //    }
 //    // Форматна стрічка "%99s" вказує, що ми читаємо рядок (символи без пробілів) і обмежуємо його довжину до 99 символів, щоб уникнути переповнення буфера.



}




void save_file(const char *filename, const char *text);




void save_file(const char *filename, const char *text) {


}







int main() {
    char *input = (char *)malloc(BUFFER_SIZE * sizeof(char));
    if (input == NULL) {
        printf("Помилка виділення пам'яті.\n");
        return 1;
    }
    input[0] = '\0';  // Ініціалізація рядка як порожнього



    char filename[FILENAME_SIZE];
    int choice;




    do {
        printf("\nChoose the command::\n");
        printf("Enter text to append: 1 \n");
        printf("New line is started: 2 \n");
        printf("Enter the file name for saving: 3 \n");
        printf("Enter the file name for loading: 4 \n");
        printf("Print the current text to console 5 \n");

        // printf("6. Вставити текст за номером рядка і індексом символу\n");
        // printf("7. Пошук тексту\n");
        // printf("0. Вихід\n");


        printf("Введіть свій вибір: ");
        scanf("%d", &choice);

        getchar();  // Споживання символу нового рядка, залишеного scanf

        switch (choice) {
            case 1 : {
                add_text();
                break;
            }

            case 2: {
                start_newline(input);
                break;

            }

            case 3: {
                file_name(filename);
                break;
            }

            case 4: {
                // код для вибору опції 4
                break;
            }

            case 5: {
                // код для вибору опції 5
                break;
            }

        }
    } while (choice != 0);


    free(input);
    return 0;  // Завершення програми з кодом успішного виконання

}









//
// // Відкриття файлу для запису
// FILE* file = fopen(FileName, "w");    // Це оголошення змінної типу FILE *. FILE - це тип даних, який представляє файл у стандартній бібліотеці введення/виведення С. // "w" - це режим відкриття файлу. У цьому випадку "w" означає, що файл буде відкритий для запису. Якщо файл не існує, він буде створений. Якщо файл вже існує, його вміст буде знищено.
// if (file == NULL) {  // Перевірка на успішність відкриття файлу
//     printf("Помилка відкриття файлу для запису.\n");
//     free(input);  // Звільнення пам'яті у випадку помилки
//     return 1;    // Повернення значення 1 з функції main зазвичай використовується для позначення того, що програма завершилася з помилкою.
// }
//

//
//
// // Запис рядка у файл
// fprintf(file, "%s", input); // fprintf - це функція для форматованого запису у файл, яка дозволяє записати рядок у файл із заданим форматуванням.
// // "%s" - це форматна стрічка, яка вказує, що ми будемо записувати рядок.
// // input - це рядок, який ми хочемо записати у файл.
//
// // Закриття файлу   для вивільнення ресурсів     запис даних на диск        ізоляція файлів від іншик операцій (  шоб не було конфлуктів  )
// fclose(file);
// // Повідомлення про успішний запис
// printf("Текст було записано у файл успішно.\n");
// // Виведення введеного рядка
// printf("Ви ввели: %s\n", input);
//
//

