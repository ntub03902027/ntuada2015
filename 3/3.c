#include <stdio.h>
#include <stdlib.h>

long long int e;
int n, c, p;

int compare(const void *a, const void *b) {
	int r = *(int *)a;
	int s = *(int *)b;
	long long int ans = (c * (r - s)) % (long long int)p;
	long long int power = e;
	long long int base = r + s;
	if (ans < 0)
		ans += p;
	while (power > 0) {
		if (power % 2 == 0) {
			power /= 2;
			base = (base * base) % (long long int)p;
		}
		else {
			ans = (ans * base) % (long long int)p;
			power--;
		}
	}

	if (ans > p / 2)
		return 0;
	else
		return 1;
}

int main(void) {
	int T;
	scanf("%d", &T);
	int queue[200000];
	while (T--) {
		scanf("%d%d%lld%d", &n, &c, &e, &p);
		int i;
		for (i = 0; i < n; i++)
			queue[i] = i + 1;
		qsort(queue, n, sizeof(int), compare);

		for (i = 0; i < n; i++)
			printf("%d ", queue[i]);
		printf("\n");
	}

}