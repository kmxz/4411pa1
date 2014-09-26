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
	kernel = NULL;
}

void FilterBrush::BrushBegin(const ImpPoint source, const ImpPoint target)
{
	size = getSize();
	kernel = new double*[size];
	double sigma = size / 6.0;
	double sigma22 = 2 * sigma * sigma;
	double weight = 0;
	for (int i = 0; i < size; i++) {
		int ii = i - size / 2;
		kernel[i] = new double[size];
		for (int j = 0; j < size; j++) {
			int jj = j - size / 2;
			kernel[i][j] = exp(-(ii * ii + jj * jj)/sigma22);
			weight += kernel[i][j];
		}
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			kernel[i][j] /= weight;
		}
	}
	glPointSize(1);
}

void FilterBrush::BrushMove(const ImpPoint source, const ImpPoint target)
{
	ImpressionistDoc* pDoc = GetDocument();

	if (pDoc == NULL) {
		printf("FilterBrush::BrushMove  document is NULL\n");
		return;
	}

	int* index = new int[size];
	int* indey = new int[size];
	for (int ix = 0; ix < size; ix++) {
		int pix = ix - size / 2 + source.x;
		for (int jy = 0; jy < size; jy++) {
			int pjy = jy - size / 2 + source.y;
			// WONTFIX: if the brush size is larger than the canvas size, segfault will occur
			for (int i = 0; i < size; i++) {
				int iix = pix + i - size / 2;
				if (iix < 0 || iix > pDoc->m_nPaintWidth) { iix = pix + size / 2 - i; }
				index[i] = iix;
				int iiy = pjy + i - size / 2;
				if (iiy < 0 || iiy > pDoc->m_nPaintHeight) { iiy = pjy + size / 2 - i; }
				indey[i] = iiy;
			}
			double total[] = { 0, 0, 0 };
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					for (int c = 0; c < 3; c++) {
						total[c] += kernel[i][j] * pDoc->m_ucPainting[(indey[j] * pDoc->m_nPaintWidth + index[i]) * 3 + c];
					}
				}
			}
			glBegin(GL_POINTS);
			glColor3d(total[0] / 255, total[1] / 255, total[2] / 255);
			glVertex2d(pix, pjy);
			glEnd();
		}
	}
}

void FilterBrush::BrushEnd(const ImpPoint source, const ImpPoint target)
{
	if (kernel) {
		for (int i = 0; i < size; i++) {
			delete[] kernel[i];
		}
		delete[] kernel;
	}
}

// @override
int FilterBrush::extra(void)
{
	return EXTRA_FILTER | EXTRA_SIZE;
}