////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

#ifndef AVBRIDGE_H
#define AVBRIDGE_H

//** begin of ffmpeg/libav import **// 

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>  
}

# pragma comment (lib, "avformat.lib")
# pragma comment (lib, "avutil.lib")
# pragma comment (lib, "avcodec.lib")
# pragma comment (lib, "swscale.lib")

//** end of ffmpeg/libav import **// 

#include "impressionistDoc.h"

class AvBridge {
public:
	enum AVBRIDGE_ERROR {
		AVBRIDGE_NO_ERROR,
		AVBRIDGEERR_FILE_NOT_FOUND,
		AVBRIDGEERR_STREAM_NOT_FOUND,
		AVBRIDGEERR_VIDEO_STREAM_NOT_FOUND,
		AVBRIDGEERR_CODEC_NOT_FOUND,
		AVBRIDGEERR_DECODER_NOT_FOUND,
		AVBRIDGEERR_DECODER_ERROR,
	};
	AVBRIDGE_ERROR ffOpen(const char* file); // actual constructor
	AVBRIDGE_ERROR readFrame();
	AvBridge(ImpressionistDoc* pDoc);
	~AvBridge();
	void stop();
private:
	ImpressionistDoc* doc;
	AVFormatContext *pFormatCtx;
	AVCodecContext *pCodecCtx;
	AVFrame *pFrame;
	AVFrame *pFrameRGB;
	uint8_t *out_buffer;
	AVPacket *packet;
	int videoIndex;
	struct SwsContext *img_convert_ctx;
	void reDoc(int width, int height);
	bool stopped;
};

#endif