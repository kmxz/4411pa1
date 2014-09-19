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

//---------------------------------------------------
// Return the name of the current brush
//---------------------------------------------------
char* ImpBrush::BrushName(void)
{
	return m_pBrushName;
}

int ImpBrush::extra(void) // to be overloadded
{
	return EXTRA_NONE;
}

int ImpBrush::minimum(void) // to be overloadded
{
	return 1;
}

//----------------------------------------------------
// Set the color to paint with to the color at source,
// which is the coord at the original window to sample 
// the color from
//----------------------------------------------------
void ImpBrush::SetColor (const Point source, const float alpha)
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