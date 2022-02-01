/*#include "corpus_inspektor.h"

bool Corpus_Inspektor::check_format(Magick::Image Image_)
{
    //  std::cout <<"filterout_bad_format()"<<"\n";
    std::vector<std::string> lossless_formats;
    lossless_formats.push_back("BMP");
    lossless_formats.push_back("PNG");
    lossless_formats.push_back("ARW");
    for (auto i : lossless_formats)
    {
        if (i == Image_.magick())
        {
            return true;
        }
    }
    return false;
}
*/