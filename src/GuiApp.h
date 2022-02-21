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
#include "corpus_inspektor.h"



using namespace ofxCv;
using namespace cv;

class GuiApp: public ofBaseApp {
public:
	void setup();
	void setup_gui();
	void setup_filter();
	void setup_imgPreview();

	void update();

	void read_Corpus();

	void load_selImg(ofxDatGuiDropdownEvent in_);

	void draw();
	void draw_gui();
	void draw_filterPreview();
	void draw_imgPreview();
	void draw_Preview_Rect();
	void update_Preview_Rect();

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
	void onDropdownEvent(ofxDatGuiDropdownEvent e);

	//----generalinformations
	int main_window_w;
	int main_window_h;
	
	int last_click_x, last_click_y;
	
	
	//---- deklaration for Previewvariables
	
	int PR_pos_x_;
	int PR_pos_y_;
	int PR_max_w_;
	int PR_max_h_;

	int prevrw;
	int prevrh;
	int prevrx;
	int prevry;

	float truth_scalefac;
	float scalefac;

	int mouse_x_dr, mouse_y_dr;
	int dragOffset_x, dragOffset_y;

	//-----------some FLAGS
	bool gui_changed;
	int  dropdownvalue;

	bool filter_loaded;
	bool filter_exists;
	bool pixel_filter_exists;
	bool bHide;

	const std::string source_folder = "01_possible_corpus";
	const std::string res_folder = "../03_received_corpus";
	const std::string reject_folder = "../02_not_used_for_corpus";

	//--cv::STRUCTS
	Filter pix_filter;

	cv::Mat actual_filterdata;
	cv::Mat lena_mat;
	cv::Mat submat;
	cv::Mat test;

	// Images
	vector<string> image_files = {};

	ofTexture prev_img;
	ofPoint pnt[4];
	ofRectangle draw_bnds;

	//ofImage test2_img;
	ofImage filterImage;
	//ofImage roi_1;
	//ofImage roi2;

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
	ofxDatGuiDropdown* dropdown;
	ofxDatGui* zoom_gui;

	vector<ofxDatGuiComponent *> components;

	// ofParameterGroup sample_slider_1;
	// ofParameterGroup command_slider_2;
	// ofParameterGroup info_slider_3;

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

	//-----zoom-GUI
	ofParameter<int> m_zoom_fac;

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

