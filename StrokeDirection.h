////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

#ifndef STROKEDIRECTION_H
#define STROKEDIRECTION_H

class ImpressionistDoc; // Pre-declaring class
class ImpPoint;

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

	virtual void StrokeDirectionBegin(const ImpPoint source, const ImpPoint target) = 0;
	virtual void StrokeDirectionMove(const ImpPoint source, const ImpPoint target) = 0;
	virtual void StrokeDirectionEnd(const ImpPoint source, const ImpPoint target) = 0;

	virtual int getAngle(void) = 0;
private:
	int m_pType;
	ImpressionistDoc *m_pDoc;
};

#endif
