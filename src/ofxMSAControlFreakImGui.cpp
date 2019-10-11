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

			int openConfirmationPopup(string title, string message, bool showCancel) {
				int ret = 0;

				if (!ImGui::IsPopupOpen(title.c_str())) ImGui::OpenPopup(title.c_str());

				if (ImGui::BeginPopupModal(title.c_str()))
				{
					ImGui::Text(message.c_str());
					//ImGui::SetNextItemWidth(-1.0f);

					if (ImGui::Button("Yes", ImVec2(80, 0))) {
						ret = 1;
						ImGui::CloseCurrentPopup();
					}
					ImGui::SameLine();
					if (ImGui::Button("No", ImVec2(80, 0))) {
						ret = 2;
						ImGui::CloseCurrentPopup();
					}
					if (showCancel) {
						ImGui::SameLine();
						if (ImGui::Button("Cancel", ImVec2(80, 0))) {
							ret = 3;
							ImGui::CloseCurrentPopup();
						}
					}
					ImGui::EndPopup();
				}
				return ret;
			}
	


	class Presets {
	public:

		//void select() { _selectedText = _strings[_selectedIndex]; }

		// getters
		//const char** charpp() const { return _charpp; }
		//int size() const { return _size; }
		//bool saveMode() const { return _saveMode; }
		//int selectedIndex() const { return _selectedIndex; }
		//string selectedText() const { return _selectedText; }
		string displayText(const ParameterGroup& params) const { return params.xmlName().empty() ? "[]" : "[ " + params.xmlName() + " ]"; }

		void updateList(ParameterGroup& params, bool saveMode) {
			_strings.clear();
			_charPtrs.clear();

			_strings = params.getPresetsList();
			if (saveMode) _strings.push_back("__NEW__");

			for (int i = 0; i < _strings.size(); i++) _charPtrs.push_back(const_cast<char*>(_strings[i].c_str()));
			//_charpp = (const char**)_charPtrs.data();
			_selectedIndex = 0;
			//_selectedText = "";
			_saveMode = saveMode;
		}

		void drawGui(ParameterGroup& params, string label) {
			ImGui::Text(displayText(params).c_str());

			string presetsLabel = "Presets for " + label;
			if (ImGui::Button(("Load Preset##" + params.getPath()).c_str())) {
				updateList(params, false); // update presets for loading
				ImGui::OpenPopup(presetsLabel.c_str());
			}
			ImGui::SameLine();
			if (ImGui::Button(("Save Preset##" + params.getPath()).c_str())) {
				updateList(params, true); // update presets for saving (with additional NEW option)
				ImGui::OpenPopup(presetsLabel.c_str());
			}

			//ImGui::SameLine();

			if (ImGui::BeginPopup(presetsLabel.c_str())) {
				if (_charPtrs.data()) {
					ImGui::ListBox(presetsLabel.c_str(), &_selectedIndex, (const char**)_charPtrs.data(), _charPtrs.size());
				}

				if (_saveMode) {
					if (ImGui::Button("Save")) {
						//select();
						string filename;
						if (_selectedIndex == _strings.size()-1) { // if we've selected the last item. i.e. NEW
							filename = ofSystemTextBoxDialog("Enter filename"); // prompt for filename
						}
						else {
							filename = _strings[_selectedIndex]; // otherwise use selected filename
						}
						params.saveXmlValues(filename);
						ImGui::CloseCurrentPopup();
					}
				}
				else {
					if (ImGui::Button("Load")) {
						//select();
						params.loadXmlValues(_strings[_selectedIndex]);
						ImGui::CloseCurrentPopup();
					}
				}

				ImGui::SameLine();
				if (ImGui::Button("Cancel")) {
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
		}

	protected:
		vector<string> _strings;
		vector<char*> _charPtrs;
		//const char** _charpp = NULL;
		int _selectedIndex = 0;
		//string _selectedText = "";
		bool _saveMode = false;
	};

	static Presets presets;


	// draw a single parameter
	void draw(Parameter& p, string labelPrefix) {
		// appending path to ensure unique names
		string label = labelPrefix + p.getName() + "##" + p.getPath();

		auto params = dynamic_cast<ParameterGroup*>(&p);
		if (params) {
			//if (typeid(p) == typeid(ParameterGroup)) { // this will fail if another type which extends ParameterGroup is used (e.g. Color or Vec)
				//auto pp = dynamic_cast<ParameterGroup*>(&p);
				//if (!pp) return;

			//ImGui::BeginChild("scrolling");
			//if (ImGui::CollapsingHeader(label.c_str(), &pp->isOpen(), 0)) {
			if (ImGui::TreeNode(label.c_str())) {//, &pp->isOpen(), 0)) {
				ImGui::Separator();

				// draw preset controls
				presets.drawGui(*params, label);

				// recursively draw child controls
				int np = params->size();
				for (int i = 0; i < np; i++) {
					draw(params->get(i));
				}
				ImGui::TreePop();
				ImGui::Separator();
			}
			//ImGui::EndChild();

			//            switch(pp->getMode()) {
			//                case ParameterGroup::kPage: {
			//                    getRoot()->addPage(*pp);
			//                }
			//                    break;

			//                case ParameterGroup::kGroup:
			//                    addPanel(*pp);
			//                    break;
			//            }

		}
		else {
			if (typeid(p) == typeid(ParameterFloat)) {
				auto pp = dynamic_cast<ParameterFloat*>(&p);
				if (!pp) return;
				if (!pp->getClamp()) ImGui::DragFloat(label.c_str(), pp->var<float>(), pp->getIncrement(), pp->getIncrement() * 10);
				else ImGui::SliderFloat(label.c_str(), pp->var<float>(), pp->getMin(), pp->getMax());

			}
			else if (typeid(p) == typeid(ParameterInt)) {
				auto pp = dynamic_cast<ParameterInt*>(&p);
				if (!pp) return;
				if (!pp->getClamp()) ImGui::InputInt(label.c_str(), pp->var<int>(), pp->getIncrement(), pp->getIncrement() * 10);
				else ImGui::SliderInt(label.c_str(), pp->var<int>(), pp->getMin(), pp->getMax());

			}
			else if (typeid(p) == typeid(ParameterBool)) {
				auto pp = dynamic_cast<ParameterBool*>(&p);
				if (!pp) return;
				if (pp->getMode() == ParameterBool::kToggle) ImGui::Checkbox(label.c_str(), pp->var<bool>());
				else if (ImGui::Button(label.c_str())) pp->set(true);

			}
			else if (typeid(p) == typeid(ParameterNamedIndex)) {
				auto pp = dynamic_cast<ParameterNamedIndex*>(&p);
				if (!pp) return;

				std::vector<char*> clabels;
				for (size_t i = 0; i < pp->getLabels().size(); ++i) clabels.push_back(const_cast<char*>(pp->getLabels()[i].c_str()));
				const char** plabels = (const char**)clabels.data();

				//        switch(pp->getMode()) {
				//        case ParameterNamedIndex::kDropdown:
				//            ImGui::Combo(label.c_str(), pp->var<int>(), cstrings.data(), pp->size());
				//            break;

				//        case ParameterNamedIndex::kList:
				ImGui::ListBox(label.c_str(), pp->var<int>(), plabels, pp->size());
				//            break;

				//        case ParameterNamedIndex::kOptions:
				//            break;
				//        }
			}

			if (ImGui::IsItemHovered() && !p.getTooltip().empty()) {
				ImGui::SetTooltip(p.getTooltip().c_str());
			}
		}


		//    ofLogWarning("ofxMSAControlFreakImGui") << "msa::controlfreak::gui::Container::add: unknown type adding parameter " << p.getPath() << " " << p.getTypeName();
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
