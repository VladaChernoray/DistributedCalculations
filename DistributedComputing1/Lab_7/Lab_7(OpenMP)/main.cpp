#include <iostream>
#include <omp.h>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

int main() {
    const int n = 100;
    double A[n][n];
    double B[n][n];
    double C[n][n];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            std::srand(unsigned(time(nullptr)));
            A[i][j] = 1;
            B[i][j] = rand()+i*j;
            C[i][j] = 0;
        }
    }

    auto start = high_resolution_clock::now();

    int line = -1;
    #pragma omp parallel num_threads(n) shared(A, B, C){
        int currLine = ++line;
        double res[n];
        double sum = 0;
        #pragma omp for
        for (int j = 0; j < n; j++) {
            sum = 0;
            for (int k = 0; k < n; k++) {
                sum += A[currLine][k] * B[k][j];
            }
            res[j] = sum;
        }

        for(int i = 0; i < n; i++){
            C[currLine][i] = res[i];
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time of execution: " << (double)duration.count() << "ms";
    return 0;
}

