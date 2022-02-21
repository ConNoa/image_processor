#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	pnt[0].x = (float)-100;
	pnt[0].y = (float)-500;
	pnt[2].x = (float)orig_img.getWidth();
	pnt[2].y = (float)orig_img.getHeight();
	draw_bnds.set(pnt[0], pnt[2]);
	pnt[1].x = gui->mouse_x_dr-gui->PR_pos_x_;
	pnt[1].y = gui->mouse_y_dr-gui->PR_pos_y_;
	pnt[3].x = (float)ofGetWindowWidth();
	pnt[3].y = (float)ofGetWindowHeight();
	//subsec_bnds.set(pnt[1], pnt[3]);

	ofSetVerticalSync(true);
	ofBackground(0,100, 255);
//-----------------------------------------------------------------------------
//-----------setting up environment--------------------------------------------
//-----------------------------------------------------------------------------
	//test_img.load("6_lena_512x512.png");
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
	//test_img.update();
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
		//pnt[0].x = (float)((gui->PR_pos_x_ - gui->mouse_x_dr) * gui->scalefac);

		//pnt[0].y = (float)((gui->PR_pos_y_ - gui->mouse_y_dr) * gui->scalefac);
		// pnt[1].x = (float)((gui->PR_pos_x_ - gui->mouse_x_dr));
		// pnt[1].y = (float)((gui->PR_pos_y_ - gui->mouse_y_dr));
		// pnt[3].x = (float)ofGetWindowWidth();
		// pnt[3].y = (float)ofGetWindowHeight();
		//subsec_bnds.set(pnt[0], 1220, 1028 );
		int o_x = -1 * (gui->mouse_x_dr - gui->PR_pos_x_ - gui->prevrw/2) * gui->truth_scalefac ;
		int o_y = -1 * (gui->mouse_y_dr - gui->PR_pos_y_ - gui->prevrh/2) * gui->truth_scalefac ;
		//cout << "truth_scalefac " << gui->truth_scalefac << endl;
		//cout << "PRmaxh - orig_img " << (gui->PR_max_h_ - orig_img.getHeight()/gui->truth_scalefac) << endl;
		//cout << ((gui->PR_max_h_ - orig_img.getHeight() / gui->truth_scalefac) / 2) * gui->truth_scalefac << endl;
		//cout << ((gui->PR_max_h_ - orig_img.getHeight() / gui->truth_scalefac) / 2) * gui->truth_scalefac << endl;

		o_x = o_x + (((gui->PR_max_w_ - orig_img.getWidth() / gui->scalefac) / 2) * gui->truth_scalefac);
		o_y = o_y + (((gui->PR_max_h_ - orig_img.getHeight() / gui->scalefac) / 2) * gui->truth_scalefac);
		o_x = o_x - mD_x;
		o_y = o_y - mD_y;
		orig_img.draw(o_x, o_y, orig_img.getWidth()* gui->m_zoom_fac, orig_img.getHeight()* gui->m_zoom_fac);
		///cout<< orig_img.getWidth()<< endl;

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

void ofApp::mouseDragged(int x, int y, int button){
	mD_x = mP_x - x;
	mD_y = mP_y - y;
	cout << "mouse dragged: " << mD_x << "  " << mD_y << endl;
	gui->dragOffset_x = mD_x;
	gui->dragOffset_y = mD_y;
}

void ofApp::mousePressed(int x, int y, int button){
	cout <<"mouse pressed: "<< x << "  " << y <<endl;
	mP_x = x;
	mP_y = y;

}


void ofApp::mouseReleased(int x, int y, int button){
	cout << "mouse released: " << x << "  " << y << endl;
	gui->prevrx = gui->prevrx + gui->dragOffset_x / gui->truth_scalefac;
	gui->prevry = gui->prevry + gui->dragOffset_y / gui->truth_scalefac;
//gui->dragOffset_x = 0;
//	gui->dragOffset_y = 0;
}

cv::Mat ofApp::ofImgToCVMat(ofImage const& img_in){
	auto pix_ = img_in.getPixels();
	cv::Mat out_m =  cv::Mat(ofxCv::toCv(pix_));

	return out_m;
}

