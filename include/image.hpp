#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <vector>
#include <cstdint>
class Image{
	unsigned bytesPerPixel, width, height;
	std::vector<uint8_t> bytes;
public:
	// Create a null image. It has no dimensions and no data.
	Image();

	// Create an empty Image with the dimensions.
	Image(unsigned bytesPerPixel, unsigned width, unsigned height);

	// Get dimensions
	unsigned getWidth() const;
	unsigned getHeight() const;
	unsigned getBytesPerPixel() const;

	// Get the pointer to a specific byte
	uint8_t * ptr(unsigned row, unsigned column, unsigned byte);
	uint8_t const * ptr(unsigned row, unsigned column, unsigned byte) const;

	// Copies data into the image. Vector length must match.
	// Returns zero for success, non zero otherwise.
	int copy(std::vector<uint8_t> const &);

	void copy(const Image & img);
};

bool sameFormat(const Image & img1, const Image & img2);

unsigned getByteCount(const Image & img);
bool isNull(const Image & img);

// Flip the image vertically, so that the last row becomes the first and the
// first becomes the last.
void flipVertically(Image & img);

// perform of blit of src into dst. The whole of src will be blitted at location
// (x, y).
// Returns 0 for success, non zeros otherwise.
int blit(const Image & src, Image & dst, unsigned x, unsigned y);
#endif
