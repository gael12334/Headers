#include <math.h>
#include <type_traits>

enum AngleUnit {
	RADIAN = 0,
	DEGREE = 1
};

/// \brief Structure containing 2 real numbers (x and y) represented as a coordinate and/or a vector.
template <class T> struct XyCoord {
	static_assert(std::numeric_limits<T>::is_bounded, "Only an numerical type can be used inside this structure.");
	T x, y; 
	
	XyCoord(T x, T y) {
		this->x = x;
		this->y = y;
	}
	XyCoord() {
		this->x = 0;
		this->y = 0;
	}
	
	/// \brief Calculates the norm of this vector
	/// \param Ti "Ti" is a numerical 
	template <class Ti> virtual inline Ti Norm() {
		static_assert(std::numeric_limits<T>::is_bounded, "Only an numerical type can be used inside this method.")
		return (Ti)sqrt(pow(x, 2) + pow(y, 2));
	}

	template <class Ti> virtual inline Ti DotProduct(XyCoord<T> xy) {
        	static_assert(std::numeric_limits<T>::is_bounded, "Only an numerical type can be used inside this method.");
        	return (x * xy.x) + (y * xy.y);
    	}

	template <class Ti, AngleUnit au> virtual inline Ti GetAngleBetween(XyCoord<T> xy) {
        	static_assert(std::numeric_limits<T>::is_bounded, "Only an numerical type can be used inside this method.");
		if(au) 
			return (Ti)(acos(DotProduct<Ti>(xy) / (Norm<Ti>() * xy.Norm<Ti>())) * 180) / 3.14159265359;
        	return (Ti)acos(DotProduct<Ti>(xy) / (Norm<Ti>() * xy.Norm<Ti>()));
	}
	
	inline virtual XyCoord<T>& Normalise() {
		x = y = (T)1;
		return this;
	}
	
	virtual XyCoord<T>& operator+=(XyCoord<T> xy) {
		x += xy.x;
		y += xy.y;
		return this;
	}
	
	virtual XyCoord<T>& operator-=(XyCoord<T> xy) {
		x -= xy.x;
		y -= xy.y;
		return this;
	}
	
	template <class Ti> virtual XyCoord<T>& operator*=(Ti integer_v) {
		static_assert(std::numeric_limits<T>::is_bounded, "Only an numerical type can be used inside this method.");
		x *= integer_v;
		y *= integer_v;
        	return this;
	}

	template <class Ti> virtual XyCoord<T>& operator/=(Ti integer_v) {
		static_assert(std::numeric_limits<T>::is_bounded, "Only an numerical type can be used inside this method.");
		x /= integer_v;
		y /= integer_v;
		return this;
	}

    	inline virtual XyCoord<T> operator+(XyCoord<T> xy) {
     	   	return XyCoord<T>(xy.x + x, xy.y + y);
    	}

    	inline virtual XyCoord<T> operator-(XyCoord<T> xy) {
    		return XyCoord<T>(xy.x - x, xy.y - y);
    	}

    	inline virtual XyCoord<T> operator*(XyCoord<T> xy) {
        	return DotProduct(xy);
    	}

    	template <class Ti> virtual XyCoord<T>& operator* (Ti integer_v) {
		static_assert(std::numeric_limits<T>::is_bounded, "Only an numerical type can be used inside this method.");
        	return XyCoord<T>(x * integer_v, y * integer_v);;
	}
};
template <class T> using XySize = XyCoord<T>;
template <class T> using Vector2D = XyCoord<T>;

template <class T> struct XyzCoord : public XyCoord<T> {
	static_assert(std::numeric_limits<T>::is_bounded, "Only an numerical type can be used inside this structure.");

    	T z;
	XyzCoord(T x, T y, T z) : XyCoord(x, y) {
        	this->z = z;
	}

   	XyzCoord() : XyCoord(0, 0) {
        	this->z = 0;
    	}
	
	template <class Ti> inline Ti Norm() {
		static_assert(std::numeric_limits<T>::is_bounded, "Only a numerical type can be used inside this method.")
		return (Ti)sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}

    	template <class Ti> inline Ti DotProduct(XyzCoord<T> xyz) {
        	static_assert(std::numeric_limits<T>::is_bounded, "Only an numerical type can be used inside this method.");
        	return (x * xyz.x) + (y * xyz.y) + (z * xyz.z);
    	}	

    	inline XyzCoord<T> CrossProduct(XyzCoord<T> xyz) {
        	return XyzCoord<T>(y * xyz.z - z * xyz.y, z * xyz.x - x * xyz.z, x * xyz.y - y * xyz.x);
    	}

    	template <class Ti, AngleUnit au> inline Ti GetAngleBetween(XyzCoord<T> xyz) {
        	static_assert(std::numeric_limits<T>::is_bounded, "Only an integer type can be used inside this method.");
		if(au) 
			return (Ti)(acos(DotProduct<Ti>(xyz) / (Norm<Ti>() * xyz.Norm<Ti>())) * 180) / 3.14159265359;
        	return (Ti)acos(DotProduct<Ti>(xyz) / (Norm<Ti>() * xyz.Norm<Ti>()));
	}
	
	inline XyzCoord<T>& Normalise() {
		x = y = z = (T)1;
		return this;
	}
	
	XyzCoord<T>& operator+=(XyzCoord<T> xyz) {
		x += xyz.x;
		y += xyz.y;
        	z += xyz.z;
		return this;
	}
	
    	XyzCoord<T>& operator-=(XyzCoord<T> xyz) {
		x -= xyz.x;
		y -= xyz.y;
        	z -= xyz.z;
		return this;
	}
	
	template <class Ti> inline XyzCoord<T>& operator*=(Ti integer_v) {
		static_assert(std::numeric_limits<T>::is_bounded, "Only an numerical type can be used inside this method.");
        	x *= integer_v;
        	y *= integer_v;
        	z *= integer_v;
        	return this;
	}

   	template <class Ti> inline XyzCoord<T>& operator/=(Ti integer_v) {
		static_assert(std::numeric_limits<T>::is_bounded, "Only an numerical type can be used inside this method.");
        	x /= integer_v;
        	y /= integer_v;
        	z /= integer_v;
        	return this;
	}

    	inline XyzCoord<T> operator+(XyzCoord<T> xyz) {
        	return XyzCoord<T>(xyz.x + x, xyz.y + y, xyz.z + z);
    	}

    	inline XyzCoord<T> operator-(XyzCoord<T> xyz) {
        	return XyzCoord<T>(xyz.x - x, xyz.y - y, xyz.z - z);
    	}

    	inline XyzCoord<T> operator*(XyzCoord<T> xyz) {
        	return DotProduct(xyz);
    	}

    	template <class Ti> inline XyzCoord<T>& operator* (Ti integer_v) {
		static_assert(std::numeric_limits<T>::is_bounded, "Only an numerical type can be used inside this method.");
        	return XyzCoord<T>(x * integer_v, y * integer_v, z * integer_v);
	}
};
template <class T> using XyzSize = XyzCoord<T>;
template <class T> using Vector3D = XyzCoord<T>;


// Exemple of implementation:

void Test() {
	Vector2D<float> vector1 = Vector2D<float>(23.4F, 12.5F);
	Vector2D<float> vector2 = Vector2D<float>(1.4F, 52.2F);
	float vectorNorm = vector1.Norm<float>();
	int vectorAngle = vector1.GetAngleBetween<int, DEGREE>(vector2);
	//etc...
	
	Vector2D<
}



