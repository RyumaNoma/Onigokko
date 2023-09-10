// pch.h: プリコンパイル済みヘッダー ファイルです。
// 次のファイルは、その後のビルドのビルド パフォーマンスを向上させるため 1 回だけコンパイルされます。
// コード補完や多くのコード参照機能などの IntelliSense パフォーマンスにも影響します。
// ただし、ここに一覧表示されているファイルは、ビルド間でいずれかが更新されると、すべてが再コンパイルされます。
// 頻繁に更新するファイルをここに追加しないでください。追加すると、パフォーマンス上の利点がなくなります。

#ifndef PCH_H
#define PCH_H

#include "CppUnitTest.h"
#include "DxLib.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// ==演算子のオーバーロード
bool operator == (const VECTOR& lhs, const VECTOR& rhs);
bool operator == (const COLOR_U8& lhs, const COLOR_U8& rhs);
// ToStringの特殊化
namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template<> inline std::wstring ToString<VECTOR>(const VECTOR& t) {
				RETURN_WIDE_STRING(std::string('(' + std::to_string(t.x) + ',' + std::to_string(t.y) + ',' + std::to_string(t.z) + ')').c_str());
			}
			template<> inline std::wstring ToString<COLOR_U8>(const COLOR_U8& t) {
				RETURN_WIDE_STRING(std::string('(' + std::to_string(t.r) + ',' + std::to_string(t.g) + ',' + std::to_string(t.b) + ',' + std::to_string(t.a) + ')').c_str());
			}
		}
	}
}

#endif //PCH_H
