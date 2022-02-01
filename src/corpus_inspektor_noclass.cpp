/*
#include <opencv2/highgui.hpp>
#include <Magick++.h>
#include <iostream>
#include <dirent.h>
#include <string>
#include <fstream>
#include <ios>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <experimental/filesystem>



using namespace cv;

const std::string source_folder= "../01_possible_corpus";
const std::string res_folder= "../03_received_corpus";
const std::string reject_folder= "../02_not_used_for_corpus";
const std::pair <int, int> disp_res (800, 600);

std::vector<std::string> filenames;
//std::vector<std::pair<std::string, Mat>> possib_corp_imgs;
std::vector<std::pair<std::string, Magick::Image>> images_possib;
std::vector<std::pair<std::string, Mat>> bad_corp;



bool hasEnding (const std::string& fullString, const std::string& ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}


bool check_format(Magick::Image Image_){
//  std::cout <<"filterout_bad_format()"<<"\n";
  std::vector<std::string> lossless_formats;
  lossless_formats.push_back("BMP");
  lossless_formats.push_back("PNG");
  lossless_formats.push_back("ARW");
  for (auto i : lossless_formats){
    if(i == Image_.magick()){
      return true;
    }
  }
  return false;
}

void moveFileTo (const std::string& filename_, const std::string& dir_, const std::string& dirToMove_){
  std::string fileToMove = dir_+"/"+filename_;
  const char* FtrM = fileToMove.c_str();
  std::string FileTo = dirToMove_+"/"+filename_;
//  std::cout << fileToMove << std::endl;
//  std::cout << FileTo << std::endl;
  std::experimental::filesystem::copy(fileToMove, FileTo);
  std::remove(FtrM);
  return;
}

void rename_file (const std::string& filename_, const std::string& dir_, const std::string& newName_){
  std::string fileToRename = dir_+"/"+filename_;
  std::string FileTo = dir_+"/"+ newName_;
  const char* fileToR = fileToRename.c_str();
  const char* NewName = FileTo.c_str();
  //  std::cout << fileToMove << std::endl;
  //  std::cout << FileTo << std::endl;
  if(std::rename(fileToR, NewName) < 0) {
    std::cout << strerror(errno) << '\n';
  }
  return;
}

//Get files of input folder:
void readFiles (const std::string& dir_){
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir_.c_str())) == NULL) {
        std::cout << "Error(" << errno << ") opening " << dir_ << std::endl;
    }

    while ((dirp = readdir(dp)) != NULL) {
      if(((std::string("README")).compare(dirp->d_name) != 0) && ((std::string(".")).compare(dirp->d_name) != 0) &&((std::string("..")).compare(dirp->d_name) != 0))
      {
      std::cout << "Found "<<dirp->d_name<<std::endl;
        Magick::Image local_file_image(dir_+"/"+dirp->d_name);
        if (check_format(local_file_image) == true){
          images_possib.push_back(std::make_pair(std::string(dirp->d_name), local_file_image));
          std::cout << dir_+"/"+dirp->d_name << " added"<<std::endl;
        }
        else {
          std::cout << dir_+"/"+dirp->d_name << " has wrong format"<<std::endl;
          moveFileTo(dirp->d_name, dir_, reject_folder);
          char newname[800];
          strcpy(newname, "wrong_format_");
          std::strcat(newname, dirp->d_name);
          rename_file(dirp->d_name, reject_folder, newname);
        }
      }
      std::cout << std::endl;
    }
    closedir(dp);
    std::cout << "Number of files in possible corpus: "<< images_possib.size() << std::endl;
    return;
}

void check_dimensions(int w_, int h_){
  auto it  = images_possib.begin();
  while (it != images_possib.end()){
    if(it->second.columns()< w_ && it->second.rows() < h_){
      std::cout  << "Image "<<it->first<<" in width and height to small for corpus:   (" ;
      std::cout  << it->second.columns() << "x"<< it->second.rows() <<") "<<std::endl;
      std::string col = std::to_string(it->second.columns());
      std::string ro = std::to_string(it->second.rows());
      std::string why = "to_small_"+col+"x"+ro+"_";
      std::string new_name = why + it->first;
      rename_file(it->first, source_folder, new_name);
      it->first = new_name;
      std::cout << it->first<<std::endl<<std::endl;
      moveFileTo(it->first, source_folder, reject_folder);
      it = images_possib.erase(it);
    }

    else if(it->second.columns()< w_){
      std::cout  << "Image "<<it->first<<" in width to small for corpus:   (" ;
      std::cout  << it->second.columns() << "x"<< it->second.rows() <<") "<<std::endl;
      std::string col = std::to_string(it->second.columns());
      std::string ro = std::to_string(it->second.rows());
      std::string why = "to_small_"+col+"x"+ro+"_";
      std::string new_name = why + it->first;
      rename_file(it->first, source_folder, new_name);
      it->first = new_name;
      std::cout << it->first<<std::endl<<std::endl;
      moveFileTo(it->first, source_folder, reject_folder);
      it = images_possib.erase(it);
    }

    else if(it->second.rows() < h_){
      std::cout  << "Image "<<it->first<<" in height to small for corpus:   (" ;
      std::cout  << it->second.columns() << "x"<< it->second.rows() <<") "<<std::endl;
      std::string col = std::to_string(it->second.columns());
      std::string ro = std::to_string(it->second.rows());
      std::string why = "to_small_"+col+"x"+ro+"_";
      std::string new_name = why + it->first;
      rename_file(it->first, source_folder, new_name);
      it->first = new_name;
      std::cout << it->first<<std::endl<<std::endl;
      moveFileTo(it->first, source_folder, reject_folder);
      it = images_possib.erase(it);
    }

    else {
      ++it;
    }
  }
  std::cout << "Number of files in possible corpus: "<< images_possib.size() << std::endl;
  return;
}

std::pair<double, double> compute_zoomfaktor(const Magick::Image& image_){

  double zoom_hori = disp_res.first/(double)image_.columns();
  double zoom_vert = disp_res.second/(double)image_.rows();
  if(zoom_hori <= zoom_vert){
    double skl_x = zoom_hori * image_.columns();
    double skl_y = zoom_hori * image_.rows();
    std::pair<double, double> zoom_output (skl_x, skl_y);
    return zoom_output;
  }
  else{
    double skl_x = zoom_vert * image_.columns();
    double skl_y = zoom_vert * image_.rows();
    std::pair<double, double> zoom_output (skl_x, skl_y);
    return zoom_output;
  }
}

// void show_img_ocv(){
//   int iter = 0;

//   for (auto& x : possib_corp_imgs){
//     std::string number = "image" + std::to_string (iter);
//     namedWindow(number, WINDOW_AUTOSIZE);
//     imshow(number, x.second);
//     ++iter;
//     waitKey(0);
//   }
// }


std::string rename_catchy(const std::pair<std::string, Magick::Image>& img_){
  std::string filename_temp_;

  int actlCountCorpus = 0;
  DIR *dc;
  struct dirent *dirp;

  if((dc  = opendir(res_folder.c_str())) == NULL) {
      std::cout << "Error(" << errno << ") opening " << res_folder << std::endl;
  }
  while ((dirp = readdir(dc)) != NULL) {
    if(((std::string("README")).compare(dirp->d_name) != 0) &&((std::string(".")).compare(dirp->d_name) != 0) && ((std::string("..")).compare(dirp->d_name) != 0))
    {
//      if (check_format(img_) == true){
// 
        ++actlCountCorpus;
  //     }
  //     else {
  //       std::cout << source_folder+"/"+dirp->d_name << " has wrong format"<<std::endl;
  //     }
  //   }
  }
  std::string actlCountCorp_S = std::to_string(actlCountCorpus);
  std::cout << "actual "<< actlCountCorpus << " pictures in corpus " << std::endl;

  std:: string actl_col  = std::to_string(img_.second.columns());
  std:: string actl_row  = std::to_string(img_.second.rows());


  std::cout << " Actual name of picture is: "<< img_.first << std::endl;
  std::cout <<"type catchy name:"<<"\n";
  std::string catchyname;
  std::cin >> catchyname;
  if(catchyname.length() > 3){
    std::string ending = img_.second.magick();
    std::for_each(ending.begin(), ending.end(), [](char & c){
      c = ::tolower(c);
    });
    catchyname = actlCountCorp_S + "_"+catchyname +"_" +actl_col+"x"+ actl_row+ "." + ending;
    filename_temp_ = catchyname;
  }
  return filename_temp_;
}

void format_to_png(){
  for (auto& img : images_possib){
    if("PNG" != img.second.magick()){
      std::cout << "wrong format"<< std::endl;
      img.second.magick("png");
    }
  }
}

int main( int argc, char** argv ) {

  std::string min_colmn_s = argv[1];
  int min_colmn = std::stoi(min_colmn_s);
  std::string min_row_s = argv[2];
  int min_row = std::stoi(min_row_s);
  std::string mincoldepth_s = argv[3];
  int min_coldepth = std::stoi(mincoldepth_s);

  std::cout << "\n";
  std::cout << "CorpusInspector will bring potential pictures to right format in order to push them to: "<<res_folder<<" \n";
  std::cout << "minimum requirements for the pictures are: min_width: "<<min_colmn_s<< "   min_height: "<<min_row_s<< "   min_colordepth of: "<<mincoldepth_s<< "\n";
  std::cout << "\n";
  std::cout << "pictures are taken from:  " << source_folder << "\n";
  std::cout << "\n";
  std::cout << "process possible corpus images\n";
  std::vector<Mat> files;
  readFiles(source_folder);
  std::cout << std::endl;
  std::cout << "cheking dimensions of images in possible corpus"<< std::endl;
  std::cout << std::endl;

  check_dimensions(min_colmn, min_row);
  std::cout << std::endl;
  std::cout << "Give files of Corpus a name, matching the theme of image";
  std::cout << "\n";

  format_to_png();


  // for (auto& x : possib_corp_imgs){
  //   //std::cout << x.first <<"\n";
  // //  Magick::Image local_file_image(source_folder+"/"+x.first);
  //   //images_possib.push_back(std::make_pair(std::string(x.first), local_file_image));
  // }


  for (auto& x : images_possib){
    Magick::Image temp_image(x.second);
    std::pair<double, double> zf = compute_zoomfaktor(temp_image);
    temp_image.zoom(Magick::Geometry(zf.first, zf.second));
    temp_image.display();
    std::string filename_temp = rename_catchy(x);
    rename_file(x.first, source_folder, filename_temp);
    x.first = filename_temp;
    moveFileTo(x.first, source_folder, res_folder);
  }



// int iters = 0;
// for (auto& x : possib_corp_imgs){
//   std::string number = "image" + std::to_string (iters);
//   std::cout << "Found "<<x.first<<"  \n";
//   if (filterout_bad_format(x.first)){
//     std::cout <<"has bad format. \n";
//     bad_corp.push_back(x);
//   }
//   else {
//     std::cout << "format fit's \n";
//   }
// //        std::cout<< x.second.type()<< "    type \n";
// //        std::cout<< x.second.depth()<< "    depth \n";
// //        std::cout<< x.second.channels()<< "   channel \n";
// }


//bad_out_of_corp();


// show_img_ocv();

  // for (auto& x : filenames){
  //   std::cout << x <<"\n";
  // }


  return 0;
}
*/