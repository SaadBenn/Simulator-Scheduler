PROGRAM_NAME = main

OBJECT_FILES = $(PROGRAM_NAME).o
CFLAGS = -O2 -g

$(PROGRAM_NAME) : $(OBJECT_FILES)
	gcc $(CFLAGS) -o $@ $(OBJECT_FILES)

$(PROGRAM_NAME).o : $(PROGRAM_NAME).c helper.h
	gcc $(CFLAGS) -c $<

clean :
	$(RM) $(PROGRAM_NAME)
	$(RM) $(OBJECT_FILES)
	$(RM) *~ *.bak