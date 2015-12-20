#include <cstdio>
#include <cstdlib>

#define edge1 0
#define edge2 1
#define WEIGHT 2

#define MAXEDGES 100000
#define MAXVERTEX 50001


typedef struct data {
	int next;
	int weight;
} Data;

typedef struct pair {
	int edges;
	long long weight;
} Pair;

int **table;


int ptr_comp (const void * a, const void * b) {
	int *ptr1 = (int*)a;
	int *ptr2 = (int*)b;

	if (ptr1[2] < ptr2[2])
		return -1;
	else if (ptr1[2] > ptr2[2])
		return 1;
	else
		return 0;
}
int sorter_comp(const void *a, const void *b) {
	int m = *(int *)a;
	int n = *(int *)b;

	if (table[m][2] < table[n][2])
		return -1;
	else if (table[m][2] > table[n][2])
		return 1;
	else
		return 0;
}
void init_set(Data set[], const int n) {
	for (int i = 1; i <= n; i++) {
		set[i].next = i;
		set[i].weight = 0;
	}
}

inline bool is_head(Data set[], const int vertex) {
	return set[vertex].next == vertex;
}
void change_head(Data set[], const int vertex) {
	if (set[vertex].next == vertex)
		return;
	int i = vertex;
	int last;
	Data current;
	Data temp;

	temp.next = set[i].next;
	temp.weight = set[i].weight;

	set[i].next = i;
	set[i].weight = 0;

	last = i;

	while (temp.next != i) {
		i = temp.next;
		//printf("head: %d\n", temp.weight);
		current.next = set[i].next;
		current.weight = set[i].weight;
		set[i].next = last;
		set[i].weight = temp.weight;
		temp.next = current.next;
		temp.weight = current.weight;

		last = i;
	}
}
void set_union(Data set[], const int vertex1, const int vertex2, const int weight) {
	if (is_head(set, vertex1)) {
		set[vertex1].next = vertex2;
		set[vertex1].weight = weight;
	}
	else if (is_head(set, vertex2)) {
		set[vertex2].next = vertex1;
		set[vertex2].weight = weight;
	}
	else {
		change_head(set, vertex1);
		set[vertex1].next = vertex2;
		set[vertex1].weight = weight;
	}
}
bool in_same_set(Data set[], const int vertex1, const int vertex2) {
	int i = vertex1;
	int j = vertex2;
	while (set[i].next != i)
		i = set[i].next;
	while (set[j].next != j)
		j = set[j].next;
	return i == j;
}

Pair find_non_MUST(Data set[], const int vertex1, const int vertex2, const int weight) {
	Pair result;
	result.edges = 0;
	result.weight = 0;
	int i = vertex1;
	while (set[i].next != vertex2) {
		if (set[i].weight == weight) {
			result.edges++;
			result.weight += set[i].weight;
			set[i].weight = 0;
		}
		i = set[i].next;
	}
	if (abs(set[i].weight) == weight) {
		result.edges++;
		result.weight += set[i].weight;
		set[i].weight = 0;
	}
	//printf("non-MUST: %d %d\n", result.edges, result.weight);
	return result;
}

int main(void) {
	int T;
	scanf("%d", &T);

	
	table = (int**)malloc(MAXEDGES * sizeof(int*));
	for (int i = 0; i < MAXEDGES; i++)
		table[i] = (int*)malloc(3 * sizeof(int));

	/*int **sort_pointer;
	sort_pointer = (int**)malloc(MAXEDGES * sizeof(int*));*/
	int *sorter;
	sorter = (int *)malloc(MAXEDGES * sizeof(int));

	Data *set;
	set = (Data*)malloc(MAXVERTEX * sizeof(Data));

	int n, m;
	while (T--) {
		scanf("%d%d", &n, &m);

		for (int i = 0; i < m; i++) {
			scanf("%d%d%d", &table[i][edge1], &table[i][edge2], &table[i][WEIGHT]);
			sorter[i] = i;
		}
		qsort(sorter, m, sizeof(int), sorter_comp);

		init_set(set, n);

		Pair result;
		result.edges = 0;
		result.weight = 0;

		/*for (int i = 0; i < m; i++) {
			printf("%d %d %d\n", table[sorter[i]][0], table[sorter[i]][1], table[sorter[i]][2]);
		}*/

		for (int i = 0; i < m; i++) {

			if (!in_same_set(set, table[sorter[i]][0], table[sorter[i]][1])) {
				set_union(set, table[sorter[i]][0], table[sorter[i]][1], table[sorter[i]][2]);
				result.edges++;
				result.weight += table[sorter[i]][2];
			}
			else {
				Pair temp;
				if (!is_head(set, table[sorter[i]][0]) && !is_head(set, table[sorter[i]][1]))
					change_head(set, table[sorter[i]][0]);
				if (is_head(set, table[sorter[i]][0])) {
					temp = find_non_MUST(set, table[sorter[i]][1], table[sorter[i]][0], table[sorter[i]][2]);
					result.edges -= temp.edges;
					result.weight -= temp.weight;
				}
				else {
					temp = find_non_MUST(set, table[sorter[i]][0], table[sorter[i]][1], table[sorter[i]][2]);
					result.edges -= temp.edges;
					result.weight -= temp.weight;
				}
			}
			//printf("i = %d: %d %lld\n", i, result.edges, result.weight);
		}

		printf("%d %lld\n", result.edges, result.weight);

/*
		for (int i = 0; i < m; i++) {
			printf("%d %d %d\n", sort_pointer[i][0], sort_pointer[i][1], sort_pointer[i][2]);
		}
*/
	}
	return 0;
}