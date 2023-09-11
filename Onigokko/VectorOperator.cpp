#include "VectorOperator.hpp"
#include "DxLib.h"

namespace DxLib {
	VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs) {
		VECTOR result;
		result.x = lhs.x + rhs.x;
		result.y = lhs.y + rhs.y;
		result.z = lhs.z + rhs.z;
		return result;
	}
	VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs) {
		VECTOR result;
		result.x = lhs.x - rhs.x;
		result.y = lhs.y - rhs.y;
		result.z = lhs.z - rhs.z;
		return result;
	}
	VECTOR operator*(float lhs, const VECTOR& rhs) {
		VECTOR result;
		result.x = lhs * rhs.x;
		result.y = lhs * rhs.y;
		result.z = lhs * rhs.z;
		return result;
	}
	VECTOR operator*(const VECTOR& lhs, float rhs) {
		return rhs * lhs;
	}
	VECTOR operator/(float lhs, const VECTOR& rhs) {
		VECTOR result;
		result.x = lhs / rhs.x;
		result.y = lhs / rhs.y;
		result.z = lhs / rhs.z;
		return result;
	}
	VECTOR operator/(const VECTOR& lhs, float rhs) {
		VECTOR result;
		result.x = lhs.x / rhs;
		result.y = lhs.y / rhs;
		result.z = lhs.z / rhs;
		return result;
	}
	VECTOR& operator+=(VECTOR& lhs, const VECTOR& rhs) {
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		lhs.z += rhs.z;
		return lhs;
	}
	VECTOR& operator-=(VECTOR& lhs, const VECTOR& rhs) {
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		lhs.z -= rhs.z;
		return lhs;
	}
	VECTOR& operator*=(VECTOR& lhs, float rhs) {
		lhs.x *= rhs;
		lhs.y *= rhs;
		lhs.z *= rhs;
		return lhs;
	}
	VECTOR& operator/=(VECTOR& lhs, float rhs) {
		lhs.x /= rhs;
		lhs.y /= rhs;
		lhs.z /= rhs;
		return lhs;
	}
	bool operator==(const VECTOR& lhs, const VECTOR& rhs) {
		return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z);
	}
	bool operator!=(const VECTOR& lhs, const VECTOR& rhs) {
		return !(lhs == rhs);
	}
}
