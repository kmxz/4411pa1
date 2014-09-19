#include "SliderRightMouseStroke.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"

SliderRightMouseStroke::SliderRightMouseStroke(ImpressionistDoc* pDoc , int type ):
StrokeDirection(pDoc,type)
{
}

void SliderRightMouseStroke::StrokeDirectionBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();

	StrokeDirectionMove(source, target);
}

void SliderRightMouseStroke::StrokeDirectionMove(const Point source, const Point target)
{

}
void SliderRightMouseStroke::StrokeDirectionEnd(const Point source, const Point target){}