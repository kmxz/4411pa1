//
// CircleBrush.cpp
//
// The implementation of Circle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "math.h"

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "circlebrush.h"

extern float frand();

CircleBrush::CircleBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void CircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();

	size = pDoc->getSize();
	steps = floor(size * 4 * PI + 0.5);
	BrushMove(source, target);
}

void CircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove  document is NULL\n");
		return;
	}

	glPushMatrix();
	glTranslatef(target.x, target.y, 0);

	glBegin(GL_POLYGON);
	SetColor(source, pDoc->getAlpha());
	for (int i = 0; i < steps; i++) {
		double a = i * 2 * PI / steps;
		glVertex2d(cos(a) * size, sin(a) * size);
	}
	glEnd();

	glPopMatrix();
}

void CircleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}
