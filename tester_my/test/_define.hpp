#pragma once

// Container type from tester
// T_COUNT type from tester
// T_SIZE type from tester

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
#endif
