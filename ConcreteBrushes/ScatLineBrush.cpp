//
// ScatLineBrush.cpp
//
// The implementation of Scattered Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "../impressionistDoc.h"
#include "../impressionistUI.h"
#include "ScatLineBrush.h"
#include "math.h"

#define DEG2RAD (3.141592654 / 180)

extern float frand();

ScatLineBrush::ScatLineBrush(ImpressionistDoc* pDoc, char* name) :
LineBrush(pDoc, name)
{
}

void ScatLineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();

	int width = pDoc->m_pUI->getLineWidth();

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}
	int count = 2 + random() * 3; // randomly choose between 2, 3 or 4 lines
	double angleRad = pDoc->m_pUI->getLineAngle() * DEG2RAD;
	for (int i = 0; i < count; i++) {
		int dx = (random() - 0.5) * (size * cos(angleRad) + width * sin(angleRad) * 3) * 1.21; // Jan. 21st is the day I declared to her
		int dy = (random() - 0.5) * (size * sin(angleRad) + width * cos(angleRad) * 3) * 1.21;
		LineBrush::BrushMove(Point(source.x + dx, source.y + dy), Point(target.x + dx, target.y + dy));
	}
}

void ScatLineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

