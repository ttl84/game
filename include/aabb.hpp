#ifndef AABB_HPP
#define AABB_HPP
namespace aabb{
template<class T>
struct Range{
	T low, high;
};

template <class T>
bool contains(const Range<T> & r, T v)
{
	return r.low < v && r.high > v;
}

template <class T>
bool intersect(const Range<T> & a, const Range<T> & b)
{
	return contains(a, b.low) || contains(a, b.high);
}

template <class T, unsigned D>
struct AABB {
	typedef Range<T> RangeT;
	RangeT ranges[D];
};

template <class T, unsigned D>
bool intersect(const AABB<T, D> & a, const AABB<T, D> & b)
{
	bool result = true;
	for(unsigned i = 0; i < D; i++) {
		result = result && intersect(a.ranges[i], b.ranges[i]);
	}
	return result;
}

} // end namespace aabb
#endif
