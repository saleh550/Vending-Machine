all: vending

vending: 
	gcc -pthread -o vending consumer.c supplier.c vending-machine.c 
clean:
	rm -rf vending
