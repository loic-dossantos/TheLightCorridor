CC		= gcc
CFLAGS	= -Wall -O2 -g
LDFLAGS	= -lglfw -lGLU -lGL -lm

# Names of directories
BINDIR	= bin/
SRCDIR	= src/
OBJDIR	= obj/

# Names of executable and objects
EXEC = LightCorridor

OBJ = $(OBJDIR)Main.o $(OBJDIR)Racket.o $(OBJDIR)Ball.o $(OBJDIR)WindowConfig.o $(OBJDIR)3Dtools.o $(OBJDIR)Collision.o $(OBJDIR)TextureControl.o $(OBJDIR)Corridor.o $(OBJDIR)Wall.o $(OBJDIR)Bonus.o

$(BINDIR)$(EXEC): $(OBJ)
	@mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(OBJDIR)Main.o: $(SRCDIR)Main.c $(SRCDIR)3Dtools.h $(SRCDIR)Racket.h $(SRCDIR)Ball.h $(SRCDIR)Collision.h $(SRCDIR)Corridor.h $(SRCDIR)TextureControl.h

$(OBJDIR)Collision.o: $(SRCDIR)Collision.c $(SRCDIR)Collision.h $(SRCDIR)Racket.h $(SRCDIR)Ball.h $(SRCDIR)Corridor.h

$(OBJDIR)Corridor.o: $(SRCDIR)Corridor.c $(SRCDIR)Corridor.h $(SRCDIR)Racket.h $(SRCDIR)Ball.h $(SRCDIR)Wall.h $(SRCDIR)Bonus.h

$(OBJDIR)3Dtools.o: $(SRCDIR)3Dtools.c $(SRCDIR)3Dtools.h

$(OBJDIR)Bonus.o: $(SRCDIR)Bonus.c $(SRCDIR)Bonus.h

$(OBJDIR)Wall.o: $(SRCDIR)Wall.c $(SRCDIR)Wall.h

$(OBJDIR)Ball.o: $(SRCDIR)Ball.c $(SRCDIR)Ball.h

$(OBJDIR)Racket.o: $(SRCDIR)Racket.c $(SRCDIR)Racket.h $(SRCDIR)WindowConfig.h

$(OBJDIR)WindowConfig.o: $(SRCDIR)WindowConfig.h

$(OBJDIR)TextureControl.o: $(SRCDIR)TextureControl.c $(SRCDIR)TextureControl.h

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	@rm -f $(OBJDIR)*.o

mrproper: clean
	@rm -rf $(OBJDIR) $(BINDIR)