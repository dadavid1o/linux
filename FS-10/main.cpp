#include <iostream>     // Для вывода ошибок и результатов в консоль
#include <fcntl.h>      // Для системных вызовов open(), fcntl() и работы с файлами
#include <unistd.h>     // Для системных вызовов read(), write(), lseek(), close()
#include <sys/stat.h>   // Для получения информации о файле через fstat()
#include <cstring>      // Для обработки строк и использования функций типа memset()

void copyFileHoles(const char* srcpath, const char* destpath)
{
  int srcFd = open(srcpath, O_WRONLY);
  if(srcFd < 0)
  {
    std::cerr << "Error: Cannot open source file";
    std::cout << std::endl;
    exit(EXIT_FAILURE);
  }

  int destFd = open(destpath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if(destFd < 0)
  {
    std::cerr << "Error: Cannot open source file";
    std::cout << std::endl;
    close(srcFd);
    close(destFd);
    exit(EXIT_FAILURE);
  }

  struct stat statbuf;
  if(fstat(srcFd, &statbuf) != 0) 
  {
    std::cerr << "Error: Cannot get file status.\n";
    close(srcFd);
    close(destFd);
    exit(EXIT_FAILURE);
  }

//   off_t — это тип данных, используемый для представления размеров файлов и смещений в них. Это стандартный тип для работы с размерами больших файлов.

// totalBytes — переменная, которая будет хранить общее количество байт, прочитанных из файла.

// totalDataBytes — количество байт реальных данных (не дыр).

// totalHoleBytes — количество байт, которые были дырами (нули).

// buffer[BUFFER_SIZE] — это буфер, в который будут считываться данные из исходного файла. Его размер равен BUFFER_SIZE, то есть 4096 байт.

// bytesRead — переменная для хранения результата системного вызова read. Она будет показывать, сколько байт было прочитано за один вызов.

  off_t totalBytes = 0, totalDataBytes = 0;

}





int main(int argc, char* argv[])
{

}
