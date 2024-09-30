#include <fcntl.h>    // Для функции open() и флагов (например, O_RDONLY, O_CREAT)
#include <unistd.h>   // Для системных вызовов read(), close()
#include <stdio.h>    // Для стандартных функций ввода-вывода (например, printf(), perror())
#include <stdlib.h>   // Для функций управления процессом (например, exit())

int main(int argc, char* argv[])
{
	if(argc != 2)
{
	fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
	return 1;
}
// int fd => хранит файловый дескриптор
	int fd = open(argv[1], O_RDONLY);
	if(fd == -1)
{
// выводим ошибку если не получилось отрыть файл
	perror("ошибка при открытии файла");
	return 1;
}
	char buffer[1024];
	size_t bytes_read;
//     читаем данные из файла, используя файловый дескриптор fd и из буфера мы вычитаем 1 байт для того что бы выделить для /0
	while((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
{
	buffer[bytes_read] = '\0'; // 
	printf("%s", buffer);
}
	if(bytes_read == -1)
{
	perror("ошибка при чтения файла");
	close(fd);
	return 1;
}
	close(fd);
	return 0;
} 
