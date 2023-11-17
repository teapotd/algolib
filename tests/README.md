# Test coverage

|                                    | deterministic | fuzz    | benchmark | yosupo  |
|------------------------------------|:-------------:|:-------:|:---------:|:-------:|
| geo2d/convex_hull                  |               | &check; |  &check;  |         |
| geo2d/halfplanes                   |    &check;    | &check; |  &check;  |         |
| geo2d/line                         |    &check;    |         |           |         |
| geo2d/minkowski                    |               | &check; |           |         |
| geo2d/rmst                         |    &check;    | &check; |  &check;  | &check; |
| geo2d/segment                      |               | &check; |           |         |
| geo2d/vector                       |    &check;    | &check; |           |         |
| graphs/2sat                        |               | &check; |           | &check; |
| graphs/bellman_ineq                |               |         |           |         |
| graphs/biconnected                 |               |         |           |         |
| graphs/bridges_online              |               | &check; |  &check;  |         |
| graphs/dense_dfs                   |               |         |           |         |
| graphs/directed_mst                |               |         |           | &check; |
| graphs/dominators                  |               |         |           | &check; |
| graphs/edge_color_bipart           |               |         |           | &check; |
| graphs/edge_color_vizing           |               |         |           |         |
| graphs/flow_edmonds_karp           |               |         |           |         |
| graphs/flow_min_cost               |               | &check; |           |         |
| graphs/flow_push_relabel           |               |         |           |         |
| graphs/flow_with_demands           |               |         |           |         |
| graphs/global_min_cut              |               | &check; |           |         |
| graphs/gomory_hu                   |               | &check; |           |         |
| graphs/kth_shortest                |               |         |           | &check; |
| graphs/matching_blossom            |               |         |           | &check; |
| graphs/matching_blossom_w          |               |         |           | &check; |
| graphs/matching_boski              |               |         |           | &check; |
| graphs/matching_turbo              |               |         |           | &check; |
| graphs/matching_weighted           |               | &check; |           | &check; |
| graphs/matroids                    |               |         |           |         |
| graphs/spfa                        |               | &check; |           | &check; |
| graphs/strongly_connected          |               | &check; |           | &check; |
| math/berlekamp_massey              |               |         |           | &check; |
| math/bit_gauss                     |               |         |           |         |
| math/bit_matrix                    |               |         |           |         |
| math/crt                           |               |         |           |         |
| math/fft_complex                   |               |         |           |         |
| math/fft_mod                       |               |         |           | &check; |
| math/fft_online                    |    &check;    |         |  &check;  |         |
| math/fwht                          |               |         |           | &check; |
| math/gauss                         |               |         |           |         |
| math/gauss_ortho                   |               |         |           |         |
| math/linear_rec                    |               |         |           | &check; |
| math/linear_rec_fast               |               |         |           | &check; |
| math/matrix                        |               |         |           |         |
| math/miller_rabin                  |               |         |           |         |
| math/modinv_precompute             |               |         |           |         |
| math/modular                       |               |         |           |         |
| math/modular64                     |               |         |           |         |
| math/modular_generator             |               |         |           |         |
| math/modular_log                   |               |         |           |         |
| math/modular_sqrt                  |               |         |           | &check; |
| math/montgomery                    |               |         |           |         |
| math/nimber                        |               |         |           | &check; |
| math/phi_large                     |               |         |           |         |
| math/phi_precompute                |               |         |           |         |
| math/phi_prefix_sum                |               |         |           | &check; |
| math/pi_large                      |               |         |           | &check; |
| math/pi_large_precomp              |               |         |           | &check; |
| math/pollard_rho                   |               |         |           | &check; |
| math/polynomial                    |               |         |           | &check; |
| math/polynomial_interp             |               |         |           |         |
| math/sieve                         |               |         |           |         |
| math/sieve_factors                 |               |         |           |         |
| math/sieve_segmented               |               |         |           |         |
| math/simplex                       |               |         |           |         |
| math/subset_sum                    |               |         |           | &check; |
| math/subset_sum_mod                |               |         |           |         |
| segtree/general_config: TREE_PLUS  |               | &check; |           |         |
| segtree/general_config: TREE_MAX   |               | &check; |           |         |
| segtree/general_config: TREE_SET   |               | &check; |           |         |
| segtree/general_config: TREE_BEATS |               | &check; |           |         |
| segtree/general_fixed              |    &check;    | &check; |           |         |
| segtree/general_persistent         |    &check;    | &check; |           |         |
| segtree/point_fixed                |    &check;    | &check; |           |         |
| segtree/point_persistent           |    &check;    | &check; |           |         |
| structures/bitset_plus             |               |         |           |         |
| structures/ext/rope                |               |         |           |         |
| structures/ext/tree                |               |         |           |         |
| structures/ext/hash_table          |               |         |           |         |
| structures/ext/heap                |               |         |           |         |
| structures/ext/trie                |               |         |           |         |
| structures/fenwick_tree            |               |         |           |         |
| structures/fenwick_tree_2d         |               |         |           |         |
| structures/find_union              |               |         |           |         |
| structures/find_union_undo         |               |         |           |         |
| structures/hull_offline            |               |         |           |         |
| structures/hull_online             |               |         |           |         |
| structures/intset                  |               |         |  &check;  | &check; |
| structures/li_chao_tree            |               |         |           |         |
| structures/max_queue               |               |         |           |         |
| structures/rmq                     |               |         |           |         |
| structures/treap                   |               |         |           |         |
| structures/wavelet_tree            |               |         |           |         |
| text/aho_corasick                  |               |         |           |         |
| text/alcs                          |               |         |           | &check; |
| text/hashing                       |    &check;    | &check; |           |         |
| text/kmp                           |               |         |           |         |
| text/kmr                           |               |         |           | &check; |
| text/lcp                           |               |         |           |         |
| text/lyndon_factorization          |               |         |           |         |
| text/main_lorentz                  |               |         |           |         |
| text/manacher                      |               |         |           | &check; |
| text/min_rotation                  |               |         |           |         |
| text/monge                         |               |         |           | &check; |
| text/palindromic_tree              |               |         |           |         |
| text/suffix_array_linear           |               |         |           | &check; |
| text/suffix_automaton              |               |         |           | &check; |
| text/suffix_tree                   |               |         |           |         |
| text/z_function                    |               |         |           | &check; |
| trees/centroid_decomp              |               |         |           |         |
| trees/centroid_offline             |               |         |           |         |
| trees/heavylight_decomp            |               |         |           |         |
| trees/lca                          |               |         |           | &check; |
| trees/lca_linear                   |               |         |           | &check; |
| trees/link_cut_tree                |               |         |           |         |
| util/arc_interval_cover            |               |         |           |         |
| util/bit_hacks                     |               |         |           |         |
| util/bump_alloc                    |               |         |           |         |
| util/compress_vec                  |               |         |           |         |
| util/deque_undo                    |               |         |           |         |
| util/inversion_vector              |               |         |           |         |
| util/longest_inc_subseq            |               |         |           |         |
| util/max_rects                     |               |         |           |         |
| util/mo                            |               |         |           |         |
| util/packing                       |               |         |           |         |
| util/parallel_binsearch            |               |         |           |         |
| util/radix_sort                    |               |         |           |         |
