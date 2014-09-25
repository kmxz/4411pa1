////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

//
// StarBrush.cpp
//
// The implementation of Star Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//


#include "../impressionistDoc.h"
#include "../impressionistUI.h"
#include "starbrush.h"

extern float frand();

StarBrush::StarBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

double StarBrush::coords[10][2] = {
	{ 0, 10 },
	{ -2.2452, 3.0902 },
	{ -9.5106, 3.0902 },
	{ -3.6328, -1.1804 },
	{ -5.8779, -8.0902 },
	{ 0, -3.8197 },
	{ 5.8779, -8.0902 },
	{ 3.6328, -1.1804 },
	{ 9.5106, 3.0902 },
	{ 2.2452, 3.0902 }
};

void StarBrush::BrushBegin(const ImpPoint source, const ImpPoint target)
{
	ImpressionistDoc* pDoc = GetDocument();

	size = getSize();
	angle = pDoc->m_pUI->getLineAngle();
	glLineWidth(pDoc->m_pUI->getLineWidth());
	BrushMove(source, target);
}

void StarBrush::BrushMove(const ImpPoint source, const ImpPoint target)
{
	ImpressionistDoc* pDoc = GetDocument();
	if (pDoc == NULL) {
		printf("StarBrush::BrushMove  document is NULL\n");
		return;
	}

	glPushMatrix();
	glTranslatef(target.x, target.y, 0);
	glRotatef(angle, 0, 0, 1);
	glScalef(size / 10.0, size / 10.0, 0);

	glBegin(GL_LINE_LOOP);
	SetColor(source, pDoc->m_pUI->getAlpha());
	for (int i = 0; i < 10; i++) {
		glVertex2d(coords[i][0], coords[i][1]);
	}
	glEnd();

	glPopMatrix();
}

// @override
int StarBrush::extra(void)
{
	return EXTRA_WIDTH | EXTRA_ANGLE | ImpBrush::extra();
}

void StarBrush::BrushEnd(const ImpPoint source, const ImpPoint target)
{
	// do nothing so far
}
