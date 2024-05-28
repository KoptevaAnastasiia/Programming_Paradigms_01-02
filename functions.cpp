void add_text(char *input, size_t bufferSize);
void start_newline(char *input);
void file_name_save_and_save_text(char *input);
void save_to_file(const char *filename, const char *text);
void load_from_file(char *input, size_t bufferSize);



void add_text(char *input, size_t bufferSize) {
    printf("Введіть рядок: ");
    char buffer[BUFFER_SIZE];
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {  // Читання рядка з введення
        printf("Помилка читання рядка.\n");
        return;
    }
    strncat(input, buffer, bufferSize - strlen(input) - 1);  // Додаємо новий рядок в кінці введеного тексту
}

void start_newline(char *input) {
    char *newline_position = strchr(input, '\n');  // Знаходження символу нового рядка
    // Якщо знайдено символ нового рядка
    if (newline_position != NULL) {
        *newline_position = '\0';  // Замінити символ нового рядка на нульовий символ
        printf("New line is started\n");
    }

    // Перевірка останнього символу в рядку (до '\0')
    if (input[strlen(input) - 1] != '\0') {
        printf("\n");  // Додавання порожнього рядка, щоб створити абзац
    }




    }

void save_to_file(const char *filename, const char *text) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Помилка відкриття файлу для запису.\n");
        return;
    }
    fprintf(file, "%s", text);
    fclose(file);
    printf("Текст успішно збережено у файл.\n");
}

void file_name_save_and_save_text(char *input) {
    char filename[FILENAME_SIZE];

    // Введення назви файлу для збереження
    printf("Введіть назву файлу для збереження: ");
    if (scanf("%99s", filename) != 1) {
        printf("Помилка читання назви файлу.\n");
        return;
    }
    getchar();  // Споживання символу нового рядка, залишеного scanf

    // Збереження тексту у файл
    save_to_file(filename, input);
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
