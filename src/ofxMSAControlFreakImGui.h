//                                      __
//     ____ ___  ___  ____ ___  ____   / /__   __
//    / __ `__ \/ _ \/ __ `__ \/ __ \ / __/ | / /
//   / / / / / /  __/ / / / / / /_/ // /_ | |/ /
//  /_/ /_/ /_/\___/_/ /_/ /_/\____(_)__/ |___/
//
//
//  Created by Memo Akten, www.memo.tv
//
//  ofxMSAControlFreakImGui
//

#pragma once


#include "ofxImGui.h"
#include "ofxMSAControlFreak/src/ofxMSAControlFreak.h"

namespace msa {
namespace controlfreak {
namespace imgui {

    // get reference to internal gui
//    ofxImGui::Gui& getGui();

//    void drawWithWindow(const ParameterGroup& params, int windowWidth, int windowHeight, ImGuiSetCond initCond = ImGuiSetCond_FirstUseEver, float fontSize = 1.0f);

    //--------------------------------------------------------------
    // single functions
    // all of the below are to be called inside a gui.begin() / gui.end() block

    // draw a single parameter
    void draw(Parameter& p);

    // draw parameter group with internal ofxImGui
//    void draw(const ParameterGroup& params);

    // draw parameter group with passed in ofxImGui
//    void draw(const ParameterGroup& params, ofxImGui::Gui& gui);

}
}
}
