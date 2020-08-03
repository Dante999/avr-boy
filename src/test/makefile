#
# Sample Makefile for uCUnit
#

#----------------------------------------------------
# Toolchain configuration
#----------------------------------------------------
# Compiler
CC:=gcc

CFLAGS  = -c                       # Compile and assemble, but do not link
CFLAGS += -g                       # Generate debug information in default format
CFLAGS += -Os                      # Optimize for space rather than speed
CFLAGS += -std=c11                 # Use this C standard
CFLAGS += -Wextra                  # Print extra (possibly unwanted) warnings
CFLAGS += -Wunused                 # Enable all -Wunused- warnings
CFLAGS += -fpack-struct            # Pack all structure members together without holes
CFLAGS += -fshort-enums            # Use the smallest needed integer for enum values
CFLAGS += -ffunction-sections      # Place each function their own section
CFLAGS += -fdata-sections          # Place data items into their own section
CFLAGS += -funsigned-char          # Make any unqualfied char type an unsigned char
CFLAGS += -funsigned-bitfields     # Make any unqualified bitfield type unsigned


#Linker
LD:=gcc
LDFLAGS=-g

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
SOURCES += protocol.c
SOURCES += cartridge.c
SOURCES += unity.c
SOURCES += mock_font.c
SOURCES += mock_transceiver.c
SOURCES += mock_logger.c
SOURCES += test_graphx.c
SOURCES += test_protocol.c
SOURCES += test_cartridge.c

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
	
