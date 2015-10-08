#include <stdio.h>
#include <stdlib.h>

long long int c, e, p;
int n;

int compare(const int a, const int b) {
	//int r = *(int *)a;
	//int s = *(int *)b;
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

	if (ans > p / 2)
		return 1;
	else
		return 0;
}

void merge_sort(int *queue, int size) {
	if ( size <= 1)
		return;
	int *subqueue1;
	subqueue1 = (int *)malloc(size / 2 * sizeof(int));
	int *subqueue2;
	subqueue2 = (int *)malloc((size - size / 2) * sizeof(int));
	int size1 = size / 2;
	int size2 = size - (size / 2);
	for (int i = 0; i < size / 2; i++)
		subqueue1[i] = queue[i];
	for (int i = size / 2; i < size; i++)
		subqueue2[i - (size / 2)] = queue[i];

	merge_sort(subqueue1, size1);
	merge_sort(subqueue2, size2);

	if (compare(subqueue1[size1 - 1], subqueue2[0])) {
		for (int i = 0; i < size1; i++)
			queue[i] = subqueue1[i];
		for (int i = size1; i < size; i++)
			queue[i] = subqueue2[i - size1];
	}
	else if (compare(subqueue2[size2 - 1], subqueue1[0])) {
		for (int i = 0; i < size2; i++)
			queue[i] = subqueue2[i];
		for (int i = size2; i < size; i++)
			queue[i] = subqueue1[i - size2];
	}
	else {
		for (int i = 0, it1 = 0, it2 = 0; i < size; i++) {
			if ( it2 >= size2 || (it1 < size1 && compare(subqueue1[it1], subqueue2[it2]))) {
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
	free(subqueue1);
	free(subqueue2);
	
	/*printf("///\n");
	for (int i = 0; i < size; i++)
			printf("%d ", queue[i]);
		printf("\n");*/
}

int main(void) {
	int T;
	scanf("%d", &T);
	int *queue;
	queue = (int *)malloc(200000* sizeof(int));
	while (T--) {
		scanf("%d%lld%lld%lld", &n, &c, &e, &p);
		e = e % (p - 1);
		for (int i = 0; i < n; i++)
			queue[i] = i + 1;
		merge_sort(queue, n);

		//qsort(queue, n, sizeof(int), compare);

		for (int i = 0; i < n; i++)
			printf("%d ", queue[i]);
		printf("\n");
	}

}