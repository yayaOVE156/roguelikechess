#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <GL/glut.h>
#include <cmath>




extern int* arrx;
extern int* arry;
extern int* arrs;


void setGLColor(int red, int green, int blue);
void DrawCircle(float cx, float cy, float r, int num_segments, float z);
void DrawMoon(float cx, float cy, float r, int num_segments, float z);
void drawStretchedLowerHalfCircle(float x, float y, float radius, float z);
void drawFlame(float x, float y, float baseWidth, float height, float z);
void drawStar(float x, float y, float Size, float z);
void drawNightSky(float x, float y, float width, float height, float z);
void largeBlock(float x, float y, float z);
void largeBlockMedH(float x, float y, float z);
void medBlock(float x, float y, float z);
void smallBlock(float x, float y, float z);
void window(float x, float y, float z);
void borderwindow(float x, float y, float z);
void torch(float x, float y, float z);
void drawBackGround(float x, float y, float z);


#endif // BACKGROUND_H
