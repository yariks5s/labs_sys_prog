#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include <unistd.h>

using namespace std;

// Функція Ейлера
long long eulerPhi(long long n)
{
    long long result = n;

    for (long long p = 2; p * p <= n; ++p)
    {
        if (n % p == 0)
        {
            while (n % p == 0) n /= p;
            result -= result / p;
        }
    }

    if (n > 1) result -= result / n;
    return result;
}

// Функція Мьобіуса
long long mebius(long long n)
{
    if (n == 1) return 1;
    long long primeFactors = 0;
    for (long long p = 2; p * p <= n; ++p)
    {
        if (n % p == 0) {
            if (n % (p * p) == 0) return 0;
            while (n % p == 0) n /= p;
            primeFactors++;
        }
    }
    if (n > 1) primeFactors++;
    return (primeFactors & 1) ? -1 : 1;
}

// Знаходження найбільшого спільного дільника
long long nsd(long long a, long long b)
{
    if (b == 0) return a;
    return nsd(b, a % b);
}

// Знаходження найменшого спільного кратного для двох чисел
long long nsk(long long a, long long b)
{
    return abs(a * b) / nsd(a, b);
}

// Знаходження найменшого спільного кратного для набору чисел
long long nskOfArray(const vector<long long>& arr)
{
    long long result = 1;
    for (long long num : arr) {
        result = nsk(result, num);
    }
    return result;
}

// Функція для обчислення факторіалу рекурсивно
unsigned long long factorial(unsigned long long n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

// Функція для обчислення суми ряду (приклад: сума з n елементів ряду 1/i)
long double calculateSeriesSum(long n) {
    long double sum = 0.0;
    for (int i = 1; i <= n; ++i) {
        sum += 1.0 / i;
    }
    return sum;
}

int main() {
    // Задаємо кількість елементів ряду
    long numElements = 1000000000;

    std::cout << "Calculating the sum of a series with " << numElements << " elements..." << std::endl;

    // Вимірюємо час виконання
    auto start = std::chrono::high_resolution_clock::now();

    // Викликаємо функцію обчислення суми ряду
    long double result = calculateSeriesSum(numElements);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Sum of the series: " << result << std::endl;
    std::cout << "Computation took " << duration.count() << " milliseconds." << std::endl;

    long long n = 15;
    cout << "Число для обчислення функцій Ейлера та Мьобіуса: 15" << endl;
    cout << "Функція Ейлера: " << eulerPhi(n) << endl;
    cout << "Функція Мьобіуса: " << mebius(n) << endl;

    cout << "Кількість чисел для знаходження НСК: 5" << endl;
    vector<long long> arr = {5,2,3,5,6};
    cout << "Введіть числа через пробіл: 5 2 3 5 6" << endl;
    cout << "Результат: " << nskOfArray(arr) << endl;

    cout << "Факторіал числа 20" << endl;
    unsigned long long number = 20;
    unsigned long long res = factorial(number);
    cout << res << endl;

    return 0;
}
