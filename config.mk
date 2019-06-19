CXX=g++
CFLAGS=--std=c++11 -g -Wall
BINDIR=bin

define mvbin
	if [ ! -d $(BINDIR) ]; then \
		mkdir $(BINDIR); \
	fi; \
	rm ${BINDIR}/* -f; \
	for arg in $^; do \
		mv $$arg $(BINDIR); \
		echo "mv $$arg $(BINDIR)"; \
	done;
endef

define cleanbin
	rm $(BINDIR) -rf; \
	echo "rm $(BINDIR) -rf"
endef

RED_TTY := \033[31;1m
GREEN_TTY := \033[32;1m
BLUE_TTY := \033[33;1m
CLOSE_TTY := \033[m

do_sub_dirs = do_sub_dirs() { \
	act=$$1; shift;\
	for dir in $$*; do \
		make -C $$dir -f Makefile $$act; \
		if [ $$? -eq 0 ]; then \
			echo -e "$(GREEN_TTY)MAKE $$act in $$dir OK$(CLOSE_TTY)";\
		else \
			echo -e "$(RED_TTY)MAKE $$act in $$dir FAIL$(CLOSE_TTY)";\
			break; \
		fi \
	done }; \
	do_sub_dirs
