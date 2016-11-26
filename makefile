basla: derle calistir

derle:
	gcc -pthread write.c -o "write"
	gcc read.c -o "read"
	

calistir:
	"./read"

temizle:
	rm -f "write"
	rm -f "read"
