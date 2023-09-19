CC      = gcc
CFLAGS  = -W -Wall -g
CFLAGS  += -D__LIB_SINGLE_APP__

INCLUDE = -I/usr/local/include
LDFLAGS = -L/usr/local/lib -lpthread

# 폴더이름으로 실행파일 생성
TARGET  := $(notdir $(shell pwd))

# 정의되어진 이름으로 실행파일 생성
# TARGET := test

SRC_DIRS = .
# SRCS     = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
SRCS     = $(shell find . -name "*.c")
OBJS     = $(SRCS:.c=.o)

all : $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)
	rm -f $(TARGET)
