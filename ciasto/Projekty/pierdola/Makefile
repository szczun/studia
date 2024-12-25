# Nazwa pliku wynikowego
TARGET = app

# Kompilator i flagi
CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -I./libs

# Domyślny cel
all: final

# Cel finalny - łączenie plików obiektowych
final: convert.o UserInput.o ConvertFile.o
	@$(CC) $(CFLAGS) convert.o UserInput.o ConvertFile.o -o $(TARGET)

# Kompilacja convert.o
convert.o: convert.cpp
	@$(CC) $(CFLAGS) -c convert.cpp -o convert.o

# Kompilacja UserInput.o
UserInput.o: libs/UserInput.cpp
	@$(CC) $(CFLAGS) -c libs/UserInput.cpp -o UserInput.o

ConvertFile.o: libs/ConvertFile.cpp
	@$(CC) $(CFLAGS) -c libs/ConvertFile.cpp -o ConvertFile.o

# Uruchomienie programu z argumentami przekazanymi z linii komend
run: final
	@./$(TARGET) $(ARGS)

# Usuwanie plików obiektowych i pliku wynikowego
clean:
	rm -f convert.o UserInput.o ConvertFile.o $(TARGET)
