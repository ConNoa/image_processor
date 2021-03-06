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

		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);

		shared_ptr<GuiApp> gui;

		cv::Mat ofImgToCVMat(ofImage const &img_in);

		//ofImage test_img;
		ofTexture orig_img;
		ofPoint pnt[4];
		ofRectangle draw_bnds;
		//ofRectangle subsec_bnds;

		int mP_x, mP_y;
		int mD_x = 0;
		int mD_y = 0;


//		int mouse_x;
	//	int mouse_y;
};
