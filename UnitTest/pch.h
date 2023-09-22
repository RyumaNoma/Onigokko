// pch.h: プリコンパイル済みヘッダー ファイルです。
// 次のファイルは、その後のビルドのビルド パフォーマンスを向上させるため 1 回だけコンパイルされます。
// コード補完や多くのコード参照機能などの IntelliSense パフォーマンスにも影響します。
// ただし、ここに一覧表示されているファイルは、ビルド間でいずれかが更新されると、すべてが再コンパイルされます。
// 頻繁に更新するファイルをここに追加しないでください。追加すると、パフォーマンス上の利点がなくなります。

#ifndef PCH_H
#define PCH_H

#include "CppUnitTest.h"
#include "DxLib.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

bool operator == (const COLOR_U8& lhs, const COLOR_U8& rhs);
// ToStringの特殊化
namespace game {
	class ModelResource;
	class ModelInstance;
}
namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template<> inline std::wstring ToString<VECTOR>(const VECTOR& t) {
				RETURN_WIDE_STRING(std::string('(' + std::to_string(t.x) + ',' + std::to_string(t.y) + ',' + std::to_string(t.z) + ')').c_str());
			}
			template<> inline std::wstring ToString<COLOR_U8>(const COLOR_U8& t) {
				RETURN_WIDE_STRING(std::string('(' + std::to_string(t.r) + ',' + std::to_string(t.g) + ',' + std::to_string(t.b) + ',' + std::to_string(t.a) + ')').c_str());
			}
			template<> inline std::wstring ToString<VERTEX3D>(VERTEX3D* t) {
				RETURN_WIDE_STRING(t);
			}
			template<> inline std::wstring ToString<unsigned short>(unsigned short* t) {
				RETURN_WIDE_STRING(t);
			}
			template<> inline std::wstring ToString<std::shared_ptr<game::ModelResource const>>(const std::shared_ptr<game::ModelResource const>& t) {
				RETURN_WIDE_STRING(t.get());
			}
			template<> inline std::wstring ToString<std::shared_ptr<game::ModelInstance const>>(const std::shared_ptr<game::ModelInstance const>& t) {
				RETURN_WIDE_STRING(t.get());
			}
			template<> inline std::wstring ToString<game::ModelInstance>(const game::ModelInstance* t) {
				RETURN_WIDE_STRING(t);
			}
		}
	}
}

#endif //PCH_H
