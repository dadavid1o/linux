#include <iostream> // для работы с консольным вводом и выводом
#include <fstream>  // для работы с файловыми потоками
#include <string>   // для работы с объектами типа std::string
#include <unistd.h> // для системных вызовов POSIX, таких как dup2()
#include <fcntl.h>  // для операций с файловыми дескрипторами, таких как open()
#include <cerrno>   // для получения номера последней ошибки
#include <cstring>  // для работы со строками C, таких как strerror()

void initil(int argc, char **argv)
{
  if (argc != 2)
  {
    std::cerr << "usege:" << argv[0] << "<input-file>" << std::endl;
    exit(EXIT_FAILURE);
  }

  int fd = open(argv[1], O_RDONLY);
  if (fd == -1)
  {
    std::cerr << "ERROR ORIGIN FILE: " << strerror(errno) << std::endl;
    exit(EXIT_FAILURE);
  }

  if (dup2(fd, STDIN_FILENO) == -1)
  {
    std::cerr << "Error redirecting input: " << strerror(errno) << std::endl;
    close(fd);
    exit(EXIT_FAILURE); // программа завершилась с ошибкой.
  }
  close(fd);
}

int main(int argc, char **argv)
{

  initil(argc, argv);

  std::string input;
  std::cin >> input;

  std::string reversed(input.rbegin(), input.rend());

  std::cout << reversed << std::endl;

  return 0;

}