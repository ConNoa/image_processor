#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

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

}

void ofApp::draw(){

	ofSetColor(255);
	test_img.update();
	test_img.draw(ofGetWidth()/2, ofGetHeight()/2, test_img.getWidth()/3, test_img.getHeight()/3);

	ofDrawBitmapString( ofToString( ofGetFrameRate() ), 250, 20 );
	ofDrawBitmapString( ofToString( gui->mouse_x ), 250, 40 );
	ofDrawBitmapString( ofToString( gui->mouse_y ), 250, 60 );
}
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}

void ofApp::gotMessage(ofMessage msg) {}

void ofApp::windowResized(int w, int h){
//	dim_monitor1 = ofToString(w)+ "x" + ofToString(h);

}



cv::Mat ofApp::ofImgToCVMat(ofImage const& img_in){
	auto pix_ = img_in.getPixels();
	cv::Mat out_m =  cv::Mat(ofxCv::toCv(pix_));

	return out_m;
}

