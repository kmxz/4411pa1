#include "BrushStroke.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"

BrushStroke::BrushStroke(ImpressionistDoc* pDoc, int type) :
StrokeDirection(pDoc, type)
{
}

void BrushStroke::StrokeDirectionBegin(const Point source, const Point target){}
void BrushStroke::StrokeDirectionMove(const Point source, const Point target){}
void BrushStroke::StrokeDirectionEnd(const Point source, const Point target){}
