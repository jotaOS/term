export PROJNAME := term
export RESULT := term

.PHONY: all

all: $(RESULT)
	@

%: force
	@$(MAKE) -f ../helper/Makefile $@ --no-print-directory
force: ;
