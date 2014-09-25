////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

#ifndef IMPBRUSH_H
#define IMPBRUSH_H

//
// ImpBrush.h
//
// The header file of virtual brush. All the other brushes inherit from it.
//

#include <stdlib.h>

#ifndef PI
#define PI 3.14159265359
#endif


#define DEFAULT_BRUSH_INDEX 0
#define DEFAULT_BRUSH_SETTINGS EXTRA_SIZE | EXTRA_ALPHA | EXTRA_AUTO

// Each brush type has an associated constant.
enum
{
	BRUSH_POINTS = 0,
	BRUSH_LINES,
	BRUSH_CIRCLES,
	BRUSH_SCATTERED_POINTS,
	BRUSH_SCATTERED_LINES,
	BRUSH_SCATTERED_CIRCLES,
	BRUSH_STARS,
	BRUSH_HEARTS,
	BRUSH_POLY_STARS,
	BRUSH_FILTERS,
	BRUSH_MASKS,
	NUM_BRUSH_TYPE // Make sure this stays at the end!
};

// types of extra settings
enum
{
	EXTRA_ANGLE = 1 << 0,
	EXTRA_WIDTH = 1 << 1,
	EXTRA_LINE = 1 << 2,
	EXTRA_SIDES = 1 << 3,
	EXTRA_FILTER = 1 << 4,
	EXTRA_ALPHA = 1 << 5,
	EXTRA_SIZE = 1 << 6,
	EXTRA_AUTO = 1 << 7
};

class ImpressionistDoc; // Pre-declaring class

class ImpPoint 
{
public:
	ImpPoint() {};
	ImpPoint(int xx, int yy) { x = xx; y = yy; };

	int x, y;
};

class ImpBrush 
{
protected:
	ImpBrush::ImpBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );

public:
	// The implementation of your brush should realize these virtual functions
	virtual void BrushBegin( const ImpPoint source, const ImpPoint target ) = 0;
	virtual void BrushMove( const ImpPoint source, const ImpPoint target ) = 0;
	virtual void BrushEnd( const ImpPoint source, const ImpPoint target ) = 0;

	// according to the source image and the position, determine the draw color
	void SetColor( const ImpPoint source, const float alpha );

	// get Doc to communicate with it
	ImpressionistDoc* GetDocument( void );

	// Return the name of the brush (not used in this version).
	char* BrushName( void );
	
	static int			c_nBrushCount;	// How many brushes we have,
	static ImpBrush**	c_pBrushes;		// and what they are.

	static double		magnify;
	static double		random(void);

	virtual int extra(void);
	virtual bool init(void);

protected:
	int getSize(void);

private:
	ImpressionistDoc*	m_pDoc;

	// Brush's name (not used in this version).
	char*				m_pBrushName;
};

#endif