CC		= gcc
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -lglfw -lGLU -lGL -lm

BINDIR	= bin/
SRCDIR	= src/
OBJDIR	= obj/

EXEC = LightCorridor
OBJ = $(OBJDIR)Main.o

$(BINDIR)$(EXEC): $(OBJ)
	mkdir -p "$(BINDIR)"
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(OBJDIR)Main.o: $(SRCDIR)Main.c

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p "$(OBJDIR)"
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	rm $(OBJDIR)*.o

mrproper: clean
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)