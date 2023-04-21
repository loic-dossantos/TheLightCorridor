CC		= gcc
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -lglfw -lGLU -lGL -lm

# Names of directories
BINDIR	= bin/
SRCDIR	= src/
OBJDIR	= obj/

# Names of executable and objects
EXEC = LightCorridor
OBJ = $(OBJDIR)Main.o

$(BINDIR)$(EXEC): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(OBJDIR)Main.o: $(SRCDIR)Main.c

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	@rm -f $(OBJDIR)*.o

mrproper: clean
	@rm -rf $(OBJDIR) $(BINDIR)