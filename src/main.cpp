#include "ofMain.h"
#include "ofApp.h"
#include <opencv2/highgui.hpp>
#include "WinApp.h"
#include "ofAppGLFWWindow.h"
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
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settingsT);

	ofGLFWWindowSettings settingsP;
	settingsP.setSize(1920, 1080);
	settingsP.setPosition(ofVec2f(0, 1080));
	settingsP.resizable = true;
	settingsP.shareContextWith = mainWindow;
	shared_ptr<ofAppBaseWindow> presentWindow = ofCreateWindow(settingsP);
	presentWindow->setVerticalSync(false);

	shared_ptr<ofApp> mainApp(new ofApp);
	mainApp->setupMain();

//	ofAddListener(presentWindow->events().draw, mainApp->draw(), &ofApp::drawMain);
	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();
}
*/

// https://github.com/whg/ofxNSWindower



//========================================================================
int main()
{
	ofGLFWWindowSettings settings_ex2;
	ofGLFWWindowSettings settings_ex1;
	ofGLFWWindowSettings settings_main;



	settings_ex1.setSize(1920, 1028);
	settings_ex1.setPosition(glm::vec2(1920, 1028));
	settings_ex1.resizable = false;
	settings_ex1.monitor = 1;
	shared_ptr<ofAppBaseWindow> extern1_Window = ofCreateWindow(settings_ex1);

	settings_ex2.setSize(1920, 1028);
	settings_ex2.setPosition(glm::vec2(1920, 0));
	settings_ex2.resizable = false;
	settings_ex1.monitor = 2;
	settings_ex2.decorated = true;
	shared_ptr<ofAppBaseWindow> extern2_Window = ofCreateWindow(settings_ex2);

	settings_main.setSize(1600, 1028);
	settings_main.setPosition(glm::vec2(0, 1028));
	settings_main.monitor = 0;
	settings_main.resizable = true;
	settings_main.shareContextWith = extern1_Window;
	settings_main.shareContextWith = extern2_Window;

	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings_main);

	shared_ptr<ofApp> mainApp(new ofApp);
	shared_ptr<WinApp> ex1App(new WinApp);
	shared_ptr<WinApp> ex2App(new WinApp);
	mainApp->ex1 = ex1App;
	mainApp->ex2 = ex2App;

	ofRunApp(extern1_Window, ex1App);
	ofRunApp(extern2_Window, ex2App);
	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();
}
