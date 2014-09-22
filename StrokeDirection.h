#ifndef STROKEDIRECTION_H
#define STROKEDIRECTION_H

class ImpressionistDoc; // Pre-declaring class
class Point;

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
protected:
	StrokeDirection::StrokeDirection(ImpressionistDoc* pDoc, int type);
public:
	static int					c_nStrokeDirectionCount;	
	static StrokeDirection**	c_pStrokeDirections;		

	// get Doc to communicate with it
	ImpressionistDoc* GetDocument(void);

	virtual void StrokeDirectionBegin(const Point source, const Point target) = 0;
	virtual void StrokeDirectionMove(const Point source, const Point target) = 0;
	virtual void StrokeDirectionEnd(const Point source, const Point target) = 0;

	virtual int getAngle(void) = 0;
private:
	int m_pType;
	ImpressionistDoc *m_pDoc;
};

#endif
