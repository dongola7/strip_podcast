#
# See the included LICENSE file for licensing information.
#
# The path to the id3lib (http://id3lib.sourceforge.net).  This library
# is used for ID3 tag parsing and is required.
TAGLIB_PATH = /opt/local

# Don't change anything below this line.
CXXFLAGS = -I $(TAGLIB_PATH)/include
LDFLAGS = -L$(TAGLIB_PATH)/lib -ltag

strip_podcast: strip_podcast.cpp cmdline.c

cmdline.h cmdline.c: cmdline.ggo
	gengetopt < cmdline.ggo

clean:
	rm -f strip_podcast

full-clean: clean
	rm -f cmdline.[hc]
