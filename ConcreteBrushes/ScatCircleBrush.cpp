//
// ScatCircleBrush.cpp
//
// The implementation of Scattered Circle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "../impressionistDoc.h"
#include "../impressionistUI.h"
#include "ScatCircleBrush.h"

extern float frand();

ScatCircleBrush::ScatCircleBrush(ImpressionistDoc* pDoc, char* name) :
CircleBrush(pDoc, name)
{
}

void ScatCircleBrush::BrushMove(const Point source, const Point target)
{
	int count = 2 + random() * 3; // randomly choose between 2, 3 or 4 lines
	for (int i = 0; i < count; i++) {
		int dx = (random() - 0.5) * size * 2;
		int dy = (random() - 0.5) * size * 2;
		CircleBrush::BrushMove(Point(source.x + dx, source.y + dy), Point(target.x + dx, target.y + dy));
	}
}

void ScatCircleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

