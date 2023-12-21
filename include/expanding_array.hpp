#ifndef EXPANDING_ARRAY_HPP
#define EXPANDING_ARRAY_HPP

#include <cstddef>

class ExpandingArray{
public:
	ExpandingArray();
	ExpandingArray(const ExpandingArray & other);
	ExpandingArray(ExpandingArray && other);
	~ExpandingArray();
	ExpandingArray & operator=(const ExpandingArray & other);
	ExpandingArray & operator=(ExpandingArray && other);

	void add(int value);
	int get(size_t i) const;
	int set(size_t i, int value);
	size_t size() const;
	int take(size_t i);

private:
	int * m_elements;
	size_t m_size;
	size_t m_allocated;
	static const size_t INITIAL_SIZE = 4;
	static const size_t MULTIPLIER = 2;

	void expand_buffer(size_t new_size);
	void populate_from(const ExpandingArray & other);
	void swap_data_with(ExpandingArray && other);
};

#endif
