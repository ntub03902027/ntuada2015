#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

long long int c, e, p;
int n;

bool beat(int a, int b) {
	long long int ans = (c * (a - b)) % p;
	long long int power = e;
	long long int base = a + b;
	if (ans < 0)
		ans += p;
	while (power > 0) {
		if (power % 2 == 1) {
			ans = (ans * base) % p;
			power--;		
		}
		power /= 2;
		base = (base * base) % p;
	}
	
	//printf("answer of %d and %d is %d.\n", a, b, ans);
	if (ans > p / 2)
		return true;
	else
		return false;

}

bool compare(int a, int b) {
	return (a > b);
}

void merge_sort(std::vector<int> &queue) {
	if (queue.size() <= 1)
		return;
	std::vector<int> subqueue1;
	std::vector<int> subqueue2;
	for (int i = 0; i < queue.size() / 2; i++)
		subqueue1.push_back(queue[i]);
	for (int i = queue.size() / 2; i < queue.size(); i++)
		subqueue2.push_back(queue[i]);

	//queue.clear();
	merge_sort(subqueue1);
	merge_sort(subqueue2);
	
	if (beat(subqueue1[subqueue1.size() - 1], subqueue2[0])) {
		for (int i = 0; i < subqueue1.size(); i++)
			queue[i] = subqueue1[i];
		for (int i = subqueue1.size(); i < queue.size(); i++)
			queue[i] = subqueue2[i - subqueue1.size()];
	}
	else if (beat(subqueue2[subqueue2.size() - 1], subqueue1[0])) {
		for (int i = 0; i < subqueue2.size(); i++)
			queue[i] = subqueue2[i];
		for (int i = subqueue2.size(); i < queue.size(); i++)
			queue[i] = subqueue1[i - subqueue2.size()];
	}
	else {
		for (int i = 0, it1 = 0, it2 = 0; i < subqueue1.size() + subqueue2.size(); i++) {
			if ( it2 >= subqueue2.size() || (it1 < subqueue1.size() && beat(subqueue1[it1], subqueue2[it2]))) {
				//queue.push_back(subqueue1[it1]);
				queue[i] = subqueue1[it1];
				it1++;
			}
			else {
				//queue.push_back(subqueue2[it2]);
				queue[i] = subqueue2[it2];
				it2++;
			}
		}
	}
	subqueue1.clear();
	subqueue2.clear();
}
/*
void examine_ans(std::vector<int> &queue, int &c, long long int &e, int &p) {
	int exarr[queue.size() + 1];
	for (int i = 0; i <= queue.size(); i++)
		exarr[i] = 0;
	for (int i = 0; i < queue.size() - 1; i++) {
		if (!beat(queue[i], queue[i + 1], c, e, p) || exarr[queue[i]] != 0) {
			printf("wrong\n");
			if (exarr[queue[i]] != 0)
				printf("%d has more than one in %d. Why?\n", queue[i], i);
			return;
		}
		exarr[queue[i]]++;
	}
	if (exarr[queue[queue.size() - 1]] != 0) {
		printf("wrong\n");
		printf("%d has more than one. Why?\n", queue.size());
		return;
	}

	printf("correct\n"); 
	return;
}*/

int main(void) {
	int T;
	scanf("%d", &T);
	std::vector<int> queue;
	while (T--) {
		scanf("%d%d%lld%d", &n, &c, &e, &p);

		e = e % (p - 1); /*fermat theorem*/
		for (int i = 0; i < n; i++)
			queue.push_back(i + 1);
		merge_sort(queue);

		for (int i = 0; i < n; i++)
			printf("%d ", queue[i]);
		printf("\n");

		queue.clear();
	}
	return 0;
}