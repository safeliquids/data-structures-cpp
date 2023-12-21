#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef>

class Stack {
public:
	Stack();
	Stack(const Stack & other);
	Stack(Stack && other);
	~Stack();
	Stack & operator=(Stack other);

	void add(int value);
	int take();
	int get() const;
	bool is_empty() const;
	
private:
	int* m_data;
	int* m_top;
	size_t m_allocated;
	static const size_t INITIAL_SIZE = 16;
	static const size_t MULTIPLIER = 2;
};

#endif