#ifndef CONFIG_HPP
#define CONFIG_HPP

#define		_CXX				"/usr/bin/g++"
#define		_CXX_WALL			"-Wall"
#define		_CXX_WEXTRA			"-Wextra"
#define		_CXX_WERROR			"-Werror"
#define		_EXEC_NAME			"test_container"
#define		_CXX_STANDART		"-std=c++98"

#define		_VALGRIND			"/usr/bin/valgrind"
#define		_VALGRIND_FLAGS1	"--leak-check=full"
#define		_VALGRIND_FLAGS2	"--track-origins=yes"
#define		_VALGRIND_EXEC_NAME	"./test_container"

#define		_LOGS_COMPILE		"./logs_compile.txt"
#define		_LOGS_LEAKS			"./logs_leaks.txt"
#define		_LOGS_LEAKS_TMP		"./logs_leaks_tmp.txt"

#define		_MAIN_PROG			"./test/main.cpp"
#define		_DATA_FILE			"./data.txt"
#define		T_COUNT				1000
#define		T_SIZE				100

#include <vector>
#include <string>

const std::vector<std::pair<std::string, std::vector<std::string> > > _containers = 
	{
		{"vector", 
			{
				// "./test/containers/01_constructor_empty.hpp",
				// "./test/containers/02_constructor_n.hpp",
				// "./test/containers/03_constructor_n_value.hpp",
				// "./test/containers/04_constructor_iterators.hpp",
				// "./test/containers/05_constructor_container.hpp",
				// "./test/containers/06_operator=.hpp",
				// "./test/containers/07_assign_n_value.hpp",
				// "./test/containers/08_assign_iterators.hpp",
				// "./test/containers/09_get_allocator.hpp",

				// "./test/containers/10_begin.hpp",
				// "./test/containers/11_end.hpp",
				// "./test/containers/12_rbegin.hpp",
				// "./test/containers/13_rend.hpp",

				// "./test/containers/14_size.hpp",
				// "./test/containers/15_max_size.hpp",
				// "./test/containers/16_resize_n_value.hpp",
				// "./test/vector/01_capacity.hpp",
				// "./test/containers/17_empty.hpp",
				// "./test/vector/02_reserve.hpp",

				// "./test/containers/18_operator[].hpp",
				// "./test/containers/19_at.hpp",
				// "./test/containers/20_front.hpp",
				// "./test/containers/21_back.hpp",

				// "./test/containers/24_push_back.hpp",
				// "./test/containers/25_pop_back.hpp",
				// "./test/containers/27_insert_iter_value.hpp",
				// "./test/containers/28_insert_iter_n_value.hpp",
				// "./test/containers/29_insert_iter_iterators.hpp",
				// "./test/containers/31_erase_iter.hpp",
				// "./test/containers/33_erase_iterators.hpp",
				// "./test/containers/34_swap.hpp",
				// "./test/containers/35_clear.hpp",

				// "./test/containers/36_operator.hpp",
			},
		},
		{"list",
			{
				// "./test/containers/01_constructor_empty.hpp",
				// "./test/containers/02_constructor_n.hpp",
				// "./test/containers/03_constructor_n_value.hpp",
				// "./test/containers/04_constructor_iterators.hpp",
				// "./test/containers/05_constructor_container.hpp",
				// "./test/containers/06_operator=.hpp",
				// "./test/containers/07_assign_n_value.hpp",
				// "./test/containers/08_assign_iterators.hpp",
				// "./test/containers/09_get_allocator.hpp",

				// "./test/containers/10_begin.hpp",
				// "./test/containers/11_end.hpp",
				// "./test/containers/12_rbegin.hpp",
				// "./test/containers/13_rend.hpp",

				// "./test/containers/14_size.hpp",
				// "./test/containers/15_max_size.hpp",
				// "./test/containers/16_resize_n_value.hpp",
				// "./test/containers/17_empty.hpp",

				// "./test/containers/20_front.hpp",
				// "./test/containers/21_back.hpp",

				// "./test/containers/22_push_front.hpp",
				// "./test/containers/23_pop_front.hpp",
				// "./test/containers/24_push_back.hpp",
				// "./test/containers/25_pop_back.hpp",
				// "./test/containers/27_insert_iter_value.hpp",
				// "./test/containers/28_insert_iter_n_value.hpp",
				// "./test/containers/29_insert_iter_iterators.hpp",
				// "./test/containers/31_erase_iter.hpp",
				// "./test/containers/33_erase_iterators.hpp",
				// "./test/containers/34_swap.hpp",
				// "./test/containers/35_clear.hpp",

				// "./test/containers/36_operator.hpp",

		// 		// !!!!!!!									//	splice -list
		// 		// !!!!!!!									//	remove - list
		// 		// !!!!!!!									//	remove_if -list
		// 		// !!!!!!!									//	unique(); - list
		// 		// !!!!!!!									//	merge -list
		// 		// !!!!!!!									//	sort(); - list 
		// 		// !!!!!!!									//	reverse();- list 
			},
		},
		{"deque", 
			{
				// "./test/containers/01_constructor_empty.hpp",
				// "./test/containers/02_constructor_n.hpp",
				// "./test/containers/03_constructor_n_value.hpp",
				// "./test/containers/04_constructor_iterators.hpp",
				// "./test/containers/05_constructor_container.hpp",
				// "./test/containers/06_operator=.hpp",
				// "./test/containers/07_assign_n_value.hpp",
				// "./test/containers/08_assign_iterators.hpp",
				// "./test/containers/09_get_allocator.hpp",

				// "./test/containers/10_begin.hpp", 
				// "./test/containers/11_end.hpp",
				// "./test/containers/12_rbegin.hpp",
				// "./test/containers/13_rend.hpp",

				// "./test/containers/14_size.hpp",
				// "./test/containers/15_max_size.hpp",
				// "./test/containers/16_resize_n_value.hpp",
				// "./test/containers/17_empty.hpp",

				// "./test/containers/18_operator[].hpp",
				// "./test/containers/19_at.hpp",
				// "./test/containers/20_front.hpp",
				// "./test/containers/21_back.hpp",

				// "./test/containers/22_push_front.hpp",
				// "./test/containers/23_pop_front.hpp",
				// "./test/containers/24_push_back.hpp",
				// "./test/containers/25_pop_back.hpp",
				// "./test/containers/27_insert_iter_value.hpp",
				// "./test/containers/28_insert_iter_n_value.hpp",
				// "./test/containers/29_insert_iter_iterators.hpp",
				// "./test/containers/31_erase_iter.hpp",
				// "./test/containers/33_erase_iterators.hpp",
				// "./test/containers/34_swap.hpp",
				// "./test/containers/35_clear.hpp",

				// "./test/containers/36_operator.hpp",
			},
		},
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
			},
		},
		{"multiset", 
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
			},
		},
		{"map", 
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

				// "./test/containers/18_operator[].hpp",

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
			},
		},
		{"multimap", 
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
			},
		},
		{"stack", 
			{
				// "./test/containers/01_constructor_empty.hpp",

				// "./test/containers/14_size.hpp",
				// "./test/containers/17_empty.hpp",

				// "./test/stack_queue/01_top.hpp",

				// "./test/stack_queue/02_push.hpp",
				// "./test/stack_queue/03_pop.hpp",

				// "./test/containers/36_operator.hpp",
			},
		},
		{"queue", 
			{
				// "./test/containers/01_constructor_empty.hpp",

				// "./test/containers/14_size.hpp",
				// "./test/containers/17_empty.hpp",

				// "./test/containers/20_front.hpp",
				// "./test/containers/21_back.hpp",
	
				// "./test/stack_queue/02_push.hpp",
				// "./test/stack_queue/03_pop.hpp",

				// "./test/containers/36_operator.hpp",
			},
		},
		{"priority_queue", 
			{
				// "./test/containers/01_constructor_empty.hpp",
				// "./test/containers/04_constructor_iterators.hpp",

				// "./test/containers/14_size.hpp",
				// "./test/containers/17_empty.hpp",
			
				// "./test/stack_queue/01_top.hpp",

				// "./test/stack_queue/02_push.hpp",
				// "./test/stack_queue/03_pop.hpp",
			},
		},
	};

#endif
