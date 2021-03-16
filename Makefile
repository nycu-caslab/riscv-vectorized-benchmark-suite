BASE_DIR := $(shell pwd)


APPLICATION_DIRS := _blackscholes _swaptions _streamcluster _canneal _particlefilter _pathfinder _axpy
all: blackscholes swaptions streamcluster canneal particlefilter pathfinder axpy

blackscholes:
	cd _blackscholes; 			\
	make vector;                            \
	make runspike;
swaptions:
	cd _swaptions; 		\
	make vector; 		\
	make runspike;

streamcluster:
	cd _streamcluster; 	\
	make vector; 		\
	make runspike;

canneal:
	cd _canneal; 		\
	make vector;            \
	make runspike;

particlefilter:
	cd _particlefilter;	\
	make vector;            \
	make runspike;

pathfinder:
	cd _pathfinder;		\
	make vector; 		\
	make runspike;

jacobi-2d:
	cd _jacobi-2d;		\
	make vector; 		\
	make host;		

axpy:
	cd _axpy;		\
	make vector;              \
	make runspike;          

clean:
	for dir in $(APPLICATION_DIRS) ; do cd $$dir ; make clean ; cd .. ; done
