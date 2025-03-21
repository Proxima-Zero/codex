#!/bin/sh

CC=${CC:=gcc}
SRCS="ds/array.c parsers/dotenv.c allocators/std_allocator.c allocators/debug_allocator.c"
OBJS=""
LIBNAME=build/libcodex.a
INCLUDE="-I./"
CFLAGS="-Wno-discarded-qualifiers -Wno-format-truncation"

set -x

mkdir -p build
mkdir -p build/ds
mkdir -p build/testing
mkdir -p build/parsers
mkdir -p build/allocators

for src in $SRCS; do
	obj="build/${src%.c}.o"
	$CC $CFLAGS -g -c "$src" -o "$obj" $INCLUDE
	OBJS="$OBJS $obj"
done

rm $LIBNAME
ar rcs "$LIBNAME" $OBJS
