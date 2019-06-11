include config.mk

SUBDIRS = src/Common src/Exception src/Task src/IO src/Scheduler

all :
	@$(do_sub_dirs) "" $(SUBDIRS)

clean :
	@$(do_sub_dirs) clean $(SUBDIRS)
