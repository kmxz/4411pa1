#include <string>

class AvBridge {
private:
	bool find_file(char* wrkdir, char* needle, char* output);
	char path[1024];
public:
	bool locate_ffmpeg();
};