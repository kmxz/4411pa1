#ifndef AVBRIDGE_H
#define AVBRIDGE_H

#include "AvProcess.h"
#include "impressionistDoc.h"

class AvBridge {
public:
	AvBridge(ImpressionistDoc* parent);
	void play();
	void die(const char* error);
private:
	char path[1024];
	bool locate_ffmpeg();
	bool find_file(char* wrkdir, char* needle, char* output);
	bool identify();

	void readVideo();

	int length;
	int width;
	int height;
	double fps;

	AvProcess* identifier;
	AvProcess* reader;
	ImpressionistDoc* doc;
};

#endif