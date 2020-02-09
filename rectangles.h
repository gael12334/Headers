#include "vector.h"

namespace Blue_GL {
	template <class T> struct XyRect {
		static_assert(std::numeric_limits<T>::is_bounded, "Only an numerical type can be used inside this structure.");
		
		T x, y, w, h;
		XyRect(T x, T y, T w, T h) {
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}
		
		XyRect() {
			x = 0;
			y = 0;
			w = 0;
			h = 0;
		}
		
		/// \brief Moves the "x" & "y" members to an added vector.
		/// \param vector The parameter requires to have a pointer to a vector; do for instance: "r.MoveBy(v&)".
		inline void MoveBy(Vector2D<T> vector) {
			x += vector.x;
			y += vector.y;
		}
		
		inline void MoveBy(T x, T y) {
			this->x += x;
			this->y += y;
		}
		
		inline void SetLocation(Vector2D<T> vector) {
			x = vector->x;
			y = vector->y;
		}
		
		inline void SetLocation(T x, T y) {
			this->x = x;
			this->y = y;
		}
		
		inline Vector2D<T> GetLocation() {
			return Vector2D<T>(x, y);
		}
		
		inline bool IsInside(Vector2D<T> vector) {
			return ((x <= vector.x) && (y <= vector.y) && (w > vector.x) && (h > vector.y));
		}
		
		inline bool IsInside(T x, T y) {
			return ((this->x <= x) && (this->y <= vector.y) && (this->w > vector.x) && (this->h > vector.y));
		}
		
		inline void operator+=(Vector2D<T> vector) {
			MoveBy(vector);
		}
		
		inline void operator-=(Vector2D<T> vector) {
			MoveBy(vector);
		}
		
		inline void Scale(float fvalue) {
			x *= fvalue;
			y *= fvalue;
			w *= fvalue;
			h *= fvalue;
		}
	};
}
