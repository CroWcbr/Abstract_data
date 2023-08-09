#pragma once

// Container type from tester
// T_COUNT type from tester
// T_SIZE type from tester

#include <iostream>

#define _DATA_FILE "./data.txt"

#if defined(VECTOR)
# include <vector>
# include "../include/vector.hpp"
#elif defined(LIST)
# include <list>
# include "../include/list.hpp"
#elif defined(DEQUE)
# include <deque>
# include "../include/deque.hpp"
#elif defined(SET) || defined(MULTISET)
# include <set>
# include "../include/set.hpp"
#elif defined(MAP) || defined(MULTIMAP)
# include <map>
# include "../include/map.hpp"
#elif defined(STACK)
# include <stack>
# include "../include/stack.hpp"
#elif defined(QUEUE) || defined(PRIORITY_QUEUE)
# include <queue>
# include "../include/queue.hpp"
#elif defined(UNORDERED_SET) || defined(UNORDERED_MULTISET)
# include <unordered_set>
# include <set>
# include "../include/unordered_set.hpp"
# include "../include/set.hpp"
#elif defined(UNORDERED_MAP) || defined(UNORDERED_MULTIMAP)
# include <unordered_map>
# include <map>
# include "../include/unordered_map.hpp"
# include "../include/map.hpp"
#endif
