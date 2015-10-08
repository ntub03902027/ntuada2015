#include <stdio.h>
#include <stdlib.h>

long long int c, e, p;
int n;

int compare(const void *a, const void *b) {
	int r = *(int *)a;
	int s = *(int *)b;
	long long int ans = (c * (r - s)) % p;
	long long int power = e;
	long long int base = r + s;
	if (ans < 0)
		ans += p;

	power = power % (p - 1);

	while (power > 0) {
		if (power % 2 == 1) {
			ans = (ans * base) % p;
			power--;		
		}
		power /= 2;
		base = (base * base) % p;
	}

	if (ans > p / 2)
		return -1;
	else
		return 1;
}

int main(void) {
	int T;
	scanf("%d", &T);
	int queue[200000];
	while (T--) {
		scanf("%d%lld%lld%lld", &n, &c, &e, &p);
		
		for (int i = 0; i < n; i++)
			queue[i] = i + 1;
		qsort(queue, n, sizeof(int), compare);

		for (int i = 0; i < n; i++)
			printf("%d ", queue[i]);
		printf("\n");
	}

}