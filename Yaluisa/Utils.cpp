#include <string>
#include <sstream>

using namespace std;

class Utils {
public:
	static float* ParseColor(string hexColor) {
		if (hexColor.empty())
			return NULL;
		if (hexColor.at(0) == '#')
			hexColor = hexColor.substr(1);
		if (hexColor.size() == 3) {
			string newStr = "";
			for (int i = 0; i < 3; i++)
				newStr += string(2, hexColor.at(i));
			hexColor = newStr;
		}
		float color[3];
		for (int i = 0; i < 6; i += 2) {
			string band = hexColor.substr(i, 2);
			stringstream ss;
			int bandInt;
			ss << hex << band;
			ss >> bandInt;
			color[i / 2] = bandInt / 255.0f;
		}
		return color;
	}
};