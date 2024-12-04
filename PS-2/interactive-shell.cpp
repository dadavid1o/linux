#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void executeCommand(const std::vector<std::string>& args, bool silent) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("Ошибка при вызове fork");
        return;
    }

    if (pid == 0) { // Дочерний процесс
        // Добавляем текущий каталог в PATH
        std::string currentDir = getcwd(nullptr, 0);
        std::string path = getenv("PATH");
        setenv("PATH", (currentDir + ":" + path).c_str(), 1);

        // Если команда silent, перенаправляем вывод в файл
        if (silent) {
            std::string logFile = std::to_string(getpid()) + ".log";
            int fd = open(logFile.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd != -1) {
                dup2(fd, STDOUT_FILENO);
                dup2(fd, STDERR_FILENO);
                close(fd);
            } else {
                perror("Ошибка при открытии файла");
                exit(1);
            }
        }

        // Преобразуем аргументы в формат для execvp
        std::vector<char*> cargs;
        for (const std::string& arg : args) {
            cargs.push_back(const_cast<char*>(arg.c_str()));
        }
        cargs.push_back(nullptr);

        // Выполняем команду
        execvp(cargs[0], cargs.data());
        perror("Ошибка при выполнении команды");
        exit(1);
    } else { // Родительский процесс
        waitpid(pid, nullptr, 0); // Ждём завершения дочернего процесса
    }
}

int main() {
    std::string input;

    while (true) {
        std::cout << "> "; // Приглашение для ввода
        std::getline(std::cin, input);

        if (input == "exit") { // Выход из оболочки
            break;
        }

        if (input.empty()) { // Игнорируем пустой ввод
            continue;
        }

        // Разделяем строку на аргументы
        std::vector<std::string> args;
        bool silent = false;
        size_t pos = 0;
        if (input.find("silent ") == 0) {
            silent = true;
            pos = 7; // Пропускаем "silent "
        }
        while ((pos = input.find(' ', pos)) != std::string::npos) {
            size_t nextPos = input.find(' ', pos + 1);
            args.push_back(input.substr(pos, nextPos - pos));
            pos = nextPos;
        }

        executeCommand(args, silent); // Выполняем команду
    }

    return 0;
}

