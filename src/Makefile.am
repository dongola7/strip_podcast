AM_CPPFLAGS = -Wall -Werror $(TAGLIB_CFLAGS)
AM_LDFLAGS = $(TAGLIB_LIBS)
EXTRA_DIST = cmdline.ggo
CLEANFILES = cmdline.cpp cmdline.h

bin_PROGRAMS = strip_podcast

strip_podcast_SOURCES = strip_podcast.cpp
nodist_strip_podcast_SOURCES = cmdline.cpp cmdline.h

strip_podcast.$(OBJEXT): cmdline.h

%.cpp %.h: %.ggo
	$(GENGETOPT) --input=$< --c-extension=cpp
