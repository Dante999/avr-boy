#
# Sample Makefile for uCUnit
#

#----------------------------------------------------
# Toolchain configuration
#----------------------------------------------------
# Compiler
CC:=gcc
CFLAGS  = -c
CFLAGS += -Os
CFLAGS += -Wall
CFLAGS += -fpack-struct
CFLAGS += -fshort-enums
CFLAGS += -ffunction-sections
CFLAGS += -fdata-sections
CFLAGS += -std=gnu99
CFLAGS += -funsigned-char
CFLAGS += -funsigned-bitfields


#Linker
LD:=gcc
LDFLAGS=

# Simulator/Emulator
RUN:=./

# Clean up
RM:=rm

#----------------------------------------------------
# Files
#----------------------------------------------------
# Name of target file
TARGET:=Testsuite.exe
BUILDPATH=./build


VPATH = ..
VPATH += ../protocol
VPATH += ../display
VPATH += ../util

# Sourcefiles
SOURCES  = testsuite.c
SOURCES += graphx.c
SOURCES += system.c
SOURCES += test_graphx.c
SOURCES += test_protocol.c
SOURCES += mock_font.c
SOURCES += protocol.c
SOURCES += mock_logger.c

OBJECTS=$(SOURCES:%.c=$(BUILDPATH)/%.o)

MKDIR=mkdir -p
#----------------------------------------------------
# Build all
#----------------------------------------------------
all: clean $(TARGET) run

run: $(TARGET)
	echo 'Running $(TARGET)...'
	$(RUN)/$(BUILDPATH)/$(TARGET)
	
#----------------------------------------------------
# Linker stage
#----------------------------------------------------
$(TARGET): $(OBJECTS)
	echo 'Linking...'
	$(LD) $(LDFLAGS) -o  $(BUILDPATH)/$@ $(OBJECTS)
#	$(LD) $(LDFLAGS) -o $(notdir $@) $(notdir $(OBJECTS))

#----------------------------------------------------
# Compiler
#----------------------------------------------------
$(BUILDPATH)/%.o: %.c
	echo 'Compiling...'
	$(MKDIR) $(BUILDPATH)
	$(CC) $(CFLAGS) $< -o $@
	#$(CC) $(CFLAGS) -o $(notdir $@) -c $<
	
#----------------------------------------------------
# Clean Project
#----------------------------------------------------
clean:
	echo 'Running clean...'
	$(RM) -f build/*
	echo 'Clean finished.'
	
