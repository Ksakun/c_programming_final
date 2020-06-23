#include <stdio.h>
#include <math.h>

int even(int *x) {
	
	printf("Even number list ~ n : \n");
	for (int i = 1; i <= *x; i++) {
		if (i % 2 == 0) {
			printf("%d ", i);
		}
	}
	return 0;
}

int odd(int *x) {
	printf("Odd number list ~n : \n");
	for (int i = 1; i <= *x; i++) {
		if (i % 2 != 0) {
			printf("%d ", i);
		}
	}
	return 0;
}

int prime(int *x) {
	int flag = 0;
	for (int i = 2; i < sqrt(*x); i++) {
		if (*x % i == 0) {
			flag = 1;
			break;
		}
	}
	if (flag) printf("%d is not prime number.", *x);
	else printf("%d is prime number.", *x);
	return 0;
}

int between_prime(int *x, int *y) {
	int i, j;
	printf("Prime number between %d and %d : ", *x, *y);
	for (i = *x; i <= *y; i++) {
		for (j = 2; j < i; j++) {
			if (i % j == 0)
				break;
		}
		if (i == j)
			printf("%d ", i);
	}
	return 0;
}

int factorial(int *x) {
	int sum =1 ;
	for (int i = 1; i <= *x; i++) {
		sum *= i;
	}
	printf("%d! = %d \n", *x, sum);
	return 0;
}

int between_fact(int *x, int *y) {
	int sum = 1;
	for (int i = *x; i <= *y; i++) {
		for (int j = 1; j <= i; j++) {
			sum *= j;
		}
		printf("%d! = %d\n", i, sum);
		sum = 1;
	}
	return 0;
}

int fibonacci(int *x) {
	int first = 0, second = 1,  tmp;
	for (int i = 0; i <= *x; i++) {
		printf("fibonacci %d = %d\n", i, first);
		tmp = first;
		first = second;
		second = tmp + second;
	}
	return 0;
}

int series_sum(int *x, int *y) {
	int sum = 0, index = 1;
	for (int i = 1; i <= *y; i += 2) {
		if (index % 2 == 0)
			sum -= pow(*x, i);
		else
			sum += pow(*x, i);

		index++;
	}
	printf("Series'x sum is %d", sum);
	return 0;
}


int main() {

	int n, m;
	int c;
	while (1) {
		printf("\n-----------------------------------------------------------------------------------\n");
		printf("1: Display a list of even numbers.\n");
		printf("2: Display a list of odd numbers.\n");
		printf("3: For a given number n check if n  is a prime number.\n");
		printf("4: Display a list of prime numbers between numbers n and m.\n");
		printf("5: Display a factorial of a given number n.\n");
		printf("6: Find factorial of all numbers between numbers n and m.\n");
		printf("7: Generate the Fibonacci sequence up to a number n.\n");
		printf("8: Find the sum of the series [ x - x^3 + x^5 - ...]\n");
		printf("9 : Exit program\n");
		printf("\n-----------------------------------------------------------------------------------\n");
		printf("Select  What to do??  ");
		scanf_s("%d", &c);
			switch (c) {
			case 1:
				printf("Enter number n: ");
				scanf_s("%d", &n);
				even(&n);
				break;
			case 2:
				printf("Enter number n: ");
				scanf_s("%d", &n);
				odd(&n);
				break;
			case 3:
				printf("Enter number n: ");
				scanf_s("%d", &n);
				prime(&n);
				break;
			case 4:
				printf("Enter number n & m : ");
				scanf_s("%d %d", &n, &m);
				between_prime(&n, &m);
				break;
			case 5:
				printf("Enter number n: ");
				scanf_s("%d", &n);
				factorial(&n);
				break;
			case 6:
				printf("Enter number n & m : ");
				scanf_s("%d %d", &n, &m);
				between_fact(&n, &m);
				break;
			case 7:
				printf("Enter number n: ");
				scanf_s("%d", &n);
				fibonacci(&n);
				break;
			case 8:
				printf("Enter number n & m : ");
				scanf_s("%d %d", &n, &m);
				series_sum(&n,&m);
				break;
			case 9:
				return 0;
			}
	}
}