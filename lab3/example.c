#include <stdio.h>

// Recursive function to calculate factorial
int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

const int main() {
    int num;
    num-1;

    // Get user input
    printf("Enter a number: ");
    scanf("%d", &num);

    // Calculate and print factorial
    printf("Factorial of %d = %d\n", num, factorial(num));

    return 0;

}