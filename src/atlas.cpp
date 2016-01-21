#include "atlas.hpp"
Atlas::Atlas(unsigned maxDimension)
{
	this->maxDimension = maxDimension;
}

int Atlas::add(const Image & img)
{
	if(isNull(img)) {
		return -1;
	}

	if(!sameFormat(img, atlas)) {
		return -2;
	}

	// The new image added to the atlas must not exceed the width limit.
	// This is because the atlas only stacks images vertically.
	if(img.getWidth() > maxDimension) {
		return -3;
	}

	// The new image added to the atlas can not cause the atlas to exceed the height limit.
	if(img.getHeight() + atlas.getHeight() > maxDimension) {
		return -3;
	}

	unsigned newWidth = atlas.getWidth();
	if(img.getWidth() > atlas.getWidth()) {
		newWidth = img.getWidth();
	}

	unsigned newHeight = atlas.getHeight() + img.getHeight();

	Image newAtlas(atlas.getBytesPerPixel(), newWidth, newHeight);

	blit(atlas, newAtlas, 0, 0);
	blit(img, newAtlas, 0, atlas.getHeight());
	std::swap(atlas, newAtlas);

	AtlasComponent comp;
	comp.x = 0;
	comp.y = atlas.getHeight();
	comp.width = img.getWidth();
	comp.height = img.getHeight();
	components.push_back(comp);

	return components.size() - 1;
}

bool Atlas::getComponent(int index, AtlasComponent & dst) const
{
	if(index >= 0 && (unsigned)index < components.size()) {
		dst = components[index];
		return true;
	} else {
		return false;
	}
}

const Image & Atlas::getImage() const
{
	return atlas;
}

unsigned bottom(AtlasComponent const & a)
{
	return a.y;
}
unsigned top(AtlasComponent const & a)
{
	return a.y + a.height;
}
unsigned left(AtlasComponent const & a)
{
	return a.x;
}
unsigned right(AtlasComponent const & a)
{
	return a.x + a.width;
}
