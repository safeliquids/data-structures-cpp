#include "expanding_array.hpp"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

void assert_array(const ExpandingArray & ea, const std::vector<int> & reference) {
	assert(ea.size() == reference.size());
	for (size_t i = 0; i < ea.size(); ++i) {
		assert(ea.get(i) == reference[i]);
	}
}

int main() {
	ExpandingArray ea;
	ea.add(3);
	ea.add(1);
	ea.add(4);
	ea.add(1);
	ea.add(5);
	ea.add(9);
	assert_array(ea, {3, 1, 4, 1, 5, 9});
	cout << '.';

	assert(ea.take(1) == 1);
	assert_array(ea, {3, 9, 4, 1, 5});
	cout << '.';

	assert(ea.take(2) == 4);
	assert_array(ea, {3, 9, 5, 1});
	cout << '.';

	ExpandingArray ea2 = ea;
	assert_array(ea, {3, 9, 5, 1});
	assert_array(ea2, {3, 9, 5, 1});
	cout << '.';

	assert(ea.take(0) == 3);
	assert_array(ea, {1, 9, 5});
	assert_array(ea2, {3, 9, 5, 1});
	cout << '.';

	ea2.add(2);
	ea2.add(6);
	assert_array(ea, {1, 9, 5});
	assert_array(ea2, {3, 9, 5, 1, 2, 6});
	cout << '.';

	ExpandingArray ea3 = ea2;
	const char * numbers = "1234567890123456789012345678901234567890"
	                   "1234567890123456789012345678901234567890"
					   "12345678901234567890";
	vector<int> reference = {3, 9, 5, 1, 2, 6};
	for (const char * c = numbers; *c; ++c) {
		int number = (*c);
		number -= '0';
		ea3.add(number);
		reference.push_back(number);
	}
	assert_array(ea, {1, 9, 5});
	assert_array(ea2, {3, 9, 5, 1, 2, 6});
	assert_array(ea3, reference);
	cout << '.';

	ea = ea3;
	assert_array(ea, reference);
	assert_array(ea3, reference);
	cout << '.';

	assert(ea.take(0) == reference[0]);
	assert(ea.get(0) == reference.back() && ea.size() == reference.size() - 1);
	assert_array(ea3, reference);
	cout << '.';

	cout << endl;

	return 0;
}