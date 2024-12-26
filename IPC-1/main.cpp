#include <iostream>
#include <csignal>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

// Signal handler
void signal_handler(int signum, siginfo_t *info, void *context) {
    if (signum == SIGUSR1) {
   
        pid_t sender_pid = info->si_pid;
        uid_t sender_uid = info->si_uid;

 
        struct passwd *pwd = getpwuid(sender_uid);
        const char *user_name = pwd ? pwd->pw_name : "unknown";

         std::cout << "ti poluchil signal?!" << std::endl;
        std::cout << "Sender PID: " << sender_pid << std::endl;
        std::cout << "Sender UID: " << sender_uid << std::endl; 
    }
}

int main() {
    // Print PID
    pid_t pid = getpid();
    std::cout << "Process PID: " << pid << "\n";

    struct sigaction action = {};
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = signal_handler;
    sigaction(SIGUSR1, &action, nullptr);

    // ожидаем сигнал
    while (true) {
        sleep(10);
    }

    return 0;
}

