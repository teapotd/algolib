#pragma once
#include "../../template.h"

#include <ext/pb_ds/priority_queue.hpp>
// Pairing heap: push O(1), pop O(lg n)
//   __gnu_pbds::priority_queue<T, Cmp>

// Standard priority_queue methods and:
// 1. Iterable
// 2. t.erase(iterator)                 O(lg n)
// 3. t.modify(iterator, value)         O(lg n)
// 4. t1.join(t2) - merge t2 into t1    O(1)
