#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define FIRST_STROKA "first line\n"
#define ENTER "\n"
#define SECOND_STROKA "second line\n"

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    std::cerr << "ERROR, few arguments" << std::endl;
    exit(1);
  }

  int fd1 = open(argv[1], O_CREAT | O_WRONLY, 0644);
  if(fd1 == -1)
  {
    std::cerr << "ERROR, no such file" << std::endl;
    exit(1);
  }

  int fd2 = dup(fd1);
  if(fd2 == -1)
  {
    std::cerr << "ERROR, no such file deskriptor";
    close(fd1);
    exit(1);
  }

  if(write(fd1, FIRST_STROKA, 11) == -1)
  {
    std::cerr << "ERROR, сould not write to file descriptor fd1" << std::endl;
    close(fd1);
    close(fd2);
    exit(1);
  }

  if(write(fd1, ENTER, 1) == -1)
  {
    std::cerr << "ERROR, сould not write to file descriptor fd1" << std::endl;
    close(fd1);
    close(fd2);
    exit(1);
  }

  if(write(fd2, SECOND_STROKA, 12) == -1)
  {
    std::cerr << "ERROR, сould not write to file descriptor fd2" << std::endl;
    close(fd1);
    close(fd2);
    exit(1);
  }

  close(fd1);
  close(fd2);
  return 0;
}
