////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

// 
// impressionistDoc.cpp
//
// It basically maintain the bitmap for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//

#include <FL/fl_ask.H>
#include "math.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"

#include "ImpBrush.h"
#include "StrokeDirection.h"

#include "ConcreteBrushes/AllBrushes.h"

// Include individual strokes headers here.
#include "SliderRightMouseStroke.h"
#include "GradientStroke.h"
#include "BrushStroke.h"

#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } }

ImpressionistDoc::ImpressionistDoc() 
{
	// Set NULL image name as init. 
	m_imageName[0]	='\0';	

	m_nWidth		= -1;
	m_ucBitmap		= NULL;
	m_ucPainting	= NULL;
	m_ucLast		= NULL;
	undoable		= false;

	// create one instance of each brush
	ImpBrush::c_nBrushCount	= NUM_BRUSH_TYPE;
	ImpBrush::c_pBrushes	= new ImpBrush* [ImpBrush::c_nBrushCount];

	ImpBrush::c_pBrushes[BRUSH_POINTS]	= new PointBrush( this, "Points" );

	// Note: You should implement these 5 brushes.  They are set the same (PointBrush) for now
	ImpBrush::c_pBrushes[BRUSH_LINES]				
		= new LineBrush( this, "Lines" );
	ImpBrush::c_pBrushes[BRUSH_CIRCLES]				
		= new CircleBrush( this, "Circles" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_POINTS]	
		= new ScatPointBrush( this, "Scattered Points" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]		
		= new ScatLineBrush( this, "Scattered Lines" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_CIRCLES]	
		= new ScatCircleBrush(this, "Scattered Circles");
	ImpBrush::c_pBrushes[BRUSH_STARS]
		= new StarBrush(this, "Extra: Hollow Stars");
	ImpBrush::c_pBrushes[BRUSH_HEARTS]
		= new HeartBrush(this, "Extra: Hearts");
	ImpBrush::c_pBrushes[BRUSH_POLY_STARS]
		= new PolyStarBrush(this, "Extra: Poly-stars");
	ImpBrush::c_pBrushes[BRUSH_FILTERS]
		= new FilterBrush(this, "Extra: Poly-stars");
	ImpBrush::c_pBrushes[BRUSH_MASKS]
		= new MaskBrush(this, "Matte (luminance mask)");

	// make one of the brushes current
	m_pCurrentBrush	= ImpBrush::c_pBrushes[DEFAULT_BRUSH_INDEX];

	// create one instance of each stroke
	StrokeDirection::c_nStrokeDirectionCount = NUM_STROKE_DIRECTION_TYPE;
	StrokeDirection::c_pStrokeDirections = new StrokeDirection*[StrokeDirection::c_nStrokeDirectionCount];
	StrokeDirection::c_pStrokeDirections[STROKE_SLIDER_RIGHT_MOUSE] = new SliderRightMouseStroke(this, STROKE_SLIDER_RIGHT_MOUSE);
	StrokeDirection::c_pStrokeDirections[STROKE_GRADIENT] = new GradientStroke(this, STROKE_GRADIENT);
	StrokeDirection::c_pStrokeDirections[STROKE_BRUSH_DIRECTION] = new BrushStroke(this, STROKE_BRUSH_DIRECTION);

	// make one of the stroke direction current
	m_pCurrentStrokeDirection = StrokeDirection::c_pStrokeDirections[0];

}


//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void ImpressionistDoc::setUI(ImpressionistUI* ui) 
{
	m_pUI	= ui;
}

//---------------------------------------------------------
// Returns the active picture/painting name
//---------------------------------------------------------
char* ImpressionistDoc::getImageName() 
{
	return m_imageName;
}

//---------------------------------------------------------
// Called by the UI when the user changes the brush type.
// type: one of the defined brush types.
//---------------------------------------------------------
bool ImpressionistDoc::setBrushType(int type)
{
	m_pCurrentBrush	= ImpBrush::c_pBrushes[type];
	if (!m_pCurrentBrush->init()) {
		return false;
	}
	m_pUI->setLineOptions(m_pCurrentBrush->extra());
	return true;
}

//---------------------------------------------------------
// Called by the UI when the user changes the stroke type.
// type: one of the defined stroke direction types.
//---------------------------------------------------------
void ImpressionistDoc::setStrokeDirectionType(int type)
{
	m_pCurrentStrokeDirection = StrokeDirection::c_pStrokeDirections[type];

}

//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadImage(char *iname) 
{
	// try to open the image to read
	unsigned char*	data;
	int				width, 
					height;

	if ( (data=readBMP(iname, width, height))==NULL ) 
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	// reflect the fact of loading the new image
	m_nWidth		= width;
	m_nPaintWidth	= width;
	m_nHeight		= height;
	m_nPaintHeight	= height;

	// release old storage
	if ( m_ucBitmap ) delete [] m_ucBitmap;
	if ( m_ucPainting ) delete [] m_ucPainting;
	if ( m_ucLast ) delete[] m_ucLast;

	undoable = false;

	m_ucBitmap		= data;

	// allocate space for draw view
	m_ucPainting	= new unsigned char [width*height*3];
	memset(m_ucPainting, 0, width*height*3);

	m_ucLast = new unsigned char[width*height * 3];
	memset(m_ucLast, 0, width*height * 3);

	m_pUI->resize_windows(width, height);

	// display it on origView
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->refresh();

	return 1;
}


//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is 
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::saveImage(char *iname) 
{

	writeBMP(iname, m_nPaintWidth, m_nPaintHeight, m_ucPainting);

	return 1;
}

//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::clearCanvas() 
{

	// Release old storage
	if ( m_ucPainting ) 
	{
		delete [] m_ucPainting;

		// allocate space for draw view
		m_ucPainting	= new unsigned char [m_nPaintWidth*m_nPaintHeight*3];
		memset(m_ucPainting, 0, m_nPaintWidth*m_nPaintHeight*3);

		// refresh paint view as well	
		m_pUI->m_paintView->refresh();
	}
	
	return 0;
}

//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( int x, int y )
{
	if ( x < 0 ) 
		x = 0;
	else if ( x >= m_nWidth ) 
		x = m_nWidth-1;

	if ( y < 0 ) 
		y = 0;
	else if ( y >= m_nHeight ) 
		y = m_nHeight-1;

	return (GLubyte*)(m_ucBitmap + 3 * (y*m_nWidth + x));
}

//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( const Point p )
{
	return GetOriginalPixel( p.x, p.y );
}

void ImpressionistDoc::undo(void) {
	if (!undoable) {
		fl_alert("Nothing to undo!");
		return;
	}
	memcpy(m_ucPainting, m_ucLast, m_nPaintWidth * m_nPaintHeight * 3);
	m_pUI->m_paintView->redraw();
	undoable = false;
}

void ImpressionistDoc::swap(void) {
	unsigned char* temp = m_ucBitmap;
	m_ucBitmap = m_ucPainting;
	m_ucPainting = temp;
	memcpy(m_ucLast, m_ucPainting, m_nPaintWidth * m_nPaintHeight * 3); // to fix color manip bug
	m_pUI->m_origView->refresh();
	m_pUI->m_paintView->refresh();
	undoable = false;
}

unsigned char ImpressionistDoc::map(unsigned char origin, double gamma) {
	return pow(origin / 255.0, gamma) * 255 + 0.5;
}

void ImpressionistDoc::gamma(double r, double g, double b) {
	int length = m_nPaintWidth * m_nPaintHeight * 3;
	for (int i = 0; i < length; i += 3) {
		m_ucPainting[i] = map(m_ucLast[i], r);
		m_ucPainting[i + 1] = map(m_ucLast[i + 1], g);
		m_ucPainting[i + 2] = map(m_ucLast[i + 2], b);
	}
}