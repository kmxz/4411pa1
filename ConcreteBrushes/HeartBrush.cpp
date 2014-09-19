//
// HeartBrush.cpp
//
// The implementation of Heart Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "math.h"

#include "../impressionistDoc.h"
#include "../impressionistUI.h"
#include "heartbrush.h"

HeartBrush::HeartBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void HeartBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();

	size = pDoc->getSize();
	angle = pDoc->getLineAngle();
	steps = floor(size / 4.0 * PI + 0.5);
	BrushMove(source, target);
}

void HeartBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();

	if (pDoc == NULL) {
		printf("HeartBrush::BrushMove  document is NULL\n");
		return;
	}

	glPushMatrix();
	glTranslatef(target.x, target.y, 0);
	glRotatef(angle, 0, 0, 1);
	glScalef(size / 4.0, size / 4.0, 0);

	glBegin(GL_POLYGON);
	SetColor(source, pDoc->getAlpha());
	glVertex2d(0, -2);
	glVertex2d(2, 1);
	for (int i = 0; i < steps; i++) {
		double a = i * PI / steps;
		glVertex2d(cos(a) + 1, sin(a) + 1);
	}
	glVertex2d(0, 1);
	for (int i = 0; i < steps; i++) {
		double a = i * PI / steps;
		glVertex2d(cos(a) - 1, sin(a) + 1);
	}
	glVertex2d(-2, 1);
	glEnd();

	glPopMatrix();
}

void HeartBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far	
}

// @override
int HeartBrush::extra(void)
{
	return EXTRA_ANGLE | ImpBrush::extra();
}

