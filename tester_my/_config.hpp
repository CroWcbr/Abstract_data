#ifndef CONFIG_HPP
#define CONFIG_HPP

#define		_CXX				"/usr/bin/g++"
#define		_CXX_WALL			"-Wall"
#define		_CXX_WEXTRA			"-Wextra"
#define		_CXX_WERROR			"-Werror"
#define		_EXEC_NAME			"test_container"
#define		_CXX_STANDART_98	"-std=c++98"
#define		_CXX_STANDART_11	"-std=c++11"

#define		_VALGRIND			"/usr/bin/valgrind"
#define		_VALGRIND_FLAGS1	"--leak-check=full"
#define		_VALGRIND_FLAGS2	"--track-origins=yes"
#define		_VALGRIND_EXEC_NAME	"./test_container"

#define		_LOGS_COMPILE		"./logs_compile.txt"
#define		_LOGS_LEAKS			"./logs_leaks.txt"
#define		_LOGS_LEAKS_TMP		"./logs_leaks_tmp.txt"

#define		_MAIN_PROG			"./test/main.cpp"
#define		_DATA_FILE			"./data.txt"

#define		T_COUNT				1
#define		T_SIZE				20

#define		T_COUNT_LEAKS		10
#define		T_SIZE_LEAKS		1000


#include <vector>
#include <string>

const std::vector<std::pair<std::string, std::vector<std::string> > > _containers = 
	{
		// {"vector", 
		// 	{
		// 		"./test/containers/01_constructor_empty.hpp",
		// 		"./test/containers/02_constructor_n.hpp",
		// 		"./test/containers/03_constructor_n_value.hpp",
		// 		"./test/containers/04_constructor_iterators.hpp",
		// 		"./test/containers/05_constructor_container.hpp",
		// 		"./test/containers/06_operator=.hpp",
		// 		"./test/containers/07_assign_n_value.hpp",
		// 		"./test/containers/08_assign_iterators.hpp",
		// 		"./test/containers/09_get_allocator.hpp",

		// 		"./test/containers/10_begin.hpp",
		// 		"./test/containers/11_end.hpp",
		// 		"./test/containers/12_rbegin.hpp",
		// 		"./test/containers/13_rend.hpp",

		// 		"./test/containers/14_size.hpp",
		// 		"./test/containers/15_max_size.hpp",
		// 		"./test/containers/16_resize_n_value.hpp",
		// 		"./test/vector/01_capacity.hpp",
		// 		"./test/containers/17_empty.hpp",
		// 		"./test/vector/02_reserve.hpp",

		// 		"./test/containers/18_operator[].hpp",
		// 		"./test/containers/19_at.hpp",
		// 		"./test/containers/20_front.hpp",
		// 		"./test/containers/21_back.hpp",

		// 		"./test/containers/24_push_back.hpp",
		// 		"./test/containers/25_pop_back.hpp",
		// 		"./test/containers/27_insert_iter_value.hpp",
		// 		"./test/containers/28_insert_iter_n_value.hpp",
		// 		"./test/containers/29_insert_iter_iterators.hpp",
		// 		"./test/containers/31_erase_iter.hpp",
		// 		"./test/containers/33_erase_iterators.hpp",
		// 		"./test/containers/34_swap.hpp",
		// 		"./test/containers/35_clear.hpp",

		// 		"./test/containers/36_operator.hpp",
		// 	},
		// },
		// {"list",
		// 	{
		// 		"./test/containers/01_constructor_empty.hpp",
		// 		"./test/containers/02_constructor_n.hpp",
		// 		"./test/containers/03_constructor_n_value.hpp",
		// 		"./test/containers/04_constructor_iterators.hpp",
		// 		"./test/containers/05_constructor_container.hpp",
		// 		"./test/containers/06_operator=.hpp",
		// 		"./test/containers/07_assign_n_value.hpp",
		// 		"./test/containers/08_assign_iterators.hpp",
		// 		"./test/containers/09_get_allocator.hpp",

		// 		"./test/containers/10_begin.hpp",
		// 		"./test/containers/11_end.hpp",
		// 		"./test/containers/12_rbegin.hpp",
		// 		"./test/containers/13_rend.hpp",

		// 		"./test/containers/14_size.hpp",
		// 		"./test/containers/15_max_size.hpp",
		// 		"./test/containers/16_resize_n_value.hpp",
		// 		"./test/containers/17_empty.hpp",

		// 		"./test/containers/20_front.hpp",
		// 		"./test/containers/21_back.hpp",

		// 		"./test/containers/22_push_front.hpp",
		// 		"./test/containers/23_pop_front.hpp",
		// 		"./test/containers/24_push_back.hpp",
		// 		"./test/containers/25_pop_back.hpp",
		// 		"./test/containers/27_insert_iter_value.hpp",
		// 		"./test/containers/28_insert_iter_n_value.hpp",
		// 		"./test/containers/29_insert_iter_iterators.hpp",
		// 		"./test/containers/31_erase_iter.hpp",
		// 		"./test/containers/33_erase_iterators.hpp",
		// 		"./test/containers/34_swap.hpp",
		// 		"./test/containers/35_clear.hpp",

		// 		"./test/containers/36_operator.hpp",

		// 		"./test/list/01_splice_iter_list.hpp",
		// 		"./test/list/02_splice_iter_list_from_iter.hpp",
		// 		"./test/list/03_splice_iter_list_from_to_iter.hpp",
		// 		"./test/list/04_remove.hpp",
		// 		"./test/list/05_remove_if.hpp",
		// 		"./test/list/06_unique.hpp",
		// 		"./test/list/07_unique_pred.hpp",
		// 		"./test/list/08_merge.hpp",
		// 		"./test/list/09_merge_comp.hpp",

		// 		"./test/list/10_sort.hpp",
		// 		"./test/list/11_sort_comp.hpp",
		// 		"./test/list/12_reverse.hpp", 
		// 	},
		// },
		// {"deque", 
		// 	{
		// 		"./test/containers/01_constructor_empty.hpp",
		// 		"./test/containers/02_constructor_n.hpp",
		// 		"./test/containers/03_constructor_n_value.hpp",
		// 		"./test/containers/04_constructor_iterators.hpp",
		// 		"./test/containers/05_constructor_container.hpp",
		// 		"./test/containers/06_operator=.hpp",
		// 		"./test/containers/07_assign_n_value.hpp",
		// 		"./test/containers/08_assign_iterators.hpp",
		// 		"./test/containers/09_get_allocator.hpp",

		// 		"./test/containers/10_begin.hpp", 
		// 		"./test/containers/11_end.hpp",
		// 		"./test/containers/12_rbegin.hpp",
		// 		"./test/containers/13_rend.hpp",

		// 		"./test/containers/14_size.hpp",
		// 		"./test/containers/15_max_size.hpp",
		// 		"./test/containers/16_resize_n_value.hpp",
		// 		"./test/containers/17_empty.hpp",

		// 		"./test/containers/18_operator[].hpp",
		// 		"./test/containers/19_at.hpp",
		// 		"./test/containers/20_front.hpp",
		// 		"./test/containers/21_back.hpp",

		// 		"./test/containers/22_push_front.hpp",
		// 		"./test/containers/23_pop_front.hpp",
		// 		"./test/containers/24_push_back.hpp",
		// 		"./test/containers/25_pop_back.hpp",
		// 		"./test/containers/27_insert_iter_value.hpp",
		// 		"./test/containers/28_insert_iter_n_value.hpp",
		// 		"./test/containers/29_insert_iter_iterators.hpp",
		// 		"./test/containers/31_erase_iter.hpp",
		// 		"./test/containers/33_erase_iterators.hpp",
		// 		"./test/containers/34_swap.hpp",
		// 		"./test/containers/35_clear.hpp",

		// 		"./test/containers/36_operator.hpp",
		// 	},
		// },
		{"set", 
			{
				// "./test/containers/01_constructor_empty.hpp",
				// "./test/containers/04_constructor_iterators.hpp",
				// "./test/containers/05_constructor_container.hpp",
				// "./test/containers/06_operator=.hpp",
				// "./test/containers/09_get_allocator.hpp",

				// "./test/containers/10_begin.hpp",
				// "./test/containers/11_end.hpp",
				// "./test/containers/12_rbegin.hpp",
				// "./test/containers/13_rend.hpp",

				// "./test/containers/14_size.hpp",
				// "./test/containers/15_max_size.hpp",
				// "./test/containers/17_empty.hpp",

				// "./test/containers/26_insert_value.hpp",
				// "./test/containers/27_insert_iter_value.hpp",
				// "./test/containers/30_insert_iterators.hpp",
				// "./test/containers/31_erase_iter.hpp",
				// "./test/containers/32_erase_value.hpp",
				// "./test/containers/33_erase_iterators.hpp",
				// "./test/containers/34_swap.hpp",
				// "./test/containers/35_clear.hpp",

				// "./test/containers/36_operator.hpp",

				// "./test/map_set/01_key_compare.hpp",
				// "./test/map_set/02_value_compare.hpp",

				// "./test/map_set/03_find.hpp",
				// "./test/map_set/04_count.hpp",
				// "./test/map_set/05_lower_bound.hpp",
				// "./test/map_set/06_upper_bound.hpp",
				// "./test/map_set/07_equal_range.hpp",
			},
		},
		{"multiset", 
			{
		// 		"./test/containers/01_constructor_empty.hpp",
		// 		"./test/containers/04_constructor_iterators.hpp",
		// 		"./test/containers/05_constructor_container.hpp",
		// 		"./test/containers/06_operator=.hpp",
		// 		"./test/containers/09_get_allocator.hpp",

		// 		"./test/containers/10_begin.hpp",
		// 		"./test/containers/11_end.hpp",
		// 		"./test/containers/12_rbegin.hpp",
		// 		"./test/containers/13_rend.hpp",

		// 		"./test/containers/14_size.hpp",
				// "./test/containers/15_max_size.hpp",
		// 		"./test/containers/17_empty.hpp",

		// 		"./test/containers/26_insert_value.hpp",
		// 		"./test/containers/27_insert_iter_value.hpp",
		// 		"./test/containers/30_insert_iterators.hpp",
		// 		"./test/containers/31_erase_iter.hpp",
		// 		"./test/containers/32_erase_value.hpp",
		// 		"./test/containers/33_erase_iterators.hpp",
		// 		"./test/containers/34_swap.hpp",
		// 		"./test/containers/35_clear.hpp",

		// 		"./test/containers/36_operator.hpp",

		// 		"./test/map_set/01_key_compare.hpp",
		// 		"./test/map_set/02_value_compare.hpp",

		// 		"./test/map_set/03_find.hpp",
		// 		"./test/map_set/04_count.hpp",
		// 		"./test/map_set/05_lower_bound.hpp",
		// 		"./test/map_set/06_upper_bound.hpp",
		// 		"./test/map_set/07_equal_range.hpp",
			},
		},
		{"map", 
			{
		// 		"./test/containers/01_constructor_empty.hpp",
		// 		"./test/containers/04_constructor_iterators.hpp",
		// 		"./test/containers/05_constructor_container.hpp",
		// 		"./test/containers/06_operator=.hpp",
		// 		"./test/containers/09_get_allocator.hpp",

		// 		"./test/containers/10_begin.hpp",
		// 		"./test/containers/11_end.hpp",
		// 		"./test/containers/12_rbegin.hpp",
		// 		"./test/containers/13_rend.hpp",

		// 		"./test/containers/14_size.hpp",
				// "./test/containers/15_max_size.hpp",
		// 		"./test/containers/17_empty.hpp",

		// 		"./test/containers/18_operator[].hpp",

		// 		"./test/containers/26_insert_value.hpp",
		// 		"./test/containers/27_insert_iter_value.hpp",
		// 		"./test/containers/30_insert_iterators.hpp",
		// 		"./test/containers/31_erase_iter.hpp",
		// 		"./test/containers/32_erase_value.hpp",
		// 		"./test/containers/33_erase_iterators.hpp",
		// 		"./test/containers/34_swap.hpp",
		// 		"./test/containers/35_clear.hpp",

		// 		"./test/containers/36_operator.hpp",

		// 		"./test/map_set/01_key_compare.hpp",
		// 		"./test/map_set/02_value_compare.hpp",

		// 		"./test/map_set/03_find.hpp",
		// 		"./test/map_set/04_count.hpp",
		// 		"./test/map_set/05_lower_bound.hpp",
		// 		"./test/map_set/06_upper_bound.hpp",
		// 		"./test/map_set/07_equal_range.hpp",
			},
		},
		{"multimap", 
			{
		// 		"./test/containers/01_constructor_empty.hpp",
		// 		"./test/containers/04_constructor_iterators.hpp",
		// 		"./test/containers/05_constructor_container.hpp",
		// 		"./test/containers/06_operator=.hpp",
		// 		"./test/containers/09_get_allocator.hpp",

		// 		"./test/containers/10_begin.hpp",
		// 		"./test/containers/11_end.hpp",
		// 		"./test/containers/12_rbegin.hpp",
		// 		"./test/containers/13_rend.hpp",

		// 		"./test/containers/14_size.hpp",
				// "./test/containers/15_max_size.hpp",
		// 		"./test/containers/17_empty.hpp",

		// 		"./test/containers/26_insert_value.hpp",
		// 		"./test/containers/27_insert_iter_value.hpp",
		// 		"./test/containers/30_insert_iterators.hpp",
		// 		"./test/containers/31_erase_iter.hpp",
		// 		"./test/containers/32_erase_value.hpp",
		// 		"./test/containers/33_erase_iterators.hpp",
		// 		"./test/containers/34_swap.hpp",
		// 		"./test/containers/35_clear.hpp",

		// 		"./test/containers/36_operator.hpp",

		// 		"./test/map_set/01_key_compare.hpp",
		// 		"./test/map_set/02_value_compare.hpp",

		// 		"./test/map_set/03_find.hpp",
		// 		"./test/map_set/04_count.hpp",
		// 		"./test/map_set/05_lower_bound.hpp",
		// 		"./test/map_set/06_upper_bound.hpp",
		// 		"./test/map_set/07_equal_range.hpp",
			},
		},
		// {"stack", 
		// 	{
		// 		"./test/containers/01_constructor_empty.hpp",

		// 		"./test/containers/14_size.hpp",
		// 		"./test/containers/17_empty.hpp",

		// 		"./test/stack_queue/01_top.hpp",

		// 		"./test/stack_queue/02_push.hpp",
		// 		"./test/stack_queue/03_pop.hpp",

		// 		"./test/containers/36_operator.hpp",
		// 	},
		// },
		// {"queue", 
		// 	{
		// 		"./test/containers/01_constructor_empty.hpp",

		// 		"./test/containers/14_size.hpp",
		// 		"./test/containers/17_empty.hpp",

		// 		"./test/containers/20_front.hpp",
		// 		"./test/containers/21_back.hpp",
	
		// 		"./test/stack_queue/02_push.hpp",
		// 		"./test/stack_queue/03_pop.hpp",

		// 		"./test/containers/36_operator.hpp",
		// 	},
		// },
		// {"priority_queue", 
		// 	{
		// 		"./test/containers/01_constructor_empty.hpp",
		// 		"./test/containers/04_constructor_iterators.hpp",

		// 		"./test/containers/14_size.hpp",
		// 		"./test/containers/17_empty.hpp",
			
		// 		"./test/stack_queue/01_top.hpp",

		// 		"./test/stack_queue/02_push.hpp",
		// 		"./test/stack_queue/03_pop.hpp",
		// 	},
		// },
		{"unordered_set",
			{
				"./test/unordered/01_constructor_empty.hpp",
				"./test/unordered/04_constructor_iterators.hpp",
				"./test/unordered/05_constructor_container.hpp",
				"./test/unordered/06_operator=.hpp",
				"./test/unordered/09_get_allocator.hpp",

				"./test/unordered/14_size.hpp",
				"./test/unordered/15_max_size.hpp",
				"./test/unordered/17_empty.hpp",

				"./test/unordered/26_insert_value.hpp",
				"./test/unordered/27_insert_iter_value.hpp",
				"./test/unordered/30_insert_iterators.hpp",
				"./test/unordered/31_erase_iter.hpp",
				"./test/unordered/32_erase_value.hpp",
				"./test/unordered/33_erase_iterators.hpp",		// different structure
				"./test/unordered/34_swap.hpp",
				"./test/unordered/35_clear.hpp",

				"./test/unordered/36_operator.hpp",

				"./test/unordered/51_key_compare.hpp",
				"./test/unordered/52_find.hpp",
				"./test/unordered/53_count.hpp",
				"./test/unordered/54_equal_range.hpp",
			},
		},
		{"unordered_multiset",
			{
				"./test/unordered/01_constructor_empty.hpp",
				"./test/unordered/04_constructor_iterators.hpp",
				"./test/unordered/05_constructor_container.hpp",
				"./test/unordered/06_operator=.hpp",
				"./test/unordered/09_get_allocator.hpp",

				"./test/unordered/14_size.hpp",
				"./test/unordered/15_max_size.hpp",
				"./test/unordered/17_empty.hpp",

				"./test/unordered/26_insert_value.hpp",
				"./test/unordered/27_insert_iter_value.hpp",
				"./test/unordered/30_insert_iterators.hpp",
				"./test/unordered/31_erase_iter.hpp",
				"./test/unordered/32_erase_value.hpp",
				"./test/unordered/33_erase_iterators.hpp",		// different structure
				"./test/unordered/34_swap.hpp",
				"./test/unordered/35_clear.hpp",

				"./test/unordered/36_operator.hpp",

				"./test/unordered/51_key_compare.hpp",
				"./test/unordered/52_find.hpp",
				"./test/unordered/53_count.hpp",
				"./test/unordered/54_equal_range.hpp",
			},
		},
		{"unordered_map",
			{
				"./test/unordered/01_constructor_empty.hpp",
				"./test/unordered/04_constructor_iterators.hpp",
				"./test/unordered/05_constructor_container.hpp",
				"./test/unordered/06_operator=.hpp",
				"./test/unordered/09_get_allocator.hpp",

				"./test/unordered/14_size.hpp",
				"./test/unordered/15_max_size.hpp",
				"./test/unordered/17_empty.hpp",

				"./test/unordered/26_insert_value.hpp",
				"./test/unordered/27_insert_iter_value.hpp",
				"./test/unordered/30_insert_iterators.hpp",
				"./test/unordered/31_erase_iter.hpp",
				"./test/unordered/32_erase_value.hpp",
				"./test/unordered/33_erase_iterators.hpp",		// different structure
				"./test/unordered/34_swap.hpp",
				"./test/unordered/35_clear.hpp",

				"./test/unordered/36_operator.hpp",

				"./test/unordered/51_key_compare.hpp",
				"./test/unordered/52_find.hpp",
				"./test/unordered/53_count.hpp",
				"./test/unordered/54_equal_range.hpp",
			},
		},
		{"unordered_multimap",
			{
				"./test/unordered/01_constructor_empty.hpp",
				"./test/unordered/04_constructor_iterators.hpp",
				"./test/unordered/05_constructor_container.hpp",
				"./test/unordered/06_operator=.hpp",
				"./test/unordered/09_get_allocator.hpp",

				"./test/unordered/14_size.hpp",
				"./test/unordered/15_max_size.hpp",
				"./test/unordered/17_empty.hpp",

				"./test/unordered/26_insert_value.hpp",
				"./test/unordered/27_insert_iter_value.hpp",
				"./test/unordered/30_insert_iterators.hpp",
				"./test/unordered/31_erase_iter.hpp",
				"./test/unordered/32_erase_value.hpp",
				"./test/unordered/33_erase_iterators.hpp",		// different structure
				"./test/unordered/34_swap.hpp",
				"./test/unordered/35_clear.hpp",

				"./test/unordered/36_operator.hpp",

				"./test/unordered/51_key_compare.hpp",
				"./test/unordered/52_find.hpp",
				"./test/unordered/53_count.hpp",
				"./test/unordered/54_equal_range.hpp",
			},
		},
	};

#endif
