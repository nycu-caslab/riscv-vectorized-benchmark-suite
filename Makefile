BASE_DIR := $(shell pwd)

APPLICATION_DIRS := _blackscholes _swaptions _streamcluster _canneal _particlefilter _pathfinder _jacobi-2d _axpy

all: blackscholes swaptions streamcluster canneal pathfinder jacobi-2d axpy

blackscholes:
	cd _blackscholes; 	\
	make start;			\
	make serial; 		\
	make vector;

swaptions:
	cd _swaptions; 		\
	make start;			\
	make serial; 		\
	make vector;

streamcluster:
	cd _streamcluster; 	\
	make start;			\
	make serial; 		\
	make vector;

canneal:
	cd _canneal; 		\
	make start;			\
	make serial; 		\
	make vector;

particlefilter:
	cd _particlefilter;	\
	make start;			\
	make serial; 		\
	make vector;

pathfinder:
	cd _pathfinder;		\
	make start;			\
	make serial; 		\
	make vector;

jacobi-2d:
	cd _jacobi-2d;		\
	make start;			\
	make serial; 		\
	make vector;

axpy:
	cd _axpy; 			\
	make start;			\
	make serial; 		\
	make vector;

clean:
	for dir in $(APPLICATION_DIRS) ; do cd $$dir ; make clean ; cd .. ; done
