# Abstract_data
C++ containers, hard mode

## tester
- minitest
```
- container std98
- containet std11 I cannot comare, because I have my realization
```
- my test
```
- config.hpp - choose test you want
- use template and defined for all test
- use fork for compile and test and leaks
- support logs from compile and valgrind
- different parameters for leaks and main test
- random generated data at the begin of test container
- simple creat and add new test template - add new test to config file
- some test can be FAILED - it is OK
	- capacity - it can be different managment memory
	- max_size - it can be different structure
	- erase for unordered_container - it can be different hash_table
	- find/equal_range for unordered_multimap - key is the same, but value can be different
```
- my test bonus (container display)
	- fibonacci heap
	- unordered_set
	- unordered_multimap
	- unordered_map
```
make "container"
```
- escole42
```
static_tester
monkey_tester
```

## Sequence containers
- list
- deque
- vector

## Associative containers
- map
- set
- multimap
- multiset

## Container adaptors
- stack
- queue
- priority_queue

## Bonus
- unorder_map
- unorder_set
- unordered_multimap
- unordered_multiset
- fibonacci_heap
