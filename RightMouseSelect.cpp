////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

#include "RightMouseSelect.h"
#include "math.h"
ImpPoint initailImpPoint;
static const GLubyte red[] = { 255, 0, 0 };

void MouseBegin(const ImpPoint source, const ImpPoint target, ImpressionistDoc* pDoc)
{
	glLineWidth(1);
	initailImpPoint = target;
	MouseMove(source, target,pDoc);
}
void MouseMove(const ImpPoint source, const ImpPoint target, ImpressionistDoc* pDoc)
{
	glBegin(GL_LINES);
	glColor3ubv(red);
	glVertex2d(initailImpPoint.x, initailImpPoint.y);
	glVertex2d(target.x, target.y);
	glEnd();
}
void MouseEnd(const ImpPoint source, const ImpPoint target, ImpressionistDoc* pDoc)
{
	ImpPoint p1 = initailImpPoint;
	ImpPoint p2 = target;
	int theta = pDoc->m_pUI->m_BrushLineAngleSlider->value();
	
	if (p2.x-p1.x!=0)
		theta=((int)(atan((p2.y - p1.y+0.0) / (p2.x - p1.x))/PI*180+360)%360);

	pDoc->m_pUI->m_BrushLineAngleSlider->value(theta);
}
