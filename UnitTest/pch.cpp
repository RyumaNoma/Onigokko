// pch.cpp: プリコンパイル済みヘッダーに対応するソース ファイル

#include "pch.h"

bool operator == (const COLOR_U8& lhs, const COLOR_U8& rhs) {
	return (lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a);
}

// プリコンパイル済みヘッダーを使用している場合、コンパイルを成功させるにはこのソース ファイルが必要です。
