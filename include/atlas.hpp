#ifndef ATLAS_HPP
#define ATLAS_HPP
#include "image.hpp"
#include "texturedquad.hpp"

// location and dimension of a texture
struct AtlasComponent {
	unsigned x, y; // origin (bottom left)
	unsigned width, height; //dimensions
};
unsigned bottom(AtlasComponent const & a);
unsigned top(AtlasComponent const & a);
unsigned left(AtlasComponent const & a);
unsigned right(AtlasComponent const & a);


class Atlas{
	unsigned maxDimension;
	Image atlas; // combined image

	std::vector<AtlasComponent> components;
public:
	Atlas(unsigned maxDimension);
	int add(const Image & img);

	bool getTexturedQuad(int index, TexturedQuad &) const;

	const Image & getImage() const;
};
#endif
