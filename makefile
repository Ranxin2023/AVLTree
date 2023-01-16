CXX=g++
C++flag=-Wall -Werror -std=c++11
G=class
DG=AVLTree
all:$(DG)
	$(DG)
$(DG):$(G).o $(DG).cpp
	$(CXX) $(C++flag)  $^ -o $(DG)
$(G).o:$(G).cpp $(G).h
	$(CXX) $(C++flag) -c $< -o $@
clean:
	rm -rf *.o $(DG)