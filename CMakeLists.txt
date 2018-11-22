cmake_minimum_required(VERSION 2.6)

project(range-search)

# Adds header files to global HEADER_LIST property
get_property(VAR_HEADER_LIST GLOBAL PROPERTY HEADER_LIST)
set_property(GLOBAL PROPERTY HEADER_LIST
	${VAR_HEADER_LIST}
	range-search/RangeSearch.h)

# Adds test files to global TEST_LIST property
get_property(VAR_TEST_LIST GLOBAL PROPERTY TEST_LIST)
set_property(GLOBAL PROPERTY TEST_LIST
	${VAR_TEST_LIST}
	range-search/test/RangeSearchTest.cpp)

install(FILES RangeSearch.h DESTINATION include/sadehghan)
