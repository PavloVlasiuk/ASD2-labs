#include <stdio.h>

#define DEFAULT_VALUE 1

double recursiveReturn(double x, unsigned int n);

double recursiveDescent(double x, unsigned int n, double tempElem, double tempSum);

double recursiveCalculationOfSum(double x, unsigned int n);

double loopCalculation(double x, unsigned int n);

int main() {
    const unsigned int FLAG = 1;

    while (FLAG) {
        double result;
        double x;
        unsigned int number;
        unsigned int n;
        char answer;

        printf("Enter x from 1 to 2: ");
        scanf("%lf", &x);

        if (x <= 1 || x >= 2) {
            printf("You've typed x out of the permissible range\n");
            continue;
        }

        printf("Enter n: ");
        scanf("%d", &n);


        printf("Enter the number of the solution method: ");
        scanf("%d", &number);

        if (number == 1) {
            result = recursiveDescent(x, n, DEFAULT_VALUE, DEFAULT_VALUE);
        } else if (number == 2) {
            result = recursiveReturn(x, n);
        } else if (number == 3) {
            result = recursiveCalculationOfSum(x, n);
        } else if (number == 4) {
            result = loopCalculation(x, n);
        } else {
            printf("You've typed wrong number of the solution method\n");
            continue;
        }

        printf("Result = %lf\n", result);

        printf("Do you want to continue y/n: ");
        scanf(" %c", &answer);

        if (answer == 'y') continue;

        break;
    }

    return 0;
}

double recursiveReturn(double x, unsigned int n) {
    double sum = 1;

    if (n == 1) {
        return 1;
    } else {
        return sum - recursiveReturn(x, n - 1) * (2 * x / 3 - 1);
    }
}

double recursiveDescent(double x, unsigned int n, double tempElem, double tempSum) {
    if (n == 1) {
        return tempSum;
    } else {
        tempElem *= -(2 * x / 3 - 1);
        tempSum += tempElem;
        return recursiveDescent(x, n - 1, tempElem, tempSum);
    }
}

double recursiveCalculationOfElement(double x, unsigned int n, double tempElem) {
    if (n == 1) {
        return tempElem;
    } else {
        tempElem *= -(2 * x / 3 - 1);
        return recursiveCalculationOfElement(x, n - 1, tempElem);
    }
}

double recursiveCalculationOfSum(double x, unsigned int n) {
    if (n == 1) {
        return recursiveCalculationOfElement(x, DEFAULT_VALUE, DEFAULT_VALUE);
    } else {
        return recursiveCalculationOfSum(x, n - 1) + recursiveCalculationOfElement(x, n, DEFAULT_VALUE);
    }
}

double loopCalculation(double x, unsigned int n) {
    double sum = 1;
    double tempElement = 1;
    double valueOfElement;

    if (n == 1) {
        return sum;
    }
    for (int i = 2; i <= n; i++) {
        valueOfElement = -tempElement * (2 * x / 3 - 1);
        sum += valueOfElement;
        tempElement = valueOfElement;
    }

    return sum;
}
