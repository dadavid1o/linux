#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/time.h>
#include <cstring>

void do_command(char** argv) {
    struct timeval start, end;
    gettimeofday(&start, nullptr);
    
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // В дочернем процессе
        execvp(argv[0], argv);
        // Если execvp возвращает, значит была ошибка
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        // В родительском процессе
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        
        gettimeofday(&end, nullptr);

        double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;

        if (WIFEXITED(status)) {
            std::cout << "Command completed with " 
                      << WEXITSTATUS(status) 
                      << " exit code and took " 
                      << elapsed 
                      << " seconds." << std::endl;
        } else if (WIFSIGNALED(status)) {
            std::cout << "Command terminated by signal " 
                      << WTERMSIG(status) 
                      << " and took " 
                      << elapsed 
                      << " seconds." << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <command> [args...]" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Формируем массив аргументов для передачи в do_command
    char** args = new char*[argc];
    for (int i = 1; i < argc; ++i) {
        args[i - 1] = argv[i];
    }
    args[argc - 1] = nullptr; // Завершающий ноль для execvp

    do_command(args);

    delete[] args;
    return EXIT_SUCCESS;
}
