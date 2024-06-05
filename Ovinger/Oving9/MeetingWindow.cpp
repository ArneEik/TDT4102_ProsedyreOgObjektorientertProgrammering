#include "MeetingWindow.h"

MeetingWindow::MeetingWindow(int x, int y, int w, int h, const string& title) : AnimationWindow(x,y,w,h,title),
    quitBtn{TDT4102::Point{w - btnW - pad, pad }, btnW, btnH, "Quit" }
{
    add(quitBtn);
    quitBtn.setCallback(std::bind(&MeetingWindow::cb_quit, this));
}