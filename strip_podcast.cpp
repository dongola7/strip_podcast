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

using namespace std;

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <mp3-file>" << endl;
        exit(-1);
    }

    TagLib::MPEG::File mpegFile(argv[1]);

    if(mpegFile.ID3v2Tag() == NULL)
        return 0;

    TagLib::ID3v2::Tag *pTag = mpegFile.ID3v2Tag();
    for(TagLib::List<TagLib::ID3v2::Frame*>::ConstIterator iter = pTag->frameList().begin();
        iter != pTag->frameList().end();
        iter++)
    {
        TagLib::ID3v2::Frame *pFrame = *iter;
        if(pFrame->frameID() != "PCST")
            continue;

        pTag->removeFrame(pFrame);
        break;
    }
    mpegFile.save();

    return 0;
}
