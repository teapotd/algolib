#pragma once
#include "../template.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/trie_policy.hpp>

using namespace __gnu_pbds;

// Trie with prefix search
using pref_trie = trie<string, null_type, trie_string_access_traits<>,
                       pat_trie_tag, trie_prefix_search_node_update>;
