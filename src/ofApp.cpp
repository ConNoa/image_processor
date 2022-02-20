#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	pnt[0].x = 0;
	pnt[0].y = 0;
	pnt[2].x = (float)ofGetWidth();
	pnt[2].y = (float)ofGetHeight();
	draw_bnds.set(pnt[0], pnt[2]);
	pnt[1].x = gui->mouse_x_dr-gui->PR_pos_x_;
	pnt[1].y = gui->mouse_y_dr-gui->PR_pos_y_;
	pnt[3].x = (float)ofGetWindowWidth();
	pnt[3].y = (float)ofGetWindowHeight();
	subsec_bnds.set(pnt[1], pnt[3]);

	ofSetVerticalSync(true);
	ofBackground(0,100, 255);
//-----------------------------------------------------------------------------
//-----------setting up environment--------------------------------------------
//-----------------------------------------------------------------------------
	test_img.load("6_lena_512x512.png");
	// lena_pix = test_img.getPixels();
	// lena_mat =  Mat(toCv(lena_pix));
	// //cout << "Testmat created"<<lena_mat.cols<<"   "<<lena_mat.rows<< endl;
//	test = lena_mat.clone();
//	submat = cv::Mat(lena_mat, cv::Rect(x_roi, y_roi, width_roi, height_roi));
//	cout << "Testmat created"<<submat.cols<<"   "<<submat.rows<< endl;
//	cout << lena_mat.channels() <<endl;
//	cout << submat<< endl;
//	cout << "Testmat created"<<lena_mat.cols<<"   "<<lena_mat.rows<< endl;
//	toOf(submat, roi_1);
//	roi_1.update();
	test_img.update();
	ofEnableAlphaBlending();
	ofLoadImage(orig_img, gui->image_files[0]);
}

void ofApp::update()
{
	if(gui->gui_changed == true){

		ofLoadImage(orig_img, gui->image_files[gui->dropdownvalue]);
		gui->gui_changed = false;
	}

	
	/*
	if(filter_exists && !filter_loaded)
	{
	actual_filterdata	= cv::Mat(superpixel_width, superpixel_height, CV_8UC1);
	filter_loaded = true;
	setFilterToPixel();
	}
*/
}

void ofApp::draw()
	{

		ofSetColor(255);
		pnt[0].x = (float)((gui->PR_pos_x_ - gui->mouse_x_dr) * gui->scalefac);

		pnt[0].y = (float)((gui->PR_pos_y_ - gui->mouse_y_dr) * gui->scalefac);
		// pnt[1].x = (float)((gui->PR_pos_x_ - gui->mouse_x_dr));
		// pnt[1].y = (float)((gui->PR_pos_y_ - gui->mouse_y_dr));
		// pnt[3].x = (float)ofGetWindowWidth();
		// pnt[3].y = (float)ofGetWindowHeight();
		subsec_bnds.set(pnt[0], 1220, 1028 );

		orig_img.draw(draw_bnds);

		ofDrawBitmapString(ofToString(ofGetFrameRate()), 250, 20);
		ofDrawBitmapString(ofToString(gui->mouse_x), 250, 40);
		ofDrawBitmapString(ofToString(gui->mouse_y), 250, 60);
	}

void ofApp::dragEvent(ofDragInfo dragInfo){
}

void ofApp::gotMessage(ofMessage msg) {}

void ofApp::windowResized(int w, int h){
//	dim_monitor1 = ofToString(w)+ "x" + ofToString(h);

}

void ofApp::mouseMoved(int x, int y){
//	cout << "mooove Main mouse-pr   x:" << x << " y:" << y << " button:" << endl;
	//mouseX = x;
	//mouseY = y;
//	return;
}

cv::Mat ofApp::ofImgToCVMat(ofImage const& img_in){
	auto pix_ = img_in.getPixels();
	cv::Mat out_m =  cv::Mat(ofxCv::toCv(pix_));

	return out_m;
}

