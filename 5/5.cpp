#include <cstdio>

#include <vector>

typedef char type;

using namespace std;


void minimum_s(int c, std::vector<type> &array) {
	array.clear();
	while (c > 0) {
		if (c >= 9) {
			array.push_back(9);
			c -= 9;
		}
		else {
			array.push_back(c);
			c = 0;
		}
	}
}
bool islarger(std::vector<type> a, std::vector<type> b) {
	if (a.size() > b.size())
		return true;
	else if (a.size() < b.size())
		return false;
	else {
		for (int i = a.size() - 1; i >= 0; i--) {
			if (a[i] > b[i])
				return true;
			else if (a[i] < b[i])
				return false;
		}
		return false;
	}
}

void fill(std::vector<type> &current, std::vector<type> last, int c) {
	int temp = c;
	current.clear();
	current.resize(last.size() + 1);
	current[last.size()] = 0;

	int flag = 0;

	for (int i = last.size() - 1; i >= 0; i--) {
		if (temp > last[i]) {
			current[i] = last[i];
			temp -= last[i];
		}
		else {
			flag = 1;
			int j = i + 1;
			current[j]++;
			temp--;
			while (current[j] > 9) {
				current[j] = 0;
				temp += 10;
				j++;
				current[j]++;
				temp--;
			}
			for (; i >= 0; i--) {
				current[i] = 0;
			}
		}
	}
	if (current[last.size()] == 0)
		current.pop_back();
	if (flag == 0) {
		int k = 0;
		while (temp > 0) {
			if (temp >= 9 - current[k]) {
				temp -= (9 - current[k]);
				current[k] = 9;
				k++;
			}
			else {
				current[k] += temp;
				temp = 0;
				k++;
			}
		}
	}
	else {
		int k = 0;
		while (temp > 0) {
			if (temp >= 9) {
				current[k] = 9;
				temp -= 9;
			}
			else {
				current[k] = temp;
				temp = 0;
			}
			k++;
		}
	}
}

int main() {
	int T;
	int n;
	int c;
	std::vector<type> last;
	std::vector<type> current;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		last.clear();
		last.push_back(0);
		while (n--) {
			scanf("%d", &c);
			minimum_s(c, current);
			if (islarger(current, last)) {
				for (int i = current.size() - 1; i >= 0; i--)
					printf("%d", current[i]);
				last = current;
			}
			else {
				fill(current, last, c);
				for (int i = current.size() - 1; i >= 0; i--)
					printf("%d", current[i]);
				last = current;
			}
			if (n > 0)
				printf(" ");
			else
				printf("\n");
		}
	}

}