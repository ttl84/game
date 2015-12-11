#include "image.hpp"

// T must be an array-like type.
// This function is a generalization of array reversal.
// Instead of swapping the first and last element, multiple elemnts are swapped
//  at one time.
// [span] is the number of elements to swap at one time.
// After running this function, dst should be the span-reversed version of src.
// example:
// src = [1 2 3 4 5 6 7 8 9 0]
// dst = []
// reverseSpan(src, dst, 2);
// dst = [9 0 7 8 5 6 3 4 1 2]
template<class T>
void reverseSpan(T const & src, T & dst, unsigned span)
{
	dst.clear();
	auto it = std::end(src) - span;
	while(it >= std::begin(src)) {
		auto dstEnd = std::end(dst);
		dst.insert(dstEnd, it, it+span);
		it = it - span;
	}
}

Image flipVertically(const Image & img)
{
	Image flipped;
	flipped.bytesPerPixel = img.bytesPerPixel;
	flipped.width = img.width;
	flipped.height = img.height;

	unsigned rowBytes = img.bytesPerPixel * img.width;
	reverseSpan(img.bytes, flipped.bytes, rowBytes);
	return flipped;
}

bool sameFormat(const Image & img1, const Image & img2)
{
	return img1.bytesPerPixel == img2.bytesPerPixel;
}

int blit(const Image & src, Image & dst, unsigned x, unsigned y)
{
	if(!src.isSane() || !dst.isSane() || !sameFormat(src, dst)) {
		return -1;
	}
	unsigned xEnd = x + src.width;
	unsigned yEnd = y + src.height;
	if(x > dst.width || y > dst.height ||
		xEnd> dst.width || yEnd > dst.height) {
		return -2;
	}

	for(unsigned i = 0; i < src.height; i++) {
		std::copy(src.ptr(i, 0, 0), src.ptr(i, src.width, 0),
			dst.ptr(y+i, x, 0));
	}
	return 0;
}

bool Image::isSane() const
{
	unsigned byteCount = width * height * bytesPerPixel;
	return byteCount != 0 && byteCount == bytes.size();
}

bool Image::isEmpty() const
{
	unsigned byteCount = width * height * bytesPerPixel;
	return byteCount == 0;
}

uint8_t * Image::ptr(unsigned row, unsigned column, unsigned byte)
{
	unsigned rowOffset = row * width * bytesPerPixel;
	unsigned columnOffset = column * bytesPerPixel;
	return bytes.data() + rowOffset + columnOffset + byte;
}
uint8_t const * Image::ptr(unsigned row, unsigned column, unsigned byte) const
{
	unsigned rowOffset = row * width * bytesPerPixel;
	unsigned columnOffset = column * bytesPerPixel;
	return bytes.data() + rowOffset + columnOffset + byte;
}
