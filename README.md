# Abstract_data
C++ containers, hard mode

## tester
- minitest
```
make
or
USAGE: g++ test_name -D TYPE=1/2
1 - std
2 - ft
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
	- max_size - I use diffetent data template
	- erase for unordered_container - because I use my own hash_table
	- find/equal_range for unordered_multimap - because key is the same, but value can be different
```
- my test bonus (container display)
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
