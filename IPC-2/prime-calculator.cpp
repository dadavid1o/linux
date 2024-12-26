#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cstring>

int findPrimeN(int n) {
    if (n <= 0) return -1;
    int count = 0;
    int chislo = 1;
    while (count < n) {
        ++chislo;
        bool prime = true;
        for (int i = 2; i * i <= chislo; ++i) {
            if (chislo % i == 0) {
                prime = false;
                break;
            }
        }
        if (prime) ++count;
    }
    return chislo;
}

int main() {
    int pipePervi[2], pipeVtoroi[2];

    if (pipe(pipePervi) == -1 || pipe(pipeVtoroi) == -1) {
        std::cerr << "ERROR Pipe creation failed." << std::endl;
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "ERROR Fork failed." << std::endl;
        return 1;
    }

    if (pid == 0) { 
        close(pipePervi[1]); 
        close(pipeVtoroi[0]);

        while (true) {
            int fd;
            if (read(pipePervi[0], &fd, sizeof(fd)) <= 0) {
                break;
            }

            std::cout << "Child Calculating " << fd << std::endl;
            int result = findPrimeN(fd);

            if (write(pipeVtoroi[1], &result, sizeof(result)) == -1) {
                std::cerr << "Child Error sending result " << std::endl;
                break;
            }
            std::cout << "Child Sending calculation result of prime (" << fd << ")" <<  std::endl;
        }

        close(pipePervi[0]);
        close(pipeVtoroi[1]);
    } else { 
        close(pipePervi[0]);  
        close(pipeVtoroi[1]); 

        while (true) {
            std::cout << "Parent Please enter the number: ";
            std::string input;
            std::getline(std::cin, input);

            if (input == "exit") {
                break;
            }

            int fd;
            try {
                fd = std::stoi(input);
            } catch (...) {
                std::cerr << "Parent Invalid input. Please enter an integer." << std::endl;
                continue;
            }

            std::cout << "Parent Sending " << fd  << std::endl;
            if (write(pipeVtoroi[1], &fd, sizeof(fd)) == -1) {
                std::cerr << "Parent Error sending data to child." << std::endl;
                break;
            }

            std::cout << "Parent Waiting" << std::endl;
            int result;
            if (read(pipePervi[0], &result, sizeof(result)) <= 0) {
                std::cerr << "Parent Error receiving data from child." << std::endl;
                break;
            }

            std::cout << "Parent Received calculation result of prime(" << fd << ") = " << result << "..." << std::endl;
        }

        close(pipeVtoroi[1]);
        close(pipePervi[0]);
    }

    return 0;
}
