#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
// file_path - это строка, содержащая путь к файлу, который нужно удалить
void sec_dellete(const char *file_path)
{
  struct stat file_stat; // специальная структура, которая хранит информацию о файле
  // проверяем на существование файла
  if (stat(file_path, &file_stat) == -1)
  {
    perror("ошибка при проверки файла");
    exit(EXIT_FAILURE);
  }
  // Открываем файл для записи
  int fd = open(file_path, O_WRONLY);
  if (fd == -1)
  {
    perror("ошибка при открытии файла");
    exit(EXIT_FAILURE);
  }

  off_t size_file = file_stat.st_size; // file_stat.st_size поле структуры stat, которое хранит размер файла в байтах.

  char null_byte = '\0';
  for (off_t i = 0; i < size_file; ++i)
  { // Перезаписываем файл нулями
    if (write(fd, &null_byte, 1) != 1)
    { // Ошибка при записи
      {
        perror("ошибка при записи в файл");
        exit(EXIT_FAILURE);
      }
    }
  }

    close(fd);

    if (unlink(file_path) == -1)
    {
      perror("ошибка при удалении файла");
      exit(EXIT_FAILURE);
    }
    else
    {
      printf("Файл %s успешно удален", file_path);
    }
  }
  int main(int argc, char *argv[])
  {
    if (argc != 2)
    {
      fprintf(stderr, "error: %s\n", argv[0]);
      exit(EXIT_FAILURE);
    }
    sec_dellete(argv[1]);
    return 0;
  }