#include <cstdio>

using namespace std;






typedef struct attribute {
	int dig_count;
	int digit[20];
} Attribute;

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


int main(void) {
	
	int T;
	long long l;
	long long r;
	long long ans;


	
	scanf("%d", &T);
	while(T--) {
		scanf("%lld%lld", &l, &r);
		ans = 0;
		for (int i = l; i <= r; i++)
			if (islucky(i))
				ans++;

		printf("%lld\n", ans);
	}
	return 0;
}