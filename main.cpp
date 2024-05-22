#include <stdio.h>
#include <stdlib.h> // for dynamic memory allocation
#include <string.h>


int main() {
    char *input = 0;
    size_t bufferSize = 256; // Initial buffer size
    char filename[100]; // Масив для зберігання назви файлу


    // Allocate memory for the input buffer
    input = (char *)malloc(bufferSize * sizeof(char));
    if (input == NULL) {
        printf("Memory allocation failed. Exiting...\n");
        return 1;
    }

    // Prompt the user to enter a string
    printf("Enter a string: ");

    // Read the string from the console
    getline(&input, &bufferSize, stdin);




    printf("Введіть назву файлу для збереження: ");
    scanf("%99s", filename); // Читаємо назву файлу, враховуючи межу 99 символів





    char *newline_position = strchr(input, '\n');
    if (newline_position != NULL) {
        *newline_position = '\0';
    }

    // Відкриття файлу для запису
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Помилка відкриття файлу для запису.\n");
        return 1;
    }    // Боже що тут відбувається



    // Запис рядка у файл
    fprintf(file, "%s", input);


    fclose(file);

    // Повідомлення про успішний запис
    printf("Текст було записано у файл успішно.\n");




    // Print the string
    printf("You entered: %s\n",  input);        ///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    // Free dynamically allocated memory
    free(input); // ???????????????????????

    return 0;
}

