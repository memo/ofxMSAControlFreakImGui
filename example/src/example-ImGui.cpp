#include "ofMain.h"

// This is a very minimal example that shows how to link the Parameters created in ofxMSAControlFreak to a GUI
// In this case using ImGui https://github.com/ocornut/imgui  (wrapped for OF by https://github.com/jvcleave/ofxImGui)

// include the ControlFreakImGui wrapper
#include "ofxMSAControlFreakImGui.h"

// Check the contents of ofxMSAControlFreakTutorial.h to see how to use ofxMSAControlFreak to create and use parameters
#include "ofxMSAControlFreakTutorial.h"
// Normally you wouldn't include this file, instead just define your own Parameters
// I just put everything in this file so I can keep this code separate and reuse it in different addons


class ofApp : public ofSimpleApp {
public:

    // declare an ofxImGui
    ofxImGui::Gui gui;

    // flag to control whether or not to show the gui. Toggle with SPACEBAR
    bool showGui = true;

    // this is defined in ofxMSAControlFreakTutorial.h
    TutorialModule tutorial;

    void setup() {
        // initialise all parameters
        tutorial.setup();
    }

    void draw() {
        tutorial.draw();

        if (showGui) {
            gui.begin();

            // this one line will draw the params with imgui, dynamically adjusting to changes in the params
            msa::controlfreak::imgui::draw( tutorial.params );
            gui.end();
        }
    }

    void keyPressed(int key) {
        switch (key) {
        case ' ': showGui ^= true; break;
        case 's': tutorial.params.saveXmlValues(); break;
        case 'S': tutorial.params.saveXmlSchema(); break;
        case 'l': tutorial.params.loadXmlValues(); break;
        case 'L': tutorial.params.loadXmlSchema(); break;
        }
    }
};

//========================================================================
int main() {
    ofSetupOpenGL(1100, 800, OF_WINDOW);
    ofRunApp(new ofApp);
}

