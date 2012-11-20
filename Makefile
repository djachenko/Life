GTEST_DIR = gtest
USER_DIR = .

CPPFLAGS += -I$(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra

CELL_TESTS = CellTests
FIELD_TESTS = FieldTests

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h $(GTEST_DIR)/include/gtest/internal/*.h

all : $(CELL_TESTS) $(FIELD_TESTS)

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)



gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^



CellTests.o : $(USER_DIR)/CellTests.cpp $(USER_DIR)/Cell.h $(USER_DIR)/Cell.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/Cell.cpp

CellTests : CellTests.o gtest_main.a 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -lpthread -o $@



FieldTests.o : $(USER_DIR)/FieldTests.cpp $(USER_DIR)/Field.h $(USER_DIR)/Field.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/Field.cpp

FieldTests : FieldTests.o gtest_main.a 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -lpthread -o $@



clean :
	rm -f $(TESTS) gtest.a gtest_main.a *.o
