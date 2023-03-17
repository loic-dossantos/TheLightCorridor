CC		= gcc
CFLAGS	= -Wall -O2 -g
LDFLAGS	= 
ifeq ($(OS),Windows_NT)
	LDFLAGS += -L"C:\Users\rikud\Documents\librairies\glfw-3.3.8.bin.WIN64\include"
endif
LDFLAGS	+= -lglfw -lGLU -lGL -lm

# Names of directories
BINDIR	= bin/
SRCDIR	= src/
OBJDIR	= obj/

# Names of executable and objects
EXEC = LightCorridor
OBJ = $(OBJDIR)Main.o

# Create the directory obj/ if doesn't exist 
MKDIR_OBJ = @
ifeq ($(OS),Windows_NT)
	MKDIR_OBJ += if not exist "obj" mkdir "obj"
else
	MKDIR_OBJ += mkdir -p $(OBJDIR)
endif

# Create the directory bin/ if doesn't exist 
MKDIR_BIN = @
ifeq ($(OS),Windows_NT)
	MKDIR_BIN += if not exist "bin" mkdir "bin"
else
	MKDIR_BIN += mkdir -p $(BINDIR)
endif

# Delete all objects files
RM_OBJ = @
ifeq ($(OS),Windows_NT)
	RM_OBJ += del /F /Q obj
else
	RM_OBJ += rm -f $(OBJDIR)*.o
endif

# Delete bin/ and obj/ directories and the executable
RM_ALL = @
ifeq ($(OS),Windows_NT)
	RM_ALL += rmdir /S /Q obj bin
else
	RM_ALL += rm -rf $(OBJDIR) $(BINDIR)
endif

$(BINDIR)$(EXEC): $(OBJ)
	$(MKDIR_BIN)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(OBJDIR)Main.o: $(SRCDIR)Main.c

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(MKDIR_OBJ)
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	$(RM_OBJ)

mrproper: clean
	$(RM_ALL)