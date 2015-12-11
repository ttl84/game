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

	uint8_t * ptr(unsigned row, unsigned column, unsigned byte);
	uint8_t const * ptr(unsigned row, unsigned column, unsigned byte) const;
};

bool sameFormat(const Image & img1, const Image & img2);

Image flipVertically(const Image & img);

// perform of blit of src into dst. The whole of src will be blitted at location
// (x, y).
// Returns 0 for success, non zeros otherwise.
int blit(const Image & src, Image & dst, unsigned x, unsigned y);
#endif
