CXX=g++
CXXFLAGS=-std=c++17 -Wall
INCLUDES=-Iinclude -Iinclude/allocator -Iinclude/cache -Iinclude/stats -Iinclude/virtual_memory

SRC=source/main.cpp \
    source/allocator/MemoryManager.cpp \
    source/allocator/FirstFit.cpp \
    source/allocator/BestFit.cpp \
    source/allocator/WorstFit.cpp \
    source/allocator/BuddyAllocator.cpp \
    source/allocator/Dump.cpp \
    source/cache/CacheHierarchy.cpp \
    source/stats/Stats.cpp \
    source/virtual_memory/VirtualMemoryManager.cpp
    
OUT=memsim

all:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) -o $(OUT)
test: all
	$(CXX) $(CXXFLAGS) tests/test_runner.cpp -o tests/runner
	./tests/runner
clean:
	rm -f $(OUT) tests/runner tests/results.log
