#pragma once
#include "../template.h"

// unique_ptr without deallocation, use with bump allocator
template<typename T> struct single_ptr {
	T* elem{0};

	single_ptr()                              {}
	single_ptr(nullptr_t)                     {}
	single_ptr(T* v)           : elem(v)      {}
	single_ptr(single_ptr&& r) : elem(r.elem) { r.elem = 0; }

	single_ptr& operator=(nullptr_t)      { elem = 0; return *this; }
	single_ptr& operator=(single_ptr&& r) { elem = r.elem; r.elem = 0; return *this; }

	T* operator->() { return elem; }
	T& operator*()  { return *elem; }
	operator bool() { return elem; }
};
