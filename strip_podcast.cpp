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
#include <mpegfile.h>
#include <id3v2tag.h>
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

void FixTitle(TagLib::MPEG::File &mpegFile, const string &splitString, bool verbose)
{
	if(verbose)
		cerr << "Attempting to fix title." << endl;
		
	TagLib::String title = mpegFile.tag()->title();
	
	int offset = title.find(splitString);
	if(offset == -1)
	{
		if(verbose)
			cerr << "Unable to find '" << splitString << "' in title '" << title << "'" << endl;
		return;
	}
	
	if(title.find(splitString, offset + 1) != -1)
	{
		if(verbose)
			cerr << "Found multiple '" << splitString << "' in title '" << title << "'" << endl;
		return;
	}
	
	TagLib::String newArtist = title.substr(0, offset);
	TagLib::String newTitle = title.substr(offset + splitString.length());
	
	mpegFile.tag()->setArtist(newArtist);
	mpegFile.tag()->setTitle(newTitle);
	
	if(verbose)
		cerr << "New author '" << newArtist << "' and title '" << newTitle << "'" << endl;
}

bool FileExists(const string &fileName)
{
	if(FILE *file = fopen(fileName.c_str(), "r"))
	{
		fclose(file);
		return true;
	}
	
	return false;
}

static const int FILE_NAME_LEN = 255;

int main(int argc, char **argv)
{
    gengetopt_args_info args_info;

	cmdline_parser_params parser_params;
	cmdline_parser_params_init(&parser_params);
	parser_params.check_required = 0;
	
	string configFileName(getenv("HOME"));
	configFileName += "/.strip_podcast";
	
	if(FileExists(configFileName))
	{
		if(cmdline_parser_config_file(const_cast<char*>(configFileName.c_str()), &args_info, &parser_params) != 0)
			exit(1);
	}
	
	parser_params.check_required = 1;
	parser_params.override = 1;
	parser_params.initialize = 0;

    if(cmdline_parser_ext(argc, argv, &args_info, &parser_params) != 0)
		exit(1);
	
	bool verbose = args_info.verbose_given != 0;

	if(args_info.inputs_num == 0 && verbose)
		cerr << "Nothing to do." << endl;
	
	cout << "args_info.inputs_num = " << args_info.inputs_num << endl;
    for(unsigned int i = 0; i < args_info.inputs_num; i++)
	{
		if(verbose)
			cerr << "Processing file " << args_info.inputs[i] << endl;
			
		TagLib::MPEG::File mpegFile(args_info.inputs[i]);
		if(args_info.fix_title_given != 0)
			FixTitle(mpegFile, args_info.title_split_string_arg, verbose);
		
		StripPodcastFlag(mpegFile, verbose);
	}

    return 0;
}
