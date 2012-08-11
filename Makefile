main:
	g++ -O2 main.cpp -o main.out

test: main
	./main.out

clean:
	rm main.out

