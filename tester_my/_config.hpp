#ifndef CONFIG_HPP
#define CONFIG_HPP

#define		T_COUNT		1000
#define		T_SIZE		100

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define CONCATENATE_IMPL(x, y) x##y
#define CONCATENATE(x, y) CONCATENATE_IMPL(x, y)

#ifdef VECTOR
	#include <vector>
	#include "../src/containers/vector.hpp"
	#define CONTAINER vector
	#define STD CONCATENATE(CONTAINER, <TYPE>)
	#define FT CONCATENATE(CONTAINER, <TYPE>)
	// #define		STD		1
	// #define		FT		2
#endif

#ifdef MAP
	#include <map>
	#include "../src/containers/map.hpp"
	#define		CONTAINER	map
	#define STD CONCATENATE(CONTAINER, <TYPE>)
	#define FT CONCATENATE(CONTAINER, <TYPE>)
	// #define		STD		1
	// #define		FT		2
#endif

	// # define	CONTAINER_VECTOR	1
	// # define	CONTAINERS_LIST		2
	// # define	CONTAINER_DEQUE		3
	// # define	CONTAINER_SET		4
	// # define	CONTAINER_MAP		5

	// #define STRINGIFY(x) #x
	// #define TOSTRING(x) STRINGIFY(x)

	// #ifdef TEST
	// 	#if TEST == CONTAINER_VECTOR
	// 		#include "../src/containers/vector.hpp"
	// 		#include <vector>
	// 		#define CONTAINER	vector
	// 		#define TYPE		int
	// 	#elif TEST == CONTAINERS_LIST
	// 		#include "../src/containers/list.hpp"
	// 		#include <list>
	// 		#define CONTAINER list
	// 		#define TYPE		int
	// 	#elif TEST == CONTAINER_DEQUE
	// 		#include "../src/containers/deque.hpp"
	// 		#include <deque>
	// 		#define CONTAINER deque
	// 		#define TYPE		int
	// 	#elif TEST == CONTAINER_SET
	// 		#include "../src/containers/set.hpp"
	// 		#include <set>
	// 		#define CONTAINER set
	// 		#define TYPE		int
	// 	#elif TEST == CONTAINER_MAP
	// 		#include "../src/containers/map.hpp"
	// 		#include <map>
	// 		#define CONTAINER	map
	// 		#define TYPE		int,int
	// 	#endif
	// #endif

#endif
