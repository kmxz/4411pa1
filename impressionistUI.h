////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

//
// impressionistUI.h
//
// The header file for the UI part
//

#ifndef ImpressionistUI_h
#define ImpressionistUI_h

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_file_chooser.H>		// FLTK file chooser
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>

#include "Impressionist.h"
#include "OriginalView.h"
#include "PaintView.h"

#include "ImpBrush.h"
#include "StrokeDirection.h"

class ImpressionistUI {
public:
	ImpressionistUI();

	// The FLTK widgets
	Fl_Window*			m_mainWindow;
	Fl_Menu_Bar*		m_menubar;
								
	PaintView*			m_paintView;
	OriginalView*		m_origView;

// for brush dialog
	Fl_Window*			m_brushDialog;
	Fl_Choice*			m_BrushTypeChoice;
	Fl_Choice*			m_StrokeDirectionTypeChoice;

	Fl_Slider*			m_BrushSizeSlider;
	Fl_Slider*			m_BrushLineWidthSlider;
	Fl_Slider*			m_BrushLineAngleSlider;
	Fl_Slider*			m_SidesSlider;
	Fl_Slider*			m_AlphaSlider;
	Fl_Slider*			m_autoDrawSpacingSlider;
	Fl_Slider*			m_autoDrawVideoSlider;
	Fl_Light_Button*	m_autoDrawSizeRandomed;
	Fl_Button*          m_AutoDrawButton;
	Fl_Button*          m_AutoDrawVideoButton;
	Fl_Light_Button*    m_extGradient;

	Fl_Button*          m_ClearCanvasButton;

// for color manip dialog
	Fl_Window*			m_colorDialog;
	Fl_Slider*			m_colorSliders[3];

// for dissolve dialog
	Fl_Window*			m_dissolveDialog;
	Fl_Slider*			m_dissolveSlider;
	Fl_Slider*			m_dissolveTimeSlider;

	// Member functions
	void				setDocument(ImpressionistDoc* doc);
	ImpressionistDoc*	getDocument();

	void				show();
	void				resize_windows(int w, int h);

	// Interface to get attribute
	int					getSize();
	int					getLineWidth();	// no need to implement setter method yet
	int					getLineAngle();	// no need to implement setter method yet
	int					getSides();	// no need to implement setter method yet
	double				getAlpha();	// no need to implement setter method yet
	void				stopAvBridges();

	int					getStrokeDirectionType();
	AvBridge*			currentAvBridge;

	void setLineOptions(int extra);

private:
	ImpressionistDoc*	m_pDoc;		// pointer to document to communicate with the document

	// All attributes here
	int		m_nSize;
	int		m_nLineWidth;
	int		m_nLineAngle;
	int		m_nStrokeDirectionType;
	double	m_nAlpha;
	int		m_nSides;
	int		m_nAutoDrawSpacing;
	int     m_currentBrushIndex;

	// Static class members
	static Fl_Menu_Item		menuitems[];
	static Fl_Menu_Item		brushTypeMenu[NUM_BRUSH_TYPE+1];
	static Fl_Menu_Item		strokeDirectionTypeMenu[NUM_STROKE_DIRECTION_TYPE + 1];

	static ImpressionistUI*	whoami(Fl_Menu_* o);

	// All callbacks here.  Callbacks are declared 
	// static
	static void cb_window(Fl_Widget* o, void* v);
	static void	cb_load_image(Fl_Menu_* o, void* v);
	static void	cb_load_mural_image(Fl_Menu_* o, void* v);
	static void	cb_save_image(Fl_Menu_* o, void* v);
	static void	cb_brushes(Fl_Menu_* o, void* v);
	static void	cb_color_manip(Fl_Menu_* o, void* v);
	static void	cb_clear_canvas(Fl_Menu_* o, void* v);
	static void	cb_exit(Fl_Menu_* o, void* v);
	static void	cb_about(Fl_Menu_* o, void* v);
	static void	cb_brushChoice(Fl_Widget* o, void* v);
	static void cb_strokeDirectionChoice(Fl_Widget* o, void* v);
	static void	cb_clear_canvas_button(Fl_Widget* o, void* v);
	static void	cb_slides(Fl_Widget* o, void* v);
	static void	cb_autodraw(Fl_Widget* o, void* v);
	static void	cb_autodraw_video(Fl_Widget* o, void* v);
	static void	cb_updateColor(Fl_Widget* o, void* v);
	static void	cb_dissolve_dialog(Fl_Menu_* o, void* v);
	static void	cb_dissolve(Fl_Widget* o, void* v);
	static void	cb_convolution_dialog(Fl_Menu_* o, void* v);
	static void	cb_load_ext_gradient(Fl_Widget* o, void* v);

	// bonus
	static void	cb_undo(Fl_Menu_* o, void* v);
	static void	cb_swap(Fl_Menu_* o, void* v);
};

#endif
