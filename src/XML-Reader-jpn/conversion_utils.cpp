/*
Codepoint conversion functions copied from
http://www.zedwood.com/article/cpp-utf8-char-to-codepoint
*/

#include "conversion_utils.h"

using namespace::std;

int toCodepoint(const string &u) {
	int l = u.length();
	if (l<1) return -1; 
	unsigned char u0 = u[0]; 
	if (u0 >= 0 && u0 <= 127) return u0;
	if (l<2) return -1; 
	unsigned char u1 = u[1]; 
	if (u0 >= 192 && u0 <= 223) return (u0 - 192) * 64 + (u1 - 128);
	if (u[0] == 0xed && (u[1] & 0xa0) == 0xa0) return -1; //code points, 0xd800 to 0xdfff
	if (l<3) return -1; 
	unsigned char u2 = u[2]; 
	if (u0 >= 224 && u0 <= 239) return (u0 - 224) * 4096 + (u1 - 128) * 64 + (u2 - 128);
	if (l<4) return -1; 
	unsigned char u3 = u[3]; 
	if (u0 >= 240 && u0 <= 247) return (u0 - 240) * 262144 + (u1 - 128) * 4096 + (u2 - 128) * 64 + (u3 - 128);
	
	return -1;
}

string toCodepointHex(const string &u) {
	stringstream ss;
	string s;
	ss << showbase << hex << toCodepoint(u);
	ss >> s;
	return s;
}

int hexToInt(const string &hexString) {
	int result;
	stringstream ss;	
	ss << hexString;
	ss >> std::hex >> result;
	return result;
}