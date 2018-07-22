CXX=mpicxx

all: pi_hybrid.exec 

pi_hybrid.exec: pi_hybrid.cpp
	$(CXX)  pi_hybrid.cpp -fopenmp -o pi_hybrid.exec

clean:
	rm -f *.exec
