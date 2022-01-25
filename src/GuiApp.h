#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "ofxGui.h"
#include <chrono>
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include <opencv2/highgui.hpp>
#include "filter.hpp"
#include <memory>

using namespace ofxCv;
using namespace cv;

class GuiApp: public ofBaseApp {
public:
	void setup();
	void setup_gui();
	void setup_filter();

	void update();

	void draw();
	void draw_gui();
	void draw_filterPreview();
	void draw_imgPreview();



	void filtermustload(bool & trig);
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void mouseEventPos(int x, int y);

	void compute_alphfilter(int w_, int h_, int cosx_, int cosy_);

    //-- added
    void cutResChanged();
    void filterbuttonPressed();
	void setFilterToPixel();
	void updateRectangleSize();

	//ofEventListener listenerMouse; // debug mouse clicks
	void onSliderEvent(ofxDatGuiSliderEvent e);

	//-----------some FLAGS
	bool filter_loaded;
	bool filter_exists;
	bool pixel_filter_exists;
	bool bHide;

	//--cv::STRUCTS

	Filter pix_filter;

	cv::Mat actual_filterdata;
	cv::Mat lena_mat;
	cv::Mat submat;
	cv::Mat test;

	// Images
	ofImage test_img;
	ofImage test2_img;
	ofImage filterImage;
	ofImage roi_1;
	ofImage roi2;

	ofPixels lena_pix;

	// testparameter
	int x_roi, y_roi;
	int width_roi, height_roi;
	int mouse_x, mouse_y;

	ofxPanel gui;
	float pos_s1_x;
	float pos_s1_y;
	float pos_s2_x;
	float pos_s2_y;
	float pos_s3_x;
	float pos_s3_y;

	ofxPanel gui_s2;
	ofxPanel gui_s3;

	ofxDatGui* m_gui;

	ofParameterGroup sample_slider_1;
	ofParameterGroup command_slider_2;
	ofParameterGroup info_slider_3;

	//-----sampleparameters
	ofParameter<int> m_sampleamm_abs;
	ofParameter<float> m_sampleamm_rel;
	ofParameter<float> m_superpix_res;
	ofParameter<int> superpixel_width;
	ofParameter<int> superpixel_height;
	ofParameter<int> cosx_e;
	ofParameter<int> cosy_e;
	ofParameter<int> border_width;
	ofParameter<int> border_height;

	//-----command-GUI

	ofParameter<bool> compute_filter;
	ofParameter<bool> randomsamp;
	ofParameter<bool> switch_screen1;
	ofParameter<bool> switch_screen2;

	//----informational-GUI

	ofParameter<int> dim_SP_ges_x;
	ofParameter<int> dim_SP_ges_y;
	ofxLabel dim_monitor1;
	ofxLabel label;

	//----testGUI
	/*		ofxPanel					gui_s4;
			ofParameterGroup			test_slider_4;
			ofParameter<int> 			int_sl1;
			ofParameter<int> 			int_sl2;
			ofParameter<int>			int_sl3;
			ofParameter<float> 			flt_sl1;
			ofParameter<float>	 		flt_sl2;
			ofParameter<float>			flt_sl3;    //100% complete resolution
			ofParameter<ofVec3f> 		clr_sl1;			//color
			ofParameter<ofVec2f> 		vec2_sl1 ;
			ofParameter<ofVec2f> 		vec2_sl2;
			ofParameter<ofVec3f> 		vec3_sl1;
			ofParameter<ofVec4f>		vec4_sl1;

			ofxToggle 					tog1;
			ofxButton 					but1;
	//----------------Inputfields
			ofxIntField					intField;
			ofxFloatField		 		floatField;
			ofxTextField 				textField;
	*/
	

};

