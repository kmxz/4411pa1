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

void StarBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();

	size = pDoc->getSize();
	BrushMove(source, target);
}

void StarBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove  document is NULL\n");
		return;
	}

	glPushMatrix();
	glTranslatef(target.x, target.y, 0);
	glScalef(size, size, 0);

	glBegin(GL_POLYGON);
	SetColor(source, pDoc->getAlpha());
	glEnd();

	glPopMatrix();
}

// @override
int StarBrush::extra(void)
{
	return EXTRA_WIDTHANGLE;
}


void StarBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}
