CXX=mpicxx

all: broadcast.exec allreduce.exec scatter.exec pi.exec

broadcast.exec: broadcast.cpp
	$(CXX)  broadcast.cpp -o broadcast.exec

allreduce.exec: allreduce.cpp
	$(CXX) allreduce.cpp -o allreduce.exec

scatter.exec: scatter.cpp
	$(CXX) scatter.cpp -o scatter.exec

pi.exec: pi.cpp
	$(CXX) pi.cpp -o pi.exec

clean:
	rm -f *.exec
