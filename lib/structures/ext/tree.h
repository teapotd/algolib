#pragma once
#include "../../template.h"

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<class T, class Cmp = less<T>>
using ordered_set = tree<
	T, null_type, Cmp, rb_tree_tag,
	tree_order_statistics_node_update
>;
