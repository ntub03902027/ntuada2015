#include <cstdio>
#include <cstdlib>
#include <ctime>

int main(void) {
	int T;
	scanf("%d", &T);

	unsigned int seed;

	seed = (unsigned) time(NULL);

	srand(seed);

	while (T--) {
		int x, a;
		scanf("%d", &x);
		switch (x) {
			case 0:
				printf("0 0\n");
			break;
			case 2000:
				printf("1000 1000\n");
			break;
			default:
				a = (x > 1000)? (rand() % (2000 - x) + (x - 1000)) : (rand() % x);
				printf("%d %d\n", a, x - a);
			break;
		}
	}

	return 0;
}