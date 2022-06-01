all: vending 
	
vending: 
	gcc -pthread -o vending vending-machine.c consumer.c supplier.c

clean:
	rm  vending		
	
