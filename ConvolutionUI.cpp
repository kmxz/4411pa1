////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

#include "ConvolutionUI.h"
#include <FL/fl_ask.H>

ConvolutionUI::ConvolutionUI() {
	sscanf(fl_input("Convolution matrix size?", "3"), "%d", &size);

	// color dialog definition
	window = new Fl_Window(max(size * 45 + 20, 200), size * 35 + 50, "Convolution matrix input");
		ok = new Fl_Button(10, 10, 80, 20, "Do now");
		ok->user_data((void*)(this));
		ok->callback(cb_draw);
		norm = new Fl_Light_Button(100, 10, 90, 20, "Normalize");

		inputs = new Fl_Float_Input**[size];
		for (int i = 0; i < size; i++) {
			inputs[i] = new Fl_Float_Input*[size];
			for (int j = 0; j < size; j++) {
				inputs[i][j] = new Fl_Float_Input(10 + 45 * i, 40 + 35 * j, 35, 25);
				inputs[i][j]->value("1");
			}
		}

	window->end();
	window->show();
}

void ConvolutionUI::cb_draw(Fl_Widget* o, void* v) {
	ConvolutionUI* self = ((ConvolutionUI*)(o->user_data()));
	float** values = new float*[self->size];
	float sum = 0;
	for (int i = 0; i < self->size; i++) {
		values[i] = new float[self->size];
		for (int j = 0; j < self->size; j++) {
			values[i][j] = 0; // in case of illegal inputs
			sscanf(self->inputs[i][j]->value(), "%f", &(values[i][j]));
			sum += values[i][j];
		}
	}
	if (self->norm->value()) {
		for (int i = 0; i < self->size; i++) {
			for (int j = 0; j < self->size; j++) {
				values[i][j] /= sum;
			}
		}
	}
	// caution: give in order ([column(X)][row(Y)])
}