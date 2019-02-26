EXENAME = game

CC = g++
INCLUDE = -lSDL2 -lSDL2_image -lSDL2_mixer

OBJ = main.o

DIR_MENU = ./menu
OBJ_MENU = menu.o

DIR_OBJ = ./object
OBJ_OBJ = character.o object.o

DIR_MAP = ./map
OBJ_MAP = level1.o

DIR_UTIL = ./util
OBJ_UTIL = util.o

OBJ_D_OBJ = $(addprefix $(DIR_OBJ)/, $(OBJ_OBJ))

game: main.o $(DIR_MENU)/$(OBJ_MENU) $(OBJ_D_OBJ) $(DIR_MAP)/$(OBJ_MAP) $(DIR_UTIL)/$(OBJ_UTIL)
	$(CC) -o $(EXENAME) $(OBJ) $(OBJ_MENU) $(OBJ_OBJ) $(OBJ_MAP) $(OBJ_UTIL) $(INCLUDE)
	rm -rf $(OBJ) $(OBJ_MENU) $(OBJ_OBJ) $(OBJ_MAP) $(OBJ_UTIL)

%.o: %.cpp
	${CC} -c $<

$(DIR_MENU)/%.o: %.cpp
	$(CC) -c $<

$(DIR_OBJ)/%.o: %.cpp
	$(CC) -c $<

$(DIR_MAP)/%.o: %.cpp
	$(CC) -c $<

$(DIR_UTIL)/%.o: %.cpp
	$(CC) -c $<

clean:
	rm -rf $(EXENAME)