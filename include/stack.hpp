#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef>

class Stack {
public:
	Stack();
	Stack(const Stack & other);
	Stack(Stack && other);
	~Stack();
	Stack & operator=(const Stack & other);
	Stack & operator=(Stack && other);

	void add(int value);
	int get() const;
	bool is_empty() const;
	int take();

private:
	int* m_data;         // start of data array
	int* m_top;          // pointer to a data element after the last one stored
	                     // (same as m_data if empty)
	size_t m_allocated;  // number of integers stored in the stack
	static const size_t INITIAL_SIZE = 4;
	static const size_t MULTIPLIER = 2;

	void copy_from(const Stack & other);
	void resize_data(size_t new_size);
	void swap_with(Stack && other);
};

#endif