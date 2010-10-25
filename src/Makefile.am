AM_CPPFLAGS = -Wall -Werror
BUILT_SOURCES = cmdline.cpp cmdline.h
EXTRA_DIST = cmdline.ggo

bin_PROGRAMS = strip_podcast

strip_podcast_CXXFLAGS = $(TAGLIB_CFLAGS)
strip_podcast_LDFLAGS = $(TAGLIB_LIBS)
strip_podcast_SOURCES = strip_podcast.cpp cmdline.cpp cmdline.h

%.cpp %.h: %.ggo
	$(gengetopt) --input=$< --c-extension=cpp
