#pragma once

#include <utility>

// unique_ptr without custom deleter

// as of C++20 and 23, to make code constexpr you...
// ... just add constexpr to it.

// if the code is in a header...
// ... just make it constexpr!!!

// you need to make your core libraries constexpr
// ... so that the users can find the constexpr usecases!
template <typename Contained>
class unique_ptr {
public:
	constexpr void reset() {
		delete m_data;
		m_data = nullptr;
	}

	constexpr unique_ptr() = default;
	constexpr ~unique_ptr() { reset(); }
	constexpr unique_ptr(Contained *data) : m_data(data) {}

	// move operations
	constexpr unique_ptr(unique_ptr &&other) : m_data(std::exchange(other.data, nullptr)) {}
	constexpr unique_ptr& operator=(unique_ptr&& other) {
		reset();
		data = std::exchange(other.data, nullptr);
	}

	// copy operations are deleted
	unique_ptr(const unique_ptr&) = delete;
	unique_ptr& operator=(const unique_ptr&) = delete;

private:
	Contained *m_data = nullptr;
};

constexpr void myfunc()
{
	unique_ptr<int> data(new int());
}

