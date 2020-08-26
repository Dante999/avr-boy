################################################################################
# General project settings
################################################################################

# Name of the target (files will be named like that)
TARGET = Testsuite.exe

# Path where objects files and binaries will be located after creation
BUILDPATH = ./build

# Simulator/Emulator
RUN:=./

# Clean up
RM    = rm -f
MKDIR = mkdir -p
################################################################################
# Project files
################################################################################
VPATH = ..
VPATH += ../display
VPATH += ../util
VPATH += ../../core

# List of all sources (only source-files)
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

################################################################################
# Building Object files 
################################################################################

# Pattern of the objects files 
OBJ_PATTERN = $(BUILDPATH)/%.o

# Change file extension from .c to .o
TMP1 =  $(SOURCES:%.c=$(OBJ_PATTERN))

# Change file extension from .cpp to .o
TMP2 = $(TMP1:%.cpp=$(OBJ_PATTERN))

# Final list ob object files to generate
OBJECTS = $(TMP2)


################################################################################
# Compiler
################################################################################
CC = g++

CFLAGS = -I.                       # Include current file location to search path
CFLAGS += -I..                       # Include current file location to search path
CFLAGS += -I../..
CFLAGS += -c                       # Compile and assemble, but do not link
#CFLAGS += -g                       # Generate debug information in default format
CFLAGS += -Os                      # Optimize for space rather than speed
CFLAGS += -std=c++11                 # Use this C standard

#CFLAGS += -Werror                  # Treat all warnings as errors
CFLAGS += -Wall                    # Print all warnings
CFLAGS += -Wextra                  # Print extra (possibly unwanted) warnings
CFLAGS += -Wunused                 # Enable all -Wunused- warnings
CFLAGS += -Wshadow                 # Warn if a variable declaration shadows one from the parent context

CFLAGS += -fpack-struct            # Pack all structure members together without holes
CFLAGS += -fshort-enums            # Use the smallest needed integer for enum values
CFLAGS += -ffunction-sections      # Place each function their own section
CFLAGS += -fdata-sections          # Place data items into their own section
CFLAGS += -funsigned-char          # Make any unqualfied char type an unsigned char
CFLAGS += -funsigned-bitfields     # Make any unqualified bitfield type unsigned

CFLAGS += $(EXTRA_FLAGS)


################################################################################
# Linker
################################################################################
LD = g++

LDFLAGS = 




################################################################################
# Makefile targets
################################################################################



#----------------------------------------------------
# Build all
#----------------------------------------------------
all: prepare clean $(TARGET) run

prepare:
	$(MKDIR) $(BUILDPATH)

run: $(TARGET)
	echo 'Running $(TARGET)...'
	$(RUN)/$(BUILDPATH)/$(TARGET)
	


$(TARGET): $(OBJECTS)
	@echo "\n\n-----\n building .elf file\n-----"
	$(LD) $(LDFLAGS) $(OBJECTS) -o $(BUILDPATH)/$(TARGET)


$(OBJ_PATTERN): %.c
	@echo "\n\n-----\n compiling c file '$<' -> '$@'\n-----"
	$(CC) $(CFLAGS) $< -o $@

$(OBJ_PATTERN): %.cpp
	@echo "\n\n-----\n compiling c++ file '$<' -> '$@'\n-----"
	$(CC) $(CFLAGS) $< -o $@
	
#----------------------------------------------------
# Clean Project
#----------------------------------------------------
clean:
	echo 'Running clean...'
	$(RM) $(BUILDPATH)/*
	echo 'Clean finished.'
	
