#pragma once
#include "../template.h"

// unique_ptr without deallocation, use with bump allocator
template<typename T> struct single_ptr {
	T* x{0};

	single_ptr()                        {}
	single_ptr(nullptr_t)               {}
	single_ptr(T* v)           : x(v)   {}
	single_ptr(single_ptr&& r) : x(r.x) { r.x = 0; }

	single_ptr& operator=(nullptr_t)      { x = 0; return *this; }
	single_ptr& operator=(single_ptr&& r) { x = r.x; r.x = 0; return *this; }

	T* operator->() { return x; }
	T& operator*()  { return *x; }
	operator bool() { return x; }
};
