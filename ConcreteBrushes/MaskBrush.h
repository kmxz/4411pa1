//
// MaskBrush.h
//
// The header file for Filter Brush. 
//

#ifndef MASKBRUSH_H
#define MASKBRUSH_H

#include "../ImpBrush.h"

class MaskBrush : public ImpBrush
{
public:
	MaskBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
	int extra(void);
	bool init(void);
	double atPosition(int x, int y);
private:
	char fileName[256];
	unsigned char* data;
	int	width, height;
};

#endif