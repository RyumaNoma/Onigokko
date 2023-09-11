#pragma once
#include "DxLib.h"

namespace DxLib {
	VECTOR operator+ (const VECTOR& lhs, const VECTOR& rhs);
	VECTOR operator- (const VECTOR& lhs, const VECTOR& rhs);
	VECTOR operator* (float lhs, const VECTOR& rhs);
	VECTOR operator* (const VECTOR& lhs, float rhs);
	VECTOR operator/ (float lhs, const VECTOR& rhs);
	VECTOR operator/ (const VECTOR& lhs, float rhs);
	VECTOR& operator+= (VECTOR& lhs, const VECTOR& rhs);
	VECTOR& operator-= (VECTOR& lhs, const VECTOR& rhs);
	VECTOR& operator*= (VECTOR& lhs, float rhs);
	VECTOR& operator/= (VECTOR& lhs, float rhs);
	bool operator== (const VECTOR& lhs, const VECTOR& rhs);
	bool operator!= (const VECTOR& lhs, const VECTOR& rhs);
}
