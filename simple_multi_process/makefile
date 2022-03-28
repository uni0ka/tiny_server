src = $(wildcard ./src/*.c)
obj = $(patsubst ./src/%.c, ./obj/%.o, $(src))     #注意： , 前不要打空格
inc_path = ./inc
my_args = -Wall -g

ALL:main

main:$(obj)
	gcc $^ -o $@ $(my_args)
$(obj):./obj/%.o:./src/%.c
	gcc -c $< -o $@ -I $(inc_path) $(my_args)


clean:
	-rm -rf main $(obj)
.PHONY:clean ALL 

