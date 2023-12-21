#include <stdexcept>
#include <cstdlib>

#include "stack.hpp"

Stack::Stack()
:
	m_data(nullptr),
	m_top(nullptr),
	m_allocated(0)
{}

Stack::Stack(const Stack & other)
:
	m_data(nullptr),
	m_top(nullptr),
	m_allocated(0)
{
	copy_from(other);
}

Stack::Stack(Stack && other)
:
	m_data(nullptr),
	m_top(nullptr),
	m_allocated(0)
{
	swap_with(std::move(other));
}

Stack::~Stack() {
	std::free(m_data);
	m_data = m_top = nullptr;
	m_allocated = 0;
}

Stack & Stack::operator=(const Stack & other) {
	if (this == &other) {
		return *this;
	}
	copy_from(other);
	return *this;
}

Stack & Stack::operator=(Stack && other) {
	if (this == &other) {
		return *this;
	}
	swap_with(std::move(other));
	return *this;
}

void Stack::add(int value) {
	if (m_allocated == 0) {
		int * new_data = (int*) std::malloc(sizeof(int) * INITIAL_SIZE);
		if (new_data == nullptr) {
			throw std::runtime_error("out of memory");
		}

		m_allocated = INITIAL_SIZE;
		m_top = m_data = new_data;
	}
	const size_t size = m_top - m_data;
	if (size == m_allocated) {
		size_t new_allocated = m_allocated * MULTIPLIER;
		int * new_data = (int*) std::realloc(m_data, sizeof(int) * new_allocated);
		if (new_data == nullptr) {
			throw std::runtime_error("out of memory");
		}
		m_data = new_data;
		m_allocated = new_allocated;
	}
	*m_top = value;
	++m_top;
}

int Stack::get() const {
	if (m_top == m_data) {
		throw std::out_of_range("stack is empty");
	}
	return *(m_top - 1);
}

bool Stack::is_empty() const {
	return m_data == m_top ? true : false;
}

int Stack::take() {
	if (m_top == m_data) {
		throw std::out_of_range("stack is empty");
	}
	--m_top;
	int top_value = *m_top;
	return top_value;
}

void Stack::copy_from(const Stack & other) {
	if (other.is_empty()) {
		m_top == m_data;
		return;
	}

	if (m_allocated < other.m_allocated) {
		int * new_data = (int*)std::realloc(m_data, sizeof(int) * other.m_allocated);
		if (!new_data) {
			throw std::runtime_error("out of memory");
		}
		m_data = new_data;
		m_allocated = other.m_allocated;
	}

	// set top to the beginning of data and populate the array with elements from other
	m_top = m_data;
	for (int * p = other.m_data; p < other.m_top; ++p) {
		*m_top = *p;
		++m_top;
	}
}

void Stack::swap_with(Stack && other) {
	std::swap(m_data, other.m_data);
	std::swap(m_top, other.m_top);
	std::swap(m_allocated, other.m_allocated);
}
