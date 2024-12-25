#include <iostream>
#include <vector>
#include <random>
#include <pthread.h>
#include <unistd.h>

std::vector<int> buffer;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;   // Условная переменная
bool dataReady = false; // Флаг готовности данных

// Генератор
std::vector<int> generateNumbers() {
    std::vector<int> numbers;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);
    for (int i = 0; i < 10; ++i) {
        numbers.push_back(dist(gen));
    }
    return numbers;
}

void* producer(void* arg) {
    while (true) {
        sleep(10); // спим

        std::vector<int> localBuffer = generateNumbers();

        // Критическая секция
        pthread_mutex_lock(&mtx);
        buffer = std::move(localBuffer);
        dataReady = true;
        pthread_cond_signal(&cv); 
        pthread_mutex_unlock(&mtx);
    }
    return nullptr;
}

void* consumer(void* arg) {
    while (true) {
        pthread_mutex_lock(&mtx);

        // Ждём
        while (!dataReady) {
            pthread_cond_wait(&cv, &mtx);
        }

        // Читаем
        std::cout << "Consumer received numbers: ";
        for (int num : buffer) {
            std::cout << num << " ";
        }
        std::cout << std::endl;

        dataReady = false; // Сбрасываем флаг
        pthread_mutex_unlock(&mtx);
    }
    return nullptr;
}

int main() {
    pthread_t producerThread, consumerThread;

    pthread_create(&producerThread, nullptr, producer, nullptr);
    pthread_create(&consumerThread, nullptr, consumer, nullptr);

 
    pthread_join(producerThread, nullptr);
    pthread_join(consumerThread, nullptr);

    // Освобождаем ресурсы
    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cv);

    return 0;
}
