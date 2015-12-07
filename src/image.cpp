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
