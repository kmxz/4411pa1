#include "AvBridge.h"
#include <FL/filename.H>
#include <FL/fl_file_chooser.H>
#include <FL/fl_ask.H>

bool AvBridge::find_file(char* wrkdir, char* needle, char* output)
{
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