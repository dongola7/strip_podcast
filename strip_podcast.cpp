//
// A simple program to strip the ID3 tags identifying an MP3 file
// as a podcast in iTunes.
//
// Requires the id3lib library, available at http://id3lib.sourceforge.net.
//
// Author: Blair Kitchen <blair@the-blair.com>
//
#include <id3/tag.h>
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

    ID3_Tag myTag;

    myTag.Link(argv[1]);

    ID3_Tag::Iterator *pFrameIterator = myTag.CreateIterator();
    ID3_Frame *pFrame;
    while(pFrame = pFrameIterator->GetNext())
    {
        if(strcmp(pFrame->GetTextID(), "PCST") != 0)
            continue;
        
        myTag.RemoveFrame(pFrame);
        delete pFrame;
    }
    delete pFrameIterator;
    myTag.Update();

    return 0;
}
