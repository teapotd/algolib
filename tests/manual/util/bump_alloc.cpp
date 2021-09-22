#include "../../../src/util/bump_alloc.h"
#include "../../../src/template.h"
#include "../testing.h"

int main() {
	constexpr int MAX_MEM = 220 * 1024 * 1024;

	printf("alloc\n");
	auto start = now();

	vector<char*> elems;
	size_t xMem = 0;

	while (xMem < MAX_MEM) {
		size_t i = elems.size();
		size_t n = i % 64;
		char* elem = new char[n];

		for (size_t j = 0; j < n; j++) {
			elem[j] = char(i % 251);
		}

		elems.push_back(elem);
		xMem += n;
	}

	printf("check %dms (%lu)\n", since(start), elems.size());
	start = now();

	for (size_t i = 0; i < elems.size(); i++) {
		size_t n = i % 64;

		for (size_t j = 0; j < n; j++) {
			assert(elems[i][j] == char(i % 251));
		}
	}

	printf("free %dms\n", since(start));
	start = now();

	for (char* e : elems) {
		delete[] e;
	}

	printf("finish %dms\n", since(start));
	return 0;
}
