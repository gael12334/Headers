
#include <math.h>
#include <type_traits>

template <class T> struct XyCoord 
{
	static_assert(std::numeric_limits<T>::is_bounded, "Only an integer type can be used inside this structure.");

    T x, y;
	XyCoord(T x, T y) 
	{
		this->x = x;
		this->y = y;
	}
	
	template <class Ti> virtual inline Ti Norm() 
	{
		static_assert(std::numeric_limits<T>::is_bounded, "Only an integer type can be used inside this method.")
		return (Ti)sqrt(pow(x, 2) + pow(y, 2));
	}
	
	template <class Ti> virtual inline Ti DotProduct(XyCoord<T> xy) 
	{
        static_assert(std::numeric_limits<T>::is_bounded, "Only an integer type can be used inside this method.");
       	return (x * xy.x) + (y * xy.y);
    }

    template <class Ti> virtual inline Ti GetAngleBetween(XyCoord<T> xy) {
        static_assert(std::numeric_limits<T>::is_bounded, "Only an integer type can be used inside this method.");
        return acos(DotProduct<Ti>(xy) / (Norm<Ti>() * xy.Norm<Ti>()));
    }
	
	virtual XyCoord<T>& operator+=(XyCoord<T> xy) 
	{
		x += xy.x;
		y += xy.y;
		return this;
	}
	
	virtual XyCoord<T>& operator-=(XyCoord<T> xy) 
	{
		x -= xy.x;
		y -= xy.y;
		return this;
	}
	
	template <class Ti> virtual XyCoord<T>& operator*=(Ti integer_v) 
	{
		static_assert(std::numeric_limits<T>::is_bounded, "Only an integer type can be used inside this method.");
        x *= integer_v;
        y *= integer_v;
        return this;
	}

    template <class Ti> virtual XyCoord<T>& operator/=(Ti integer_v) 
	{
		static_assert(std::numeric_limits<T>::is_bounded, "Only an integer type can be used inside this method.");
        	x /= integer_v;
        	y /= integer_v;
        	return this;
	}

    	inline virtual XyCoord<T> operator+(XyCoord<T> xy)
    {
        return XyCoord<T>(xy.x + x, xy.y + y);
    }

    inline virtual XyCoord<T> operator-(XyCoord<T> xy)
    {
        return XyCoord<T>(xy.x - x, xy.y - y); 
    }

    inline virtual XyCoord<T> operator*(XyCoord<T> xy)
    {
        return DotProduct(xy);
    }

    template <class Ti> virtual XyCoord<T>& operator* (Ti integer_v) {
		static_assert(std::numeric_limits<T>::is_bounded, "Only an integer type can be used inside this method.");
        return XyCoord<T>(x * integer_v, y * integer_v);;
	}
};
template <class T> using XySize = XyCoord<T>;
template <class T> using Vector2D = XyCoord<T>;

template <class T> struct XyzCoord : public XyCoord<T> {
	static_assert(std::numeric_limits<T>::is_bounded, "Only an integer type can be used inside this structure.");

    T z;
	XyzCoord(T x, T y, T z) : XyCoord(x, y) {
        this->z = z;
	}

    XyzCoord() : XyCoord(0, 0) {
        this->z = 0;
    }
	
	template <class Ti> inline Ti Norm() {
		static_assert(std::numeric_limits<T>::is_bounded, "Only an integer type can be used inside this method.")
		return (Ti)sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}

    template <class Ti> inline Ti DotProduct(XyzCoord<T> xyz) {
        static_assert(std::numeric_limits<T>::is_bounded, "Only an integer type can be used inside this method.");
        return (x * xyz.x) + (y * xyz.y) + (z * xyz.z);
    }

    inline XyzCoord<T> CrossProduct(XyzCoord<T> xyz) {
        return XyzCoord<T>(y * xyz.z - z * xyz.y, z * xyz.x - x * xyz.z, x * xyz.y - y * xyz.x);
    }

    template <class Ti> inline Ti GetAngleBetween(XyzCoord<T> xyz) {
        static_assert(std::numeric_limits<T>::is_bounded, "Only an integer type can be used inside this method.");
        return acos(DotProduct<Ti>(xyz) / (Norm<Ti>() * xyz.Norm<Ti>()));
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
		static_assert(std::numeric_limits<T>::is_bounded, "Only an integer type can be used inside this method.");
        x *= integer_v;
        y *= integer_v;
        z *= integer_v;
        return this;
	}

    template <class Ti> inline XyzCoord<T>& operator/=(Ti integer_v) {
		static_assert(std::numeric_limits<T>::is_bounded, "Only an integer type can be used inside this method.");
        x /= integer_v;
        y /= integer_v;
        z /= integer_v;
        return this;
	}

    inline XyzCoord<T> operator+(XyzCoord<T> xyz)
    {
        return XyzCoord<T>(xyz.x + x, xyz.y + y, xyz.z + z);
    }

    inline XyzCoord<T> operator-(XyzCoord<T> xyz)
    {
        return XyzCoord<T>(xyz.x - x, xyz.y - y, xyz.z - z);
    }

    inline XyzCoord<T> operator*(XyzCoord<T> xyz)
    {
        return DotProduct(xyz);
    } 

    template <class Ti> inline XyzCoord<T>& operator* (Ti integer_v) {
		static_assert(std::numeric_limits<T>::is_bounded, "Only an integer type can be used inside this method.");
        return XyzCoord<T>(x * integer_v, y * integer_v, z * integer_v);
	}
};
template <class T> using XyzSize = XyzCoord<T>;
template <class T> using Vector3D = XyzCoord<T>;


void test()
{
    XyCoord<float> d = XyCoord<float>(3.44, 25.66);
}
