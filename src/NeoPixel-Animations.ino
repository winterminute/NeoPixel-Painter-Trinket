const int duration = 2000;  //number of loops to run each animation for

#define NUMBEROFPIXELS 12   //Number of LEDs on the strip
#define PIXELPIN 8          //Pin where WS281X pixels are connected

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include <NeoPixelPainter.h>

Adafruit_NeoPixel neopixels = Adafruit_NeoPixel(NUMBEROFPIXELS, PIXELPIN, NEO_GRB + NEO_KHZ800);

NeoPixelPainterCanvas pixelcanvas = NeoPixelPainterCanvas(&neopixels); //create canvas, linked to the neopixels (must be created before the brush)
NeoPixelPainterBrush pixelbrush = NeoPixelPainterBrush(&pixelcanvas); //crete brush, linked to the canvas to paint to


void setup() {
	randomSeed(analogRead(0)); //new random seed 
	pinMode(PIXELPIN, OUTPUT);
	neopixels.begin();
}

unsigned long loopcounter; //count the loops, switch to next animation after a while
bool initialized = false; //initialize the canvas & brushes in each loop when zero

void loop() {

for(loopcounter = 0; loopcounter<duration; loopcounter++) 
	{

		HSV brushcolor;

		if (initialized == false)
		{
			initialized = true;
			pixelbrush.setSpeed(0); //do not move automatically
			pixelbrush.setFadein(true); //fade in 
			pixelbrush.setFadeout(true); //and fade out
		}


		if (rand() % 100 == 0) //at a random interval, move the brush to paint a new pixel (brush only paints a new pixel once)
		{
			brushcolor.h = rand();
			brushcolor.s = random(40); //set low saturation, almost white
			brushcolor.v = random(200) + 20; //set random brightness
			pixelbrush.setColor(brushcolor);
			pixelbrush.moveTo(random(NUMBEROFPIXELS)); //move the brush to a new, random pixel
			pixelbrush.setFadeSpeed(random(10) + 5); //set random fade speed, minimum of 5
		}

		//add a background color by setting all pixels to a color (instead of clearing all pixels):
		int i;
		for (i = 0; i < NUMBEROFPIXELS; i++)
		{
			neopixels.setPixelColor(i, 1, 0, 6); //color in RGB: dark blue
		}


		pixelbrush.paint(); //paint the brush to the canvas 
		pixelcanvas.transfer(); //transfer (add) the canvas to the neopixels

		neopixels.show();
	}


	initialized = false; //reset the variable before moving to the next loop

}
