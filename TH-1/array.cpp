#include <iostream>
#include <pthread.h>
#include <vector>
#include <sys/time.h>  

std::vector<int> array;
pthread_mutex_t mutex;
int N = 0; int M = 0;
long long globalSum = 0;
int chunksize = 0; // размер блока обрабатываемого одним потоком.
void* threadSum(void* arg) 
{
  int index = *(int*)arg; // приведение в тип инт
  int start = index * chunksize;
  int end = (index == M - 1) ? N : start + chunksize; 

  long long localSum = 0;
  for(size_t i = start; i < end; ++i) 
  { 
    localSum += array[i];
  }   
  pthread_mutex_lock(&mutex);
  globalSum += localSum;
  pthread_mutex_unlock(&mutex);

  return NULL;
}

long long SumSum(const std::vector<int>& arr) 
{
  long long sum = 0;
  for(int num : arr)
  {
    sum += num;
  } 
  return sum;
}

double getTimeDifference(const timeval& start, const timeval& end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
}

int main(int argc, char* argv[])
{
  if (argc < 3) 
  {
      std::cerr << "Usage: " << argv[0] << " N M" << std::endl;
      return 1;
  }

  N = std::atoi(argv[1]);
  M = std::atoi(argv[2]);
  chunksize = N / M;

  array.resize(N);
  std::srand(std::time(NULL));
    for (int i = 0; i < N; ++i) {
        array[i] = std::rand() % 100 + 1;
    }

    // Последовательное суммирование
    timeval start, end;
    gettimeofday(&start, nullptr);
    long long sumWithoutThreads = SumSum(array);
    gettimeofday(&end, nullptr);
    double elapsedWithoutThreads = getTimeDifference(start, end);
    std::cout << "Time spent without threads: " << elapsedWithoutThreads << " seconds" << std::endl;

    // Параллельное суммирование с использованием мьютекса
    pthread_mutex_init(&mutex, nullptr); // Инициализация мьютекса

    std::vector<pthread_t> threads(M);
    std::vector<int> indices(M);

    gettimeofday(&start, nullptr);
    for (int i = 0; i < M; ++i) {
        indices[i] = i;
        pthread_create(&threads[i], nullptr, threadSum, &indices[i]);
    }

    for (int i = 0; i < M; ++i) {
        pthread_join(threads[i], nullptr);
    }
    gettimeofday(&end, nullptr);

    double elapsedWithThreads = getTimeDifference(start, end);
    std::cout << "Time spent with " << M << " threads: " << elapsedWithThreads << " seconds" << std::endl;
    std::cout << "Sum with threads: " << globalSum << std::endl;

    pthread_mutex_destroy(&mutex); // Уничтожение мьютекса

  return 0;
}