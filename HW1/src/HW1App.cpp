#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Resources.h"
#include <cstdlib> 
#include <iostream>
#include <math.h>

using namespace ci;
using namespace ci::app;
using namespace std;

class HW1App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void setPixel(uint8_t* pixelarray, int x, int y, Color8u color);
	void drawRectangle(uint8_t* pixelarray, int x, int y, int width, int height, Color8u color);
	void drawCircle(uint8_t* pixelarray, int x, int y, double radius, Color8u color);

private:
	Surface* mySurface_;
	uint8_t* pixels;
};

static const int displayWidth = 800;
static const int displayHeight = 800;

void HW1App::setup()
{
	mySurface_ = new Surface(displayWidth,displayHeight,false);
}

void HW1App::mouseDown( MouseEvent event )
{

}

void HW1App::setPixel(uint8_t* pixelarray, int x, int y, Color8u color)
{
	//Sets pixel at location (x,y) to the color passed
	{
		pixelarray[y*displayWidth*3 + 3*x]=color.r;
		pixelarray[y*displayWidth*3 + 3*x]=color.g;
		pixelarray[y*displayWidth*3 + 3*x]=color.b;
	}
}

void HW1App::drawRectangle(uint8_t* pixelarray, int x, int y, int width, int height, Color8u color)
{
	//Sets pixels (going right to left, top to bottom) to form a filled rectangle
	for(int m=x; m<x+width; m++){

		for(int n=y; n<y+height; n++){
			setPixel(pixelarray, m, n, color);
		}

	}
}

void HW1App::drawCircle(uint8_t* pixelarray, int x, int y, double radius, Color8u color)
{
	//Sets pixels in the circumference of the circle
	for(double i=0; i<360; i=i+0.01){
		setPixel(pixelarray, cos(i)*radius+x, sin(i)*radius+y, color);	//Credit to cluelesswalnut for correct math for drawing circle (github.com/cluelesswalnut)
	}
}

void HW1App::update()
{
	uint8_t* pixels = (*mySurface_).getData();
	drawRectangle(pixels,0,0,800,800,Color8u(150,0,150));
	drawRectangle(pixels,350,50,150,150,Color8u(0,0,0));
	drawCircle(pixels,200,200,150,Color8u(255,255,255));
}

void HW1App::draw()
{
	gl::draw(*mySurface_);
}

CINDER_APP_BASIC( HW1App, RendererGl )
