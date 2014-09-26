////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

#include "ConvolutionUI.h"
#include <FL/fl_ask.H>

ConvolutionUI::ConvolutionUI(ImpressionistDoc* d) {
	doc = d;

	sscanf(fl_input("Kernel size?", "3"), "%d", &size);

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
	self->do_draw(values);
	for (int i = 0; i < self->size; i++) {
		delete[] values[i];
	}
	delete[] values;
}

void ConvolutionUI::do_draw(float** kernel) {
	int* index = new int[size];
	int* indey = new int[size];
	unsigned char* last = doc->m_ucLast;
	doc->m_ucLast = doc->m_ucPainting;
	doc->m_ucPainting = last;
	for (int pix = 0; pix < doc->m_nPaintWidth; pix++) {
		for (int pjy = 0; pjy < doc->m_nPaintHeight; pjy++) {
			// WONTFIX: if the brush size is larger than the canvas size, segfault will occur
			for (int i = 0; i < size; i++) {
				int iix = pix + i - size / 2;
				if (iix < 0 || iix > doc->m_nPaintWidth) { iix = pix + size / 2 - i; }
				index[i] = iix;
				int iiy = pjy + i - size / 2;
				if (iiy < 0 || iiy > doc->m_nPaintHeight) { iiy = pjy + size / 2 - i; }
				indey[i] = iiy;
			}
			double total[] = { 0, 0, 0 };
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					for (int c = 0; c < 3; c++) {
						total[c] += kernel[i][j] * doc->m_ucLast[(indey[j] * doc->m_nPaintWidth + index[i]) * 3 + c];
					}
				}
			}
			for (int c = 0; c < 3; c++) {
				last[(pjy * doc->m_nPaintWidth + pix) * 3 + c] = total[c];
			}
		}
	}
	doc->m_pUI->m_paintView->redraw();
}