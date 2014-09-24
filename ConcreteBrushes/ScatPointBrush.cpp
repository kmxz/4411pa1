////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

//
// ScatPointBrush.cpp
//
// The implementation of Scattered Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "../impressionistDoc.h"
#include "../impressionistUI.h"
#include "ScatPointBrush.h"

extern float frand();

ScatPointBrush::ScatPointBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void ScatPointBrush::BrushBegin(const Point source, const Point target)
{
	glPointSize(1);

	BrushMove(source, target);
}

void ScatPointBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = getSize();

	glPushMatrix();
	glTranslatef(target.x, target.y, 0);

	for (int i = - size / 2; i < size / 2; i++) {
		for (int j = -size / 2; j < size / 2; j++) {
			if (random() > 0.230493) { // my birthday as magic number
				continue;
			}
			glBegin(GL_POINTS);
			Point real_source = Point(source.x + i, source.y + j);
			SetColor(real_source, pDoc->m_pUI->getAlpha());
			glVertex2d(i, j);
			glEnd();
		}
	}

	// hack: always paint at center
	glBegin(GL_POINTS);
	SetColor(source, pDoc->m_pUI->getAlpha());
	glVertex2d(0, 0);
	glEnd();

	glPopMatrix();
}

void ScatPointBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

