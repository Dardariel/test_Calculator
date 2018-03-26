all:
	g++ -o libMyMath.so -shared -fPIC my_math_lib.cpp
	
clean:
	rm -rf libMyMath.so
	
install:
	install -m 0777 -o root -g root -D ./libMyMath.so /usr/lib 
	install -m 0666 -o root -g root -D ./my_math_lib.h /usr/include
	