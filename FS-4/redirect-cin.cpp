#include <iostream>
#include <fstream> 
#include <unistd.h> // Для dup2 и STDIN_FILENO
#include <fcntl.h>  // Для open
#include <cerrno>   // Для errno
#include <cstring>  // Для strerror

// функция инициализации перенаправления ввода
void initialize(int argc, char **argv)
{
  // проверяем количество аргументов, чтобы убедиться, что передан файл
  if (argc != 2)
  {
    // выводим сообщение об использовании программы
    std::cerr << "Usage: " << argv[0] << " <input-file>" << std::endl;
    exit(EXIT_FAILURE); // завершаем программу с ошибкой
  }

  // открываем файл для чтения с помощью системного вызова open
  int file_fd = open(argv[1], O_RDONLY); // открываем файл в режиме только для чтения
  if (file_fd == -1)
  {
    // если не удалось открыть файл, выводим сообщение об ошибке
    std::cerr << "Error opening file: " << strerror(errno) << std::endl;
    exit(EXIT_FAILURE); // завершаем программу с ошибкой
  }

  // перенаправляем стандартный ввод (STDIN_FILENO) на открытый файл
  if (dup2(file_fd, STDIN_FILENO) == -1)
  {
    // если dup2 завершился с ошибкой, выводим сообщение об ошибке
    std::cerr << "Error redirecting input: " << strerror(errno) << std::endl;
    close(file_fd);     // закрываем файловый дескриптор, если произошла ошибка
    exit(EXIT_FAILURE); // завершаем программу с ошибкой
  }

  // закрываем файловый дескриптор, так как он больше не нужен
  close(file_fd);
}

int main(int argc, char **argv)
{
  // инициализируем программу, перенаправляем ввод на файл
  initialize(argc, argv);

  // читаем строку из стандартного ввода (который теперь перенаправлен на файл)
  std::string input;
  std::cin >> input; // читаем строку из файла через std::cin

  // переворачиваем строку
  std::string reversed(input.rbegin(), input.rend());

  // выводим перевёрнутую строку в консоль
  std::cout << reversed << std::endl;

  return 0;
}
