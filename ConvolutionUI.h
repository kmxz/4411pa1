////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <Fl/Fl_Float_Input.H>
#include "impressionistDoc.h"

class ConvolutionUI {
public:
	ConvolutionUI();
	static void cb_draw(Fl_Widget* o, void* v);
private:
	ImpressionistDoc* doc;
	Fl_Window* window;
	Fl_Button* ok;
	Fl_Light_Button* norm;
	Fl_Float_Input*** inputs;
	int size;
};