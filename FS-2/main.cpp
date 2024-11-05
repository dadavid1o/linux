#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
// argc - количество переданных аргументов программе, a argv - массив строк
// где argv[0] - имя программы, argv[1] - исходный файл, argv[2] - целевой файл
int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    perror("неправильное количество аргументов");
    return 1;
  }
  // открываем исходный файл
  int isx_fd = open(argv[1], O_RDONLY);
  if (isx_fd == -1)
  {
    perror("ошибка при открытии файла");
    return 1;
  }
  // создаем целевой файл
  int cel_fd = creat(argv[2], 0644); // права доступа rw-r--r-- =>0644
  if (cel_fd == -1)
  {
    perror("не удалось создать целевой файл");
    close(cel_fd);
    return 1;
  }

  char buffer[1024]; // массив символов для хранения данных при чтении
  size_t bytes_read; // Переменная для хранения количества прочитанных байт

  // Читаем содержимое исходного файла и записываем в целевой
  while ((bytes_read = read(isx_fd, buffer, 1024)) > 0) // Читаем данные из исходного файла в буфер

  {
    if (write(cel_fd, buffer, bytes_read) == -1) // Пытаемся записать данные из буфера в целевой файл
    {
      perror("ошибка при записи в целевой файл"); // Если не удалось, выводим сообщение об ошибке
      close(isx_fd);
      close(cel_fd);
      return 1; // Завершаем программу с кодом ошибки 1
    }
  }

  if (bytes_read == -1)
  {
    // Если произошла ошибка при чтении
    perror("Ошибка при чтении исходного файла"); // Выводим сообщение об ошибке
  }
  close(isx_fd);
  close(cel_fd);

  printf("файл успешно скопирован %s в %s\n", argv[1], argv[2]); // выводим сообщение об успешном копировании файла

  return 0;
}
