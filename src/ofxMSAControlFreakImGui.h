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
#include "ofxMSAControlFreak.h"

namespace msa {
	namespace controlfreak {
		namespace imgui {
			// all of the below are to be called inside a gui.begin() / gui.end() block

			// draw a single parameter
			void draw(Parameter& p, string labelPrefix = "");

			// open a Yes/No confirmation popup window
			// returns 0 (while open), 1 (yes), 2 (no), 3 (cancel) // TODO: generalize to vector of buttons?
			int openConfirmationPopup(string title, string message = "", bool showCancel = false);
		}
	}
}
