#include "pch.h"
#include "VectorOperator.hpp"

namespace game {
	TEST_CLASS(VectorOperatorTest) {
		public:
		TEST_METHOD(Plus) {
			Assert::AreEqual(VGet(5, 7, 9), VGet(1, 2, 3) + VGet(4, 5, 6));
			Assert::AreEqual(VGet(0, 0, -1), VGet(1, 2, 3) + VGet(-1, -2, -4));
		}
		TEST_METHOD(Minus) {
			Assert::AreEqual(VGet(-3, -3, -3), VGet(1, 2, 3) - VGet(4, 5, 6));
			Assert::AreEqual(VGet(95, 360, 140), VGet(100, 400, 240) - VGet(5, 40, 100));
		}
		TEST_METHOD(Multiple) {
			Assert::AreEqual(VGet(3, 6, 9), VGet(1, 2, 3) * 3);
			Assert::AreEqual(VGet(3, 6, 9), 3 * VGet(1, 2, 3));
		}
		TEST_METHOD(Divide) {
			Assert::AreEqual(VGet(1, 2, 3), VGet(3, 6, 9) / 3);
			Assert::AreEqual(VGet(100, 50, 20), 100 / VGet(1, 2, 5));
		}
		TEST_METHOD(PlusEqual) {
			VECTOR v = VGet(1, 2, 3);
			v += VGet(0.5, 0.5, 0.5);
			Assert::AreEqual(VGet(1.5, 2.5, 3.5), v);
		}
		TEST_METHOD(MinusEqual) {
			VECTOR v = VGet(1, 2, 3);
			v -= VGet(0.5, 0.5, 0.5);
			Assert::AreEqual(VGet(0.5, 1.5, 2.5), v);
		}
		TEST_METHOD(MultipleEqual) {
			VECTOR v = VGet(1, 2, 3);
			v *= 4;
			Assert::AreEqual(VGet(4, 8, 12), v);
		}
		TEST_METHOD(DivideEqual) {
			VECTOR v = VGet(1, 2, 3);
			v /= 2;
			Assert::AreEqual(VGet(0.5, 1, 1.5), v);
		}
		TEST_METHOD(NotSame) {
			Assert::IsFalse(VGet(1, 2, 3) == VGet(1, 2, 5));
			Assert::IsTrue(VGet(1, 2, 3) != VGet(1, 2, 5));
		}
	};
}
