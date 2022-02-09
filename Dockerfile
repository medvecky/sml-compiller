FROM archlinux 

WORKDIR /home/project

RUN pacman -Sy --noconfirm clang
RUN pacman -Sy --noconfirm make 
RUN pacman -Sy --noconfirm ctags
RUN pacman -Sy --noconfirm autoconf
RUN pacman -Sy --noconfirm automake
RUN pacman -Sy --noconfirm valgrind 
RUN pacman -Sy --noconfirm bear  
RUN pacman -Sy --noconfirm gdb 
