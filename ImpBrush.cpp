////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

//
// ImpBrush.cpp
//
// The implementation of virtual brush. All the other brushes inherit from it.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ImpBrush.h"

// Static class member initializations
int			ImpBrush::c_nBrushCount	= 0;
ImpBrush**	ImpBrush::c_pBrushes	= NULL;
double		ImpBrush::magnify = 1;

ImpBrush::ImpBrush(ImpressionistDoc*	pDoc, 
				   char*				name) :
					m_pDoc(pDoc), 
					m_pBrushName(name)
{
}

//---------------------------------------------------
// Return m_pDoc, which connects the UI and brushes
//---------------------------------------------------
ImpressionistDoc* ImpBrush::GetDocument(void)
{
	return m_pDoc;
}

int ImpBrush::getSize(void)
{
	int baseSize = m_pDoc->m_pUI->getSize();
	return baseSize * magnify;
}

//---------------------------------------------------
// Return the name of the current brush
//---------------------------------------------------
char* ImpBrush::BrushName(void)
{
	return m_pBrushName;
}

int ImpBrush::extra(void) // to be overloadded
{
	return DEFAULT_BRUSH_SETTINGS;
}

bool ImpBrush::init(void) { // to be overloadded
	return true;
}

//----------------------------------------------------
// Set the color to paint with to the color at source,
// which is the coord at the original window to sample 
// the color from
//----------------------------------------------------
void ImpBrush::SetColor (const ImpPoint source, const float alpha)
{
	ImpressionistDoc* pDoc = GetDocument();

	GLubyte color[4];

	unsigned char alphaByte = alpha * 255;
	color[3] = alphaByte;
	memcpy ( color, pDoc->GetOriginalPixel( source ), 3 );

	glColor4ubv( color );

}

// return a random number in [0, 1), which i prefer more (as my mother tounge is JavaScript)
double ImpBrush::random(void)
{
	return (rand() / (double)(RAND_MAX + 1));
}