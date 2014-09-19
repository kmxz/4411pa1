
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "StrokeDirection.h"


StrokeDirection::StrokeDirection(ImpressionistDoc* pDoc, int type) :
m_pType(type),
m_pDoc(pDoc)
{
	c_pAngle = 0;
}


