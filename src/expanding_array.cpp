#include <cstdlib>
#include <stdexcept>
#include <utility>

#include "expanding_array.hpp"

ExpandingArray::ExpandingArray() 
:
	m_elements(nullptr),
	m_size(0u),
	m_allocated(0u)
{}

ExpandingArray::ExpandingArray(const ExpandingArray & other)
:
	m_elements(nullptr),
	m_size(0),
	m_allocated(0)
{
	if (other.m_size == 0) {
		return;
	}
	m_size = other.m_size;
	m_allocated = other.m_allocated;
	m_elements = (int*)std::malloc(sizeof(int) * m_allocated);
	for (size_t i = 0; i < m_size; ++i) {
		m_elements[i] = other.m_elements[i];
	}
}

ExpandingArray::ExpandingArray(ExpandingArray && other)
:
	m_elements(nullptr),
	m_size(0u),
	m_allocated(0u)
{
	std::swap(m_elements, other.m_elements);
	std::swap(m_size, other.m_size);
	std::swap(m_allocated, other.m_allocated);
}

ExpandingArray::~ExpandingArray() {
	std::free(m_elements);
	m_elements = nullptr;
	m_size = m_allocated = 0u;
}

ExpandingArray & ExpandingArray::operator=(ExpandingArray other) {
	if (this == &other) {
		return *this;
	}
	std::swap(m_elements, other.m_elements);
	std::swap(m_size, other.m_size);
	std::swap(m_allocated, other.m_allocated);
	return *this;
}

void ExpandingArray::add(int value) {
	if (m_elements == nullptr) {
		m_elements = (int*) std::malloc(sizeof(int) * INITIAL_SIZE);
		if (!m_elements) {
			throw std::runtime_error("out of memory");
		}
		m_allocated = INITIAL_SIZE;
		m_size = 0u;
	}
	if (m_size == m_allocated) {
		size_t new_allocated = m_allocated * MULTIPLIER;
		int * new_elements = (int*) std::realloc(m_elements, sizeof(int) * new_allocated);
		if (!new_elements) {
			throw std::runtime_error("out of memory");
		}
		m_allocated = new_allocated;
		m_elements = new_elements;
	}
	m_elements[m_size++] = value;
}

int ExpandingArray::get(size_t i) const {
	if (i >= m_size) {
		throw std::out_of_range("index out of range");
	}
	return m_elements[i];
}

int ExpandingArray::set(size_t i, int value) {
	if (i >= m_size) {
		throw std::out_of_range("index out of range");
	}
	int old_value = m_elements[i];
	m_elements[i] = value;
	return old_value;
}

size_t ExpandingArray::size() const {
	return m_size;
}

int ExpandingArray::take(size_t i) {
	if (i >= m_size) {
		throw std::out_of_range("index out of range");
	}
	int old_value = m_elements[i];
	// replace value at index i with the last element
	m_elements[i] = m_elements[m_size - 1];
	--m_size;
	// return value that used to be at index i
	return old_value;
}