//
// ScatCircleBrush.cpp
//
// The implementation of Scattered Circle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatCircleBrush.h"

extern float frand();

ScatCircleBrush::ScatCircleBrush(ImpressionistDoc* pDoc, char* name) :
CircleBrush(pDoc, name)
{
}

void ScatCircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();

	
}

void ScatCircleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

