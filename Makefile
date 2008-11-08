# The path to the id3lib (http://id3lib.sourceforge.net).  This library
# is used for ID3 tag parsing and is required.
ID3LIB_PATH = $(HOME)/local

# Don't change anything below this line.
CXXFLAGS = -I $(ID3LIB_PATH)/include
LDFLAGS = -L$(ID3LIB_PATH)/lib -lid3

strip_podcast: strip_podcast.cpp

clean:
	rm -f strip_podcast
