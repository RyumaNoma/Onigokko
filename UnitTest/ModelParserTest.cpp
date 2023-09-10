#include "pch.h"
#include "ModelParser.hpp"
#include "DxLib.h"
#include <stdexcept>

namespace game {
	TEST_CLASS(ModelParserTest) {
		public:
		TEST_METHOD(DefaultConstructor) {
			ModelParser mp;
			Assert::IsTrue(mp.getVertexBuffer().empty());
			Assert::IsTrue(mp.getIndexBuffer().empty());
			Assert::AreEqual(static_cast<size_t>(0), mp.getVertexNum());
			Assert::AreEqual(static_cast<size_t>(0), mp.getPolygonNum());
		}
		TEST_METHOD(ConstructWithSampleModelFile) {
			ModelParser mp("../../Onigokko/sampleModel.txt");

			const auto& vb = mp.getVertexBuffer();
			const auto& ib = mp.getIndexBuffer();

			// 頂点数
			Assert::AreEqual(static_cast<size_t>(4), mp.getVertexNum());

			// 0
			Assert::AreEqual(VGet(100, 100, 0), vb.at(0).pos);
			Assert::AreEqual(VGet(0, 0, -1), vb.at(0).norm);
			Assert::AreEqual(GetColorU8(255, 255, 255, 255), vb.at(0).dif);
			Assert::AreEqual(GetColorU8(0, 0, 0, 0), vb.at(0).spc);
			Assert::AreEqual(0.0f, vb.at(0).u);
			Assert::AreEqual(0.0f, vb.at(0).v);
			Assert::AreEqual(0.0f, vb.at(0).sv);
			Assert::AreEqual(0.0f, vb.at(0).sv);
			// 1
			Assert::AreEqual(VGet(250, 100, 0), vb.at(1).pos);
			Assert::AreEqual(VGet(0, 0, -1), vb.at(1).norm);
			Assert::AreEqual(GetColorU8(255, 0, 255, 255), vb.at(1).dif);
			Assert::AreEqual(GetColorU8(0, 0, 0, 0), vb.at(1).spc);
			Assert::AreEqual(0.0f, vb.at(1).u);
			Assert::AreEqual(0.0f, vb.at(1).v);
			Assert::AreEqual(0.0f, vb.at(1).sv);
			Assert::AreEqual(0.0f, vb.at(1).sv);
			// 2
			Assert::AreEqual(VGet(100, 300, 0), vb.at(2).pos);
			Assert::AreEqual(VGet(0, 0, -1), vb.at(2).norm);
			Assert::AreEqual(GetColorU8(0, 255, 255, 255), vb.at(2).dif);
			Assert::AreEqual(GetColorU8(0, 0, 0, 0), vb.at(2).spc);
			Assert::AreEqual(0.0f, vb.at(2).u);
			Assert::AreEqual(0.0f, vb.at(2).v);
			Assert::AreEqual(0.0f, vb.at(2).sv);
			Assert::AreEqual(0.0f, vb.at(2).sv);
			// 3
			Assert::AreEqual(VGet(400, 200, 0), vb.at(3).pos);
			Assert::AreEqual(VGet(0, 0, -1), vb.at(3).norm);
			Assert::AreEqual(GetColorU8(255, 255, 255, 255), vb.at(3).dif);
			Assert::AreEqual(GetColorU8(0, 0, 0, 0), vb.at(3).spc);
			Assert::AreEqual(0.0f, vb.at(3).u);
			Assert::AreEqual(0.0f, vb.at(3).v);
			Assert::AreEqual(0.0f, vb.at(3).sv);
			Assert::AreEqual(0.0f, vb.at(3).sv);

			// ポリゴン数
			Assert::AreEqual(static_cast<size_t>(2), mp.getPolygonNum());

			// index
			Assert::AreEqual(static_cast<unsigned short>(0), ib.at(0).at(0));
			Assert::AreEqual(static_cast<unsigned short>(1), ib.at(0).at(1));
			Assert::AreEqual(static_cast<unsigned short>(2), ib.at(0).at(2));

			Assert::AreEqual(static_cast<unsigned short>(3), ib.at(1).at(0));
			Assert::AreEqual(static_cast<unsigned short>(2), ib.at(1).at(1));
			Assert::AreEqual(static_cast<unsigned short>(1), ib.at(1).at(2));
		}
		TEST_METHOD(ConstructWithNotExistFile) {
			try {
				ModelParser mp("hello.txt");
			}
			catch (std::invalid_argument) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}
	};
}