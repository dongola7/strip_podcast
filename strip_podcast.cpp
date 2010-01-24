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
#include <string>
#include "cmdline.h"

using namespace std;

void StripPodcastFlag(TagLib::MPEG::File &mpegFile, bool verbose)
{
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
	
	bool verbose = args_info.verbose_given != 0;

	if(args_info.inputs_num == 0 && verbose)
		cerr << "Nothing to do." << endl;
		
    for(int i = 0; i < args_info.inputs_num; i++)
	{
		if(verbose)
			cerr << "Processing file " << args_info.inputs[i] << endl;
			
		TagLib::MPEG::File mpegFile(args_info.inputs[i]);		
		StripPodcastFlag(mpegFile, verbose);
	}

    return 0;
}
