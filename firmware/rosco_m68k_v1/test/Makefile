# Make rosco_m68k hosted test pack
# 
# Copyright (c)2019 Ross Bamford
# See LICENSE
#
# This is based on the example Unity makefile

EXTRA_CFLAGS?=
CC=gcc
LD=gcc
RM=rm -f
MKDIR=mkdir -p

# Paths and wildcards
PATHT=src/
PATHB=build/
PATHS=../
PATHU=../../unity/src/
PATHO=$(PATHB)objs/
PATHR=$(PATHB)results/

BUILD_PATHS=$(PATHB) $(PATHO) $(PATHR)
SRCT=$(wildcard $(PATHT)*.c)
RESULTS=$(patsubst $(PATHT)Test%.c,$(PATHR)Test%.txt,$(SRCT))

CFLAGS=-DTEST -std=c11 -Wall -pedantic -Werror -I./include -I$(PATHS)include  \
	-I$(PATHU)

$(PATHR)%.txt: $(PATHB)%.out
	-./$< > $@ 2>&1

$(PATHB)Test%.out: $(PATHO)Test%.o $(PATHO)%.o $(PATHO)unity.o
	$(LD) $(LDFLAGS) -o $@ $^

$(PATHO)%.o:: $(PATHT)%.c
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c -o $@ $<

$(PATHO)%.o:: $(PATHS)%.c
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c -o $@ $<

$(PATHO)%.o:: $(PATHU)%.c $(PATHU)%.h
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c -o $@ $<

$(PATHB):
	$(MKDIR) $(PATHB)

$(PATHO):
	$(MKDIR) $(PATHO)

$(PATHR):
	$(MKDIR) $(PATHR)


.PHONY: all clean check

all: check

clean: 
	$(RM) -r $(PATHB)

check: $(BUILD_PATHS) $(RESULTS)
	@echo -e "-------------------------\nIGNORES:\n-------------------------"
	@echo `grep -s IGNORE $(PATHR)*.txt`
	@echo -e "-------------------------\nFAILURES:\n-------------------------"
	@echo `grep -s FAIL $(PATHR)*.txt`
	@echo -e "\nDONE"

.PRECIOUS: $(PATHB)Test%.out
.PRECIOUS: $(PATHO)%.o
.PRECIOUS: $(PATHR)%.txt

