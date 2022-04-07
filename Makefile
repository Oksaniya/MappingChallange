NAME = LOG_DECODER

CC = gcc
FLAG = -glldb -g3 -Wall -Wextra -Werror

all: obj
	$(CC) $(FLAG) obj/main.o \
	obj/log_decoder.o \
	obj/validator.o \
	obj/additional_fn.o \
	obj/val_col.o \
	 -o $(NAME) -glldb -fsanitize=address -g3
	@echo "\033[0;32mFillit compiled : \033[0m\033[31m$(NAME)\033[0m"	

obj:
	mkdir obj
	$(CC) $(FLAG) -c src/main.c -o obj/main.o 
	$(CC) $(FLAG) -c src/log_decoder.c -o obj/log_decoder.o 
	$(CC) $(FLAG) -c src/validator.c -o obj/validator.o 
	$(CC) $(FLAG) -c src/additional_fn.c -o obj/additional_fn.o 
	$(CC) $(FLAG) -c src/val_col.c -o obj/val_col.o 

clean:
	rm -fr obj/*.o
	rm -fr obj

fclean: clean
	rm -fr $(NAME)

re: fclean all

run: re
	./$(NAME) input_log.csv output_log.csv

debug: re
	lldb -- ./$(NAME) input_log.csv output_log.csv