#include "AvBridge.h"
#include <FL/filename.H>
#include <FL/fl_file_chooser.H>
#include <FL/fl_ask.H>
#include <windows.h> 
#include <tchar.h>
#include <stdio.h> 
#include <sstream>
#include <strsafe.h>
#include "impressionistDoc.h"
#include "impressionistUI.h"

bool AvBridge::find_file(char* wrkdir, char* needle, char* output) {
	dirent** list;
	bool success = false;
	int count = filename_list(wrkdir, &list);
	for (int i = 0; i < count; i++) {
		char fullname[1024];
		char* name = list[i]->d_name;
		strcpy(fullname, wrkdir);
		strcat(fullname, name);
		if (filename_isdir(fullname)) {
			if (strcmp(name, "..") != 0 && strcmp(name, ".") != 0) {
				strcat(fullname, "\\");
				if (find_file(fullname, needle, output)) {
					success = true; break;
				}
			}
		} else if (strcmp(name, needle) == 0) {
			strcpy(output, fullname);
			success = true; break;
		}
	}
	return success;
}

bool AvBridge::locate_ffmpeg() {
	if (find_file(".\\", "ffmpeg.exe", path)) {
		return true;
	}
	char* newfile = fl_file_chooser("Where is FFmpeg executable?", "*.*", "ffmpeg.exe");
	if (newfile == NULL) {
		return false;
	}
	strcpy(path, newfile);
	return true;
}

bool AvBridge::identify() {
	DWORD dwRead;
	char chBuf[1024];
	char lineBuf[1024] = "";
	char sectionBuf[1024];
	bool bSuccess = false;
	bool hit = false;

	int currentLinePassed; // -1 for failed. 0 for none printable chars met yet.
	char* matcher = "Stream"; // magic number

	while (true) {
		bSuccess = ReadFile(identifier->g_hChildStd_OUT_Rd, chBuf, 1024, &dwRead, NULL);
		if (!bSuccess || dwRead == 0) { break; }
		for (int i = 0; i < dwRead; i++) {
			if (chBuf[i] == '\r' || chBuf[i] == '\n') {
				currentLinePassed = 0;
				int len = strlen(lineBuf);
				if (len > 0) {
					// further analyze!
					if (strstr(lineBuf, "Video") != NULL) {
						if (hit) {
							die("More than one video tracks detected."); return false;
						}
						hit = true;
						bool subhit = false;
						bool fpshit = false;
						sectionBuf[0] = '\0';
						for (int j = 0; j < len; j++) {
							if (lineBuf[j] == ',') {
								if (strlen(sectionBuf) > 0) {
									int w = 0; int h = 0;
									sscanf(sectionBuf, "%dx%d", &w, &h);
									if (w > 0 && h > 0) {
										if (subhit) {
											die("More than one video dimensions detected."); return false;
										}
										width = w; height = h;
										subhit = true;
									}
									double f = 0;
									sscanf(sectionBuf, "%f fps", &f);
									if (f > 0) {
										if (fpshit) {
											die("More than one frame rates detected."); return false;
										}
										fps = f;
										fpshit = true;
									}
								}
								sectionBuf[0] = '\0';
							} else if (lineBuf[j] != ' ' && lineBuf[j] != '\t') {
								strncat(sectionBuf, lineBuf + j, 1);
							}
						}
						if (!subhit) { die("No video dimensions detected."); return false; }
						if (!fpshit) { die("No frame rates detected."); return false; }
					}
				}
				lineBuf[0] = '\0';
			} else if (currentLinePassed >= 0 && currentLinePassed <= 5 && matcher[currentLinePassed] == chBuf[i]) {
				currentLinePassed++;
				if (currentLinePassed == 6) {
					currentLinePassed = -2;
				}
			} else if (currentLinePassed == -2) {
				strncat(lineBuf, chBuf + i, 1);
			} else if (chBuf[i] != ' ' && chBuf[i] != '\t') {
				currentLinePassed = -1;
			}
		}
	}
	if (!hit) { die("No video tracks detected."); return false; }
	return true;
}

void AvBridge::readVideo() {
	DWORD dwRead;
	bool bSuccess = false;
	while (true) {
		bSuccess = ReadFile(reader->g_hChildStd_OUT_Rd, doc->m_ucBitmap, length, &dwRead, NULL);
		if (!bSuccess || dwRead == 0) { break; }
		doc->m_pUI->m_paintView->refresh();
		Sleep(1000 / fps);
	}
}

void AvBridge::die(const char* error) {
	printf("Fatal error: %s\n", error); // TODO: GUI Style!
}

void AvBridge::play() {
	AvProcess* identifier = new AvProcess(this);
	AvProcess* reader = new AvProcess(this);
	if (!locate_ffmpeg()) {
		die("No available FFmpeg binary in the system."); return;
	}
	char* vidFile = fl_file_chooser("Select your video file.", "*.*", "");
	if (vidFile == NULL) {
		die("No valid video file selected."); return;
	}
	std::stringstream command;
	command << path << " -i " << vidFile;
	if (!identifier->init(command.str().c_str())) { return; }
	CloseHandle(identifier->g_hChildStd_IN_Rd);
	CloseHandle(identifier->g_hChildStd_IN_Wr);
	CloseHandle(identifier->g_hChildStd_OUT_Wr);
	if (!identify()) { return; }
	length = width * height * 3;
	delete[] doc->m_ucBitmap;
	delete[] doc->m_ucPainting;
	delete[] doc->m_ucLast;
	doc->m_nWidth = width;
	doc->m_nPaintWidth = width;
	doc->m_nHeight = height;
	doc->m_nPaintHeight = height;
	doc->m_ucBitmap = new unsigned char[length];
	doc->m_ucPainting = new unsigned char[length];
	doc->m_pUI->resize_windows(width, height);
	command << " -f imagepipe" << " -pix_fmt rgb24" << " -vcodec rawvideo" << " -";
	reader->init(command.str().c_str());
	readVideo();
}

AvBridge::AvBridge(ImpressionistDoc* parent) {
	doc = parent;
}