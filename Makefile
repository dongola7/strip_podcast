#
# See the included LICENSE file for licensing information.
#
# The path to the id3lib (http://id3lib.sourceforge.net).  This library
# is used for ID3 tag parsing and is required.
TAGLIB_PATH = /opt/local

# Don't change anything below this line.
CXX = g++
CXXFLAGS = -I $(TAGLIB_PATH)/include
LDFLAGS = -L$(TAGLIB_PATH)/lib -ltag
OBJS := cmdline.o strip_podcast.o
PROGRAM_NAME = strip_podcast

$(PROGRAM_NAME): $(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $^

-include $(OBJS:.o=.d)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $*.cpp -o $*.o
	$(CXX) -MM $(CXXFLAGS) $*.cpp > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
		sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

%.cpp %.h: %.ggo
	gengetopt --input=$< --c-extension=cpp

clean:
	rm -rf *.o *.d
	rm -rf $(PROGRAM_NAME)

full-clean: clean
	rm -f cmdline.h
	rm -f cmdline.cpp

.SECONDARY:
