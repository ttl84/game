#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <vector>
#include <cstdint>
class Image{
public:
	unsigned width, height, bytesPerPixel;
	std::vector<uint8_t> bytes;
};
#endif
