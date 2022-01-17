#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);


//----------LISTENER----------------------------------------------
	//
	// roi_size.addListener(this, &ofApp::cutResChanged(ofxIntSlider));
	// compute_filter.addListener(this, &ofApp::filterbuttonPressed(ofxButton));

//-------------GÚI INTERFACE------------------------------------------------
	sample_slider_1.setName("sample-parameters");
	sample_slider_1.add(m_sampleamm_abs.set("Sampleammount ABS", 1000, 10, 200000));
	sample_slider_1.add(m_sampleamm_rel.set("Sampleammount REL", 10, 0, 100));
	sample_slider_1.add(m_superpix_res.set("Superpixel Res.", 100, 0, 100));
	sample_slider_1.add(superpixel_width.setup("S.Pix width", 1, 1, 19));
	sample_slider_1.add(superpixel_height.setup("S.Pix height", 1, 1, 19));
	sample_slider_1.add(cosx_e.setup("Cosx^", 1, 1, 15));
	sample_slider_1.add(cosy_e.setup("Cosy^", 1, 1, 15));
	sample_slider_1.add(border_width.setup("Border width", 0, 0, 5));
	sample_slider_1.add(border_height.setup("Border height", 0, 0, 5));
	gui_s1.setup(sample_slider_1);

//-------------------------------------------------------------------------
	command_slider_2.setName("command GUI");
	gui.add(compute_filter.setup("Compute Filter"));
	gui.add(randomsamp.setup("Sample Random Points"));
	gui.add(switch_screen1.setup("Screen 1 Switch"));
	gui.add(switch_screen2.setup("Screen 2 Switch"));
	gui_s2.setup(command_slider_2);

//-------------------------------------------------------------------------
	info_slider_3.setName("informational GUI");
	gui.add(dim_monitor1.setup("screen size screen 1", ofToString(ofGetWidth())+"x"+ofToString(ofGetHeight())));
	gui.add(dim_monitor2.setup("screen size screen 2", ofToString(ofGetWidth())+"x"+ofToString(ofGetHeight())));
	gui.add(dim_monitor3.setup("screen size screen 3", ofToString(ofGetWidth())+"x"+ofToString(ofGetHeight())));
	gui.add(label.setup("hierkommt was hilfreiches rein", ofToString(ofGetWidth())+"x"+ofToString(ofGetHeight())));
	gui_s3.setup(info_slider_3);

//-------------------------------------------------------------------------
	test_slider_4.setName(" sliders for testing");
	test_slider_4.add(filled.setup("fill", true));
	test_slider_4.add(roi_size.setup("RectangleOfinterest size", 1, 1, 500));
	test_slider_4.add(intField.setup("INTEGER field", 100, 0, 10000));
	test_slider_4.add(floatField.setup("FLOAT field", 100.0, 0, 10000));
	test_slider_4.add(textField.setup("TEXT field", "text"));
	test_slider_4.add(toggle.setup("toggle",false));
	test_slider_4.add(button.setup("button",));
	test_slider_4.add(label.setup("label","This is a Label"));
	test_slider_4.add(vec2S.setup("vec2 Slider", ofVec2f(0,0), ofVec2f(0,0), ofVec2f(0,0)));
	test_slider_4.add(vec3S.setup("vec3 Slider", ofVec3f(100, 100, 100), ofVec3f(100, 100, 100), ofVec3f(100, 100, 100));
	test_slider_4.add(vec4S.setup("vec4 Slider", ofVec4f(50, 50, 50, 50), ofVec4f(50, 50, 50, 50), ofVec4f(50, 50, 50, 50), ofVec4f(50, 50, 50, 50)));
	gui_s4.setup(test_slider_4);

	gui.setup();
//-----------------------------------------------------------------------------
//-----------setting up environment--------------------------------------------
//-----------------------------------------------------------------------------
	pix_filter.intg_array_map(1, 20, 1000);
	bHide = false;
	filter_exists = false;
	filter_loaded = false;
	pixel_filter_exists = false;
 	x_roi= 100;
	y_roi = 100;
	width_roi = 10;
	height_roi = 10;

	test_img.load("6_lena_512x512.png");
	lena_pix = test_img.getPixels();
	lena_mat =  Mat(toCv(lena_pix));
	cout << "Testmat created"<<lena_mat.cols<<"   "<<lena_mat.rows<< endl;

	test = lena_mat.clone();
	submat = cv::Mat(lena_mat, cv::Rect(x_roi, y_roi, width_roi, height_roi));

	cout << lena_mat.channels() <<endl;
	cout << submat<< endl;


	toOf(submat, roi_1);

	roi_1.update();
	test_img.update();

	ofEnableAlphaBlending();
}

void ofApp::update(){
	if(filter_exists && !filter_loaded){
	actual_filterdata	= cv::Mat(superpixel_width, superpixel_height, CV_8UC1);
	filter_loaded = true;
	setFilterToPixel();
	}
}

void ofApp::draw(){
	ofSetColor(10);

	if(pixel_filter_exists){
		filterImage.draw(100, 100, 600, 600);
	}

	test_img.update();
	test_img.draw(0,0,ofGetWidth(),ofGetHeight());

	roi_1.update();
	roi_1.draw(200,10);

	int cTr = (int)(399/roi_size);
	RecOfIntr(mouse_x, mouse_y,1000, cTr, 500 , 300);
	//	roi_out.draw(100, 10, 120, 30);
	// auto draw?
	// should the gui control hiding?
	if(!bHide){
		gui.draw();
		ofDrawBitmapString( ofToString( ofGetFrameRate() ), 250, 20 );
		ofDrawBitmapString( ofToString( mouse_x ), 250, 40 );
		ofDrawBitmapString( ofToString( mouse_y ), 250, 60 );

	}
}


//-------added--
void ofApp::exit(){
	roi_size.removeListener(this, &ofApp::cutResChanged(&));

	compute_filter.removeListener(this, &ofApp::filterbuttonPressed(&));
	return;
}



void ofApp::keyPressed(int key){
	if(key == 'h'){
		bHide = !bHide;
	}
	else if(key == 's'){
		gui.saveToFile("settings.xml");
	}
	else if(key == 'l'){
		gui.loadFromFile("settings.xml");
	}
	else if(key == ' '){
		color = ofColor(255);
	}
}

void ofApp::keyReleased(int key){

}

void ofApp::mouseMoved(int x, int y ){

}

void ofApp::mouseDragged(int x, int y, int button){
	//cout<< "mouse-dr   x:"<<x<<" y:"<<y<<" button:"<<button<<endl;
	mouse_x = x;
	mouse_y = y;

}

void ofApp::mousePressed(int x, int y, int button){
	//cout<< "mouse-pr   x:"<<x<<" y:"<<y<<" button:"<<button<<endl;
	mouse_x = x;
	mouse_y = y;
}

void ofApp::mouseReleased(int x, int y, int button){

}

void ofApp::mouseEntered(int x, int y){

}

void ofApp::mouseExited(int x, int y){

}

void ofApp::mouseEventPos(int x, int y){
	mouse_x = x;
	mouse_y = y;
	return;
}


void ofApp::windowResized(int w, int h){
	screenSize = ofToString(w)+ "x" + ofToString(h);

}

void ofApp::dragEvent(ofDragInfo dragInfo){

}

void ofApp::gotMessage(ofMessage msg){

}



cv::Mat ofApp::ofImgToCVMat(ofImage const& img_in){
	auto pix_ = img_in.getPixels();
	cv::Mat out_m =  cv::Mat(ofxCv::toCv(pix_));

	return out_m;
}


void ofApp::cutResChanged(){
	updateRectangleSize();
	return;
}


void ofApp::filterbuttonPressed(){
	pix_filter.createFilter_xy(superpixel_width, superpixel_height, cosx_e, cosy_e);
	filter_exists = true;
	filter_loaded = false;
	return;
}

void ofApp::setFilterToPixel(){
	Mat act_colordata(pix_filter.get_FMat2D().rows, pix_filter.get_FMat2D().cols,  CV_8UC3, Scalar(255,255, 255));
	cout << "here comes colordata"<< act_colordata  <<endl;
	actual_filterdata = pix_filter.get_FMat2D();
	cout << "here comes actual filterdata" << actual_filterdata<<'\n';
	std::vector<cv::Mat> channels;
	channels.push_back(act_colordata);
	channels.push_back(actual_filterdata);
	Mat matG;
	merge(channels, matG);
	cout<< "here is combinded" << matG<< endl;
	toOf(matG,filterImage);
	filterImage.update();
	pixel_filter_exists = true;
	return;
}

void ofApp::updateRectangleSize(){
	Mat submat_t = Mat(lena_mat, cv::Rect(x_roi, y_roi, roi_size, heightRectangleOfinteresti));
	toOf(submat_t, roi_1);
	roi_1.update();

	return;
}
