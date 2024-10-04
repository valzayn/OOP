#include <iostream>
#include <thread>
#include <chrono>
#include <numeric>
#include <vector>


std::vector<int> arr(1000000);
std::vector<int> arr1(8);
int summ = 0;

void randomFill(std::vector<int> &arr) {
    for (int i = 0; i < 1000000; i++) {
        arr[i] = rand() % 4;
    }
}


void mult(int start, int end) {
    for (int i = start; i < end; i++) {
        arr[i] = arr[i] * 2;
    }
}

void sum(int start, int end, int j) {
    summ = 0;
    for (int i = start; i < end; i++) {
        summ += arr[i];
    }
    arr1[j] = summ;
}


int main()
{
    randomFill(arr);
    int start = 0;
    int end = 8;
    int step = 8;

    double time;

    auto start_ = std::chrono::high_resolution_clock::now();
    sum(0, 1000000, 0);
    summ = arr1[0];
    auto end_ = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_ - start_;
    time = duration.count();
    std::cout << "posled: " << time << " | result: " << summ << "\n";


    std::thread f1(sum, 0, 125000, 0);
    std::thread f2(sum, 125000, 250000, 1);
    std::thread f3(sum, 250000, 375000, 2);
    std::thread f4(sum, 375000, 500000, 3);
    std::thread f5(sum, 500000, 625000, 4);
    std::thread f6(sum, 625000, 750000, 5);
    std::thread f7(sum, 750000, 875000, 6);
    std::thread f8(sum, 875000, 1000000, 7);
    auto start1 = std::chrono::high_resolution_clock::now();
    f1.join();
    f2.join();
    f3.join();
    f4.join();
    f5.join();
    f6.join();
    f7.join();
    f8.join();
    summ = std::accumulate(arr1.begin(), arr1.end(), 0);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end1 - start1;
    time = duration1.count();
    std::cout << "parall " << time << "\n";
    arr.clear();
}