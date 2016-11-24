basla: derle calistir

derle:
	gcc harici.c -o harici
	gcc pro1.c -o pro1

calistir:
	./pro1

temizle:
	rm -f harici
	rm -f pro1
