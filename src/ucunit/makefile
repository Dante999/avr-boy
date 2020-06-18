#
# Sample Makefile for uCUnit
#

#----------------------------------------------------
# Toolchain configuration
#----------------------------------------------------
# Compiler
CC:=gcc
CFLAGS:=-g

#Linker
LD:=gcc
LDFLAGS:=-g

# Simulator/Emulator
RUN:=./

# Clean up
RM:=rm

#----------------------------------------------------
# Files
#----------------------------------------------------
# Name of target file
TARGET:=Testsuite.exe
VPATH = ..


# Sourcefiles
SRCS:=           \
system.c       \
test_graphx.c \
test_protocol.c \
testsuite.c \
mock_font.c \
../graphx.c \
../protocol/avrboy-protocol.c \




# Objectfiles
OBJS:=           \
system.obj     \
test_graphx.obj \
test_protocol.obj \
testsuite.obj \
graphx.obj \
mock_font.obj \
../protocol/avrboy-protocol.obj \

#----------------------------------------------------
# Build all
#----------------------------------------------------
all: clean $(TARGET) run

run: $(TARGET)
	echo 'Running $(TARGET)...'
	$(RUN)$(TARGET)
	
#----------------------------------------------------
# Linker stage
#----------------------------------------------------
$(TARGET):	$(OBJS)
	echo 'Linking...'
	$(LD) $(LDFLAGS) -o $(notdir $@) $(notdir $(OBJS))

#----------------------------------------------------
# Compiler
#----------------------------------------------------
%.obj: %.c
	echo 'Compiling...'
	$(CC) $(CFLAGS) -o $(notdir $@) -c $<
	
#----------------------------------------------------
# Clean Project
#----------------------------------------------------
clean:
	echo 'Running clean...'
	$(RM) -f $(TARGET)
	$(RM) -f *.obj
	echo 'Clean finished.'
	
