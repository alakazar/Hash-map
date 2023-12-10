SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
INC=$(wildcard *.h)


all : exec 

debug :
	@echo $(SRC)
	@echo $(OBJ)
	@echo $(INC)

%.o : %.c $(INC)
	gcc -c $< -o $@
	
exec : $(OBJ)
	gcc -fsanitize=address $^ -o $@
	

		
clean:
	rm -f *.o
	rm -f exec
	
