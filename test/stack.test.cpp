#include <iostream>
#include <cassert>
#include <vector>

#include "stack.hpp"

using namespace std;

int main() {
	Stack s0;
	assert(s0.is_empty());
	cout << '.';

	Stack s1;
	s1.add(1);
	s1.add(10);
	assert(!s1.is_empty());
	assert(s1.get() == 10);
	assert(s1.take() == 10);
	cout << '.';

	assert(!s1.is_empty());
	assert(s1.get() == 1);
	assert(s1.take() == 1);
	assert(s1.is_empty());
	s1.add(2);
	assert(s1.get() == 2);
	Stack s2 = s1;
	assert(s2.take() == 2);
	assert(s1.get() == 2);
	assert(s2.is_empty());
	assert(!s1.is_empty());
	cout << '.';

	Stack s3;
	s3.add(1);
	s3.add(2);
	s3.add(3);
	s3.add(4);
	assert(s3.get() == 4);
	assert(s3.get() == 4);
	assert(s3.get() == 4);
	assert(s3.take() == 4);
	
	assert(s3.get() == 3);
	assert(s3.get() == 3);
	assert(s3.get() == 3);
	assert(s3.take() == 3);
	
	assert(s3.get() == 2);
	assert(s3.get() == 2);
	assert(s3.get() == 2);
	assert(s3.take() == 2);
	
	assert(s3.get() == 1);
	assert(s3.get() == 1);
	assert(s3.get() == 1);
	assert(s3.take() == 1);

	try {
		s3.take();
		assert(nullptr == "stack should be empty");
	}
	catch (out_of_range) {
		assert(true);
	}
	cout << '.';
	
	Stack s4;
	std::vector<int> numbers = {1, 2, 3, 11, 55, 2, 69, 420, 0, -1, 100, -3333, 3333, -333, 333, 14, 15, 16, 17, 18, 19};
	for (int n: numbers) {
		s4.add(n);
	}
	Stack s5;
	s5.add(1);
	s5 = s4;
	const int top_of_s5 = s5.get();
	for (decltype(numbers)::const_reverse_iterator it = numbers.crend(); it < numbers.crbegin(); ) {
		++it;
		assert(s4.take() == *it);
		assert(s5.get() == top_of_s5);
	}
	for (decltype(numbers)::const_reverse_iterator it = numbers.crend(); it < numbers.crbegin(); ) {
		++it;
		assert(s5.take() == *it);
		assert(s4.is_empty());
	}
	cout << endl;
	
	return 0;
}