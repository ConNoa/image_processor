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
		ofxButton 				compute_filter;
		ofxButton 				randomsamp;
		ofxToggle 				switch_screen1;
		ofxToggle 				switch_screen2;


//----informational-GUI
		ofxPanel 					gui_s3;
		ofxLabel 					dim_monitor1;
		ofxLabel 					dim_monitor2;
		ofxLabel 					dim_monitor3;

		ofxLabel 					label;


		bool 							filter_loaded;
		bool 							filter_exists;
		bool 							pixel_filter_exists;
		bool 							bHide;


//----testGUI
		ofxIntSlider 			filter_expo;
		ofxIntSlider 			cutResolution;
		ofxFloatSlider 		radius;
		ofxColorSlider 		color;
		ofxVec2Slider 		center;

		ofxToggle 				filled;
		ofxButton 				twoCircles;

//Sampleparameter
		// ofxIntSlider 				m_sampleamm_abs;
		// ofxFloatSlider	 			m_sampleamm_rel;
		// ofxFloatSlider				m_superpix_res;    //100% complete resolution





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
//Testparameter
		int 							x_roi, y_roi;
		int 							width_roi, height_roi;
		int 							mouse_x, mouse_y;


//----------------Tutorial Zusatz
		ofxIntField				intField;
		ofxFloatField		 	floatField;
		ofxTextField 			textField;


		ofxVec2Slider 		vec2S;
		ofxVec3Slider 		vec3S;
		ofxVec4Slider			vec4S;

};
