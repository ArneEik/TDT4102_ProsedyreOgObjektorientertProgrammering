#include "subprojects\std_lib_facilities\std_lib_facilities.h"
#include "subprojects/animationwindow/include/AnimationWindow.h"
#include "oppgave4.h"
#include "farger.h"
// #include <cstdlib>  
// #include <ctime>   

vector<Color> getRandomColors(size_t num_colors) {
    vector<Color> random_colors;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, all_colors.size() - 1);

    for (int i = 0; i < num_colors; ++i) {
        int index = distrib(gen);
        random_colors.push_back(all_colors[index]);
    }
    return random_colors;
}

void Oppgave4::pythagoras(){ 
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib1(-25,25);
    int w = 1000;   int h = 1100;
    int Xm = w/4;   int Ym = h/4;
    int l_a = 200;  int l_b = 300;
    int r{10};      int rx{0};
    int cx{w/2};    int cy{h/2};
    

    AnimationWindow win{100,100, w, h, "Pythagoras"};
    
    while(!win.should_close()) {
            vector<Color> randomColors = getRandomColors(7);
            // Tilfeldig endring
            int index1 = distrib1(gen);int index2 = distrib1(gen);int index3 = distrib1(gen);int index4 = distrib1(gen);int index5 = distrib1(gen);int index6 = distrib1(gen);
            int deltaX = distrib1(gen);int deltaY = distrib1(gen);
            l_a += index1;  l_b += index2;
            Xm += index3;   Ym += index4;
            r += index5;    rx += index6;
            cx += deltaX;   cy += deltaY; 

            // begrensninga
            if (l_a > 500) l_a = 500;   if (l_a < 0) l_a = 0;
            if (l_b > 500) l_b = 500;   if (l_b < 0) l_b = 0;
            if (Xm > 500) Xm = 500;     if (Xm < 0) Xm = 0;
            if (Ym > 500) Ym = 500;     if (Ym < 0) Ym = 0;
            if (r > 300) r = 300;       if (r < 1) r = 1;    
            if (rx > 10) rx = 5;        if (rx < -10) rx = -5;

            // Tilfeldig endring i posisjon
            Point p1{Xm,Ym}; Point p2{Xm + l_b,Ym}; Point p3{Xm,Ym+l_a};
            Point Z1{Xm + l_b,Ym};Point Z2{Xm,Ym+l_a}; Point Z3{p3.x + l_a, p3.y + l_b};Point Z4{p2.x + l_a, p2.y + l_b};
            Point A1{p3.x - l_a, p3.y}; Point A2 = p3; Point A3 = p1; Point A4{p1.x - l_a, p1.y};
            Point B1{p2.x,p2.y -l_b}; Point B2 = p2; Point B3 = p1;Point B4{p1.x, p1.y-l_b}; 
            Point C{cx,cy}; Point Ha{cx+r/4,cy-r/4}; Point Va{cx-r/4,cy-r/4}; Point M{cx,cy + r/2};
            int auge = r/4 +rx; int munn = r/3 +rx* 1.3;
            
            //tegninga
            win.draw_triangle(p1, p2, p3, randomColors[0]);//Color::red
            win.draw_quad(Z1, Z2, Z3, Z4, randomColors[1]);//Color::blue
            win.draw_quad(A1, A2, A3, A4, randomColors[2]);//Color::black
            win.draw_quad(B1, B2, B3, B4, randomColors[3]);//Color::green
            win.draw_circle(C,r,randomColors[4]);
            win.draw_circle(Ha,auge,randomColors[5]);
            win.draw_circle(Va,auge,randomColors[6]);
            win.draw_circle(M,munn,randomColors[7]);
            _sleep(0.5);
            win.next_frame();
        }
    win.wait_for_close();
}

void Oppgave4::chooseTask() {
    int pick;
    bool validPick = false;

    while (!validPick) { 
        cout << "Velg funksjon: \n"
             << "0) Tilbake\n"
             << "1) pythagoras\n"
             << "Angi valg (0-1): ";
        cin >> pick;

        switch (pick) {
            case 0:
                validPick = true;
                break;
            case 1:
                Oppgave4::pythagoras();
                break;
            default:
                cout << "Ikke gyldig valg, prøv igjen\n";
                break;
        }
    }
}
