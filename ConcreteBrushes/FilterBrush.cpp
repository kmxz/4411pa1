////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

//
// FilterBrush.cpp
//
// The implementation of Filter Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "../impressionistDoc.h"
#include "../impressionistUI.h"
#include "FilterBrush.h"

FilterBrush::FilterBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void FilterBrush::BrushBegin(const Point source, const Point target)
{
	BrushMove(source, target);
}

void FilterBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();

	if (pDoc == NULL) {
		printf("FilterBrush::BrushMove  document is NULL\n");
		return;
	}
}

void FilterBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far	
}

// @override
int FilterBrush::extra(void)
{
	return EXTRA_FILTER;
}

