BASE_DIR := $(shell pwd)

export llvm_dump_options?= -d --mattr=experimental-v

APPLICATION_DIRS := _blackscholes _swaptions _streamcluster _canneal _particlefilter _pathfinder _jacobi-2d _axpy

all: blackscholes swaptions streamcluster canneal particlefilter pathfinder jacobi-2d axpy

all_clang: blackscholes_clang swaptions_clang streamcluster_clang canneal_clang particlefilter_clang pathfinder_clang jacobi-2d_clang axpy_clang

all_O2: blackscholes_O2 swaptions_O2 streamcluster_O2 canneal_O2 particlefilter_O2 pathfinder_O2 jacobi-2d_O2 axpy_O2

all_O2_clang: blackscholes_O2_clang swaptions_O2_clang streamcluster_O2_clang canneal_O2_clang particlefilter_O2_clang pathfinder_O2_clang jacobi-2d_O2_clang axpy_O2_clang

rungem5_all: rungem5_blackscholes rungem5_swaptions rungem5_streamcluster rungem5_canneal rungem5_particlefilter rungem5_pathfinder rungem5_jacobi-2d rungem5_axpy

rungem5_all_O2:rungem5_blackscholes_O2 rungem5_swaptions_O2 rungem5_streamcluster_O2 rungem5_canneal_O2 rungem5_particlefilter_O2 rungem5_pathfinder_O2 rungem5_jacobi-2d_O2 rungem5_axpy_O2

runqemu_all: runqemu_blackscholes runqemu_swaptions runqemu_streamcluster runqemu_canneal runqemu_particlefilter runqemu_pathfinder runqemu_jacobi-2d runqemu_axpy

runqemu_all_O2:runqemu_blackscholes_O2 runqemu_swaptions_O2 runqemu_streamcluster_O2 runqemu_canneal_O2 runqemu_particlefilter_O2 runqemu_pathfinder_O2 runqemu_jacobi-2d_O2 runqemu_axpy_O2

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

blackscholes_O2:
	cd _blackscholes; 	\
	make start;			\
	make serial_O2; 	\
	make vector_O2;

swaptions_O2:
	cd _swaptions; 		\
	make start;			\
	make serial_O2; 	\
	make vector_O2;

streamcluster_O2:
	cd _streamcluster; 	\
	make start;			\
	make serial_O2; 	\
	make vector_O2;

canneal_O2:
	cd _canneal; 		\
	make start;			\
	make serial_O2; 	\
	make vector_O2;

particlefilter_O2:
	cd _particlefilter;	\
	make start;			\
	make serial_O2; 	\
	make vector_O2;

pathfinder_O2:
	cd _pathfinder;		\
	make start;			\
	make serial_O2; 	\
	make vector_O2;

jacobi-2d_O2:
	cd _jacobi-2d;		\
	make start;			\
	make serial_O2; 	\
	make vector_O2;

axpy_O2:
	cd _axpy; 			\
	make start;			\
	make serial_O2; 	\
	make vector_O2;

blackscholes_clang:
	cd _blackscholes; 		\
	make start;				\
	make serial_clang; 		\
	make vector_clang;

swaptions_clang:
	cd _swaptions; 			\
	make start;				\
	make serial_clang; 		\
	make vector_clang;

streamcluster_clang:
	cd _streamcluster; 		\
	make start;				\
	make serial_clang; 		\
	make vector_clang;

canneal_clang:
	cd _canneal; 			\
	make start;				\
	make serial_clang; 		\
	make vector_clang;

particlefilter_clang:
	cd _particlefilter;		\
	make start;				\
	make serial_clang; 		\
	make vector_clang;

pathfinder_clang:
	cd _pathfinder;			\
	make start;				\
	make serial_clang; 		\
	make vector_clang;

jacobi-2d_clang:
	cd _jacobi-2d;			\
	make start;				\
	make serial_clang; 		\
	make vector_clang;

axpy_clang:
	cd _axpy; 				\
	make start;				\
	make serial_clang; 		\
	make vector_clang;

blackscholes_O2_clang:
	cd _blackscholes; 		\
	make start;				\
	make serial_O2_clang; 	\
	make vector_O2_clang;

swaptions_O2_clang:
	cd _swaptions; 			\
	make start;				\
	make serial_O2_clang; 	\
	make vector_O2_clang;

streamcluster_O2_clang:
	cd _streamcluster; 		\
	make start;				\
	make serial_O2_clang; 	\
	make vector_O2_clang;

canneal_O2_clang:
	cd _canneal; 			\
	make start;				\
	make serial_O2_clang; 	\
	make vector_O2_clang;

particlefilter_O2_clang:
	cd _particlefilter;		\
	make start;				\
	make serial_O2_clang; 	\
	make vector_O2_clang;

pathfinder_O2_clang:
	cd _pathfinder;			\
	make start;				\
	make serial_O2_clang; 	\
	make vector_O2_clang;

jacobi-2d_O2_clang:
	cd _jacobi-2d;			\
	make start;				\
	make serial_O2_clang; 	\
	make vector_O2_clang;

axpy_O2_clang:
	cd _axpy; 				\
	make start;				\
	make serial_O2_clang; 	\
	make vector_O2_clang;

rungem5_blackscholes: 
	cd _blackscholes; 	\
	make rungem5;

rungem5_swaptions:
	cd _swaptions; 		\
	make rungem5;

rungem5_streamcluster:
	cd _streamcluster; 	\
	make rungem5;

rungem5_canneal:
	cd _canneal; 		\
	make rungem5;

rungem5_particlefilter:
	cd _particlefilter;	\
	make rungem5;

rungem5_pathfinder:
	cd _pathfinder;		\
	make rungem5;

rungem5_jacobi-2d:
	cd _jacobi-2d;		\
	make rungem5;

rungem5_axpy:
	cd _axpy; 			\
	make rungem5;

rungem5_blackscholes_O2: 
	cd _blackscholes; 	\
	make rungem5_O2;

rungem5_swaptions_O2:
	cd _swaptions; 		\
	make rungem5_O2;

rungem5_streamcluster_O2:
	cd _streamcluster; 	\
	make rungem5_O2;

rungem5_canneal_O2:
	cd _canneal; 		\
	make rungem5_O2;

rungem5_particlefilter_O2:
	cd _particlefilter;	\
	make rungem5_O2;

rungem5_pathfinder_O2:
	cd _pathfinder;		\
	make rungem5_O2;

rungem5_jacobi-2d_O2:
	cd _jacobi-2d;		\
	make rungem5_O2;

rungem5_axpy_O2:
	cd _axpy; 			\
	make rungem5_O2;

runqemu_blackscholes: 
	cd _blackscholes; 	\
	make runqemu;

runqemu_swaptions:
	cd _swaptions; 		\
	make runqemu;

runqemu_streamcluster:
	cd _streamcluster; 	\
	make runqemu;

runqemu_canneal:
	cd _canneal; 		\
	make runqemu;

runqemu_particlefilter:
	cd _particlefilter;	\
	make runqemu;

runqemu_pathfinder:
	cd _pathfinder;		\
	make runqemu;

runqemu_jacobi-2d:
	cd _jacobi-2d;		\
	make runqemu;

runqemu_axpy:
	cd _axpy; 			\
	make runqemu;

runqemu_blackscholes_O2: 
	cd _blackscholes; 	\
	make runqemu_O2;

runqemu_swaptions_O2:
	cd _swaptions; 		\
	make runqemu_O2;

runqemu_streamcluster_O2:
	cd _streamcluster; 	\
	make runqemu_O2;

runqemu_canneal_O2:
	cd _canneal; 		\
	make runqemu_O2;

runqemu_particlefilter_O2:
	cd _particlefilter;	\
	make runqemu_O2;

runqemu_pathfinder_O2:
	cd _pathfinder;		\
	make runqemu_O2;

runqemu_jacobi-2d_O2:
	cd _jacobi-2d;		\
	make runqemu_O2;

runqemu_axpy_O2:
	cd _axpy; 			\
	make runqemu_O2;


clean:
	for dir in $(APPLICATION_DIRS) ; do cd $$dir ; make clean ; cd .. ; done
