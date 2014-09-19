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

void PolyStarBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();

	size = pDoc->getSize();
	angle = pDoc->getLineAngle();
	sides = pDoc->getSides();
	BrushMove(source, target);
}

void PolyStarBrush::BrushMove(const Point source, const Point target)
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

	SetColor(source, pDoc->getAlpha());

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

void PolyStarBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far	
}

// @override
int PolyStarBrush::extra(void)
{
	return EXTRA_ANGLE | EXTRA_SIDES | ImpBrush::extra();
}

