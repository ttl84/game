#include "image.hpp"
Image flipVertically(const Image & img)
{
	Image flipped;
	flipped.bytesPerPixel = img.bytesPerPixel;
	flipped.width = img.width;
	flipped.height = img.height;

	unsigned rowBytes = img.bytesPerPixel * img.width;
	auto it = img.bytes.end() - rowBytes;
	while(it >= img.bytes.begin()) {
		flipped.bytes.insert(flipped.bytes.end(), it, it+rowBytes);
		it = it - rowBytes;
	}
	return flipped;
}
