////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

//
// LineBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "../impressionistDoc.h"
#include "../impressionistUI.h"
#include "linebrush.h"

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void LineBrush::BrushBegin(const ImpPoint source, const ImpPoint target)
{
	ImpressionistDoc* pDoc = GetDocument();

	size = getSize();
	
	glLineWidth(pDoc->m_pUI->getLineWidth());
}

void LineBrush::BrushMove(const ImpPoint source, const ImpPoint target)
{
	ImpressionistDoc* pDoc = GetDocument();

	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}

	glPushMatrix();
	glTranslatef(target.x, target.y, 0);
	glRotatef(pDoc->m_pUI->getLineAngle(), 0, 0, 1);

	glBegin(GL_LINES);
	SetColor(source, pDoc->m_pUI->getAlpha());
	glVertex2d(-size/2, 0);
	glVertex2d(size/2, 0);
	glEnd();

	glPopMatrix();
}

void LineBrush::BrushEnd(const ImpPoint source, const ImpPoint target)
{
	// do nothing so far	
}

// @override
int LineBrush::extra(void)
{
	return EXTRA_WIDTH | EXTRA_ANGLE | EXTRA_LINE | ImpBrush::extra();
}

