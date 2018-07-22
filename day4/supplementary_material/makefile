CXX=mpicxx

all: pi_openmp_parallel.exec 

pi_openmp_parallel.exec: pi_openmp_parallel.cpp
	$(CXX)  pi_openmp_parallel.cpp -fopenmp -o pi_openmp_parallel.exec

clean:
	rm -f *.exec
