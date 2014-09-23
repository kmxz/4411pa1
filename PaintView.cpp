//
// paintview.cpp
//
// The code maintaining the painting view of the input images
//

#include "math.h"
#include "impressionist.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "paintview.h"
#include "ImpBrush.h"
#include "RightMouseSelect.h"
#include <vector>
#include <algorithm>


#define LEFT_MOUSE_DOWN		1
#define LEFT_MOUSE_DRAG		2
#define LEFT_MOUSE_UP		3
#define RIGHT_MOUSE_DOWN	4
#define RIGHT_MOUSE_DRAG	5
#define RIGHT_MOUSE_UP		6
#define LEFT_MOUSE_MOVE     7
#define AUTO_DRAW			8


#ifndef WIN32
#define min(a, b)	( ( (a)<(b) ) ? (a) : (b) )
#define max(a, b)	( ( (a)>(b) ) ? (a) : (b) )
#endif

static int		eventToDo;
static int		isAnEvent=0;
static Point	coord;
struct { int spacing; bool randomSize; } autoDrawSettings;

static const GLubyte filterIndicatorColor[3] = { 255, 0, 0 };

PaintView::PaintView(int			x, 
					 int			y, 
					 int			w, 
					 int			h, 
					 const char*	l)
						: Fl_Gl_Window(x,y,w,h,l)
{
	m_nWindowWidth	= w;
	m_nWindowHeight	= h;

}


void PaintView::draw()
{
	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_FRONT_AND_BACK);
	#endif // !MESA

	if(!valid())
	{
		glClearColor(0.7f, 0.7f, 0.7f, 1.0);

		// We're only using 2-D, so turn off depth 
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); glEnable(GL_BLEND);
		glDisable( GL_DEPTH_TEST );

		ortho();

		glClear( GL_COLOR_BUFFER_BIT );
	}

	Point scrollpos;// = GetScrollPosition();
	scrollpos.x = 0;
	scrollpos.y	= 0;

	m_nWindowWidth	= w();
	m_nWindowHeight	= h();

	int drawWidth, drawHeight;
	drawWidth = min( m_nWindowWidth, m_pDoc->m_nPaintWidth );
	drawHeight = min( m_nWindowHeight, m_pDoc->m_nPaintHeight );

	int startrow = m_pDoc->m_nPaintHeight - (scrollpos.y + drawHeight);
	if ( startrow < 0 ) startrow = 0;

	m_pPaintBitstart = m_pDoc->m_ucPainting + 
		3 * ((m_pDoc->m_nPaintWidth * startrow) + scrollpos.x);

	m_nDrawWidth	= drawWidth;
	m_nDrawHeight	= drawHeight;

	m_nStartRow		= startrow;
	m_nEndRow		= startrow + drawHeight;
	m_nStartCol		= scrollpos.x;
	m_nEndCol		= m_nStartCol + drawWidth;

	if ( m_pDoc->m_ucPainting && !isAnEvent) 
	{
		RestoreContent();
	}

	if ( m_pDoc->m_ucPainting && isAnEvent) 
	{

		// Clear it after processing.
		isAnEvent	= 0;	

		// issue #4: out-of-boundary detection
		if (coord.x < 0) { coord.x = 0; }
		if (coord.x >= m_nDrawWidth) { coord.x = m_nDrawWidth - 1; }
		if (coord.y < 0) { coord.y = 0; }
		if (coord.y >= m_nDrawHeight) { coord.y = m_nDrawHeight - 1; }

		Point source( coord.x + m_nStartCol, m_nEndRow - coord.y );
		Point target( coord.x, m_nWindowHeight - coord.y );

		// This is the event handler
		switch (eventToDo) 
		{
		case LEFT_MOUSE_DOWN:
			m_pDoc->m_pCurrentStrokeDirection->StrokeDirectionBegin(source, target);
			m_pDoc->m_pCurrentBrush->BrushBegin( source, target );
			break;
		case LEFT_MOUSE_DRAG:
			m_pDoc->m_pCurrentStrokeDirection->StrokeDirectionMove(source, target);
			m_pDoc->m_pCurrentBrush->BrushMove( source, target );
			// updateFilterCircle(target);
			break;
		case LEFT_MOUSE_UP:
			m_pDoc->m_pCurrentStrokeDirection->StrokeDirectionEnd(source, target);
			m_pDoc->m_pCurrentBrush->BrushEnd( source, target );
			SaveCurrentContent();
			RestoreContent();
			m_pDoc->undoable = true;
			break;
		case RIGHT_MOUSE_DOWN:
			if (m_pDoc->m_pCurrentBrush->extra() & EXTRA_LINE) {
				MouseBegin(source, target, m_pDoc);
			}
			break;
		case RIGHT_MOUSE_DRAG:
				if (m_pDoc->m_pCurrentBrush->extra() & EXTRA_LINE) {
				RestoreContent();
				MouseMove(source, target, m_pDoc);
			}
			break;
		case RIGHT_MOUSE_UP:
			if (m_pDoc->m_pCurrentBrush->extra() & EXTRA_LINE) {
				MouseEnd(source, target, m_pDoc);
				RestoreContent();
			}
			break;
		case LEFT_MOUSE_MOVE:
			// updateFilterCircle(target);
			break;
		case AUTO_DRAW:
			realAutoDraw();

			SaveCurrentContent();
			RestoreContent();
			break;
		default:
			printf("Unknown event!!\n");		
			break;
		}
	}

	glFlush();

	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_BACK);
	#endif // !MESA

}


int PaintView::handle(int event)
{
	switch(event)
	{
	case FL_ENTER:
	    redraw();
		break;
	case FL_PUSH:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DOWN;
		else
			eventToDo=LEFT_MOUSE_DOWN;
		isAnEvent=1;
		redraw();
		break;
	case FL_DRAG:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DRAG;
		else
			eventToDo=LEFT_MOUSE_DRAG;
		isAnEvent=1;
		redraw();
		m_pDoc->m_pUI->m_origView->markCoord(coord);
		break;
	case FL_RELEASE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_UP;
		else
			eventToDo=LEFT_MOUSE_UP;
		isAnEvent=1;
		redraw();
		break;
	case FL_MOVE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		// seems this section will cause bug on some computers. let's comment it out first and fix it later.
		//eventToDo = LEFT_MOUSE_MOVE;
		//isAnEvent = 1;
		//redraw();
		m_pDoc->m_pUI->m_origView->markCoord(coord);
		break;
	default:
		return 0;
		break;
	}

	return 1;
}

void PaintView::refresh()
{
	redraw();
}

void PaintView::resizeWindow(int width, int height)
{
	resize(x(), y(), width, height);
}

void PaintView::SaveCurrentContent()
{
	// Tell openGL to read from the front buffer when capturing
	// out paint strokes
	glReadBuffer(GL_FRONT);

	glPixelStorei( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei( GL_PACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	
	memcpy(m_pDoc->m_ucLast, m_pDoc->m_ucPainting, m_nDrawWidth * m_nDrawHeight * 3);

	glReadPixels( 0, 
				  m_nWindowHeight - m_nDrawHeight, 
				  m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart );
}


void PaintView::RestoreContent()
{
	glDrawBuffer(GL_BACK);

	glClear( GL_COLOR_BUFFER_BIT );

	glRasterPos2i( 0, m_nWindowHeight - m_nDrawHeight );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glPixelStorei( GL_UNPACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	glDrawPixels( m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart);

//	glDrawBuffer(GL_FRONT);
}

void PaintView::updateFilterCircle(Point target) {
	if (m_pDoc->m_pCurrentBrush->extra() & EXTRA_FILTER) {
		RestoreContent();
		glBegin(GL_LINE_LOOP);
		glLineWidth(1);
		int size = m_pDoc->m_pUI->getSize() / 2;
		int steps = floor(size * 4 * PI + 0.5);
		for (int i = 0; i < steps; i++) {
			double a = i * 2 * PI / steps;
			glVertex2d(target.x + cos(a) * size, target.y + sin(a) * size);
		}
		glColor3ubv(filterIndicatorColor);
		glEnd();
	}
}

#include<iostream>

void PaintView::autoDraw(int spacing, bool randomSize) {
	autoDrawSettings.spacing = spacing;
	autoDrawSettings.randomSize = randomSize;
	eventToDo = AUTO_DRAW;
	isAnEvent = 1;
	redraw();
}

void PaintView::realAutoDraw() {
	std::vector<Point> spots;
	if (autoDrawSettings.randomSize) { ImpBrush::randomSize = true; }
	for (int x = 0; x < m_pDoc->m_nPaintWidth + autoDrawSettings.spacing; x += autoDrawSettings.spacing) {
		for (int y = 0; y < m_pDoc->m_nPaintHeight + autoDrawSettings.spacing; y += autoDrawSettings.spacing) {
			Point punkt = Point(x, y);
			spots.push_back(punkt);
		}
	}
	std::random_shuffle(spots.begin(), spots.end());
	for (std::vector<Point>::iterator i = spots.begin(); i != spots.end(); i++) {
		m_pDoc->m_pCurrentBrush->BrushBegin(*i, *i);
	}
	ImpBrush::randomSize = false;
	m_pDoc->undoable = true;
}