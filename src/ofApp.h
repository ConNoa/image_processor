#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include <chrono>
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include <opencv2/highgui.hpp>

#include "filter.hpp"


using namespace ofxCv;


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void mouseEventPos(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		cv::Mat ofImgToCVMat(ofImage const& img_in);

		//-- added
		void cutResChanged();
		void filterbuttonPressed();
		void setFilterToPixel();
		void updateRectangleSize();


		ofParameterGroup	main_group;
		ofParameterGroup	slider_group;
		ofxPanel					gui;
		ofxPanel					main_gui;
//-----sampleparameters
		ofxPanel 					gui_s1;
 		ofParameterGroup	sample_slider_1;
		ofParameter<int>	m_sampleamm_abs;
		ofParameter<float>m_sampleamm_rel;
	  ofParameter<float>m_superpix_res;
		ofParameter<int>	superpixel_width;
		ofParameter<int>	superpixel_height;
		ofParameter<int>	cosx_e;
		ofParameter<int>	cosy_e;
		ofParameter<int>	border_width;
		ofParameter<int>	border_height;

//-----command-GUI
		ofxPanel 					gui_s2;
		ofParameterGroup	command_slider_2;
		ofxButton 				compute_filter;
		ofxButton 				randomsamp;
		ofxToggle 				switch_screen1;
		ofxToggle 				switch_screen2;


//----informational-GUI
		ofxPanel 					gui_s3;
		ofParameterGroup	info_slider_3;
		ofxLabel 					dim_monitor1;
		ofxLabel 					dim_monitor2;
		ofxLabel 					dim_monitor3;
		ofxLabel 					label;

//----testGUI
		ofxPanel								gui_s4;
		ofParameterGroup				test_slider_4;
		ofParameter<int> 				int_sl1;
		ofParameter<int> 				int_sl2;
		ofParameter<int>				int_sl3;
		ofParameter<float> 			flt_sl1;
		ofParameter<float>	 		flt_sl2;
		ofParameter<float>			flt_sl3;    //100% complete resolution
		ofParameter<ofVec3f> 		clr_sl1;			//color
		ofParameter<ofVec2f> 		vec2_sl1 ;
		ofParameter<ofVec2f> 		vec2_sl2;
		ofParameter<ofVec3f> 		vec3_sl1;
		ofParameter<ofVec4f>		vec4_sl1;

		ofxToggle 							tog1;
		ofxButton 							but1;
//----------------Inputfields
		ofxIntField				intField;
		ofxFloatField		 	floatField;
		ofxTextField 			textField;

//-----------some FLAGS
		bool 							filter_loaded;
		bool 							filter_exists;
		bool 							pixel_filter_exists;
		bool 							bHide;

//--cv::STRUCTS

		Filter 						pix_filter;

		cv::Mat 					actual_filterdata;
		cv::Mat 					lena_mat;
		cv::Mat 					submat;
		cv::Mat 					test;

//Images
		ofImage 					test_img;
		ofImage 					test2_img;
		ofImage 					filterImage;
		ofImage 					roi_1;
		ofImage 					roi2;

		ofPixels 					lena_pix;

//testparameter
		int 							x_roi, y_roi;
		int 							width_roi, height_roi;
		int 							mouse_x, mouse_y;


};
