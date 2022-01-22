#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	//Backgroundcolor
	ofBackground(0,0, 255);
//----------LISTENER----------------------------------------------
	setup_gui();
	setup_filter();
//-----------------------------------------------------------------------------
//-----------setting up environment--------------------------------------------
//-----------------------------------------------------------------------------
	bHide = false;
	filter_loaded = false;
	pixel_filter_exists = false;
 	x_roi= 100;
	y_roi = 100;
	width_roi = 10;
	height_roi = 10;

	test_img.load("6_lena_512x512.png");
	lena_pix = test_img.getPixels();
	lena_mat =  Mat(toCv(lena_pix));
	//cout << "Testmat created"<<lena_mat.cols<<"   "<<lena_mat.rows<< endl;
	test = lena_mat.clone();
	submat = cv::Mat(lena_mat, cv::Rect(x_roi, y_roi, width_roi, height_roi));
//	cout << "Testmat created"<<submat.cols<<"   "<<submat.rows<< endl;
//	cout << lena_mat.channels() <<endl;
//	cout << submat<< endl;
//	cout << "Testmat created"<<lena_mat.cols<<"   "<<lena_mat.rows<< endl;
	toOf(submat, roi_1);

	roi_1.update();
	test_img.update();

	ofEnableAlphaBlending();
}

void ofApp::setup_gui(){

	//-------------GÚI INTERFACE------------------------------------------------
	pos_s1_x = 10;
	pos_s1_y = 100;
	pos_s2_x = 10;
	pos_s2_y = 350;
	pos_s3_x = 10;
	pos_s3_y = 10;

	sample_slider_1.setName("sample-parameters");
	sample_slider_1.add(m_sampleamm_abs.set("Sampleammount ABS", 1000, 10, 200000));
	sample_slider_1.add(m_sampleamm_rel.set("Sampleammount REL", 10, 0, 100));
	sample_slider_1.add(m_superpix_res.set("Superpixel Res.", 100, 0, 100));
	sample_slider_1.add(superpixel_width.set("S.Pix width", 10, 1, 19));
	sample_slider_1.add(superpixel_height.set("S.Pix height", 10, 1, 19));
	sample_slider_1.add(cosx_e.set("Cosx^", 1, 1, 15));
	sample_slider_1.add(cosy_e.set("Cosy^", 1, 1, 15));
	sample_slider_1.add(border_width.set("Border width", 0, 0, 5));
	sample_slider_1.add(border_height.set("Border height", 0, 0, 5));
	gui.setup(sample_slider_1, "settings.xml", pos_s1_x, pos_s1_y);

	//-------------------------------------------------------------------------
	command_slider_2.setName("command GUI");
	command_slider_2.add(compute_filter.set("Compute Filter"));
	command_slider_2.add(randomsamp.set("Sample Random Points"));
	command_slider_2.add(switch_screen1.set("Screen 1 Switch"));
	command_slider_2.add(switch_screen2.set("Screen 2 Switch"));
	gui_s2.setup(command_slider_2, "settings.xml", pos_s2_x, pos_s2_y);
	//-------------------------------------------------------------------------
	info_slider_3.setName("informational GUI");
	dim_monitor1.setup("screen size screen 1", "this is now on screen", 120.0f, 20.0f);
	dim_SP_ges_x.setName("Breite gesamt");
	dim_SP_ges_x = superpixel_width + border_width;
	info_slider_3.add(dim_SP_ges_x);
	dim_SP_ges_y.setName("Höhe gesamt");
	dim_SP_ges_y = superpixel_height + border_height;
	info_slider_3.add(dim_SP_ges_y);
	// info_slider_3.add(dim_monitor2.setup("screen size screen 2"));
	// info_slider_3.add(dim_monitor3.setup("screen size screen 3"));
	// info_slider_3.add(label.setup("hierkommt was hilfreiches rein", (ofToString(ofGetWidth())+"x"+ofToString(ofGetHeight()))));
	gui_s3.setup(info_slider_3, "settings.xml", pos_s3_x, pos_s3_y);

	//-------------------------------------------------------------------------
	// test_slider_4.setName(" sliders for testing");
	/*test_slider_4.add(int_sl1.set("int_sl", 0, 1, 100));
	test_slider_4.add(int_sl2.set("int_sl", 0, 1, 100));
	test_slider_4.add(int_sl3.set("int_sl", 0, 1, 100));
	test_slider_4.add(flt_sl1.set("flt_sl", 1, 1, 3.4159));
	test_slider_4.add(flt_sl2.set("flt_sl", 1, 1, 3.4159));
	test_slider_4.add(flt_sl3.set("flt_sl", 1, 1, 3.4159));
*/
	//	test_slider_4.add(clr_sl1.set("clr_sl1" , ofVec3f(125, 150, 35), ofVec3f(255, 150, 120), ofVec3f(70, 150, 0)));
	/*	test_slider_4.add(vec2_sl1.set("vec2_sl1", ofVec2f(0,0), ofVec2f(0,0), ofVec2f(ofGetWidth(),ofGetHeight())));
		test_slider_4.add(vec2_sl2.set("vec2_sl2", ofVec2f(0,0), ofVec2f(0,0), ofVec2f(0,0)));
		test_slider_4.add(vec3_sl1.set("vec3_sl1", ofVec3f(100, 150, 90), ofVec3f(0, 0, 100), ofVec3f(255, 255, 255)));
		test_slider_4.add(vec4_sl1.set("vec4_sl1", ofVec4f(50, 50, 50, 50), ofVec4f(0,0,0,0), ofVec4f(255, 255, 255, 255)));
	*/
	// gui_s4.setup(test_slider_4);
	/*	gui.add(tog1.setup("toggle1", true));
		gui.add(but1.setup("but1",true));

		gui.add(intField.setup("int field", 100, 0, 100));
		gui.add(floatField.setup("float field", 100.0, 0, 100));
		gui.add(textField.setup("text field", "Probetext"));
	*/
	// slider_group.add(sample_slider_1);
	// slider_group.add(gui);
	// gui.add(slider_group);

	// fxDatGui* nui = new ofxDatGui( 300, 300 );
	// ofxDatGui* nui = new ofxDatGui( ofxDatGuiAnchor::BOTTOM_RIGHT );
	// nui->addButton("Click!");
	//	ofxDatGuiMatrix* myMatrix = ("MATRIX", 100, true);
}

void ofApp::setup_filter(){
	pix_filter.intg_array_map(1, 20, 1000);

	pix_filter.createFilter_xy(superpixel_width, superpixel_height, cosx_e, cosy_e);
	filter_exists = true;
	cout<< "setup_filter()"<<endl;
}

void ofApp::update(){
	/*
	if(filter_exists && !filter_loaded)
	{
	actual_filterdata	= cv::Mat(superpixel_width, superpixel_height, CV_8UC1);
	filter_loaded = true;
	setFilterToPixel();
	}
*/
	//recompute sizes and dimensions
	dim_SP_ges_x = superpixel_width + border_width;
	dim_SP_ges_y = superpixel_height + border_height;
}

void ofApp::draw(){
/*
	if(pixel_filter_exists){
		filterImage.draw(100, 100, 600, 600);
	}
*/
	ofSetColor(255);

	test_img.update();
	test_img.draw(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/2, ofGetHeight()/2);

	roi_1.update();
	roi_1.draw(200,10);

	// hello constantin
	
	draw_filterwindow();
	//int cTr = (int)(399/int_sl1);
	//cv::Rect roi_rect = cv::Rect(mouse_x, mouse_y, x_roi, cTr, width_roi , height_roi);
	//	roi_out.draw(100, 10, 120, 30);
	// auto draw?
	// should the gui control hiding?
	if(!bHide){
		gui.draw();
		gui_s2.draw();
		gui_s3.draw();
		// ofDrawBitmapString( ofToString( ofGetFrameRate() ), 250, 20 );
		// ofDrawBitmapString( ofToString( mouse_x ), 250, 40 );
		// ofDrawBitmapString( ofToString( mouse_y ), 250, 60 );

	}
}

void ofApp::draw_filterwindow(){
	int x_ = 300;
	int y_ = 50;
	int wi_ = 150;
	int he_ = 150;
	int fp_w = wi_/dim_SP_ges_x;
	int fp_h = he_/dim_SP_ges_y;
	Mat filter_temp = pix_filter.get_FMat2D();
	//cout << filter_temp << endl;

	ofSetRectMode(OF_RECTMODE_CORNER);
	ofBeginShape();
	ofSetColor(255);
	ofDrawRectangle(x_, y_, fp_w*dim_SP_ges_x, fp_h*dim_SP_ges_y);
	for (int i = 0; i < superpixel_width; i++)
	{
		for (int j = 0; j < superpixel_height; j++)
		{
			int field_alpha = filter_temp.at<uchar>(i,j);
			ofSetColor(field_alpha);
			ofDrawRectangle(x_ + fp_w * i, y_ + fp_h * j, fp_w, fp_h);
		}
	}
	ofSetColor(0);
	// draw under Border
	ofDrawRectangle(x_, y_ + fp_h * superpixel_height, fp_w * dim_SP_ges_x, fp_h * border_height); 
	// draw right Border
	ofDrawRectangle(x_ + fp_w * superpixel_width, y_, fp_w * border_width, fp_h * dim_SP_ges_y);
	ofEndShape();
	
}


//-------added--
void ofApp::exit(){
//	int_sl3.removeListener(this, &ofApp::cutResChanged);

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
	  ofSetColor(255);
	}
}

void ofApp::keyReleased(int key){

}

void ofApp::mouseMoved(int x, int y ){

}

void ofApp::mouseDragged(int x, int y, int button){
	cout<< "mouse-dr   x:"<<x<<" y:"<<y<<" button:"<<button<<endl;
	mouse_x = x;
	mouse_y = y;

}

void ofApp::mousePressed(int x, int y, int button){
	cout<< "mouse-pr   x:"<<x<<" y:"<<y<<" button:"<<button<<endl;
	mouse_x = x;
	mouse_y = y;
}

void ofApp::mouseReleased(int x, int y, int button){
	cout << "mouse released"<< endl;
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
//	dim_monitor1 = ofToString(w)+ "x" + ofToString(h);

}

void ofApp::dragEvent(ofDragInfo dragInfo){

}

void ofApp::gotMessage(ofMessage msg){}

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
	Mat submat_t = Mat(lena_mat, cv::Rect(x_roi, y_roi, mouse_x, mouse_y));
	toOf(submat_t, roi_1);
	roi_1.update();

	return;
}
