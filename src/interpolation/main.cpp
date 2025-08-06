#include "../../include/EasySDL/Window.hpp"
#include <GL/glew.h>
#include "../../include/EasySDL/utils/pathList.hpp"
#include "../../include/EasySDL/objects/shape/square/Square.hpp"
#include "../../include/Math/interpolation/Lerp.hpp"
#include "../../include/Math/utils/pingPong.hpp"
#include <cmath>
#include <cstdio>


EasySDL::Window *w = new EasySDL::Window(600, 600, "Ventana");
EasySDL::Square s({100,500},100,100);
EasySDL::Square s2({300,300},100,100);

void setup()
{
	s.setup();	
	s2.setup();

}

float t = 0.0f;
float delta = 0.01;
void draw()
{
	s.draw(w);
	s2.draw(w);
	// s.setPos(
	// 	EasySDL::Lerp::lerp(
	// 		{100,500},
	// 		{500,500},
	// 		EasySDL::pingPong(t,0.0f,1)
	// 	)
	// );
	s2.setAngle(
		EasySDL::Lerp::lerpAngle(0,M_PI,
			EasySDL::pingPong(t,0.0f,1)
		)
	);

	t += delta;
}

int main()
{
    w->start(draw, setup);
}
