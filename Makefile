CC = cc
CFLAGS = -Wall -Wextra -Werror

TARGET = DirMerge
SRC = main.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET) /path/to/directory

help:
	@echo "Usage:"
	@echo "  make         - Compile the program"
	@echo "  make run     - Run the program with a sample directory"
	@echo "  make clean   - Remove object files"
	@echo "  make fclean  - Remove object files and executable"
	@echo "  ./$(TARGET) <directory_path> [output_file] - Run program with a directory path and optional output file"
	@echo "               If no output file is specified, output is printed to stdout."

.PHONY: all clean fclean run help

