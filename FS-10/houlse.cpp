#include <iostream>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Открытие файла для записи (если файл не существует, он будет создан)
    int fd = open("source_file", O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    // Запись первых 5 байт данных
    char buf1[] = "Hello";
    if (write(fd, buf1, 5) != 5) {
        std::cerr << "Error writing data" << std::endl;
        close(fd);
        return 1;
    }

    // Создание дыры размером 100000 байт
    if (lseek(fd, 100000, SEEK_END) == -1) {
        std::cerr << "Error creating hole" << std::endl;
        close(fd);
        return 1;
    }

    // Запись последних 5 байт данных
    char buf2[] = "World";
    if (write(fd, buf2, 5) != 5) {
        std::cerr << "Error writing data" << std::endl;
        close(fd);
        return 1;
    }

    // Закрытие файла
    close(fd);
    return 0;
}

