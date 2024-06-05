#pragma once

#include "AnimationWindow.h"
#include "Meeting.h"
#include "Person.h"
#include "widgets/Button.h"
#include "widgets/TextInput.h"
#include "widgets/DropdownList.h"

#include <string>
#include <vector>
struct MeetingWindow : TDT4102::AnimationWindow {
	static constexpr int pad = 4;
	static constexpr int btnW = 100;
	static constexpr int btnH = 50;
	static constexpr int fieldW = 200;
	static constexpr int fieldH = 50;    
    MeetingWindow(int x, int y, int w, int h, const string& title);

private:
    TDT4102::Button quitBtn;
    
    void cb_quit(){close();}

};