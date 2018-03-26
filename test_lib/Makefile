all:
	g++ main.cpp -fPIC -L. -lMyMath -o testlib
	export LD_LIBRARY_PATH=.

clean:
	rm -rf testlib libMyMath.so
	