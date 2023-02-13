# variable for the compiler used
CC = gcc
# flags used to compile the program
CFLAGS = -Wall -Wextra -Werror
# file target. this represent the object file to created
TARGET = my_mastermind

# all: $(TARGET)
# the actual compilation of the project
$(TARGET) : $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c
# cleans the directory of any object file created 
clean:
	rm -f *.o
#removes the compiled file 
fclean: clean
	rm -f $(TARGET)

re: fclean all