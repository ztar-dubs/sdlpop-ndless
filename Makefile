# Makefile for SDLPoP TI-Nspire CX CAS II port
# Requires: ndless-sdk (nspire-gcc, genzehn, make-prg)

# Output
TARGET  = prince
ELF     = $(TARGET).elf
ZEHN    = $(TARGET).zehn
TNS     = $(TARGET).tns

# Toolchain
CC      = nspire-gcc
LD      = nspire-gcc
GENZEHN = genzehn
MAKEPRG = make-prg

# Directories
SRCDIR  = src
NSPDIR  = nspire
PRODDIR = prod

# Compiler flags
GCCFLAGS = -Wall -W -marm -mno-unaligned-access \
           -ffunction-sections -fdata-sections \
           -fno-unwind-tables -fno-asynchronous-unwind-tables \
           -std=c99 -Os

CFLAGS  = $(GCCFLAGS) \
          -I$(NSPDIR) -I$(SRCDIR) \
          -DNSPIRE -DNDEBUG -DLSB_FIRST=1 -DNO_AUDIO \
          -D_GNU_SOURCE

LDFLAGS = -Wl,--gc-sections \
          -Wl,--wrap=fopen \
          -Wl,--wrap=open \
          -Wl,--wrap=stat \
          -Wl,--wrap=clock \
          -Os -marm -mno-unaligned-access

LIBS    = -lSDL -lz -lm

# Source files - SDLPoP core (excluding audio/features disabled on Nspire)
CORE_SRC = \
	$(SRCDIR)/main.c \
	$(SRCDIR)/data.c \
	$(SRCDIR)/seg000.c \
	$(SRCDIR)/seg001.c \
	$(SRCDIR)/seg002.c \
	$(SRCDIR)/seg003.c \
	$(SRCDIR)/seg004.c \
	$(SRCDIR)/seg005.c \
	$(SRCDIR)/seg006.c \
	$(SRCDIR)/seg007.c \
	$(SRCDIR)/seg008.c \
	$(SRCDIR)/seg009.c \
	$(SRCDIR)/seqtbl.c \
	$(SRCDIR)/options.c \
	$(SRCDIR)/midi.c \
	$(SRCDIR)/opl3.c

# Nspire platform files
NSPIRE_SRC = \
	$(NSPDIR)/nspire_compat.c \
	$(NSPDIR)/nspire_stubs.c

# nspire_fopen.c must be compiled WITHOUT -flto for --wrap to work
FOPEN_SRC = $(NSPDIR)/nspire_fopen.c

# Objects
CORE_OBJ   = $(CORE_SRC:.c=.o)
NSPIRE_OBJ = $(NSPIRE_SRC:.c=.o)
FOPEN_OBJ  = $(FOPEN_SRC:.c=.o)
ALL_OBJ    = $(CORE_OBJ) $(NSPIRE_OBJ) $(FOPEN_OBJ)

# Rules
.PHONY: all clean prod

all: $(PRODDIR)/$(TNS)

# nspire_fopen.o: compile without -flto so --wrap symbols are visible
$(FOPEN_OBJ): $(FOPEN_SRC)
	$(CC) $(filter-out -flto,$(CFLAGS)) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(ELF): $(ALL_OBJ)
	$(LD) $(LDFLAGS) -Wl,-Map=prince.map -o $@ $^ $(LIBS)

$(ZEHN): $(ELF)
	$(GENZEHN) --input $< --output $@

$(TNS): $(ZEHN)
	$(MAKEPRG) $< $@

$(PRODDIR)/$(TNS): $(TNS) | $(PRODDIR)
	cp $< $(PRODDIR)/$(TNS)

$(PRODDIR):
	mkdir -p $(PRODDIR)

# Copy game data files to prod/data with .tns suffix (skip audio files)
prod: $(PRODDIR)/$(TNS)
	@mkdir -p $(PRODDIR)/data
	@echo "Copying game data files to $(PRODDIR)/data/..."
	@for f in "C:/Jeux/Prince/"*.DAT; do \
		base=$$(basename "$$f"); \
		case "$$base" in \
			DIGISND*|IBM_SND*|MIDISND*) ;; \
			*) cp "$$f" "$(PRODDIR)/data/$$base.tns" ;; \
		esac; \
	done
	@echo "Done. Production files are in $(PRODDIR)/"

clean:
	rm -f $(ALL_OBJ) $(ELF) $(ZEHN) $(TNS)
	rm -f $(PRODDIR)/$(TNS)
