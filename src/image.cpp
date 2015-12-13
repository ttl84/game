#include "image.hpp"
#include <algorithm>

Image::Image()
{

}
Image::Image(unsigned bytesPerPixel, unsigned width, unsigned height)
{
	this->bytesPerPixel = bytesPerPixel;
	this->width = width;
	this->height = height;
	bytes.resize(bytesPerPixel * width * height);
}

unsigned Image::getWidth() const
{
	return width;
}
unsigned Image::getHeight() const
{
	return height;
}
unsigned Image::getBytesPerPixel() const
{
	return bytesPerPixel;
}
int Image::copy(std::vector<uint8_t> const & data)
{
	if(data.size() == bytes.size()) {
		bytes = data;
		return 0;
	} else {
		return -1;
	}
}

void Image::copy(const Image & img)
{
	bytesPerPixel = img.bytesPerPixel;
	width = img.width;
	height = img.height;
	bytes = img.bytes;
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

void flipVertically(Image & img)
{
	if(img.getHeight() < 1) {
		return;
	}

	unsigned i = 0;
	unsigned j = img.getHeight() - 1;
	while(i < j) {
		std::swap_ranges(img.ptr(i, 0, 0), img.ptr(i+1, 0, 0),
			img.ptr(j, 0, 0));
		i++;
		j--;
	}
}

int blit(const Image & src, Image & dst, unsigned x, unsigned y)
{
	if(isNull(src) || isNull(dst) || !sameFormat(src, dst)) {
		return -1;
	}
	unsigned xEnd = x + src.getWidth();
	unsigned yEnd = y + src.getHeight();
	if(x > dst.getWidth() || y > dst.getHeight() ||
		xEnd> dst.getWidth() || yEnd > dst.getHeight()) {
		return -2;
	}

	for(unsigned i = 0; i < src.getHeight(); i++) {
		std::copy(src.ptr(i, 0, 0), src.ptr(i+1, 0, 0),
			dst.ptr(y+i, x, 0));
	}
	return 0;
}

bool sameFormat(const Image & img1, const Image & img2)
{
	return img1.getBytesPerPixel() == img2.getBytesPerPixel();
}

unsigned getByteCount(const Image & img)
{
	unsigned byteCount = img.getWidth() * img.getHeight() * img.getBytesPerPixel();
	return byteCount;
}

bool isNull(const Image & img)
{
	return getByteCount(img) == 0;
}
