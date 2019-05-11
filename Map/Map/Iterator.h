#pragma once
#include <cstddef>

template <class T, class G>
class Iterator
{
public:
	virtual G operator*() const = 0;
	virtual void operator++(int) = 0;
	virtual bool operator==(const nullptr_t) const = 0;
	virtual bool operator!=(const nullptr_t) const = 0;
	virtual T current_key() = 0;
	virtual bool current_color() = 0;
};