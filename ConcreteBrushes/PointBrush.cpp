////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

//
// PointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "../impressionistDoc.h"
#include "../impressionistUI.h"
#include "pointbrush.h"

extern float frand();

PointBrush::PointBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void PointBrush::BrushBegin( const ImpPoint source, const ImpPoint target )
{
	int size = getSize();
	glPointSize( (float)size );
}

void PointBrush::BrushMove( const ImpPoint source, const ImpPoint target )
{
	ImpressionistDoc* pDoc = GetDocument();

	if ( pDoc == NULL ) {
		printf( "PointBrush::BrushMove  document is NULL\n" );
		return;
	}

	glBegin( GL_POINTS );
	SetColor(source, pDoc->m_pUI->getAlpha());

		glVertex2d( target.x, target.y );

	glEnd();
}

void PointBrush::BrushEnd( const ImpPoint source, const ImpPoint target )
{
	// do nothing so far
}

