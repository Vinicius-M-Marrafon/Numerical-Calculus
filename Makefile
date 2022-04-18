# By: Vinicius Mari Marrafon
# Makefile -> cfgauss_completo.exe!

COMPILER = gcc
FLAGS    = -Wall -Werror -ggdb -lgfortran
HEADERS  = ..\..\Libs\numeric.c
OBJS	 = cgauss_completo.o fgauss_completo.o


cfgauss_completo: cgauss_completo.o fgauss_completo.o
	$(COMPILER) $(OBJS) $(HEADERS) -o cfgauss_completo.exe $(FLAGS)

cgauss_completo.o: cgauss_completo.c
	gcc -c cgauss_completo.c

fgauss_completo.o: fgauss_completo.f95
	gfortran -c fgauss_completo.f95

gauss_completo:
	$(COMPILER) gauss_completo.c $(HEADERS) -o gauss_completo.exe -Wall -Werror -ggdb