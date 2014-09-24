////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

//
// MaskBrush.cpp
//
// The implementation of Mask Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include <FL/fl_ask.H>

#include "../impressionistDoc.h"
#include "../impressionistUI.h"
#include "MaskBrush.h"

#define MAX2(M, N) ((M) > (N) ? (M) : (N))
#define MIN2(M, N) ((M) < (N) ? (M) : (N))

#define MAX(A,B,C) (MAX2((A), MAX2((B), (C))))
#define MIN(A,B,C) (MIN2((A), MIN2((B), (C))))

MaskBrush::MaskBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
	fileName[0] = '\0';
}

void MaskBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();

	glPointSize((float)1);
	BrushMove(source, target);
}

void MaskBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();

	if (pDoc == NULL) {
		printf("MaskBrush::BrushMove  document is NULL\n");
		return;
	}

	glPushMatrix();
	glTranslatef(target.x, target.y, 0);

	int xOffset = -width / 2;
	int yOffset = -height / 2;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			int mappedX = x + xOffset;
			int mappedY = y + yOffset;
			glBegin(GL_POINTS);
			SetColor(source, atPosition(x, y));
			glVertex2d(mappedX, mappedY);
			glEnd();
		}
	}

	glPopMatrix();
}

void MaskBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

// @override
int MaskBrush::extra(void)
{
	return 0;
}

// @override
bool MaskBrush::init(void) {
	char* newfile = fl_file_chooser("Load mask image?", "*.bmp", fileName);
	if (newfile == NULL) {
		return false;
	}
	if ((data = readBMP(newfile, width, height)) == NULL)
	{
		fl_alert("Can't load bitmap file");
		return false;
	}
	return true;
}

double MaskBrush::atPosition(int x, int y) {
	// here we get luminance using HSL's definition
	unsigned char* src = data + 3 * (y*width + x);
	return (MAX(src[0], src[1], src[2]) + MIN(src[0], src[1], src[2])) / 2.0 / 255;
}