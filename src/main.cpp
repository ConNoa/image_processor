#include "ofMain.h"
#include "ofApp.h"
#include "GuiApp.h"
#include "ofAppGLFWWindow.h"
#include <memory>

//========================================================================
/*
int main( ){
	ofSetupOpenGL(1028,720,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}
*/
/*
int main()
{
	// first approach
	//  https://forum.openframeworks.cc/t/maintaining-fullscreen-in-linux-touchscreen/38858
	ofxAppGLFWWindowMult

	ofGLFWWindowSettings settingsT;
	settingsT.setSize(1920, 1080);
	settingsT.setPosition(ofVec2f(1920, 0));
	settingsT.resizable = true;
	shared_ptr<ofAppBaseWindow> main_Window = ofCreateWindow(settingsT);

	ofGLFWWindowSettings settingsP;
	settingsP.setSize(1920, 1080);
	settingsP.setPosition(ofVec2f(0, 1080));
	settingsP.resizable = true;
	settingsP.shareContextWith = main_Window;
	shared_ptr<ofAppBaseWindow> presentWindow = ofCreateWindow(settingsP);
	presentWindow->setVerticalSync(false);

	shared_ptr<ofApp> mainApp(new ofApp);
	mainApp->setupMain();

//	ofAddListener(presentWindow->events().draw, mainApp->draw(), &ofApp::drawMain);
	ofRunApp(main_Window, mainApp);
	ofRunMainLoop();
}
*/

// https://github.com/whg/ofxNSWindower
//========================================================================
int main()
{
	ofGLFWWindowSettings settings_main;

	settings_main.setSize(1220, 1028);
	settings_main.setPosition(glm::vec2(1920, 1028));
	settings_main.resizable = false;
	settings_main.monitor = 1;
	//ofSetWindowTitle("extern1");
	shared_ptr<ofAppBaseWindow> gui_Window = ofCreateWindow(settings_main);

	int main_window_w = 1920;
	int main_window_h = 1028;
	settings_main.setSize(main_window_w, main_window_h);
	settings_main.setPosition(glm::vec2(0, 1028));
	settings_main.monitor = 0;
	settings_main.resizable = true;
	settings_main.shareContextWith = gui_Window;
	shared_ptr<ofAppBaseWindow> main_Window = ofCreateWindow(settings_main);


	shared_ptr<ofApp> mainApp(new ofApp);
	shared_ptr<GuiApp> guiApp(new GuiApp);

	mainApp->gui = guiApp;
	mainApp->gui->main_window_w = main_window_w;
	mainApp->gui->main_window_h = main_window_h;

	//ofAddListener(main_Window->events().draw, mainApp->draw(), &ofApp::draw());
	ofRunApp(gui_Window, guiApp);
	ofRunApp(main_Window, mainApp);
	ofRunMainLoop();
}
