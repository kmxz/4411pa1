#include "RightMouseSelect.h"
#include "math.h"
Point initailPoint;
static const GLubyte red[] = { 255, 0, 0 };

void MouseBegin(const Point source, const Point target)
{
	glLineWidth(1);
	initailPoint = source;
	MouseMove(source, target);
}
void MouseMove(const Point source, const Point target)
{
	glBegin(GL_LINES);
	glColor3ubv(red);
	glVertex2d(initailPoint.x, initailPoint.y);
	glVertex2d(target.x, target.y);
	glEnd();
}
void MouseEnd(const Point source, const Point target)
{

}
