#include "avbridge.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include <Windows.h>
#include <time.h> 

AvBridge::AvBridge(ImpressionistDoc* pDoc) {
	doc = pDoc;
	stopped = false;
}

AvBridge::AVBRIDGE_ERROR AvBridge::ffOpen(const char* file) {
	av_register_all();
	pFormatCtx = avformat_alloc_context();
	AVCodec *pCodec;
	if (avformat_open_input(&pFormatCtx, file, NULL, NULL) != 0){
		return AVBRIDGEERR_FILE_NOT_FOUND;
	}
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
		return AVBRIDGEERR_STREAM_NOT_FOUND;
	}
	videoIndex = -1;
	for (int i = 0; i < pFormatCtx->nb_streams; i++) {
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
			videoIndex = i;
			break;
		}
	}
	if (videoIndex == -1) { return AVBRIDGEERR_VIDEO_STREAM_NOT_FOUND; }
	pCodecCtx = pFormatCtx->streams[videoIndex]->codec;
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL) {
		return AVBRIDGEERR_CODEC_NOT_FOUND;
	}
	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0){
		return AVBRIDGEERR_DECODER_NOT_FOUND;
	}
	reDoc(pCodecCtx->width, pCodecCtx->height);
	pFrame = avcodec_alloc_frame();
	pFrameRGB = avcodec_alloc_frame();
	int numBytes = avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
	out_buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));
	avpicture_fill((AVPicture *)pFrameRGB, out_buffer, PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
	packet = (AVPacket *)av_malloc(sizeof(AVPacket));
	img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL); // no actual resize involved
	return AVBRIDGE_NO_ERROR;
}

void AvBridge::stop() {
	stopped = true;
}

void AvBridge::reDoc(int width, int height) {
	int length = width * height * 3;
	delete[] doc->m_ucBitmap;
	delete[] doc->m_ucPainting;
	delete[] doc->m_ucLast;
	doc->m_nWidth = width;
	doc->m_nPaintWidth = width;
	doc->m_nHeight = height;
	doc->m_nPaintHeight = height;
	doc->m_ucBitmap = new unsigned char[length];
	memset(doc->m_ucBitmap, 0, length);
	doc->m_ucPainting = new unsigned char[length];
	memset(doc->m_ucPainting, 0, length);
	doc->m_ucLast = new unsigned char[length];
	memset(doc->m_ucLast, 0, length);
	doc->m_pUI->resize_windows(width, height);
}

AvBridge::~AvBridge() {
	av_free(out_buffer);
	av_free(pFrameRGB);
	av_free(pFrame);
	sws_freeContext(img_convert_ctx);
	avcodec_close(pCodecCtx);
	avformat_close_input(&pFormatCtx);
}

AvBridge::AVBRIDGE_ERROR AvBridge::readFrame() {
	int height = pCodecCtx->height;
	int64_t last_pts = 0;
	clock_t tLast, tCurrent;
	tLast = clock();
	while (true) {
		if (stopped) {
			return AVBRIDGE_NO_ERROR; // manually stopped
		}
		int ret, got_picture;
		if (av_read_frame(pFormatCtx, packet) < 0){
			break;
		}
		if (packet->stream_index == videoIndex){
			ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
			if (ret < 0){
				return AVBRIDGEERR_DECODER_ERROR;
			}
			if (got_picture) {
				sws_scale(img_convert_ctx, pFrame->data, pFrame->linesize, 0, height, pFrameRGB->data, pFrameRGB->linesize);
				int lineSize = pFrameRGB->linesize[0];
				for (int i = 0; i < height; i++) {
					memcpy(doc->m_ucBitmap + (height - 1 - i) * (lineSize), out_buffer + i * lineSize, lineSize);
				}
				tCurrent = clock();
				double secondsIdeal = (packet->pts - last_pts) * pCodecCtx->time_base.num / (double)pCodecCtx->time_base.den;
				double secondsToWait = secondsIdeal - (tCurrent - tLast) / (double) CLOCKS_PER_SEC;
				if (secondsToWait > 0) {
					Sleep(secondsToWait * 1000);
				}
				last_pts = packet->pts;
				tLast = tCurrent;
				doc->m_pUI->m_origView->refresh();
				doc->m_pUI->m_paintView->RestoreContent();
				doc->m_pUI->m_paintView->singleAutoDraw();
				Fl::check();
			}
		}
		av_free_packet(packet);
	}
	return AVBRIDGE_NO_ERROR;
}
