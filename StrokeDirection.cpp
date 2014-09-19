
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "StrokeDirection.h"

// Static class member initializations
int			StrokeDirection::c_nStrokeDirectionCount = 0;
StrokeDirection**	StrokeDirection::c_pStrokeDirections = NULL;

StrokeDirection::StrokeDirection(ImpressionistDoc* pDoc,
								int type) :
								m_pType(type),
								m_pDoc(pDoc)
{
	c_pAngle = 0;
}


//---------------------------------------------------
// Return m_pDoc, which connects the UI and brushes
//---------------------------------------------------
ImpressionistDoc* StrokeDirection::GetDocument(void)
{
	return m_pDoc;
}

