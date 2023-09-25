#include "pch.h"
#include "CollisionDetection.hpp"
#include "AABB.hpp"

namespace game {
	TEST_CLASS(CollisionDetectionTest)
	{
	public:
		TEST_METHOD(StopCollision) {
			AABB a, b;
			a.update(VGet(-20, -20, -20), VGet(10, 10, 10));
			b.update(VGet(-5, -5, -5), VGet(40, 40, 40));
			Assert::IsTrue(CollisionDetection::testStop(a, b));
			Assert::IsTrue(CollisionDetection::testStop(b, a));
		}
		TEST_METHOD(StopCollisionXY) {
			AABB a, b;
			a.update(VGet(5, 2, -20), VGet(100, 4, 10));
			b.update(VGet(10, 0, -5), VGet(140, 8, 40));
			Assert::IsTrue(CollisionDetection::testStop(a, b));
			Assert::IsTrue(CollisionDetection::testStop(b, a));
		}
		TEST_METHOD(StopCollisionYZ) {
			AABB a, b;
			a.update(VGet(5, -20, 2), VGet(100, 10, 4));
			b.update(VGet(10, -5, 0), VGet(140, 40, 8));
			Assert::IsTrue(CollisionDetection::testStop(a, b));
			Assert::IsTrue(CollisionDetection::testStop(b, a));
		}
		TEST_METHOD(StopCollisionZX) {
			AABB a, b;
			a.update(VGet(-20, 2, 5), VGet(10, 4, 100));
			b.update(VGet(-5, 0, 10), VGet(40, 8, 140));
			Assert::IsTrue(CollisionDetection::testStop(a, b));
			Assert::IsTrue(CollisionDetection::testStop(b, a));
		}
		TEST_METHOD(StopInclude) {
			AABB a, b;
			a.update(VGet(0, 0, 0), VGet(100, 100, 100));
			b.update(VGet(10, 10, 10), VGet(20, 20, 20));
			Assert::IsTrue(CollisionDetection::testStop(a, b));
			Assert::IsTrue(CollisionDetection::testStop(b, a));
		}
		TEST_METHOD(StopSame) {
			AABB a, b;
			a.update(VGet(30, 30, 30), VGet(50, 50, 50));
			b.update(VGet(30, 30, 30), VGet(50, 50, 50));
			Assert::IsTrue(CollisionDetection::testStop(a, b));
			Assert::IsTrue(CollisionDetection::testStop(b, a));
		}
	};
}
