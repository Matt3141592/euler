#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct node
{
    char str[15];
    struct node *next;
}node;
//test
int prime(long x);
int palindrome(char *str);
int *primegen_array(int x);
int *primegen(int x);
int m(int a, int b, int c);
int m2(int a, int b, int c, int arr[1001]);
int factors(int x, int *primes);
int collatz(long x);
node *quick(node *list);
void freelist(node *list);
int pan(char *str);
void heap(char digits[], int n, long *patterns, int *count);
void merge(long list[], int start, int end);
int recurring(int x);
int coin(int coins[], int target, int x);
int digit_cancelling(int x, int y);
int circular(int x, int *primes);
char *base2(int x);
int truncatable(int x);

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
			char str[10];
			sprintf(str, "%d", x);
			if (palindrome(str))
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
    int teens = 70; // 3 6 6 8 8 7 7 9 8 8
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

void pe19(void)
{
    int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int day = 0; // 0 is monday
    for (int i = 0; i < 12; i++)
        day += days[i];
    day %= 7;
    
    int ans = 0;
    for (int i = 1901; i <= 2000; i++)
        for (int j = 0; j < 12; j++)
        {
            if (day == 6)
                ans++;
            day += days[j];
            if (j == 1 && !(i % 4))
                day++;
            day %= 7;
        }
    printf("%i\n", ans);
}

void pe20(void)
{
    int arr[200];
    for (int i = 0; i < 200; i++)
        arr[i] = 0;
    
    arr[0] = 1;
    for (int i = 2; i < 100; i++)
    {
        int carry = 0;
        for (int j = 0; j < 200; j++)
        {
            arr[j] *= i;
            arr[j] += carry;
            carry = arr[j] / 10;
            arr[j] %= 10;
        }
    }
    
    int sum = 0;
    for (int i = 0; i < 200; i++)
        sum += arr[i];
    
    printf("%i\n", sum);
}

void pe21(void)
{
    int arr[10000];
    
    for (int i = 0; i < 10000; i++)
    {
        arr[i] = 1;
        for (int j = 2; j * j <= i; j++)
            if (!(i % j))
                arr[i] += j + (i / j) * (j * j != i);
    }
    
    int ans = 0;
    for (int i = 2; i < 10000; i++)
        if (arr[i] < 10000)
            if (i == arr[arr[i]] && i != arr[i])
                ans += i;
    printf("%i\n", ans);
}

void pe22(void)
{
    FILE *in = fopen("pe22.txt", "r");
    char buffer[50000];
    fscanf(in, "%s", buffer);
    fclose(in);
    
    node *buckets[26];
    for (int i = 0; i < 26; i++)
        buckets[i] = NULL;
    
    char *name = strtok(buffer, "\",\"");
    while (name)
    {
        node *n = malloc(sizeof(node));
        strcpy(n -> str, name);
        n -> next = buckets[n -> str[0] - 'A'];
        buckets[n -> str[0] - 'A'] = n;
        name = strtok(NULL, "\",\"");
    }
    
    int ans = 0;
    int count = 1;
    for (int i = 0; i < 26; i++)
    {
        buckets[i] = quick(buckets[i]);
        node *temp = buckets[i];
        
        while (temp != NULL)
        {
            name = temp -> str;
            while (*name)
                ans += count * (*name++ - '@');
            count++;
            temp = temp -> next;
        }
        freelist(buckets[i]);
    }
    printf("%i\n", ans);
}

void pe23(void)
{
    int abundant[28123];
    int summable[28123];
    for (int i = 0; i < 28123; i++)
        summable[i] = 0;
    
    for (int i = 1; i < 28123; i++)
    {
        int sum = 1;
        for (int j = 2; j * j <= i; j++)
            if (!(i % j))
                sum += j + (i / j) * (j * j != i);
        abundant[i] = sum > i;
    }
        
    for (int i = 0; i < 28123; i++)
        if (abundant[i])
            for (int j = i; i + j < 28123; j++)
                if (abundant[j])
                    summable[i + j] = 1;
    
    int sum = 0;
    for (int i = 0; i < 28123; i++)
        sum += i * !summable[i];
    printf("%i\n", sum);
    
}

void pe24(void)
{
    char digits[] = "0123456789";
    long *patterns = malloc(sizeof(long) * 3628800);
    int count = 0;
    heap(digits, 10, patterns, &count);
    merge(patterns, 0, 3628799);
    
    printf("%li\n", patterns[999999]);
    free(patterns);
}

void pe25(void)
{
    char one[1000];
    char two[1000];
    for (int i = 1; i < 1000; i++)
    {
        one[i] = 0;
        two[i] = 0;
    }
    
    one[0] = 1;
    two[0] = 1;
    char temp;
    int count = 2;
    
    while (!two[999])
    {
        int carry = 0;
        for (int i = 0; i < 1000; i++)
        {
            temp = two[i];
            carry += one[i] + two[i];
            two[i] = carry % 10;
            carry /= 10;
            one[i] = temp;
        }
        count++;
    }
    printf("%i\n", count);
}

void pe26(void)
{
	int highest = 0; 
	int ans;
	
	for (int i = 1; i < 1000; i += 2)
	{
		int x = recurring(i);
		if (x > highest)
		{
			highest = x;
			ans = i;
		}
		//printf("%.3i %.3i\n", x, i);
	}
	printf("%i %i\n", highest, ans);
}

void pe27(void)
{
	// j must be a prime because it must satisfy x = 0. 
	int ans;
	int longest = 0;
	int *primes = primegen(1000);
	
	for (int i = -999; i < 1000; i ++)
	{
		int k = -1;
		while (primes[++k])
		{
			int x = 0, j = primes[k];
			while (prime(x * x + i * x + j))
				x++;
			if (x > longest)
			{
				longest = x;
				ans = i * j;
			}
		}
	}
	printf("%i %i\n", longest, ans);
	free(primes);
}

void pe28(void)
{
	int sum = 1;
	for (int i = 3; i < 1002; i += 2)
		sum += (4 * i * i) - (6 * (i - 1));
	printf("%i\n", sum);
}

/*void pe29(void)
{
	int nums[101];
	int count = 0;
	
	for (int i = 0; i < 101; i++)
		nums[i] = 1;
	
	for (int i = 2; i < 101; i++)
		if (nums[i])
		{
			int arr[601];
			for (int j = 0; j < 601; j++)
				arr[j] = 0;
			int x = 1, y = i;
			while (y <= 100 && nums[y])
			{
				for (int k = 1; k <= 100; k++)
					arr[k * x] = 1;
				x++;
				nums[y] = 0;
				y *= i;
			}
			for (int k = 2; k < 601; k++)
				count += arr[k];
		}
	printf("%i\n", count);
}*/

void pe29(void)
{
	int distinct[7], arr[601] = {0}, count = 0;
	distinct[0] = 0;
	
	for (int i = 1; i < 7; i++)
	{
		for (int j = 2; j <= 100; j++)
			arr[i * j] = 1;
		int sum = 0;
		for (int j = 2; j <= i * 100; j++)
			sum += arr[j];
		distinct[i] = sum;
	}
	
	int nums[101];
	for (int i = 0; i < 101; i++)
		nums[i] = 1;
	
	for (int i = 2; i < 101; i++)
	{
		int x = 0, y = i;
		while (y <= 100 && nums[y])
		{
			x++;
			nums[y] = 0;
			y *= i;
		}
		count += distinct[x];
	}
	printf("%i\n", count);
}

void pe30(void)
{
	int pows[10];
	for (int i = 0; i < 10; i++)
	{
		pows[i] = 1;
		for (int j = 0; j < 5; j++)
			pows[i] *= i;
	}
	
	int ans = 0;
	for (int a = 0; a < 4; a++)
		for (int b = 0; b < 10; b++)
			for (int c = 0; c < 10; c++)
				for (int d = 0; d < 10; d++)
					for (int e = 0; e < 10; e++)
						for (int f = 0; f < 10; f++)
						{
							int sum = pows[a] + pows[b] + pows[c] + pows[d] + pows[e] + pows[f];
							int n = f + 10 * e + 100 * d + 1000 * c + 10000 * b + 100000 * a;
							if (sum == n)
								ans += n;
						}
	printf("%i\n", ans - 1);
}

/*void pe31(void)
{
	// solution from project euler, initially brute forced.
	int coins[] = {1,2,5,10,20,50,100,200};
	printf("%i\n", coin(coins, 200, 7)); 
}*/

void pe31(void)
{
	// soloution from project euler.
	int coins[] = {1,2,5,10,20,50,100,200};
	int ans[201] = {1};
	
	for (int i = 0; i < 8; i++)
		for (int j = coins[i]; j < 201; j++)
		{
			ans[j] += ans[j - coins[i]];
			printf("%i ", ans[j]);
			}
	printf("%i\n", ans[10]);
}

void pe32(void)
{
	int products[100] = {0};
	int count = 0;
	
	for (int i = 2; i < 100; i++)
		for (int j = i + 1; j < 5000; j++)
		{
			int product = i * j;
			char str[12];
			sprintf(str,"%d%d%d", i,j,product);
			if (strlen(str) > 9)
				break;
			if (strlen(str) == 9)
				if (pan(str))
				{
					int found = 0;
					for (int k = 0; k < count; k++)
						found += product == products[k];
					if (!found)
						products[count++] = product;
				}
		}
	int ans = 0;
	for (int i = 0; i < count; i++)
		ans += products[i];
	printf("%i\n", ans);
}

void pe33(void)
{
	int top = 1, bottom = 1;
	
	for (int i = 11; i < 100; i++)
		for (int j = i + 1; j < 100; j++)
			if (digit_cancelling(i,j))
			{
				top *= i;
				bottom *= j;
			}
	printf("%i %i\n", top, bottom);
}

void pe34(void)
{
	int factorial[10] = {1};
	int ans = 0;
	for (int i = 1; i < 10; i++)
		factorial[i] = i * factorial[i - 1];
	
	for (int i = 3; i < 10000000; i++)
	{
		int sum = 0;
		int x = i;
		while (x)
		{
			sum += factorial[x % 10];
			x /= 10;
		}
		
		if (sum == i)
			ans += sum;
	}
	
	printf("%i\n", ans);
} 		

void pe35(void)
{
	int *primes = primegen_array(1000000);
	int count = 1;
	
	for (int i = 3; i < 1000000; i += 2)
		if (primes[i])
			count += circular(i, primes);
	
	printf("%i\n", count);
	free(primes);
}

void pe36(void)
{
	int sum = 0;
	for (int i = 1; i < 1000; i++)
	{
		char str[4];
		sprintf(str, "%d", i);
		int x = strlen(str);
		
		char palin[6];
		strcpy(palin, str);
		for (int j = x - 2; j >= 0; j--)
			palin[(x << 1) - j - 2] = str[j];
		palin[(x << 1) - 1] = '\0';
		
		int num = atoi(palin);
		char *bin = base2(num);
		sum += palindrome(bin) * num;
		free(bin);
		
		strcpy(palin,str);
		for (int j = x - 1; j >= 0; j--)
			palin[(x << 1) - j - 1] = str[j];
		palin[(x << 1)] = '\0';
		
		num = atoi(palin);
		bin = base2(num);
		sum += palindrome(bin) * num;
		free(bin);
	}
	printf("%i\n", sum);
}

void pe37(void)
{
	int sum = 0;
	int count = 0;
	int *primes = primegen(1000000);
	int *p = primes;
	
	while (count != 11 && *primes)
	{
		int x = *primes++;
		if (truncatable(x))
		{
			sum += x;
			count++;
		}
	}
	printf("%i\n", sum);
	free(p);
}

void pe38(void)
{
	long highest = 0;
	for (int i = 1; i < 10000; i++)
	{
		int x = 2;
		char str[20];
		char temp[10];
		sprintf(str, "%d", i);
		
		while (strlen(str) < 9)
		{
			sprintf(temp, "%d", i * x++);
			strcat(str, temp);
		}
		
		if (strlen(str) != 9)
			continue;
		
		if (pan(str))
		{
			long n = atol(str);
			if (n > highest)
				highest = n;
		}
	}
	printf("%li\n", highest);
}

void pe39(void)
{
	int arr[1001] = {0};
	m2(3,4,5,arr);
	
	int most = 0;
	int ans;
	
	for (int i = 0; i < 1001; i++)
		if (arr[i] > most)
		{
			ans = i;
			most = arr[i];
		}
	printf("%i\n", ans);
}		

void pe40(void)
{
	int ans = 1;
	int count = 0;
	int len = -1;
	char str[10];
	
	for (int i = 1; i < 10000000; i++)
	{
		count += log10(i) + 1;
		if ((int)log10(count) > len)
		{
			len++;
			sprintf(str, "%d", i);
			ans *= str[strlen(str) - count + (int)pow(10,len) - 1] - '0';
		}
		
		if (count >= 1000000)
			break;
	}
	printf("%i\n", ans);
}

void pe41(void)
{
	int highest = 0;
	int *primes = primegen(7654321); // cannot be 8 or 9 pandigital as it would be a multiple of 3
	int *p = primes;
	char str[10];
	
	while (*p)
	{
		sprintf(str, "%d", *p);
		if (pan(str))
			highest = *p; // checking in order so don't need to check if it's higher than the last
		p++;
	}
	
	printf("%i\n", highest);
	free(primes);
}

void pe42(void)
{
	int ans = 0;
	int triangles[500] = {0};
	for (int i = 1, j = 2; i < 500; i += j, j++)
		triangles[i] = 1;
		
	FILE *in = fopen("pe42.txt", "r");
	char buffer[50000];
	fscanf(in, "%s", buffer);
	fclose(in);
	
	char *word = strtok(buffer, "\",\"");
	char *temp;
	while ((temp = word))
	{
		int sum = 0;
		while (*temp)
			sum += *(temp++) - '@';
		if (triangles[sum])
			ans++;
		word = strtok(NULL, "\",\"");
	}
	
	printf("%i\n", ans);
}
		
void pe67(void)
{
    FILE *in = fopen("pe67.txt", "r");
    if (in == NULL)
        return;
    int arr[100][100];
    char buffer[2];
    for (int i = 0; i < 100; i++)
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
		case 19:
			pe19();
			break;
		case 20:
			pe20();
			break;		
		case 21:
			pe21();
			break;
		case 22:
			pe22();
			break;
		case 23:
			pe23();
			break;
		case 24:
			pe24();
			break;
		case 25:
			pe25();
			break;
		case 26:
			pe26();
			break;
		case 27:
			pe27();
			break;
		case 28:
			pe28();
			break;
		case 29:
			pe29();
			break;
		case 30:
			pe30();
			break;
		case 31:
			pe31();
			break;
		case 32:
			pe32();
			break;
		case 33:
			pe33();
			break;
		case 34:
			pe34();
			break;
		case 35:
			pe35();
			break;
		case 36:
			pe36();
			break;
		case 37:
			pe37();
			break;
		case 38:
			pe38();
			break;
		case 39:
			pe39();
			break;
		case 40:
			pe40();
			break;
		case 41:
			pe41();
			break;
		case 42:
			pe42();
			break;
		case 67:
			pe67();
			break;
		default:
			printf("Invalid\n");		
	}
	
	printf("%f\n", (double)(clock() - begin) / CLOCKS_PER_SEC);
}

int prime(long x)
{
	if (x < 2)
		return 0;
	
	for (long i = 2; i * i <= x; i++)
		if (!(x % i))
			return 0;
			
	return 1;
}

int palindrome(char *str)
{
	int i = strlen(str) - 1;

	for (int a = 0; a <= i / 2; a++)
		if (str[a] != str[i - a])
			return 0;
	return 1;
}

int *primegen_array(int x)
{
	int *arr = malloc(sizeof(int) * (x+1));
	for (int i = 0; i < x; i++)
		arr[i] = 0;
		
	arr[2] = 1;
	for (int i = 3; i <= x; i += 2)
		arr[i] = 1;
		
	for (int i = 3; i * i <= x; i += 2)
		if (arr[i])
			for (int j = i << 1; j <= x; j += i)
				arr[j] = 0;
 	return arr;
    /*int count = 2;
    for (int i = 3; i <= x; i += 2)
        if (arr[i])
            count++;
	
	int *primes = malloc(count * sizeof(int));
    primes[0] = 2;
	primes[count - 1] = 0; // so the end can be found without knowing length
	count = 1;
    for (int i = 3; i <= x; i += 2)
		if (arr[i])
			primes[count++] = i;
    free(arr);
	return primes;*/
}

int *primegen(int x)
{
    int y = (x + 1) >> 1;
    int *arr = malloc(sizeof(int) * y);
    
    for (int i = 0; i < y; i++)
        arr[i] = 1;
    
    for (int i = 1; (i * i) << 1 <= y; i++)
        if (arr[i])
        {
            int a = (i << 1) + 1;
            for (int j = i + a; j < y; j += a)
                arr[j] = 0;
        }
    
    int count = 2;
    for (int i = 1; i < y; i++)
        count += arr[i];
    
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

int m2(int a, int b, int c, int arr[1001])
{
	int sum = a + b + c;
	if (sum > 1000)
		return 0;
	
	int x = sum;
	while (x <= 1000)
	{
		arr[x]++;
		x += sum;
	}
	
	if (m2(a + (b<<1) + 2*c, (a<<1) + b + (c<<1), (a<<1) + (b<<1) + (c<<1) + c, arr))
		return 1;
	if (m2(-a + (b<<1) + 2*c, -(a<<1) + b + (c<<1), -(a<<1) + (b<<1) + (c<<1) + c, arr))
		return 1;
	if (m2(a - (b<<1) + 2*c, (a<<1) - b + (c<<1), (a<<1) - (b<<1) + (c<<1) + c, arr))
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

void freelist(node *list)
{
    node *temp = list;
    while (list != NULL)
    {
        list = list -> next;
        free(temp);
        temp = list;
    }
}

node *quick(node *list)
{
    if (list == NULL)
        return NULL;
    node *small = NULL;
    node *big = NULL;
    node *piv = list;
    
    list = list -> next;
    while (list != NULL)
    {
        node *temp = list -> next;
        if (strcmp(list -> str, piv -> str) < 0)
        {
            list -> next = small;
            small = list;
        }
        else
        {
            list -> next = big;
            big = list;
        }
        list = temp;
    }
    small = quick(small);
    piv -> next = quick(big);
    
    node *temp = small;
    if (temp != NULL)
    {
        while (temp -> next != NULL)
            temp = temp -> next;
        temp -> next = piv;
    }
    else
        small = piv;
    return small;
}

int pan(char *str)
{
	int x = strlen(str) + 1;
    int nums[10] = {0};
    
    while (*str)
        nums[*str++ - '0']++;
    
    for (int i = 1; i < x; i++)
        if (nums[i] != 1)
            return 0;
    
    for (int i = x; i < 10; i++)
    	if (nums[i] != 0)
    		return 0;
    
    return nums[0] < 1;
}

void heap(char digits[], int n, long *patterns, int *count)
{
    if (n == 1)
    {
        patterns[(*count)++] = strtol(digits, NULL, 10);
        return;
    }
    
    for (int i = 0; i < n; i++)
    {
        heap(digits, n - 1, patterns, count);
        char temp = digits[n - 1];
        
        if ((n & 1))
        {
            digits[n - 1] = digits[0];
            digits[0] = temp;
        }
        else
        {
            digits[n - 1] = digits[i];
            digits[i] = temp;
        }
    }
}

void insert(long list[], int start, int end)
{
    for (int i = start + 1; i <= end; i++)
    {
        long x = list[i];
        int j = i;
        while (j > start)
        {
            if (x < list[j - 1])
            {
                list[j] = list[j - 1];
                j--;
            }
            else
                break;
        }
        list[j] = x;
    }
}

void merge(long list[], int start, int end)
{
    if (end == start)
        return;
    
    int y = end - start;
    if (y < 32)
    {
        insert(list, start, end);
        return;
    }
    int x = y >> 1;
    
    merge(list, start, x + start);
    merge(list, x + 1 + start, end);
    
    long left = 0;
    long right = x + 1;
    long *temp = malloc(sizeof(long) * (y + 1));
    for (int i = 0; i <= y; i++)
        temp[i] = list[start + i];
    
    for (int i = 0; i <= y; i++)
    {
        if (right <= y && left <= x)
        {
            if (temp[left] >= temp[right])
                list[start + i] = temp[right++];
            else
                list[start + i] = temp[left++];
        }
        else
        {
            if(right <= y)
                list[start + i] = temp[right++];
            else
                list[start + i] = temp[left++];
        }
    }
    free(temp);
}

int recurring(int x)
{
	int decimals[1000];
	int a = 10;
	
	for (int i = 0; i < 6; i++)
	{
		decimals[i] = a / x;
		a %= x;
		a *= 10;
	}
	
	for (int i = 6; i < 1000; i++)
	{
		decimals[i] = a / x;
		a %= x;
		a *= 10;
		
		if (!a) // when the decimal stops it is not recurring
			return 0;
			
		if (decimals[3] == decimals[i - 2])
			if (decimals[4] == decimals[i - 1])
				if (decimals[5] == decimals[i])
					return i - 5;
	}
	return 0;
}

int coin(int coins[], int target, int x)
{
	if (!x) // when down to 1s, can always make up the amount
		return 1;

	int ans = 0;
	while (x && target > 0)
	{
		ans += coin(coins, target, x - 1);
		target -= coins[x];
	}
	return ans + !target;
}

int digit_cancelling(int x, int y)
{
	float b = x % 10;
	float a = x / 10;
	float d = y % 10;
	float c = y / 10;

	if (!b || !d)
		return 0;
	
	if (a == b || c == d)
		return 0;
		
	float div = (float)x / y;
	if (a == c)
		return (div == b / d);
	if (a == d)
		return (div == b / c);
	if (b == c)
		return (div == a / d);
	if (b == d)
		return (div == a / c);
	return 0;
}

int circular(int x, int *primes)
{	
	char str[10];
	sprintf(str, "%d", x);
	int len = strlen(str);
	
	for (int i = 1; i < len; i++)
	{
		int rotated = 0;
		for (int j = i; j < i + len; j++)
		{
			rotated *= 10;
			rotated += str[j % len] - '0';
		}
		if (!primes[rotated])
			return 0;
	}
	return 1;
}

char *base2(int x) //backwards
{
	char *str = malloc(20);
	int i = 0;
	while (x)
	{
		str[i++] = (x & 1) + '0';
		x = x >> 1;
	}
	str[i] = '\0';
	return str;
}

int truncatable(int x)
{
	char str[10];
	sprintf(str, "%d", x);
	int len = strlen(str);
	if (len == 1)
		return 0;
	
	for (int i = 0; i < len - 1; i++)
	{
		x /= 10;
		if (!prime(x))
			return 0;
			
		str[i] = '0';
		if (!prime(atoi(str)))
			return 0;
	}

	return 1;
}
