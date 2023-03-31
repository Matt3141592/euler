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
int collatz(long x);

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
        {
            x /= i;
            if (prime(i))
                ans = i;
        }
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

void pe8(void)
{
	char buffer[1000];
	FILE *in = fopen("digits.txt", "r");
	if (in == NULL)
		return;
	
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

void pe11(void)
{
	FILE *in = fopen("grid.txt", "r");
    if (in == NULL)
        return;
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
    printf("%i", carry);
    for (int i = 0; i < 8; i++)
        printf("%i", arr[i]);
    printf("\n");
    fclose(in);
}

void pe14(void)
{
    int highest = 0;
    int ans = 0;
    for (long i = 1; i < 1000000; i++)
    {
        int x = collatz(i);
        if (x > highest)
        {
            highest = x;
            ans = i;
        }
    }
    printf("%i\n", ans);
}

void pe15(void)
{
    // must include 20 downs and 20 rights.
    // 40C20
    double ans = 1;
    for (int i = 21; i <= 40; i++)
        ans *= (double)i;
    for (int i = 1; i < 21; i++)
        ans /= (double)i;
    printf("%.0f\n", ans);
}

void pe16(void)
{
    int arr[350];
    for (int i = 0; i < 350; i++)
        arr[i] = 0;
    arr[0] = 1;
    
    for (int i = 0; i < 100; i++)
    {
        int carry = 0;
        for (int k = 0; k < 350; k++)
        {
            arr[k] = arr[k] << 10;
            arr[k] += carry;
            carry = arr[k] / 10;
            arr[k] = arr[k] % 10;
        }
    }
    
    int sum = 0;
    for (int i = 0; i < 350; i++)
        sum += arr[i];
    printf("%i\n", sum);
}

void pe17(void)
{
    int total = 0;
    int onetonine = 36; // 3 3 5 4 4 3 5 5 4
    int and = 3;
    int hundred = 7;
    int teens = 69; // 3 6 6 8 8 7 7 9 8 8
    int tens = 46; // 6 6 5 5 5 7 6 6
    
    total += onetonine * 90;
    total += onetonine * 100;
    total += and * 99 * 9;
    total += hundred * 900;
    total += teens * 10;
    total += tens * 100;
    total += 11;
    
    printf("%i\n", total);
}

void pe18(void)
{
    FILE *in = fopen("pe18.txt", "r");
    if (in == NULL)
        return;
    int arr[15][15];
    char buffer[2];
    for (int i = 0; i < 15; i++)
        for (int j = 0; j <= i; j++)
        {
            fscanf(in, "%s", buffer);
            arr[i][j] = atoi(buffer);
        }
    fclose(in);
    
    for (int i = 14; i >= 0; i--)
        for (int j = 0; j < i; j++)
            arr[i - 1][j] += arr[i][j] * (arr[i][j] > arr[i][j + 1]) + arr[i][j + 1] * (arr[i][j] <= arr[i][j + 1]);
    printf("%i\n", arr[0][0]);
}

void pe67(void)
{
    FILE *in = fopen("pe67.txt", "r");
    if (in == NULL)
        return;
    int arr[100][100];
    char buffer[2];
    for (int i = 0; i < 15; i++)
        for (int j = 0; j <= i; j++)
        {
            fscanf(in, "%s", buffer);
            arr[i][j] = atoi(buffer);
        }
    fclose(in);
    
    for (int i = 99; i >= 0; i--)
        for (int j = 0; j < i; j++)
            arr[i - 1][j] += arr[i][j] * (arr[i][j] > arr[i][j + 1]) + arr[i][j + 1] * (arr[i][j] <= arr[i][j + 1]);
    printf("%i\n", arr[0][0]);
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
        case 14:
            pe14();
            break;
        case 15:
            pe15();
            break;
        case 16:
            pe16();
            break;
        case 17:
            pe17();
            break;
        case 18:
            pe18();
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

/*int *primegen(int x)
{
	int *arr = malloc(sizeof(int) * (x+1));
	int count = 2;
	
	for (int i = 3; i <= x; i += 2)
		arr[i] = 1;
		
	for (int i = 3; i * i <= x; i += 2)
		if (arr[i])
		{
			for (int j = i + i; j <= x; j += i)
				arr[j] = 0;
			count++;
		}
	
	int *primes = malloc(count * sizeof(int));
    primes[0] = 2;
	primes[count - 1] = 0; // so the end can be found without knowing length
	count = 1;
    for (int i = 3; i <= x; i += 2)
		if (arr[i])
			primes[count++] = i;
    free(arr);
	return primes;
}*/

int *primegen(int x)
{
    int y = (x + 1) >> 1;
    int *arr = malloc(sizeof(int) * y);
    
    for (int i = 0; i < y; i++)
        arr[i] = 1;
    
    int count = 2;
    for (int i = 1; (i * i) << 1 <= y; i++)
        if (arr[i])
        {
            int a = (i << 1) + 1;
            for (int j = i + a; j < y; j += a)
                arr[j] = 0;
            count++;
        }
    
    int *primes = malloc(sizeof(int) * count);
    primes[0] = 2;
    primes[count - 1] = 0;
    count = 1;
    
    for (int i = 1; i < y; i++)
        if (arr[i])
            primes[count++] = (i << 1) + 1;
    
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

int collatz(long x)
{
    int count = 1;
    while (x != 1)
    {
        if ((x & 1))
            x = (x << 1) + x + 1;
        else
            x = x >> 1;
        count++;
    }
    return count;
}
