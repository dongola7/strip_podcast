//
// See the included LICENSE file for licensing information.
//
// A simple program to strip the ID3 tags identifying an MP3 file
// as a podcast in iTunes.
//
// Requires the id3lib library, available at http://id3lib.sourceforge.net.
//
// Author: Blair Kitchen <blair@the-blair.com>
//
#include <taglib/mpegfile.h>
#include <taglib/id3v2tag.h>
#include <iostream>
#include <cstdlib>
#include "cmdline.h"

using namespace std;

void StripPodcastFlag(const char *const fileName, bool verbose)
{
	if(verbose)
		cerr << "Processing file " << fileName << endl;
		
    TagLib::MPEG::File mpegFile(fileName);

    if(mpegFile.ID3v2Tag() == NULL)
	{
		if(verbose)
			cerr << "Could not find a valid ID3v2 header." << endl;
		return;
	}

    TagLib::ID3v2::Tag *pTag = mpegFile.ID3v2Tag();
    for(TagLib::List<TagLib::ID3v2::Frame*>::ConstIterator iter = pTag->frameList().begin();
        iter != pTag->frameList().end();
        iter++)
	{
		TagLib::ID3v2::Frame *pFrame = *iter;
        if(pFrame->frameID() != "PCST")
            continue;

        pTag->removeFrame(pFrame);
		if(verbose)
			cerr << "Removed podcast frame in ID3v2 header." << endl;
        break;
      }
      mpegFile.save();
}

int main(int argc, char **argv)
{
    gengetopt_args_info args_info;

    if(cmdline_parser(argc, argv, &args_info) != 0)
		exit(1);

	if(args_info.inputs_num == 0 && args_info.verbose_given != 0)
		cerr << "Nothing to do." << endl;
		
    for(int i = 0; i < args_info.inputs_num; i++)
		StripPodcastFlag(args_info.inputs[i], args_info.verbose_given != 0);

    return 0;
}
