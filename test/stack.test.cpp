#include <iostream>
#include <cassert>

#include "stack.hpp"

using namespace std;

int main() {
	Stack s1;
	s1.add(1);
	s1.add(10);
	assert(s1.get() == 10);
	assert(s1.take() == 10);
	cout << '.';
	assert(s1.get() == 1);
	assert(s1.take() == 1);

	s1.add(2);
	assert(s1.get() == 2);
	Stack s2 = s1;
	assert(s2.take() == 2);
	assert(s1.get() == 2);
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
	cout << endl;
	
	return 0;
}