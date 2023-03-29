#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

int prime(long x);
int palindrome(int x);
int *primegen(int x);
int m(int a, int b, int c);
int factors(int x, int *primes);

void pe1(void)
{
	int sum = 0;
	for (int i = 1; i < 1000; i++)
		sum += (!(i % 3) || !(i % 5)) * i;
	printf("%i\n", sum);
}

void pe2(void)
{
	int arr[] = {1,2};
	int sum = 2;
	while (arr[1] < 4000000)
	{
		int temp = arr[1];
		arr[1] += arr[0];
		arr[0] = temp;
		sum += arr[1] * !(arr[1] & 1);
	}
	printf("%i\n", sum);
}

void pe3(void)
{
	long x = 600851475143;
	long ans;
	for (long i = 3; i * i <= x; i += 2)
		if (!(x % i))
			if (prime(i))
				ans = i;
	printf("%li\n", ans);
}

void pe4(void)
{
	int highest = 0;
	for (int i = 100; i < 1000; i++)
		for (int j = i; j < 1000; j++)
		{
			int x = i * j;
			if (palindrome(x))
				if (x > highest)
					highest = x;
		}
	printf("%i\n", highest);
}

void pe5(void)
{
	// using intersection of prime factors
	int primes[] = {2,3,5,7,11,13,17,19};
	int highest[] = {0,0,0,0,0,0,0,0};
	
	for (int i = 1; i <= 20; i++)
		for (int j = 0; j < 8; j++)
		{
			int x = i;
			int count = 0;
			while ((x % primes[j] == 0) && (x != 0))
			{
				x /= primes[j];
				count++;
			}
			if (count > highest[j])
				highest[j] = count;
		}
	
	int result = 1;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < highest[i]; j++)
			result *= primes[i];
	printf("%i\n", result);
}

void pe6(void)
{
	// sum of x squared = n(n+1)/2 = n^4/4 + n^3/2 + n^2/4
	// sum of x^2 = n(n+1)(2n+1)/6

	printf("%i\n", 25000000 + (999900/6) - 2500);
}

void pe7(void)
{
	int *primes = primegen(200000);
	printf("%i\n", primes[10000]);
	free(primes);
}

int pe8(void)
{
	char buffer[1000];
	FILE *in = fopen("digits.txt", "r");
	if (in == NULL)
		return 0;
	
	long highest = 0;
	fscanf(in, "%s", buffer);
	for (int i = 0; i < 988; i++)
	{
		long product = 1;
		for (int j = i; j < i + 13; j++)
			product *= buffer[j] - '0';
		if (product > highest)
			highest = product;
	}
	printf("%li\n", highest);
	fclose(in);
	return 1;
}

void pe9(void)
{
	int a = 3;
	int b = 4;
	int c = 5;
	// using primative triples and doing 1000 mod sum.
	m(a,b,c);
}

void pe10(void)
{
	int *primes = primegen(2000000);
	int *temp = primes;
	long sum = 0;
	while (*primes)
		sum += *primes++;
	printf("%li\n", sum);
	free(temp);
}

int pe11(void)
{
	FILE *in = fopen("grid.txt", "r");
    if (in == NULL)
        return 0;
	char buffer[2];
	int arr[20][20];
    int highest;
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
		{
			fscanf(in, "%s", buffer);
			arr[i][j] = atoi(buffer);
		}
	
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 17; j++)
		{
			int product = 1;
			int product1 = 1;
			for (int k = j; k < j + 4; k++)
			{
				product *= arr[i][k];
				product1 *= arr[k][i];
			}
			if (product > highest)
				highest = product;
			if (product1 > highest)
				highest = product1;
		}
	
	for (int i = 0; i < 17; i++)
		for (int k = 0; k < 17; k++)
		{
			int product = 1;
			int product1 = 1;
			for (int j = 0; j < 4; j++)
			{
				product *= arr[i+j][k+j];
				product1 *= arr[19-i-j][k+j];
			}
			if (product > highest)
				highest = product;
			if (product1 > highest)
				highest = product1;
		}
		
	printf("%i\n", highest);
	fclose(in);
    return 1;
}

void pe12(void)
{
    int count = 2;
    int triangle = 1;
    int *primes = primegen(10000);
    while (factors(triangle, primes) < 500)
        triangle += count++;
    printf("%i\n", triangle);
    free(primes);
}

void pe13(void)
{
    FILE *in = fopen("pe13.txt", "r");
    if (in == NULL)
        return;
    
    int arr[50];
    for (int i = 0; i < 50; i++)
        arr[i] = 0;
    
    char buffer[50];
    for (int i = 0; i < 100; i++)
    {
        fscanf(in, "%s", buffer);
        for (int j = 0; j < 50; j++)
            arr[j] += buffer[j] - 48;
    }
    
    int carry = 0;
    for (int i = 49; i >= 0; i--)
    {
        arr[i] += carry;
        carry = arr[i] / 10;
        arr[i] = arr[i] % 10;
    }
    printf("\n%i\n", carry);
    fclose(in);
}

int main(int argc, char *argv[])
{
	int x;
	if (argc != 2)
	{
		printf("Enter a problem number: ");
		scanf("%i", &x);
	}
	else
		x = atoi(argv[1]);
		
	clock_t begin = clock();
	
	switch (x)
	{
		case 1:
            pe1();
            break;
		case 2:
            pe2();
            break;
		case 3:
            pe3();
            break;
		case 4:
            pe4();
            break;
		case 5:
            pe5();
            break;
		case 6:
            pe6();
            break;
		case 7:
            pe7();
            break;
		case 8:
            pe8();
            break;
		case 9:
            pe9();
            break;
		case 10:
            pe10();
            break;
		case 11:
            pe11();
            break;
        case 12:
            pe12();
            break;
        case 13:
            pe13();
            break;
            
		default:
		printf("Invalid\n");
	}
	printf("%f\n", (double)(clock() - begin) / CLOCKS_PER_SEC);
}

int prime(long x)
{
	if (x == 1)
		return 0;
	
	for (long i = 2; i * i <= x; i++)
		if (!(x % i))
			return 0;
			
	return 1;
}

int palindrome(int x)
{
	char str[50]; 
	sprintf(str, "%i", x);
	int i = strlen(str) - 1;

	for (int a = 0; a <= i / 2; a++)
		if (str[a] != str[i - a])
			return 0;
	return 1;
}

int *primegen(int x)
{
	int *arr = malloc(sizeof(int) * (x+1));
	int count = 1;
	
	for (int i = 0; i <= x; i++)
		arr[i] = 1;
		
	for (int i = 2; i < x; i++)
		if (arr[i])
		{
			for (int j = i + i; j <= x; j += i)
				arr[j] = 0;
			count++;
		}
	
	int *primes = malloc(count * sizeof(int));
	primes[count - 1] = 0; // so the end can be found without knowing length
	count = 0;
	for (int i = 2; i <= x; i++)
		if (arr[i])
			primes[count++] = i;
    free(arr);
	return primes;
}

int m(int a, int b, int c)
{
	int sum = a + b + c;
	if (sum > 1000)
		return 0;
	if (!(1000 % sum))
	{
		int x = 1000 / sum;
		printf("%i\n", x * x * x * a * b * c);
		return 1;
	}
	if (m(a + (b<<1) + 2*c, (a<<1) + b + (c<<1), (a<<1) + (b<<1) + (c<<1) + c))
		return 1;
	if (m(-a + (b<<1) + 2*c, -(a<<1) + b + (c<<1), -(a<<1) + (b<<1) + (c<<1) + c))
		return 1;
	if (m(a - (b<<1) + 2*c, (a<<1) - b + (c<<1), (a<<1) - (b<<1) + (c<<1) + c))
		return 1;
    return 0;
}

int factors(int x, int *primes)
{
    int result = 1;
    while(*primes && x != 1)
    {
        int count = 1;
        while (!(x % *primes))
        {
            x /= *primes;
            count++;
        }
        result *= count;
        count++;
        primes++;
    }
    //printf("%i\n", result);
    return result;
}
