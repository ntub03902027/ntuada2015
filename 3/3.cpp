#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

bool beat(int a, int b, int &c, int &e, int &p) {
	long long int ans = (c * (a - b)) % p;
	long long int power = e;
	long long int base = a + b;
	while (power > 0) {
		if (power % 2 == 0) {
			power /= 2;
			base = (base * base) % p;
		}
		else {
			ans = (ans * base) % p;
			power--;
		}
	}
	if (ans < 0)
		ans = p + ans;
	//printf("answer of %d and %d is %d.\n", a, b, ans);
	if (ans > p / 2)
		return true;
	else
		return false;

}

bool compare(int a, int b, int &c, int &e, int &p) {
	return (a > b);
}

void merge_sort(std::vector<int> &queue, int &c, int &e, int &p) {
	if (queue.size() <= 1)
		return;
	std::vector<int> subqueue1;
	std::vector<int> subqueue2;
	for (int i = 0; i < queue.size() / 2; i++)
		subqueue1.push_back(queue[i]);
	for (int i = queue.size() / 2; i < queue.size(); i++)
		subqueue2.push_back(queue[i]);

	queue.clear();
	merge_sort(subqueue1, c, e, p);
	merge_sort(subqueue2, c, e, p);
	
	for (int i = 0, it1 = 0, it2 = 0; i < subqueue1.size() + subqueue2.size(); i++) {
		if ( it2 >= subqueue2.size() || (it1 < subqueue1.size() && beat(subqueue1[it1], subqueue2[it2], c, e, p))) {
			queue.push_back(subqueue1[it1]);
			it1++;
		}
		else {
			queue.push_back(subqueue2[it2]);
			it2++;
		}
	}
	subqueue1.clear();
	subqueue2.clear();
}

int main(void) {
	int T;
	scanf("%d", &T);
	std::vector<int> queue;
	while (T--) {
		int n, c, e, p;
		scanf("%d%d%d%d", &n, &c, &e, &p);
		for (int i = 0; i < n; i++)
			queue.push_back(i + 1);
		merge_sort(queue, c, e, p);

		for (int i = 0; i < n; i++)
			printf("%d ", queue[i]);
		printf("\n");
		queue.clear();
	}
	return 0;
}