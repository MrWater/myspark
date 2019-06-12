include config.mk

SUBDIRS = src/common src/exception src/task src/io src/scheduler

all :
	@$(do_sub_dirs) "" $(SUBDIRS)

clean :
	@$(do_sub_dirs) clean $(SUBDIRS)
