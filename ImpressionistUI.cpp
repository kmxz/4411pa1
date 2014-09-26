////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

//
// impressionistUI.h
//
// The user interface part for the program.
//


#include <FL/fl_ask.h>
#include <FL/Enumerations.H>
#include <FL/Fl_Box.H>
#include <math.h>

#include "impressionistUI.h"
#include "impressionistDoc.h"

#include "ConvolutionUI.h"

#define STYLIZE_THE_FUCKING_SLIDER(slider) { slider->type(FL_HOR_NICE_SLIDER); slider->labelfont(FL_COURIER); slider->labelsize(12); slider->align(FL_ALIGN_RIGHT); }

#define ITEM_ACTIVATION(name, widget) { if (extra & name) { widget->activate(); } else { widget->deactivate(); } }

/*
//------------------------------ Widget Examples -------------------------------------------------
Here is some example code for all of the widgets that you may need to add to the 
project.  You can copy and paste these into your code and then change them to 
make them look how you want.  Descriptions for all of the widgets here can be found 
in links on the fltk help session page.

//---------Window/Dialog and Menubar-----------------------------------
	
	//----To install a window--------------------------
	Fl_Window* myWindow = new Fl_Window(600, 300, "MyWindow");
		myWindow->user_data((void*)(this));	// record self to be used by static callback functions
		
		// install menu bar
		myMenubar = new Fl_Menu_Bar(0, 0, 600, 25);
		Fl_Menu_Item ImpressionistUI::myMenuItems[] = {
			{ "&File",		0, 0, 0, FL_SUBMENU },
				{ "&Load...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load },
				{ "&Save...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save }.
				{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
				{ 0 },
			{ "&Edit",		0, 0, 0, FL_SUBMENU },
				{ "&Copy",FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_copy, (void *)COPY },
				{ "&Cut",	FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_cut, (void *)CUT },
				{ "&Paste",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_paste, (void *)PASTE },
				{ 0 },
			{ "&Help",		0, 0, 0, FL_SUBMENU },
				{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
				{ 0 },
			{ 0 }
		};
		myMenubar->menu(myMenuItems);
    m_mainWindow->end();

	//----The window callback--------------------------
	// One of the callbacks
	void ImpressionistUI::cb_load(Fl_Menu_* o, void* v) 
	{	
		ImpressionistDoc *pDoc=whoami(o)->getDocument();

		char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
		if (newfile != NULL) {
			pDoc->loadImage(newfile);
		}
	}


//------------Slider---------------------------------------

	//----To install a slider--------------------------
	Fl_Value_Slider * mySlider = new Fl_Value_Slider(10, 80, 300, 20, "My Value");
	mySlider->user_data((void*)(this));	// record self to be used by static callback functions
	mySlider->type(FL_HOR_NICE_SLIDER);
    mySlider->labelfont(FL_COURIER);
    mySlider->labelsize(12);
	mySlider->minimum(1);
	mySlider->maximum(40);
	mySlider->step(1);
	mySlider->value(m_nMyValue);
	mySlider->align(FL_ALIGN_RIGHT);
	mySlider->callback(cb_MyValueSlides);

	//----The slider callback--------------------------
	void ImpressionistUI::cb_MyValueSlides(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyValue=int( ((Fl_Slider *)o)->value() ) ;
	}
	

//------------Choice---------------------------------------
	
	//----To install a choice--------------------------
	Fl_Choice * myChoice = new Fl_Choice(50,10,150,25,"&myChoiceLabel");
	myChoice->user_data((void*)(this));	 // record self to be used by static callback functions
	Fl_Menu_Item ImpressionistUI::myChoiceMenu[3+1] = {
	  {"one",FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)ONE},
	  {"two",FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)TWO},
	  {"three",FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)THREE},
	  {0}
	};
	myChoice->menu(myChoiceMenu);
	myChoice->callback(cb_myChoice);
	
	//-----The choice callback-------------------------
	void ImpressionistUI::cb_myChoice(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
		ImpressionistDoc* pDoc=pUI->getDocument();

		int type=(int)v;

		pDoc->setMyType(type);
	}


//------------Button---------------------------------------

	//---To install a button---------------------------
	Fl_Button* myButton = new Fl_Button(330,220,50,20,"&myButtonLabel");
	myButton->user_data((void*)(this));   // record self to be used by static callback functions
	myButton->callback(cb_myButton);

	//---The button callback---------------------------
	void ImpressionistUI::cb_myButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
		ImpressionistDoc* pDoc = pUI->getDocument();
		pDoc->startPainting();
	}


//---------Light Button------------------------------------
	
	//---To install a light button---------------------
	Fl_Light_Button* myLightButton = new Fl_Light_Button(240,10,150,25,"&myLightButtonLabel");
	myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
	myLightButton->callback(cb_myLightButton);

	//---The light button callback---------------------
	void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->myBool==TRUE) pUI->myBool=FALSE;
		else pUI->myBool=TRUE;
	}

//----------Int Input--------------------------------------

    //---To install an int input-----------------------
	Fl_Int_Input* myInput = new Fl_Int_Input(200, 50, 5, 5, "&My Input");
	myInput->user_data((void*)(this));   // record self to be used by static callback functions
	myInput->callback(cb_myInput);

	//---The int input callback------------------------
	void ImpressionistUI::cb_myInput(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyInputValue=int( ((Fl_Int_Input *)o)->value() );
	}

//------------------------------------------------------------------------------------------------
*/

//------------------------------------- Help Functions --------------------------------------------

//------------------------------------------------------------
// This returns the UI, given the menu item.  It provides a
// link from the menu items to the UI
//------------------------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Menu_* o)	
{
	return ( (ImpressionistUI*)(o->parent()->user_data()) );
}


//--------------------------------- Callback Functions --------------------------------------------

void ImpressionistUI::cb_window(Fl_Widget* o, void* v) {
	exit(0);
}

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();
	whoami(o)->stopAvBridges();
	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->loadImage(newfile, false);
	}
}

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_mural_image(Fl_Menu_* o, void* v)
{
	ImpressionistDoc *pDoc = whoami(o)->getDocument();
	whoami(o)->stopAvBridges();
	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadImage(newfile, true);
	}
}

//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Save File?", "*.bmp", "save.bmp" );
	if (newfile != NULL) {
		pDoc->saveImage(newfile);
	}
}

//-------------------------------------------------------------
// Brings up the paint dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_brushes(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_brushDialog->show();
}

//-------------------------------------------------------------
// Brings up the color manipulation dialog
// This is called by the UI when the color manip menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_color_manip(Fl_Menu_* o, void* v)
{
	whoami(o)->m_colorDialog->show();
}

//-------------------------------------------------------------
// Brings up the dissolve dialog
// This is called by the UI when the color manip menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_dissolve_dialog(Fl_Menu_* o, void* v)
{
	whoami(o)->m_dissolveDialog->show();
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();

	pDoc->clearCanvas();
}

//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v) 
{
	whoami(o)->stopAvBridges();
	whoami(o)->m_mainWindow->hide();
	whoami(o)->m_brushDialog->hide();

}

//------------------------------------------------------------
// Bonus: undo
//------------------------------------------------------------
void ImpressionistUI::cb_undo(Fl_Menu_* o, void* v)
{
	whoami(o)->m_pDoc->undo();
}

//------------------------------------------------------------
// Bonus: swap canvas
//------------------------------------------------------------
void ImpressionistUI::cb_swap(Fl_Menu_* o, void* v)
{
	whoami(o)->m_pDoc->swap();
}

//-----------------------------------------------------------
// Brings up an about dialog box
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_about(Fl_Menu_* o, void* v) 
{
	fl_message("Impressionist FLTK version for CS341, Spring 2002");
}

//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of brush to use to the one chosen in the brush 
// choice.  
// Called by the UI when a brush is chosen in the brush choice
//-------------------------------------------------------------
void ImpressionistUI::cb_brushChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	int type=(int)v;

	if (!pDoc->setBrushType(type)) {
		((Fl_Choice*)o)->value(pUI->m_currentBrushIndex);
	} else {
		pUI->m_currentBrushIndex = type;
	}
}

//-------------------------------------------------------------
// Sets the type of stroke direction to use to the one chosen  
// in the stroke direction choice.  
// Called by the UI when a stroke direction is chosen in the 
// stroke direction choice.
//-------------------------------------------------------------
void ImpressionistUI::cb_strokeDirectionChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();
	int type = (int)v;
	
	pUI->m_nStrokeDirectionType = type;
	pDoc->setStrokeDirectionType(type);
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}

//-----------------------------------------------------------
// Do a dissolve
//-----------------------------------------------------------
void ImpressionistUI::cb_dissolve(Fl_Widget* o, void* v)
{
	ImpressionistUI* self = ((ImpressionistUI*)(o->user_data()));
	self->m_dissolveDialog->hide();
	double until = self->m_dissolveSlider->value();
	double seconds = self->m_dissolveTimeSlider->value();
	self->m_pDoc->dissolve(until, seconds);
}

//-----------------------------------------------------------
// Do a gradient
//-----------------------------------------------------------
void ImpressionistUI::cb_load_ext_gradient(Fl_Widget* o, void* v) {
	Fl_Light_Button* myself = (Fl_Light_Button*)o;
	ImpressionistUI* self = ((ImpressionistUI*)(o->user_data()));
	if (myself->value()) {
		char* newfile = fl_file_chooser("Open File?", "*.bmp", "");
		if (newfile != NULL) {
			int width, height;
			readBMP(newfile, width, height);
			if (width == self->m_pDoc->m_nWidth && height == self->m_pDoc->m_nHeight) {
				// file name to use
			} else {
				fl_alert("Dimensions mismatch!");
			}
		} else {
			fl_alert("No valid image selected.");
		}
		myself->value(0);
	}
}

//-----------------------------------------------------------
// Do a convolution
//-----------------------------------------------------------
void ImpressionistUI::cb_convolution_dialog(Fl_Menu_* o, void* v)
{
	new ConvolutionUI();
}

//-----------------------------------------------------------
// Do a auto-draw
//-----------------------------------------------------------
void ImpressionistUI::cb_autodraw(Fl_Widget* o, void* v)
{
	ImpressionistUI* self = ((ImpressionistUI*)(o->user_data()));
	self->m_paintView->initAutoDraw(self->m_autoDrawSpacingSlider->value(), self->m_autoDrawSizeRandomed->value(), 0, false);
	self->m_paintView->singleAutoDraw();
}

//-----------------------------------------------------------
// Do a auto-draw on video
//-----------------------------------------------------------
void ImpressionistUI::cb_autodraw_video(Fl_Widget* o, void* v)
{
	ImpressionistUI* self = ((ImpressionistUI*)(o->user_data()));
	self->stopAvBridges();
	AvBridge::AVBRIDGE_ERROR err;
	char* vidFile = fl_file_chooser("Select your video file.", "*.*", "");
	if (vidFile == NULL) {
		fl_alert("No valid video file selected."); return;
	}
	self->currentAvBridge = new AvBridge(self->m_pDoc);
	if (self->currentAvBridge->ffOpen(vidFile) != AvBridge::AVBRIDGE_NO_ERROR) {
		fl_alert("Video file cannot be identified by FFmpeg."); return;
	}
	self->m_AutoDrawButton->deactivate();
	self->m_autoDrawSpacingSlider->deactivate();
	self->m_autoDrawVideoSlider->deactivate();
	self->m_autoDrawSizeRandomed->deactivate();
	double coherency = self->m_autoDrawVideoSlider->value();
	self->m_paintView->initAutoDraw(self->m_autoDrawSpacingSlider->value(), self->m_autoDrawSizeRandomed->value(), coherency, true);
	if (self->currentAvBridge->readFrame() != AvBridge::AVBRIDGE_NO_ERROR) {
		fl_alert("Error occured with FFmpeg");
	}
	self->m_AutoDrawButton->activate();
	self->m_autoDrawSpacingSlider->activate();
	self->m_autoDrawVideoSlider->activate();
	self->m_autoDrawSizeRandomed->activate();
}


//-----------------------------------------------------------
// Color manipulation related
//-----------------------------------------------------------

void ImpressionistUI::cb_updateColor(Fl_Widget* o, void* v) {
	ImpressionistUI* self = ((ImpressionistUI*)(o->user_data()));
	self->m_pDoc->gamma(self->m_colorSliders[0]->value(), self->m_colorSliders[1]->value(), self->m_colorSliders[2]->value());
	self->m_paintView->refresh();
	self->m_pDoc->undoable = true;
}

//---------------------------------- per instance functions --------------------------------------

//------------------------------------------------
// Return the ImpressionistDoc used
//------------------------------------------------
ImpressionistDoc* ImpressionistUI::getDocument()
{
	return m_pDoc;
}

//------------------------------------------------
// Draw the main window
//------------------------------------------------
void ImpressionistUI::show() {
	m_mainWindow->show();
	m_paintView->show();
	m_origView->show();
}

void ImpressionistUI::stopAvBridges() {
	if (currentAvBridge) { 
		AvBridge* bridge = currentAvBridge;
		currentAvBridge = NULL;
		bridge->stop();
	}
}

//------------------------------------------------
// Change the paint and original window sizes to 
// w by h
//------------------------------------------------
void ImpressionistUI::resize_windows(int w, int h) {
	m_mainWindow->resize(m_mainWindow->x(), m_mainWindow->y(), w * 2, h + 25);
	m_origView->resizeWindow(w, h);
	m_paintView->resizeWindow(w, h);
}

//------------------------------------------------ 
// Set the ImpressionistDoc used by the UI to 
// communicate with the brushes 
//------------------------------------------------
void ImpressionistUI::setDocument(ImpressionistDoc* doc)
{
	m_pDoc = doc;

	m_origView->m_pDoc = doc;
	m_paintView->m_pDoc = doc;
}

//------------------------------------------------
// Return the brush size
//------------------------------------------------
int ImpressionistUI::getSize()
{
	return m_BrushSizeSlider->value();
}

//------------------------------------------------
// Return the brush line width
//------------------------------------------------
int ImpressionistUI::getLineWidth()
{
	return m_BrushLineWidthSlider->value();
}

//------------------------------------------------
// Return the brush line angle
//------------------------------------------------
int ImpressionistUI::getLineAngle()
{
	return m_pDoc->m_pCurrentStrokeDirection->getAngle();
}

//------------------------------------------------
// Return the brush line angle
//------------------------------------------------
int ImpressionistUI::getSides()
{
	return m_SidesSlider->value();
}

//------------------------------------------------
// Return the brush line angle
//------------------------------------------------
int ImpressionistUI::getStrokeDirectionType()
{
	return m_nStrokeDirectionType;
}

//------------------------------------------------
// Return the brush alpha opacity
//------------------------------------------------
double ImpressionistUI::getAlpha()
{
	return m_AlphaSlider->value();
}

// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Load Image...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load_image },
		{ "&Load Mural...", FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_load_mural_image },
		{ "&Save Image...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save_image },
		{ "&Brushes...",	FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushes }, 
		{ "&Clear Canvas", FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_clear_canvas, 0, FL_MENU_DIVIDER },
		
		{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
		{ 0 },

	{ "&Action",	0, 0, 0, FL_SUBMENU },
		{ "&Undo", NULL, (Fl_Callback *)ImpressionistUI::cb_undo },
		{ "&Swap", NULL, (Fl_Callback *)ImpressionistUI::cb_swap },
		{ "&Color manipulation", NULL, (Fl_Callback *)ImpressionistUI::cb_color_manip },
		{ "&Dissolve", NULL, (Fl_Callback *)ImpressionistUI::cb_dissolve_dialog },
		{ "&Convolution", NULL, (Fl_Callback *)ImpressionistUI::cb_convolution_dialog },
		{ 0 },

	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
		{ 0 },

	{ 0 }
};

// Brush choice menu definition
Fl_Menu_Item ImpressionistUI::brushTypeMenu[NUM_BRUSH_TYPE+1] = {
  {"Points",			FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_POINTS},
  {"Lines",				FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LINES},
  {"Circles",			FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CIRCLES},
  {"Scattered Points",	FL_ALT+'q', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POINTS},
  {"Scattered Lines",	FL_ALT+'m', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_LINES},
  {"Scattered Circles",	FL_ALT+'d', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_CIRCLES},
  {"Extra: Hollow Stars",NULL,		(Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_STARS },
  {"Extra: Hearts",		 NULL,		(Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_HEARTS },
  {"Extra: Poly - stars",NULL,		(Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_POLY_STARS },
  {"Filter: Gaussian blur",	NULL,	(Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_FILTERS },
  {"Matte (luminance mask)", NULL,	(Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_MASKS },
  {0}
};

// Stroke Direction Type choice menu definition
Fl_Menu_Item ImpressionistUI::strokeDirectionTypeMenu[NUM_STROKE_DIRECTION_TYPE + 1] = {
  {"Slider/Right Mouse", FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_strokeDirectionChoice, (void *)STROKE_SLIDER_RIGHT_MOUSE },
  {"Gradient",			 FL_ALT + 'g', (Fl_Callback *)ImpressionistUI::cb_strokeDirectionChoice, (void *)STROKE_GRADIENT },
  {"Brush Direction",	 FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_strokeDirectionChoice, (void *)STROKE_BRUSH_DIRECTION },
  { 0 }
};


//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImpressionistUI::ImpressionistUI() {
	// Create the main window
	m_mainWindow = new Fl_Window(600, 300, "Impressionist");
		m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
		// install menu bar
		m_menubar = new Fl_Menu_Bar(0, 0, 600, 25);
		m_menubar->menu(menuitems);

		// Create a group that will hold two sub windows inside the main
		// window
		Fl_Group* group = new Fl_Group(0, 25, 600, 275);

			// install paint view window
			m_paintView = new PaintView(300, 25, 300, 275, "This is the paint view");//0jon
			m_paintView->box(FL_DOWN_FRAME);

			// install original view window
			m_origView = new OriginalView(0, 25, 300, 275, "This is the orig view");//300jon
			m_origView->box(FL_DOWN_FRAME);
			m_origView->deactivate();

		group->end();
		Fl_Group::current()->resizable(group);
    m_mainWindow->end();

	m_mainWindow->callback(cb_window);

	currentAvBridge = NULL;

	m_nStrokeDirectionType = 0;

	m_currentBrushIndex = DEFAULT_BRUSH_INDEX;

	// brush dialog definition
	m_brushDialog = new Fl_Window(400, 325, "Brush Dialog");
		// Add a brush type choice to the dialog
		m_BrushTypeChoice = new Fl_Choice(50,10,150,25,"&Brush");
		m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushTypeChoice->menu(brushTypeMenu);
		m_BrushTypeChoice->callback(cb_brushChoice);

		// Add a stroke direction type choice to the dialog
		m_StrokeDirectionTypeChoice = new Fl_Choice(110, 45, 150, 25, "&Stroke Direction");
		m_StrokeDirectionTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_StrokeDirectionTypeChoice->menu(strokeDirectionTypeMenu);
		m_StrokeDirectionTypeChoice->callback(cb_strokeDirectionChoice);

		m_extGradient = new Fl_Light_Button(275, 45, 145, 25, "Ext. Gradient");
		m_extGradient->user_data((void*)(this));	// record self to be used by static callback functions
		m_extGradient->callback(cb_load_ext_gradient);

		m_ClearCanvasButton = new Fl_Button(240,10,150,25,"&Clear Canvas");
		m_ClearCanvasButton->user_data((void*)(this));
		m_ClearCanvasButton->callback(cb_clear_canvas_button);

		// Add brush size slider to the dialog 
		m_BrushSizeSlider = new Fl_Value_Slider(10, 80, 300, 20, "Size");
		STYLIZE_THE_FUCKING_SLIDER(m_BrushSizeSlider);
		m_BrushSizeSlider->minimum(1);
		m_BrushSizeSlider->maximum(40);
		m_BrushSizeSlider->step(1);
		m_BrushSizeSlider->value(10);
		
		m_BrushLineWidthSlider = new Fl_Value_Slider(10, 110, 300, 20, "Line Width");
		STYLIZE_THE_FUCKING_SLIDER(m_BrushLineWidthSlider);
		m_BrushLineWidthSlider->minimum(1);
		m_BrushLineWidthSlider->maximum(40);
		m_BrushLineWidthSlider->step(1);
		m_BrushLineWidthSlider->value(1);

		m_BrushLineAngleSlider = new Fl_Value_Slider(10, 140, 300, 20, "Angle");
		STYLIZE_THE_FUCKING_SLIDER(m_BrushLineAngleSlider);
		m_BrushLineAngleSlider->minimum(0);
		m_BrushLineAngleSlider->maximum(359);
		m_BrushLineAngleSlider->step(1);
		m_BrushLineAngleSlider->value(0);

		m_SidesSlider = new Fl_Value_Slider(10, 170, 300, 20, "Sides");
		STYLIZE_THE_FUCKING_SLIDER(m_SidesSlider);
		m_SidesSlider->minimum(2);
		m_SidesSlider->maximum(20);
		m_SidesSlider->step(1);
		m_SidesSlider->value(6);

		m_AlphaSlider = new Fl_Value_Slider(10, 200, 300, 20, "Alpha");
		STYLIZE_THE_FUCKING_SLIDER(m_AlphaSlider);
		m_AlphaSlider->minimum(0);
		m_AlphaSlider->maximum(1);
		m_AlphaSlider->step(0.01);
		m_AlphaSlider->value(1);

		Fl_Group* autoDrawGroup = new Fl_Group(10, 230, 380, 70);

			autoDrawGroup->box(FL_FRAME_BOX);

			m_autoDrawSpacingSlider = new Fl_Value_Slider(20, 240, 140, 20, "Spacing");
			STYLIZE_THE_FUCKING_SLIDER(m_autoDrawSpacingSlider);
			m_autoDrawSpacingSlider->minimum(1);
			m_autoDrawSpacingSlider->maximum(16);
			m_autoDrawSpacingSlider->step(1);
			m_autoDrawSpacingSlider->value(4);

			m_autoDrawSizeRandomed = new Fl_Light_Button(220, 240, 90, 20, "Size rand.");

			m_AutoDrawButton = new Fl_Button(320, 240, 60, 20, "Draw");
			m_AutoDrawButton->user_data((void*)(this));
			m_AutoDrawButton->callback(cb_autodraw);

			m_autoDrawVideoSlider = new Fl_Value_Slider(20, 270, 140, 20, "Temporal coherency");
			STYLIZE_THE_FUCKING_SLIDER(m_autoDrawVideoSlider);
			m_autoDrawVideoSlider->minimum(0);
			m_autoDrawVideoSlider->maximum(1);
			m_autoDrawVideoSlider->step(0.01);
			m_autoDrawVideoSlider->value(1);

			m_AutoDrawVideoButton = new Fl_Button(300, 270, 80, 20, "On video");
			m_AutoDrawVideoButton->user_data((void*)(this));
			m_AutoDrawVideoButton->callback(cb_autodraw_video);

			autoDrawGroup->end();

		m_brushDialog->end();
		setLineOptions(DEFAULT_BRUSH_SETTINGS);

	// color dialog definition
	m_colorDialog = new Fl_Window(400, 140, "Color Manipulation");
		new Fl_Box(10, 10, 305, 20, "Gamma correction for color channels");

		m_colorSliders[0] = new Fl_Value_Slider(10, 40, 300, 20, "Red");
		m_colorSliders[0]->labelcolor(FL_RED);
		m_colorSliders[1] = new Fl_Value_Slider(10, 70, 300, 20, "Green");
		m_colorSliders[1]->labelcolor(FL_GREEN);
		m_colorSliders[2] = new Fl_Value_Slider(10, 100, 300, 20, "Blue");
		m_colorSliders[2]->labelcolor(FL_BLUE);
		for (int i = 0; i < 3; i++) {
			STYLIZE_THE_FUCKING_SLIDER(m_colorSliders[i]);
			m_colorSliders[i]->minimum(0.4);
			m_colorSliders[i]->maximum(2.5);
			m_colorSliders[i]->step(0.02);
			m_colorSliders[i]->value(1);
			m_colorSliders[i]->user_data((void*)(this));	// record self to be used by static callback functions
			m_colorSliders[i]->callback(cb_updateColor);
		}
		m_colorDialog->end();

	// dissolve dialog definition
	m_dissolveDialog = new Fl_Window(400, 160, "Dissolve");
		new Fl_Box(10, 10, 305, 20, "This will dissolve the left view into the right view\n up to a certain degree.");

		m_dissolveSlider = new Fl_Value_Slider(10, 50, 280, 20, "Percentage");
		STYLIZE_THE_FUCKING_SLIDER(m_dissolveSlider);
		m_dissolveSlider->minimum(0);
		m_dissolveSlider->maximum(1);
		m_dissolveSlider->step(0.01);
		m_dissolveSlider->value(0.75);

		m_dissolveTimeSlider = new Fl_Value_Slider(10, 80, 280, 20, "Duration (sec)");
		STYLIZE_THE_FUCKING_SLIDER(m_dissolveTimeSlider);
		m_dissolveTimeSlider->minimum(0.5);
		m_dissolveTimeSlider->maximum(5);
		m_dissolveTimeSlider->step(0.1);
		m_dissolveTimeSlider->value(1);

		Fl_Button* dissolveBtn = new Fl_Button(10, 110, 60, 20, "Dissolve");
		dissolveBtn->user_data((void*)(this));
		dissolveBtn->callback(cb_dissolve);

		m_dissolveDialog->end();
}

void ImpressionistUI::setLineOptions(int extra) {
	ITEM_ACTIVATION(EXTRA_ANGLE, m_BrushLineAngleSlider);
	ITEM_ACTIVATION(EXTRA_WIDTH, m_BrushLineWidthSlider);
	ITEM_ACTIVATION(EXTRA_LINE, m_StrokeDirectionTypeChoice);
	ITEM_ACTIVATION(EXTRA_SIDES, m_SidesSlider);
	ITEM_ACTIVATION(EXTRA_ALPHA, m_AlphaSlider);
	ITEM_ACTIVATION(EXTRA_SIZE, m_BrushSizeSlider);
	ITEM_ACTIVATION(EXTRA_AUTO, m_AutoDrawButton);
	ITEM_ACTIVATION(EXTRA_AUTO, m_AutoDrawVideoButton);
}