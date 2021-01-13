##
## EPITECH PROJECT, 2020
## OOP_indie_studio_2019
## File description:
## Makefile
##

SPHINX_SOURCE_FOLDER	=	./source
SPHINX_BUILD_FOLDER	=	./doc/html

all:
	/usr/bin/cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/bin/gcc -DCMAKE_CXX_COMPILER:FILEPATH=/bin/g++ -H./ -B./build -G "Unix Makefiles"

doc:
	doxygen
	sphinx-build ${SPHINX_SOURCE_FOLDER} ${SPHINX_BUILD_FOLDER}

clean:
	rm -rf build html latex xml

.PHONY: all doc clean
