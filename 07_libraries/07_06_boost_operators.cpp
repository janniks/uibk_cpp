#include <string>
#include <iostream>
#include <cmath>

#include <boost/operators.hpp>

template<typename T>
class Vec2D    // note: private inheritance is OK here!
	: boost::addable< Vec2D<T>           // point + point
	, boost::subtractable< Vec2D<T>      // point - point
	, boost::dividable2< Vec2D<T>, T     // point / T
	, boost::multipliable2< Vec2D<T>, T  // point * T, T * point
	> > > > // note: base class chaining technique
{
	T x_;
	T y_;

public:
	Vec2D(T x, T y) : x_(x), y_(y) {
	}
	T x() const {
		return x_;
	}
	T y() const {
		return y_;
	}

	Vec2D operator+=(const Vec2D& other) {
		x_ += other.x_;
		y_ += other.y_;
		return *this;
	}
	// point operator+(point, const point&) automatically
	// generated by addable.

	Vec2D operator-=(const Vec2D& other) {
		x_ -= other.x_;
		y_ -= other.y_;
		return *this;
	}
	// point operator-(point, const point&) automatically
	// generated by subtractable.

	Vec2D operator*=(T other) {
		x_ *= other;
		y_ *= other;
		return *this;
	}
	// point operator*(point, const T&) and
	// point operator*(const T&, point) auto-generated
	// by multipliable.

	Vec2D operator/=(T other) {
		x_ /= other;
		y_ /= other;
		return *this;
	}
	// point operator/(point, const T&) auto-generated
	// by dividable.
};

/// Base class chaining result:
///            chained                              unchained
///            binary ; sizeof(Vec2D<float>)        binary ; sizeof(Vec2D<float>)
/// VS2017.5      10752       8                     10752         12
/// GCC4.8.5       8992       8                      8984          8
/// Clang3.5          -       8                         -          8
/// ICC13             -       8                         -          8

// now use the Vec2D<T> class:

template<typename T>
T length(const Vec2D<T> p) {
	return sqrt(p.x()*p.x() + p.y()*p.y());
}

int main() {
	const Vec2D<float> right(0, 1);
	const Vec2D<float> up(1, 0);
	const Vec2D<float> pi_over_4 = up + right;
	const Vec2D<float> pi_over_4_normalized = pi_over_4 / length(pi_over_4);

	std::cout << sizeof(Vec2D<float>) << std::endl;
}