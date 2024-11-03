#include <iostream>   // Для вывода ошибок и результатов в консоль
#include <fcntl.h>    // Для системных вызовов open(), fcntl() и работы с файлами
#include <unistd.h>   // Для системных вызовов read(), write(), lseek(), close()
#include <sys/stat.h> // Для получения информации о файле через fstat()
#include <cstring>    // Для обработки строк и использования функций типа memset()

void printUsage()
{
    std::cerr << "Usage: ./copy <source-file> <destination-file>\n";
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printUsage();
        std::cerr << "ERROR: Few arguments" << std::endl;
        exit(1);
    }

    int srcFile = open(argv[1], O_RDONLY);
    if (srcFile == -1) {
        std::cerr << "ERROR: No such source file" << std::endl;
        exit(1);
    }

    int destFile = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (destFile == -1) {
        std::cerr << "ERROR: Cannot create destination file" << std::endl;
        close(srcFile);
        exit(1);
    }

    const size_t bufferSize = 4096;
    char buffer[bufferSize];
    ssize_t bytesRead;
    ssize_t totalBytes = 0;
    ssize_t dataBytes = 0;
    ssize_t holeBytes = 0;

    while ((bytesRead = read(srcFile, buffer, bufferSize)) > 0) {
        ssize_t bytesWritten = 0;
        size_t offset = 0;

        for (ssize_t i = 0; i < bytesRead; ++i) {
            if (buffer[i] == '\0') {
                // Записываем данные перед дырой, если такие есть
                if (offset < i) {
                    bytesWritten = write(destFile, buffer + offset, i - offset);
                    if (bytesWritten < 0) {
                        std::cerr << "ERROR: Writing to destination file failed" << std::endl;
                        close(srcFile);
                        close(destFile);
                        exit(1);
                    }
                    dataBytes += bytesWritten; // Увеличиваем счетчик данных
                    totalBytes += bytesWritten;
                }
                // Пропускаем 1 байт в целевом файле, создавая дыру
                lseek(destFile, 1, SEEK_CUR);
                holeBytes++;
                totalBytes++;
                offset = i + 1;
            }
        }

        // Записываем оставшиеся данные в буфере
        if (offset < bytesRead) {
            bytesWritten = write(destFile, buffer + offset, bytesRead - offset);
            if (bytesWritten < 0) {
                std::cerr << "ERROR: Writing to destination file failed" << std::endl;
                close(srcFile);
                close(destFile);
                exit(1);
            }
            dataBytes += bytesWritten;
            totalBytes += bytesWritten;
        }
    }

    if (bytesRead < 0) {
        std::cerr << "ERROR: Reading from source file failed" << std::endl;
    }

    close(srcFile);
    close(destFile);

    std::cout << "Successfully copied " << totalBytes << " bytes (data: " << dataBytes << ", hole: " << holeBytes << ").\n";
    return 0;
}
