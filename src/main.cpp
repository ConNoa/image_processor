#include "ofMain.h"
#include "ofApp.h"
#include <opencv2/highgui.hpp>
#include "GuiApp.h"
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
	ofGLFWWindowSettings settings;

	settings.setSize(600, 600);
	settings.setPosition(glm::vec2(300, 0));
	settings.resizable = true;
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

	settings.setSize(300, 300);
	settings.setPosition(glm::vec2(0, 0));
	settings.resizable = false;
	shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);

	shared_ptr<ofApp> mainApp(new ofApp);
	shared_ptr<GuiApp> guiApp(new GuiApp);
	mainApp->gui = guiApp;

	ofRunApp(guiWindow, guiApp);
	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();
}
