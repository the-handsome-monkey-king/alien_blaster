# makefile
# 
# @author Ryan Morehouse
# @date May 1, 2018
#
# *** Instructions ***
#
# make: compile everything
#
# make all: compile everything
#
# make nomappywarnings: compile and ignore warnings
# 		from the mappyal library
#
# make clean: remove all object files

OBJECTS = mappyal.o sprite.o playersprite.o bulletsprite.o bullethandler.o crawlersprite.o centipede.o boss.o powerup.o alienblaster.o grabframe.o poweruphandler.o main.o 
FLAGS = -Wall -lalleg 
NOMAPPYWARNFLAGS = -Wno-pointer-to-int-cast -Wno-unused-but-set-variable -Wno-deprecated-declarations -Wno-pointer-sign -Wno-int-conversion -Wno-parentheses
.SUFFIXES: .cpp .o

.cpp.o:
	g++ -o $@ $^ $(FLAGS)

all: $(OBJECTS)

nomappywarnings: $(OBJECTS) $(NOMAPPYWARNFLAGS)

# Compile with C compiler, ignore enormous list of warnings
# With time, these warnings could be fixed by hand
mappyal.o: mappyal.c
	gcc mappyal.c -O2 -Wall -c -o mappyal.o $(NOMAPPYWARNFLAGS)
	
sprite.o: sprite.cpp sprite.h
	g++ -c -o sprite.o sprite.cpp -lalleg -Wall
	
playersprite.o: playersprite.cpp playersprite.h
	g++ -c -o playersprite.o playersprite.cpp -lalleg -Wall
	
bulletsprite.o: bulletsprite.cpp bulletsprite.h
	g++ -c -o bulletsprite.o bulletsprite.cpp -lalleg -Wall
	
bullethandler.o: bullethandler.cpp bullethandler.h
	g++ -c -o bullethandler.o bullethandler.cpp -lalleg -Wall
	 
crawlersprite.o: crawlersprite.cpp crawlersprite.h
	g++ -c -o crawlersprite.o crawlersprite.cpp -lalleg -Wall
	
centipede.o: centipede.cpp centipede.h
	g++ -c -o centipede.o centipede.cpp -lalleg -Wall
	
boss.o: boss.cpp boss.h
	g++ -c -o boss.o boss.cpp -lalleg -Wall
	
powerup.o:  powerup.cpp powerup.h
	g++ -c -o powerup.o powerup.cpp -lalleg -Wall
	
alienblaster.o:  alienblaster.cpp alienblaster.h
	g++ -c -o alienblaster.o alienblaster.cpp -lalleg -Wall
	
grabframe.o: grabframe.cpp grabframe.h
	g++ -c -o grabframe.o grabframe.cpp -lalleg -Wall
	
poweruphandler.o: poweruphandler.cpp poweruphandler.h
	g++ -c -o poweruphandler.o poweruphandler.cpp -lalleg -Wall
	
main.o: sprite.o playersprite.o bulletsprite.o bullethandler.o crawlersprite.o centipede.o mappyal.o boss.o powerup.o alienblaster.o grabframe.o poweruphandler.o

clean:
	\rm -f *.o
