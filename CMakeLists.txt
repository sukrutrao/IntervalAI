cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
project(IntervalAI)

set(IntervalAI_VERSION_MAJOR 0)
set(IntervalAI_VERSION_MINOR 0)

include_directories(include)
include_directories(cbmc/src)

file(GLOB SOURCES "src/*.cpp")
file(GLOB_RECURSE OBJS "cbmc/*.o")

FOREACH(item ${OBJS})
	IF(${item} MATCHES "main.o")
		LIST(REMOVE_ITEM OBJS ${item})
	ENDIF(${item} MATCHES "main.o")
	IF(${item} MATCHES "test.o")
		LIST(REMOVE_ITEM OBJS ${item})
	ENDIF(${item} MATCHES "test.o")
ENDFOREACH(item)

file(GLOB_RECURSE DOMAIN_OBJS "cbmc/*_domain.o")

LIST(APPEND OBJS cbmc/src/goto-symex/symex_main.o)
LIST(APPEND OBJS ${DOMAIN_OBJS})

add_executable(IntervalAI ${SOURCES} ${OBJS})
