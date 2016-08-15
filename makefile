BIN_SIMULADOR = simulador
SRCS_SIMULADOR = $(wildcard src/ep1sh/*.c) $(wildcard src/*.c)

INCS = -Isrc/
LIBS = -lpthread

CFLAGS = $(INCS) -c -g -Wall -pedantic
LDFLAGS = $(LIBS)
OUTFLAG = -o
INFLAG =

CC = gcc
DEPGEN = gcc $(INCS) -MM -MP -MT $(patsubst %$(SRCEXT),%$(OBJEXT),$<)
RM = rm -f
TOUCH = touch

OBJEXT = .o
DEPEXT = .d
SRCEXT = .c
OBJS_SIMULADOR = $(SRCS_SIMULADOR:$(SRCEXT)=$(OBJEXT))
DEPS = $(SRCS_EP1:$(SRCEXT)=$(DEPEXT)) $(SRCS_SIMULADOR:$(SRCEXT)=$(DEPEXT))

all: $(BIN_SIMULADOR)

$(BIN_SIMULADOR): $(OBJS_SIMULADOR)
	$(CC) $(LDFLAGS) $(INFLAG)$^ $(OUTFLAG)$@

clean: clean_ep1sh

clean_ep1simulador:
	$(RM) $(BIN_SIMULADOR) $(OBJS_SIMULADOR) $(DEPS)

%$(OBJEXT): %$(SRCEXT)
	$(DEPGEN) $< $(OUTFLAG)$(patsubst %$(OBJEXT),%$(DEPEXT),$@)
	$(CC) $(CFLAGS) $(INFLAG)$< $(OUTFLAG)$@

%$(DEPEXT): %$(SRCEXT)
	@$(TOUCH) $@

-include $(DEPS)
