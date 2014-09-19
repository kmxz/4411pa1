#pragma once

// Each stroke direction type has an associated constant.
enum
{
	STROKE_SLIDER_RIGHT_MOUSE = 0,
	STROKE_GRADIENT,
	STROKE_BRUSH_DIRECTION,
	NUM_STROKE_DIRECTION_TYPE // Make sure this stays at the end!
};

class StrokeDirection
{
public:
	int c_pAngle;

	static int					c_nStrokeDirectionCount;	
	static StrokeDirection**	c_pStrokeDirections;		

	virtual void StrokeDirectionBegin(const Point source, const Point target) = 0;
	virtual void StrokeDirectionMove(const Point source, const Point target) = 0;
	virtual void StrokeDirectionEnd(const Point source, const Point target) = 0;

	StrokeDirection(ImpressionistDoc* pDoc = NULL, int type = NULL);

private:
	int m_pType;
	ImpressionistDoc *m_pDoc;
};

