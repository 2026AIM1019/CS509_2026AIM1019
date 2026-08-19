CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -pedantic

WRAPPER := common_wrapper

ASSIGNMENT_01 := assignment_01
ASSIGNMENT_02 := assignment_02
ASSIGNMENT_03 := assignment_03

.PHONY: all
all: build


.PHONY: build
build:
	@echo ""
	@echo "========================================"
	@echo " Building Assignment 01"
	@echo "========================================"
	$(MAKE) -C $(ASSIGNMENT_01)

	@echo ""
	@echo "========================================"
	@echo " Building Assignment 02"
	@echo "========================================"
	$(MAKE) -C $(ASSIGNMENT_02)

	@echo ""
	@echo "========================================"
	@echo " Building Assignment 03"
	@echo "========================================"
	$(MAKE) -C $(ASSIGNMENT_03)

	@echo ""
	@echo "========================================"
	@echo " Building Common Wrapper"
	@echo "========================================"
	$(CXX) $(CXXFLAGS) common_wrapper.cpp -o $(WRAPPER)

	@echo ""
	@echo "========================================"
	@echo " Build completed successfully!"
	@echo "========================================"
	@echo ""



.PHONY: assignment_01
assignment_01:
	$(MAKE) -C $(ASSIGNMENT_01)


.PHONY: assignment_02
assignment_02:
	$(MAKE) -C $(ASSIGNMENT_02)


.PHONY: assignment_03
assignment_03:
	$(MAKE) -C $(ASSIGNMENT_03)



.PHONY: run
run: build
	@echo ""
	@echo "Starting Assignment Runner..."
	@echo ""
	./$(WRAPPER)


.PHONY: run01
run01: assignment_01
	@echo ""
	@echo "========================================"
	@echo " Running Assignment 01"
	@echo "========================================"
	@echo ""
	cd $(ASSIGNMENT_01) && ./driver/driver


.PHONY: run02
run02: assignment_02
	@echo ""
	@echo "========================================"
	@echo " Running Assignment 02"
	@echo "========================================"
	@echo ""
	cd $(ASSIGNMENT_02) && ./graph_runner


.PHONY: run03
run03: assignment_03
	@echo ""
	@echo "========================================"
	@echo " Running Assignment 03"
	@echo "========================================"
	@echo ""
	cd $(ASSIGNMENT_03) && ./mst_driver


.PHONY: clean
clean:
	@echo ""
	@echo "========================================"
	@echo " Cleaning Assignment 01"
	@echo "========================================"
	$(MAKE) -C $(ASSIGNMENT_01) clean

	@echo ""
	@echo "========================================"
	@echo " Cleaning Assignment 02"
	@echo "========================================"
	$(MAKE) -C $(ASSIGNMENT_02) clean

	@echo ""
	@echo "========================================"
	@echo " Cleaning Assignment 03"
	@echo "========================================"
	$(MAKE) -C $(ASSIGNMENT_03) clean

	@echo ""
	@echo "Cleaning common wrapper..."
	rm -f $(WRAPPER)

	@echo ""
	@echo "========================================"
	@echo " Clean completed successfully!"
	@echo "========================================"
	@echo ""


.PHONY: rebuild
rebuild: clean build

.PHONY: help
help:
	@echo ""
	@echo "========================================"
	@echo "       Assignment Project"
	@echo "========================================"
	@echo ""
	@echo "Available commands:"
	@echo ""
	@echo "  make"
	@echo "      Build all assignments and the"
	@echo "      common wrapper."
	@echo ""
	@echo "  make build"
	@echo "      Build all assignments and the"
	@echo "      common wrapper."
	@echo ""
	@echo "  make run"
	@echo "      Build everything and launch the"
	@echo "      interactive assignment selector."
	@echo ""
	@echo "  make run01"
	@echo "      Build and run Assignment 01."
	@echo ""
	@echo "  make run02"
	@echo "      Build and run Assignment 02."
	@echo ""
	@echo "  make run03"
	@echo "      Build and run Assignment 03."
	@echo ""
	@echo "  make assignment_01"
	@echo "      Build only Assignment 01."
	@echo ""
	@echo "  make assignment_02"
	@echo "      Build only Assignment 02."
	@echo ""
	@echo "  make assignment_03"
	@echo "      Build only Assignment 03."
	@echo ""
	@echo "  make clean"
	@echo "      Remove all generated binaries and"
	@echo "      object files."
	@echo ""
	@echo "  make rebuild"
	@echo "      Clean everything and build again."
	@echo ""
	@echo "  make help"
	@echo "      Display this help message."
	@echo ""
	@echo "========================================"
	@echo ""
