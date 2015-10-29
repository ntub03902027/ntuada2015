#include <cstdio>


#define DPL 1
using namespace std;

const int mod7cycle[10][6] = {
	{0, 0, 0, 0, 0, 0},
	{5, 1, 3, 2, 6, 4},
	{3, 2, 6, 4, 5, 1},
	{1, 3, 2, 6, 4, 5},
	{6, 4, 5, 1, 3, 2},
	{4, 5, 1, 3, 2, 6},
	{2, 6, 4, 5, 1, 3},
	{0, 0, 0, 0, 0, 0},
	{5, 1, 3, 2, 6, 4},
	{3, 2, 6, 4, 5, 1}
};


typedef struct value {
	long long num_count;
	bool visited = false;
} Value;

typedef struct attribute {
	int dig_count;
	int digit[20];
} Attribute;


#ifdef DPL
long long table_l[19][7][19][19];
#else
Value table[19][7][19][19];
#endif


inline int min(int a, int b) {
	return (a < b)? a : b;
}

Attribute seek_number(long long num) {
	Attribute result;

	/*for (int i = 0; i < 20; i++)
		result.digit[i] = 0;*/

	int count = 0;
	long long divider = 1;
	while (num / divider != 0) {
		count++;
		divider *= 10;
	}
	divider /= 10;
	result.dig_count = count;

	result.digit[count + 1] = 0; //marginal digit


	long long temp = num;
	for (int i = count; i > 0; i--) {
		result.digit[i] = temp / divider;
		temp %= divider;
		divider /= 10;
	}


	return result;
}

bool istenpower(Attribute prop) {
	if (prop.digit[prop.dig_count] != 1)
		return false;
	for (int i = 1; i < prop.dig_count; i++)
		if (prop.digit[i] != 0)
			return false;
	return true;
}

#ifdef DPL
void init_table_l(void) {

	for (int b = 0; b < 7; b++)
		for (int c = 0; c < 19; c++)
			for (int d = 0; d < 19; d++) {

				if (c > 1 || d > 1)
					table_l[1][b][c][d] = 0;
				else if (c == 1) {
					if (b == 0 && d == 0)
						table_l[1][b][c][d] = 1; //7
					else
						table_l[1][b][c][d] = 0;
				}
				else if (d == 1) {
					if (b == 4 && c == 0)
						table_l[1][b][c][d] = 1; //4
					else
						table_l[1][b][c][d] = 0;
				}
				else {
					if (b == 1 || b == 2)
						table_l[1][b][c][d] = 2; //1, 8 ; 2, 9
					else if ( b == 4)
						table_l[1][b][c][d] = 0; //4
					else {
						table_l[1][b][c][d] = 1; //0, 3, 5, 6
					}
				}
			}


	for (int a = 2; a < 19; a++)
		for (int b = 0; b < 7; b++)
			for (int c = 0; c < 19; c++)
				for (int d = 0; d < 19; d++) {
					table_l[a][b][c][d] = 
					table_l[a - 1][(b - mod7cycle[0][a % 6] + 7) % 7][c][d] +
					table_l[a - 1][(b - mod7cycle[1][a % 6] + 7) % 7][c][d] * 2 + 
					table_l[a - 1][(b - mod7cycle[2][a % 6] + 7) % 7][c][d] * 2 + 
					table_l[a - 1][(b - mod7cycle[3][a % 6] + 7) % 7][c][d] + 
					table_l[a - 1][(b - mod7cycle[5][a % 6] + 7) % 7][c][d] + 
					table_l[a - 1][(b - mod7cycle[6][a % 6] + 7) % 7][c][d];
					if (c > 0)
						table_l[a][b][c][d] += table_l[a - 1][(b - mod7cycle[7][a % 6] + 7) % 7][c - 1][d];
					if (d > 0)
						table_l[a][b][c][d] += table_l[a - 1][(b - mod7cycle[4][a % 6] + 7) % 7][c][d - 1];
				}
}

long long dpl(int digit, int mod7, int count7, int count4) {
	return table_l[digit][mod7][count7][count4];
}
#else
void init_table(void) {
	for (int b = 0; b < 7; b++)
		for (int c = 0; c < 19; c++)
			for (int d = 0; d < 19; d++) {
				/*table[0][b][c][d].visited = true;
				table[0][b][c][d].num_count = 0;*/

				table[1][b][c][d].visited = true;
				if (c > 1 || d > 1)
					table[1][b][c][d].num_count = 0;
				else if (c == 1) {
					if (b == 0 && d == 0)
						table[1][b][c][d].num_count = 1; //7
					else
						table[1][b][c][d].num_count = 0;
				}
				else if (d == 1) {
					if (b == 4 && c == 0)
						table[1][b][c][d].num_count = 1; //4
					else
						table[1][b][c][d].num_count = 0;
				}
				else {
					if (b == 1 || b == 2)
						table[1][b][c][d].num_count = 2; //1, 8 ; 2, 9
					else if ( b == 4)
						table[1][b][c][d].num_count = 0; //4
					else {
						table[1][b][c][d].num_count = 1; //0, 3, 5, 6
					}
				}
				/*if (c <= 1 && d <= 1)
				 printf("(1, %d, %d, %d) = %d\n", b, c, d, table[1][b][c][d].num_count);*/
			}
	//init_table_l();
}



long long dp(int digit, int mod7, int count7, int count4) {
	if (digit == 0 || count7 < 0 || count4 < 0) {
		//printf("dp(%d, %d, %d, %d) out of bound\n", digit, mod7, count7, count4);
		return 0;
	}
	else if (table[digit][mod7][count7][count4].visited == true) {
		//printf("dp(%d, %d, %d, %d) visited, value is %lld\n", digit, mod7, count7, count4, table[digit][mod7][count7][count4].num_count);
		return table[digit][mod7][count7][count4].num_count;
	}
	else {
		//printf("dp(%d, %d, %d, %d) not visited, now find\n", digit, mod7, count7, count4);
		table[digit][mod7][count7][count4].visited = true;
		table[digit][mod7][count7][count4].num_count = 
		dp(digit - 1, (mod7 - mod7cycle[0][digit % 6] + 7) % 7, count7, count4) + 
		2 * dp(digit - 1, (mod7 - mod7cycle[1][digit % 6] + 7) % 7, count7, count4) + 
		2 * dp(digit - 1, (mod7 - mod7cycle[2][digit % 6] + 7) % 7, count7, count4) + 
		dp(digit - 1, (mod7 - mod7cycle[3][digit % 6] + 7) % 7, count7, count4) + 
		dp(digit - 1, (mod7 - mod7cycle[4][digit % 6] + 7) % 7, count7, count4 - 1) + 
		dp(digit - 1, (mod7 - mod7cycle[5][digit % 6] + 7) % 7, count7, count4) + 
		dp(digit - 1, (mod7 - mod7cycle[6][digit % 6] + 7) % 7, count7, count4) + 
		dp(digit - 1, (mod7 - mod7cycle[7][digit % 6] + 7) % 7, count7 - 1, count4);
		//printf("dp(%d, %d, %d, %d) found, answer is: %lld\n", digit, mod7, count7, count4, table[digit][mod7][count7][count4].num_count);
		return table[digit][mod7][count7][count4].num_count;
	}
}
#endif

long long find_lucky(int digit, int mod7, int current7, int diff) {
	if (digit == 0) {
		if ((7 - mod7) % 7 == 0 && current7 >= 3 && diff > 0)
			return 1;
		else
			return 0;
	}
	long long count = 0;
	int count7;
	if (3 - current7 >= 0)
		count7 = 3 - current7;
	else count7 = 0;
	for (; count7 <= digit; count7++)  {
		for (int count4 = min(digit - count7, diff + count7 - 1); count4 >= 0; count4--) {
			/*if (diff + count7 - count4 <= 0)
				continue;
			else {*/
				//printf("add: (%d, %d ,%d ,%d) = %lld\n", digit, mod7, count7, count4, dp(digit, mod7, count7, count4));
#ifdef DPL
				count += dpl(digit, mod7, count7, count4);
#else
				count += dp(digit, mod7, count7, count4);
#endif
				//count += dpl(digit, mod7, count7, count4);
				//count += table[digit][mod7][count7][count4].num_count;
			/*}*/
		}
	}
	//printf("(%d, %d ,%d ,%d) = %lld\n", digit, mod7, current7, diff, count);
	return count;
}

long long calculate(long long n) {
	long long ans = 0;
	Attribute prop;
	prop = seek_number(n);

	//add istenpower
	if (istenpower(prop)) {
		ans = find_lucky(prop.dig_count - 1, 0, 0, 0);
		//printf("lucky numbers <  %lld is %lld\n", n, ans);
		return ans;
	}
	int count7 = 0;
	int count4 = 0;
	int temp7 = 0;
	int temp4 = 0;
	int compmod = 0;
	int tempmod = 0;

	for (int current_dig_num = prop.dig_count; current_dig_num > 0; current_dig_num--) {
		if (prop.digit[current_dig_num + 1] == 7)
			count7++;
		if (prop.digit[current_dig_num + 1] == 4)
			count4++;
		temp7 = count7;
		temp4 = count4;
		compmod = (compmod + (7 - mod7cycle[prop.digit[current_dig_num + 1]][(current_dig_num + 1) % 6])) % 7;
		for (int cycle = 0; cycle < prop.digit[current_dig_num]; cycle++) {
			if (cycle == 4)
				temp4++;
			else if (cycle == 7)
				temp7++;
			tempmod = (compmod + (7 - mod7cycle[cycle][(current_dig_num) % 6])) % 7;

			int difference = temp7 - temp4;

			ans += find_lucky(current_dig_num - 1, tempmod, temp7, difference);
			


			//restore temp
			temp7 = count7;
			temp4 = count4;
		}
	}
	//printf("lucky numbers <  %lld is %lld\n", n, ans);
	return ans;
}

bool islucky(long long num) {
	if (num % 7 != 0)
		return false;
	Attribute prop = seek_number(num);
	int count4 = 0;
	int count7 = 0;
	for (int i = 1; i <= prop.dig_count; i++) {
		if (prop.digit[i] == 4)
			count4++;
		else if (prop.digit[i] == 7)
			count7++;
	}
	if (count7 < 3 || count7 <= count4)
		return false;
	return true;
}
bool belong(int num, int digit, int mod, int q7, int q4) {
	if (num % 7 != mod)
		return false;
	Attribute prop = seek_number(num);
	if (prop.dig_count > digit)
		return false;
	int count4 = 0;
	int count7 = 0;
	for (int i = 1; i <= prop.dig_count; i++) {
		if (prop.digit[i] == 4)
			count4++;
		else if (prop.digit[i] == 7)
			count7++;
	}
	if (q7 != count7)
		return false;
	if (q4 != count4)
		return false;
	return true;
}

int main(void) {
	
#ifdef DPL
	init_table_l();
#else
	init_table();
#endif

	//init_table();
	int T;
	long long l;
	long long r;
	long long ans;

	/*
	printf("dp(4, 0, 1, 0) = %lld\n", dp(4,0,1,0));

	long long count = 0;
		for (int i = 1; i < 1000000; i++)
			if (belong(i, 4, 0, 1, 0))
				count++;
	printf("%lld\n", count);*/
	
	scanf("%d", &T);
	while(T--) {
		scanf("%lld%lld", &l, &r);

		ans = calculate(r) - calculate(l);
		if (islucky(r))
			ans++;

		printf("%lld\n", ans);
	}
	return 0;
}