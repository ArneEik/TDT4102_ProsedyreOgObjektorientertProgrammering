// Utdelt kode, visualisering av cannonball-spillet i øving 3.

#include "subprojects\animationwindow\include\AnimationWindow.h"
#include "subprojects\std_lib_facilities\std_lib_facilities.h"
#include "cannonball_viz.h"
#include "cannonball.h"
// Pass på sirkulaer headerinkludering.
using namespace TDT4102;
Cannonball cannonball;

void cannonBallViz(double targetPosition, int fieldLength, double initVelocityX, double initVelocityY,
				   int timeSteps)
{
	constexpr int w_width = 800;
	constexpr int w_height = 500;
	int target_x = static_cast<int>((targetPosition * w_width) / fieldLength);
	AnimationWindow window(100, 100, w_width, w_height, "Cannonball Visualizer"); //100, 100 angir x og y, som er overst til venstre i vinduet
	window.keep_previous_frame(false);
	
	// forste tidssteg er 0
	for (int i = 0; i <= timeSteps; ++i) {
		// Lag en ny frame ved starten av løkken slik at siste bildet er vist naar animasjonen er ferdig
		window.next_frame();

		// Plot target. targetPosition er [100, 1000] i main programmet
		// denne funksjonen mapper 0 til 0, og fieldLength til w_width
		
		window.draw_rectangle(Point{target_x - 10, w_height - 20}, 20, 20, Color::dark_green);

		double time = i * (cannonball.flightTime(initVelocityY) / timeSteps);
		double yPos =  cannonball.posY(0, initVelocityY, time);

		// maa skalere x til w_width, som beskrevet over
		int xPos = (cannonball.posX(0, initVelocityX, time) * w_width) / fieldLength;
		window.draw_circle(Point{xPos, static_cast<int>(w_height - cannonball.posY(0, initVelocityY, time))}, 8, Color::red);
		// cout<< time << setw(4) << xPos<<"    "<<yPos<<endl;
	}
	int xPos = static_cast<int>(cannonball.posX(0, initVelocityX, cannonball.flightTime(initVelocityY)));
	if (cannonball.isInRange(targetPosition,xPos)) {
		string text = "U WON!!!";

		for (int j = 0; j < 325; j++) { 
			int fontSize = 40 + static_cast<int>(15 * sin(j * M_PI / 30));
			int textWidth = text.length() * (fontSize / 2); 
			int xPost = (w_width - textWidth) / 2;
			int yPos = (w_height - fontSize) / 2;
			window.next_frame();

			window.draw_text(Point{xPost, yPos}, text, Color::red, fontSize,Font::courier_bold_italic);
			window.draw_circle(Point{(xPos* w_width) / fieldLength, static_cast<int>(w_height - cannonball.posY(0, initVelocityY, cannonball.flightTime(initVelocityY)))}, 8, Color::red);
			window.draw_rectangle(Point{target_x - 10, w_height - 20}, 20, 20, Color::dark_green);
		}
	}
}
