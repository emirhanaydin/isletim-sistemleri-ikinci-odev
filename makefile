basla: derle calistir

derle:
	gcc -pthread uretici.c -o "uretici"
	gcc -pthread tuketici.c -o "tuketici"
	
calistir:
	"./tuketici"

temizle:
	rm -f "uretici"
	rm -f "tuketici"
