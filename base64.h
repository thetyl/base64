// MIT License
// 
// Copyright(c) 2023 Tyl
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software andassociated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, andto permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright notice andthis permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <unordered_map>
#include <string>
#include <sstream>

const std::unordered_map<uint32_t, char> BASE64_TABLE = {
	{0, 'A'},
	{1, 'B'},
	{2, 'C'},
	{3, 'D'},
	{4, 'E'},
	{5, 'F'},
	{6, 'G'},
	{7, 'H'},
	{8, 'I'},
	{9, 'J'},
	{10, 'K'},
	{11, 'L'},
	{12, 'M'},
	{13, 'N'},
	{14, 'O'},
	{15, 'P'},
	{16, 'Q'},
	{17, 'R'},
	{18, 'S'},
	{19, 'T'},
	{20, 'U'},
	{21, 'V'},
	{22, 'W'},
	{23, 'X'},
	{24, 'Y'},
	{25, 'Z'},
	{26, 'a'},
	{27, 'b'},
	{28, 'c'},
	{29, 'd'},
	{30, 'e'},
	{31, 'f'},
	{32, 'g'},
	{33, 'h'},
	{34, 'i'},
	{35, 'j'},
	{36, 'k'},
	{37, 'l'},
	{38, 'm'},
	{39, 'n'},
	{40, 'o'},
	{41, 'p'},
	{42, 'q'},
	{43, 'r'},
	{44, 's'},
	{45, 't'},
	{46, 'u'},
	{47, 'v'},
	{48, 'w'},
	{49, 'x'},
	{50, 'y'},
	{51, 'z'},
	{52, '0'},
	{53, '1'},
	{54, '2'},
	{55, '3'},
	{56, '4'},
	{57, '5'},
	{58, '6'},
	{59, '7'},
	{60, '8'},
	{61, '9'},
	{62, '+'},
	{63, '/'}
};

std::string base64_encode(const char *data, size_t num_bytes) {
	uint32_t value;
	uint32_t buffer = 0;
	int buffer_index = 7;

	std::string encoding;

	for (int i = 0; i < num_bytes; ++i) {
		buffer |= data[i];

		encoding += BASE64_TABLE.find(buffer >> (buffer_index - 5))->second;

		if (buffer_index == 7) {
			buffer = (buffer & 0x3) << 8;
			buffer_index += 2;
		} else if (buffer_index == 9) {
			buffer = (buffer & 0xf) << 8;
			buffer_index += 2;
		} else {
			encoding += BASE64_TABLE.find(buffer & 0x3f)->second;
			buffer = 0;
			buffer_index = 7;
		}
	}

	if (buffer_index != 7) {
		encoding += BASE64_TABLE.find(buffer >> (buffer_index - 5))->second;
		encoding += (buffer_index == 9) ? "==" : "=";
	}

	return encoding;
}

std::string base64_encode_hex(const std::string &hex_data) {
	std::stringstream ss;
	uint32_t value;
	uint32_t buffer = 0;
	int buffer_index = 7;

	std::string encoding;

	for (int i = 0; i < hex_data.size(); i += 2) {
		ss << std::hex << hex_data.substr(i, 2);
		ss >> value;
		ss.clear();

		buffer |= value;

		encoding += BASE64_TABLE.find(buffer >> (buffer_index - 5))->second;

		if (buffer_index == 7) {
			buffer = (buffer & 0x3) << 8;
			buffer_index += 2;
		} else if (buffer_index == 9) {
			buffer = (buffer & 0xf) << 8;
			buffer_index += 2;
		} else {
			encoding += BASE64_TABLE.find(buffer & 0x3f)->second;
			buffer = 0;
			buffer_index = 7;
		}
	}

	if (buffer_index != 7) {
		encoding += BASE64_TABLE.find(buffer >> (buffer_index - 5))->second;
		encoding += (buffer_index == 9) ? "==" : "=";
	}

	return encoding;
}
