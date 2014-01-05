BOOST_INCLUDE=/home/robert/boost/include/
BOOST_LIB=/home/robert/boost/lib/
all:
	g++ --std=c++0x -I$(BOOST_INCLUDE) -L$(BOOST_LIB) *.cpp -o tests.out 2>&1 | tee build_log.log && vim build_log.log

