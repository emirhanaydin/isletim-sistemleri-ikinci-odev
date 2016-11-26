basla: derle calistir

derle:
	gcc read.c -o "read"
	gcc write.c -o "write"

calistir:
	"./write"

temizle:
	rm -f "write"
	rm -f "read"
