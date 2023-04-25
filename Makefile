CC		= gcc
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -lglfw -lGLU -lGL -lm

# Names of directories
BINDIR	= bin/
SRCDIR	= src/
OBJDIR	= obj/

# Names of executable and objects
EXEC = LightCorridor
OBJ = $(OBJDIR)Main.o $(OBJDIR)Racket.o $(OBJDIR)Ball.o $(OBJDIR)WindowConfig.o $(OBJDIR)3Dtools.o $(OBJDIR)Collision.o

$(BINDIR)$(EXEC): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(OBJDIR)Main.o: $(SRCDIR)Main.c $(SRCDIR)3Dtools.h $(SRCDIR)Racket.h $(SRCDIR)Ball.h $(SRCDIR)Collision.h

$(OBJDIR)Collision.o: $(SRCDIR)Collision.c $(SRCDIR)Collision.h $(SRCDIR)Racket.h $(SRCDIR)Ball.h

$(OBJDIR)3Dtools.o: $(SRCDIR)3Dtools.c $(SRCDIR)3Dtools.h

$(OBJDIR)Ball.o: $(SRCDIR)Ball.c $(SRCDIR)Ball.h

$(OBJDIR)Racket.o: $(SRCDIR)Racket.c $(SRCDIR)Racket.h $(SRCDIR)WindowConfig.h

$(OBJDIR)WindowConfig.o: $(SRCDIR)WindowConfig.h


$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	@rm -f $(OBJDIR)*.o

mrproper: clean
	@rm -rf $(OBJDIR) $(BINDIR)