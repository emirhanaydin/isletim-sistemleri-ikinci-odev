basla: derle calistir

derle:
	gcc read.c -o "read"
	gcc write.c -o "write"

calistir:
	"./write"

temizle:
	rm -f "read"
	rm -f "write"
