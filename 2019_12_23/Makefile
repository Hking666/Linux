.PHONY:all
all:sh_read sh_write  

sh_write:sh_write.c myshm.h
	gcc $^ -o $@
sh_read:sh_read.c myshm.h
	gcc $^ -o $@
creat:creat.c
	gcc $^ -o $@
read:read.c
	gcc $^ -o $@


write:write.c
	gcc $^ -o $@

.PHONY:clean
	rm sh_reader sh_write
