/*#pragma once

#include <opencv2/highgui.hpp>
#include <iostream>
#include <dirent.h>
#include <string>
#include <fstream>
#include <ios>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <experimental/filesystem>
#include <Magick++.h>



using namespace cv;
using namespace std;

class CorpusInspektor{
    
    public:
        const std::string source_folder = "../01_possible_corpus";
        const std::string res_folder = "../03_received_corpus";
        const std::string reject_folder = "../02_not_used_for_corpus";
        const std::pair<int, int> disp_res(800, 600);

        std::vector<std::string> filenames;
        // std::vector<std::pair<std::string, Mat>> possib_corp_imgs;
        std::vector<std::pair<std::string, Magick::Image>> images_possib;
        std::vector<std::pair<std::string, Mat>> bad_corp;

        bool check_format(Magick::Image Image_);

    private:
};
*/