#include "RightMouseSelect.h"
#include "math.h"
Point initailPoint;
static const GLubyte red[] = { 255, 0, 0 };

void MouseBegin(const Point source, const Point target, ImpressionistDoc* pDoc)
{
	glLineWidth(1);
	initailPoint = target;
	MouseMove(source, target,pDoc);
}
void MouseMove(const Point source, const Point target, ImpressionistDoc* pDoc)
{
	glBegin(GL_LINES);
	glColor3ubv(red);
	glVertex2d(initailPoint.x, initailPoint.y);
	glVertex2d(target.x, target.y);
	glEnd();
}
void MouseEnd(const Point source, const Point target, ImpressionistDoc* pDoc)
{
	Point p1 = initailPoint;
	Point p2 = target;
	int theta = pDoc->m_pUI->m_BrushLineAngleSlider->value();
	
	if (p2.x-p1.x!=0)
		theta=((int)(atan((p2.y - p1.y+0.0) / (p2.x - p1.x))/PI*180+360)%360);

	pDoc->m_pUI->m_BrushLineAngleSlider->value(theta);
	StrokeDirection::c_pAngle = theta;
}
