CXX=g++
CFLAGS=--std=c++11
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
