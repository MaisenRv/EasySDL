#include "../../include/EasySDL/Window.hpp"
#include <GL/glew.h>
#include "../../include/EasySDL/utils/colors.hpp"
#include "../../include/EasySDL/objects/shape/square/Square.hpp"
#include "../../include/Math/interpolation/Lerp.hpp"
#include "../../include/Math/interpolation/Quadratic.hpp"
#include "../../include/Math/utils/pingPong.hpp"
#include "../../include/EasySDL/objects/chart/StaticLineChart.hpp"
#include <cmath>
#include <cstdio>


EasySDL::Window *w = new EasySDL::Window(900, 450, "Ventana");
EasySDL::Square s3({225,225},200,200);
EasySDL::StaticLineChart lc({460,25},400,400,"prueba");

float f(float x) {return x*x;}

void setup()
{
	lc.setRange(0,1);
	lc.setDomain(0,1);
	lc.addCurve("lineal",2,EasySDL::Quadratic::easeOutF);
	lc.setCurveColor("lineal",EasySDL::MINT_GREEN_NORMALIZED);

	lc.setup();
	s3.setup();
}

float t = 0.0f;
float delta = 0.01;
float pingpong = 0;
void draw()
{
	lc.draw(w);

	s3.draw(w);
	// s3.setScale(EasySDL::Lerp::lerp(1,1.5,pingpong));
	s3.setScale(EasySDL::Quadratic::quadratic(1,1.5,pingpong,EasySDL::Quadratic::easeOut));
	lc.setPointPosition("lineal",pingpong,EasySDL::Quadratic::easeOutF(pingpong));
	pingpong = EasySDL::pingPongUp(t,0.0f,1);
	t += delta;
}

int main()
{
    w->start(draw, setup);
}
