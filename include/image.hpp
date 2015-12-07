#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <vector>
#include <cstdint>
class Image{
public:
	unsigned width, height, bytesPerPixel;
	std::vector<uint8_t> bytes;

	// returns true if the image has an area of 0.
	bool isEmpty() const;

	// returns true if the image has a non zero area and the byte coutn matches
	// the size of the "bytes" array.
	bool isSane() const;
};

Image flipVertically(const Image & img);


#endif
