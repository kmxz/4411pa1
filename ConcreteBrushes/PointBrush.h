////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

//
// PointBrush.h
//
// The header file for Point Brush. 
//

#ifndef POINTBRUSH_H
#define POINTBRUSH_H

#include "../ImpBrush.h"

class PointBrush : public ImpBrush
{
public:
	PointBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );

	void BrushBegin( const ImpPoint source, const ImpPoint target );
	void BrushMove( const ImpPoint source, const ImpPoint target );
	void BrushEnd( const ImpPoint source, const ImpPoint target );
	char* BrushName( void );
};

#endif