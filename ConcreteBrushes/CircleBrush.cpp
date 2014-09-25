////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

//
// CircleBrush.cpp
//
// The implementation of Circle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "math.h"

#include "../impressionistDoc.h"
#include "../impressionistUI.h"
#include "circlebrush.h"

CircleBrush::CircleBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void CircleBrush::BrushBegin(const ImpPoint source, const ImpPoint target)
{
	size = getSize() / 2;
	steps = floor(size * 4 * PI + 0.5);
	BrushMove(source, target);
}

void CircleBrush::BrushMove(const ImpPoint source, const ImpPoint target)
{
	ImpressionistDoc* pDoc = GetDocument();
	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove  document is NULL\n");
		return;
	}

	glPushMatrix();
	glTranslatef(target.x, target.y, 0);

	glBegin(GL_POLYGON);
	SetColor(source, pDoc->m_pUI->getAlpha());
	for (int i = 0; i < steps; i++) {
		double a = i * 2 * PI / steps;
		glVertex2d(cos(a) * size, sin(a) * size);
	}
	glEnd();

	glPopMatrix();
}

void CircleBrush::BrushEnd(const ImpPoint source, const ImpPoint target)
{
	// do nothing so far
}
