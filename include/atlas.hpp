#ifndef ATLAS_HPP
#define ATLAS_HPP
#include "image.hpp"

// location and dimension of a texture
struct AtlasComponent {
	unsigned x, y; // origin (bottom left)
	unsigned width, height; //dimensions
};

class Atlas{
	unsigned maxDimension;
	Image atlas; // combined image

	std::vector<AtlasComponent> components;
public:
	Atlas(unsigned maxDimension);
	int add(const Image & img);

	bool getComponent(int index, AtlasComponent &) const;
};
#endif
