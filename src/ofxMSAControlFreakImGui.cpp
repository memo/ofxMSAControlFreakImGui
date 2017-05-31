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

#include "ofxMSAControlFreakImGui.h"

namespace msa {
namespace controlfreak {
namespace imgui {

//static unique_ptr<ofxImGui::Gui> _gui = nullptr;


//// get reference to internal gui
//ofxImGui::Gui& getGui() {
//    if(!_gui) _gui = unique_ptr<ofxImGui::Gui>(new ofxImGui::Gui);
//    return *_gui;
//}


// draw a single parameter
void draw(Parameter& p) {
    if(typeid(p) == typeid(ParameterGroup)) {
        auto pp = dynamic_cast<ParameterGroup*>(&p);
        if(!pp) return;

        if(ImGui::CollapsingHeader(pp->getName().c_str(), "", true, pp->isOpen())) {;
            int np = pp->size();
            for(int i=0; i<np; i++) {
                draw(pp->get(i));
            }
        }

        //            switch(pp->getMode()) {
        //                case ParameterGroup::kPage: {
        //                    getRoot()->addPage(*pp);
        //                }
        //                    break;

        //                case ParameterGroup::kGroup:
        //                    addPanel(*pp);
        //                    break;
        //            }

    } else if(typeid(p) == typeid(ParameterFloat)) {
        auto pp = dynamic_cast<ParameterFloat*>(&p);
        if(!pp) return;
        if(pp->getClamp()) ImGui::InputFloat(pp->getName().c_str(), pp->var<float>(), pp->getIncrement(), pp->getIncrement() * 10);
        else ImGui::SliderFloat(pp->getName().c_str(), pp->var<float>(), pp->getMin(), pp->getMax());

    } else if(typeid(p) == typeid(ParameterInt)) {
        auto pp = dynamic_cast<ParameterInt*>(&p);
        if(!pp) return;
        if(pp->getClamp()) ImGui::InputInt(pp->getName().c_str(), pp->var<int>(), pp->getIncrement(), pp->getIncrement() * 10);
        else ImGui::SliderInt(pp->getName().c_str(), pp->var<int>(), pp->getMin(), pp->getMax());

    } else if(typeid(p) == typeid(ParameterBool)) {
        auto pp = dynamic_cast<ParameterBool*>(&p);
        if(!pp) return;
        if(pp->getMode() == ParameterBool::kToggle) ImGui::Checkbox(pp->getName().c_str(), pp->var<bool>());
        else if(ImGui::Button(pp->getName().c_str())) pp->set(true);

    } if(typeid(p) == typeid(ParameterNamedIndex)) {
        auto pp = dynamic_cast<ParameterNamedIndex*>(&p);
        if(!pp) return;

        // TODO
        //        switch(pp->getMode()) {
        //        case ParameterNamedIndex::kDropdown:
        //            ImGui::Combo(pp->getName().c_str(), pp->var<int>(), pp->getLabels(), pp->size());
        //            break;

        //        case ParameterNamedIndex::kList:
        //            ImGui::ListBox(pp->getName().c_str(), pp->var<int>(), pp->getLabels(), pp->size());
        //            break;

        //        case ParameterNamedIndex::kOptions:
        //            break;
        //        }
    }

    if(ImGui::IsAnyItemHovered()) {
        ImGui::SetTooltip(p.getTooltip().c_str());
    }


    //    ofLogWarning() << "msa::controlfreak::gui::Container::add: unknown type adding parameter " << p.getPath() << " " << p.getTypeName();
}


//// draw parameter group with internal ofxImgGui
//void drawWithWindow(const ParameterGroup& params, int windowWidth, int windowHeight, ImGuiSetCond_initCond, float fontSize) {
//    gui.begin();
//    ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight), ImGuiSetCond_initCond);
//    ImGui::Begin(params.getName(), NULL);
//    ImGui::SetWindowFontScale(fontSize);

//    draw(params, getGui());

//    ImGui::End;

//    gui.end();
//}

//// draw parameter group with passed in ofxImgGui
//void draw(const ParameterGroup& params, ofxImgGui& gui) {
//    width = 0;
//    height = 0;

//    //    presetManager = new PanelPresetManager(this);

//    //    titleButton = new BoolTitle(this, getName());
//    //    titleButton->setZ(1);
//    //    titleButton->getParameter().trackVariable(&paramT->isOpen());
//    //    addControl(titleButton);

//    //    collapseAllButton = new BoolSimpleCircle(this, "-");
//    //    collapseAllButton->layout.positionMode = LayoutSettings::kAbsolute;
//    //    collapseAllButton->setZ(2);
//    //    collapseAllButton->setMode(ParameterBool::kBang);
//    //    addControl(collapseAllButton);

//    //    saveButton = new BoolSimpleCircle(this, "s");
//    //    saveButton->layout.positionMode = LayoutSettings::kAbsolute;
//    //    saveButton->setZ(2);
//    //    saveButton->setMode(ParameterBool::kToggle);
//    //    saveButton->getParameter().setTooltip("Save preset for '" + getPath() + "'");
//    //    saveButton->getParameter().trackVariable(&presetManager->bSaveOpen);
//    //    addControl(saveButton);

//    //    loadButton = new BoolSimpleCircle(this, "l");
//    //    loadButton->layout.positionMode = LayoutSettings::kAbsolute;
//    //    loadButton->setZ(2);
//    //    loadButton->setMode(ParameterBool::kToggle);
//    //    loadButton->getParameter().setTooltip("Load preset for '" + getPath() + "'");
//    //    loadButton->getParameter().trackVariable(&presetManager->bLoadOpen);
//    //    addControl(loadButton);

//    //    presetDropdown = new OptionsList(this, "presets");
//    //    presetDropdown->layout.positionMode = LayoutSettings::kAbsolute;
//    //    presetDropdown->layout.doIncludeInContainerRect = false;
//    //    presetDropdown->setZ(1e100);
//    //    presetDropdown->setMode(ParameterNamedIndex::kList);
//    //    addControl(presetDropdown);

//    //    children = new Container(this, getName() + "_children");
//    //    children->scale.y = 0;  // everything start closed
//    //    addControl(children);

//    //    children->addParameterChildren(*paramT);

//    drawParameter(params);
//}


}
}
}
