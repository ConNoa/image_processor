
#include "GuiApp.h"

void GuiApp::setup(){
	ofSetVerticalSync(true);
	// Backgroundcolor
	ofBackground(999999);

	bHide = false;
	filter_loaded = false;
	pixel_filter_exists = false;
	x_roi = 100;
	y_roi = 100;
	width_roi = 10;
	height_roi = 10;

	prev_img.load("wrong_format_calf-3833880_960_720.jpg");

	//----------LISTENER----------------------------------------------
	setup_gui();
	setup_filter();
	draw_filterPreview();
	
	
	//gui.addListener(this, &GuiApp::filtermustload);

	//
}

void GuiApp::setup_gui()
{
	//-------------GÚI INTERFACE------------------------------------------------
	pos_s1_x = 10;
	pos_s1_y = 100;
	pos_s2_x = 10;
	pos_s2_y = 350;
	pos_s3_x = 10;
	pos_s3_y = 10;

	m_sampleamm_abs.set("Sampleammount ABS", 1000, 10, 200000);
	m_sampleamm_rel.set("Sampleammount REL", 10, 0, 100);
	m_superpix_res.set("Superpixel Res.", 100, 0, 100);
	superpixel_width.set("S.Pix width", 10, 1, 19);
	superpixel_height.set("S.Pix height", 10, 1, 19);
	cosx_e.set("Cosx^", 1, 0, 15);
	cosy_e.set("Cosy^", 1, 0, 15);
	border_width.set("Border width", 0, 0, 5);
	border_height.set("Border height", 0, 0, 5);

	m_gui = new ofxDatGui();
	m_gui->addLabel("Sample Parameters");
	m_gui->addSlider(m_sampleamm_abs);
	m_gui->addSlider(m_sampleamm_rel);
	m_gui->addSlider(m_superpix_res);
	m_gui->addSlider(superpixel_width);
	m_gui->addSlider(superpixel_height);
	m_gui->addSlider(cosx_e);
	m_gui->addSlider(cosy_e);
	m_gui->addSlider(border_width);
	m_gui->addSlider(border_height);
	m_gui->setPosition(20, 100);
	m_gui->onSliderEvent(this, &GuiApp::onSliderEvent);


	ofxDatGuiDropdown *dropdown;
	//vector<string> options = {"one", "two", "three", "four"};
	dropdown = new ofxDatGuiDropdown("Image Data", image_files);
	dropdown->setPosition(20, 700);
	dropdown->expand();
	dropdown->onDropdownEvent(this, &GuiApp::onDropdownEvent);
	components.push_back(dropdown);

	//-------------------------------------------------------------------------
	/*
	command_slider_2.setName("command GUI");
	command_slider_2.add(compute_filter.set("Compute Filter", true));
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
*/
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

void GuiApp::setup_filter()
{
	pix_filter.intg_array_map(1, 20, 1000);

	pix_filter.createFilter_xy(superpixel_width, superpixel_height, cosx_e, cosy_e);
	filter_exists = true;
	cout << "setup_filter()" << endl;

	compute_alphfilter(superpixel_width, superpixel_height, cosx_e, cosy_e);
}

void GuiApp::update(){
	// recompute sizes and dimensions
	dim_SP_ges_x = superpixel_width + border_width;
	dim_SP_ges_y = superpixel_height + border_height;

	for (int i = 0; i < components.size(); i++)components[i]->update();
}

void GuiApp::load_selImg(ofxDatGuiDropdownEvent in_)
{
	cout << "onDropdownEvent: " << in_.child << endl;

	prev_img.load(image_files[in_.child]);
	prev_img.update();
}

void GuiApp::draw(){

	/*
		if(pixel_filter_exists){
			filterImage.draw(100, 100, 600, 600);
		}
	*/
	draw_filterPreview();

	draw_imgPreviewRect();

	// should the gui control hiding?
	if(!bHide)draw_gui();
	ofSetColor(255);
	ofDrawBitmapString(ofToString(ofGetFrameRate()), ofGetWidth()-200, 20);
	ofDrawBitmapString(ofToString(mouse_x), ofGetWidth() - 200, 40);
	ofDrawBitmapString(ofToString(mouse_y), ofGetWidth() - 200, 60);
}

void GuiApp::compute_alphfilter(int w_, int h_, int cosx_, int cosy_){
	//cout<<"compute_aplhfilter"<<endl;
	actual_filterdata = pix_filter.get_FMat2D(w_, h_, cosx_, cosy_);
	draw_filterPreview();
	return;
}

void GuiApp::draw_filterPreview(){
	//cout<<"drawing Filterprev"<<endl;
	int x_ = 300;
	int y_ = 50;
	int wi_ = 250;
	int he_ = 250;
	int fp_w = wi_ / dim_SP_ges_x;
	int fp_h = he_ / dim_SP_ges_y;
	int scale_fak = min(fp_w, fp_h);

	// cout << actual_filterdata << endl;
	fp_w = 20;
	fp_h = fp_w;

	ofSetRectMode(OF_RECTMODE_CORNER);
	ofBeginShape();
	// ofSetColor(255);
	// ofDrawRectangle(x_, y_, fp_w*dim_SP_ges_x, fp_h*dim_SP_ges_y);
	for (int i = 0; i < superpixel_width; i++)
	{
		for (int j = 0; j < superpixel_height; j++)
		{
			// Mat actual_filterdata = pix_filter.get_FMat2D(superpixel_width, superpixel_height, cosx_e, cosy_e);
			int field_alpha = actual_filterdata.at<uchar>(j, i);
			ofFill();
			ofSetColor(field_alpha);
			// draw rectangle for Pixel
			// with (pos_x, pos_y, breite, höhe)
			ofDrawRectangle(x_ + fp_w * i, y_ + fp_h * j, fp_w-2, fp_h-2);
		}
	}
	ofSetColor(0);
	// draw under Border
	ofDrawRectangle(x_, y_ + fp_h * superpixel_height, fp_w * dim_SP_ges_x, fp_h * border_height);
	// draw right Border
	ofDrawRectangle(x_ + fp_w * superpixel_width, y_, fp_w * border_width, fp_h * dim_SP_ges_y);
	ofEndShape();
	compute_filter = false;
	return;
}

void GuiApp::draw_imgPreviewRect(){

	int pos_x_ = 300;
	int pos_y_ = 600;
	int max_w_ = 400;
	int max_h_ = 300;
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofBeginShape();
	ofFill();
	ofSetColor(0);
	ofDrawRectangle(pos_x_+max_w_/2, pos_y_+max_h_/2, max_w_, max_h_);
	ofEndShape();
	ofSetColor(255);
	float scalefac = max((prev_img.getWidth() / max_w_), (prev_img.getHeight() / max_h_));
	prev_img.update();
	prev_img.draw(pos_x_ + max_w_ / 2, pos_y_ + max_h_ / 2, prev_img.getWidth() / scalefac, prev_img.getHeight() / scalefac);
	ofBeginShape();
	ofNoFill();
	ofSetColor(50, 205, 50);
	ofDrawRectangle(pos_x_+max_w_/2, pos_y_+max_h_/2, max_w_, max_h_);
	ofEndShape();
	ofSetColor(255);	
	ofSetRectMode(OF_RECTMODE_CORNER);

	return;
}

void GuiApp::draw_gui(){

	for (int i = 0; i < components.size(); i++)
		components[i]->draw();
	//gui.draw();
	//gui_s2.draw();
	//gui_s3.draw();
	return;
}

void GuiApp::filtermustload(bool & trig){
	cout<< "filter_must_LOAD"<<endl;
	draw_filterPreview();
	return;
}

void GuiApp::mouseDragged(int x, int y, int button)
{
	//cout << "mouse-dr   x:" << x << " y:" << y << " button:" << button << endl;
	mouse_x = x;
	mouse_y = y;
	//compute_filter = true;

}

void GuiApp::mousePressed(int x, int y, int button)
{
	cout << "mouse-pr   x:" << x << " y:" << y << " button:" << button << endl;
	mouse_x = x;
	mouse_y = y;
}

void GuiApp::keyReleased(int key)
{
}

void GuiApp::mouseMoved(int x, int y)
{
}

void GuiApp::mouseReleased(int x, int y, int button)
{
	cout << "mouse released" << endl;
}

void GuiApp::mouseEntered(int x, int y)
{
}

void GuiApp::mouseExited(int x, int y)
{
}

void GuiApp::mouseEventPos(int x, int y)
{
	mouse_x = x;
	mouse_y = y;
	return;
}

void GuiApp::keyPressed(int key)
{
	// if(key == 'h'){
	// 	bHide = !bHide;
	// }
	// else if(key == 's'){
	// 	gui.saveToFile("settings.xml");
	// }
	// else if(key == 'l'){
	// 	gui.loadFromFile("settings.xml");
	// }
	// else if(key == ' '){
	//   ofSetColor(255);
	// }
}


void GuiApp::cutResChanged()
{
	updateRectangleSize();
	return;
}

void GuiApp::filterbuttonPressed()
{
	pix_filter.createFilter_xy(superpixel_width, superpixel_height, cosx_e, cosy_e);
	filter_exists = true;
	filter_loaded = false;
	return;
}

void GuiApp::setFilterToPixel()
{
	Mat act_colordata(pix_filter.get_FMat2D().rows, pix_filter.get_FMat2D().cols, CV_8UC3, Scalar(255, 255, 255));
	cout << "here comes colordata" << act_colordata << endl;
	actual_filterdata = pix_filter.get_FMat2D();
	cout << "here comes actual filterdata" << actual_filterdata << '\n';
	std::vector<cv::Mat> channels;
	channels.push_back(act_colordata);
	channels.push_back(actual_filterdata);
	Mat matG;
	merge(channels, matG);
	cout << "here is combinded" << matG << endl;
	toOf(matG, filterImage);
	filterImage.update();
	pixel_filter_exists = true;
	return;
}

void GuiApp::updateRectangleSize()
{
	Mat submat_t = Mat(lena_mat, cv::Rect(x_roi, y_roi, mouse_x, mouse_y));
	toOf(submat_t, roi_1);
	roi_1.update();

	return;
}

void GuiApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
	cout << e.target->getName() << " : " << e.value << endl;
	compute_alphfilter(superpixel_width, superpixel_height, cosx_e, cosy_e);
}

void GuiApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
	load_selImg(e);
}