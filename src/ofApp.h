#pragma once

#include "ofMain.h"
#include "GuiApp.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include <opencv2/highgui.hpp>
#include <memory>

//using namespace ofxCv;
//using namespace cv;


class ofApp : public ofBaseApp{

	public:
		void setup();

		void update();
		void draw();
		void drawPresentWindow();

		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		shared_ptr<GuiApp> gui;

		cv::Mat ofImgToCVMat(ofImage const &img_in);

		ofImage test_img;
};
