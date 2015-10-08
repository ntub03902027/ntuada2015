#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

long long int e;
int n, c, p;

bool compare(int a, int b) {
	long long int ans = (c * (a - b)) % (long long int)p;
	long long int power = e;
	long long int base = a + b;
	if (ans < 0)
		ans += p;
	while (power > 0) {
		if (power % 3 == 0) {
			power /= 3;
			base = (base * base * base) % (long long int)p;
		}
		else if (power % 3 == 2){
			ans = (ans * base * base) % (long long int)p;
			power -= 2;
		}
		else {
			ans = (ans * base) % (long long int)p;
			power--;
		}
	}
	
	//printf("answer of %d and %d is %d.\n", a, b, ans);
	if (ans > p / 2)
		return true;
	else
		return false;
}

int main(void) {
	int T;
	scanf("%d", &T);
	std::vector<int> queue;
	while (T--) {
		scanf("%d%d%lld%d", &n, &c, &e, &p);
		for (int i = 0; i < n; i++)
			queue.push_back(i + 1);
		stable_sort(queue.begin(), queue.end(), compare);

		for (int i = 0; i < n; i++)
			printf("%d ", queue[i]);
		printf("\n");
		queue.clear();
	}
	return 0;
}