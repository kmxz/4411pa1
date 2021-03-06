////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

//
// PolyStarBrush.cpp
//
// The implementation of Poly Star Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "math.h"

#include "../impressionistDoc.h"
#include "../impressionistUI.h"
#include "PolyStarBrush.h"

PolyStarBrush::PolyStarBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void PolyStarBrush::BrushBegin(const ImpPoint source, const ImpPoint target)
{
	ImpressionistDoc* pDoc = GetDocument();

	size = getSize();
	angle = pDoc->m_pUI->getLineAngle();
	sides = pDoc->m_pUI->getSides();
}

void PolyStarBrush::BrushMove(const ImpPoint source, const ImpPoint target)
{
	ImpressionistDoc* pDoc = GetDocument();

	if (pDoc == NULL) {
		printf("PolyStarBrush::BrushMove  document is NULL\n");
		return;
	}

	glPushMatrix();
	glTranslatef(target.x, target.y, 0);
	glRotatef(angle, 0, 0, 1);
	glScalef(size, size, 1);

	SetColor(source, pDoc->m_pUI->getAlpha());

	glBegin(GL_POLYGON);
	for (int i = 0; i < sides; i++) {
		double in = i * 2  * PI / sides;
		glVertex2d(cos(in) / 2, sin(in) / 2);
	}
	glEnd();

	for (int i = 0; i < sides; i++) {
		glBegin(GL_POLYGON);
		double inl = i * 2 * PI / sides;
		double inr = (i + 1) * 2 * PI / sides;
		double out = (i * 2 + 1) * PI / sides;
		glVertex2d(cos(inl) / 2, sin(inl) / 2);
		glVertex2d(cos(inr) / 2, sin(inr) / 2);
		glVertex2d(cos(out), sin(out));
		glEnd();
	}

	glPopMatrix();
}

void PolyStarBrush::BrushEnd(const ImpPoint source, const ImpPoint target)
{
	// do nothing so far	
}

// @override
int PolyStarBrush::extra(void)
{
	return EXTRA_ANGLE | EXTRA_SIDES | ImpBrush::extra();
}

