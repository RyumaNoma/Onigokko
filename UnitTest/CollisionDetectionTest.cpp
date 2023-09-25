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
		TEST_METHOD(StopNotCollision) {
			AABB a, b;
			a.update(VGet(30, 30, 30), VGet(50, 50, 50));
			b.update(VGet(60, 60, 60), VGet(70, 70, 70));
			Assert::IsFalse(CollisionDetection::testStop(a, b));
			Assert::IsFalse(CollisionDetection::testStop(b, a));
		}
		TEST_METHOD(StopNotCollisionX) {
			AABB a, b;
			a.update(VGet(0, -20, -20), VGet(10, 10, 10));
			b.update(VGet(100, -5, -5), VGet(1000, 40, 40));
			Assert::IsFalse(CollisionDetection::testStop(a, b));
			Assert::IsFalse(CollisionDetection::testStop(b, a));
		}
		TEST_METHOD(StopNotCollisionY) {
			AABB a, b;
			a.update(VGet(-20, 0, -20), VGet(10, 10, 10));
			b.update(VGet(-5, 100, -5), VGet(40, 1000, 40));
			Assert::IsFalse(CollisionDetection::testStop(a, b));
			Assert::IsFalse(CollisionDetection::testStop(b, a));
		}
		TEST_METHOD(StopNotCollisionZ) {
			AABB a, b;
			a.update(VGet(-20, -20, 0), VGet(10, 10, 10));
			b.update(VGet(-5, -5, 100), VGet(40, 40, 1000));
			Assert::IsFalse(CollisionDetection::testStop(a, b));
			Assert::IsFalse(CollisionDetection::testStop(b, a));
		}
		TEST_METHOD(StopCollisionOnlyPoint) {
			AABB a, b;
			a.update(VGet(30, 30, 30), VGet(50, 50, 50));
			b.update(VGet(50, 50, 50), VGet(70, 70, 70));
			Assert::IsFalse(CollisionDetection::testStop(a, b));
			Assert::IsFalse(CollisionDetection::testStop(b, a));
		}
		TEST_METHOD(StopCollisionOnlyLine) {
			AABB a, b;
			a.update(VGet(0, 0, 0), VGet(50, 50, 50));
			b.update(VGet(50, 50, 20), VGet(70, 70, 70));
			Assert::IsFalse(CollisionDetection::testStop(a, b));
			Assert::IsFalse(CollisionDetection::testStop(b, a));
		}
		TEST_METHOD(StopCollisionOnlySurface) {
			AABB a, b;
			a.update(VGet(0, 0, 0), VGet(50, 50, 50));
			b.update(VGet(20, 20, 50), VGet(70, 70, 70));
			Assert::IsFalse(CollisionDetection::testStop(a, b));
			Assert::IsFalse(CollisionDetection::testStop(b, a));
		}

		TEST_METHOD(MoveToSamePos) {
			AABB a, b;
			a.update(VGet(0, 0, 0), VGet(1, 1, 1));
			b.update(VGet(100, 100, 100), VGet(101, 101, 101));
			VECTOR va = VGet(50, 50, 50);
			VECTOR vb = VGet(-50, -50, -50);
			Assert::IsTrue(CollisionDetection::testMove(a, va, b, vb));
			Assert::IsTrue(CollisionDetection::testMove(b, vb, a, va));
		}
		TEST_METHOD(MoveCollision) {
			// (100, 0, 0)Ç≈è’ìÀ
			AABB a, b;
			a.update(VGet(0, 0, 0), VGet(1, 1, 1));
			b.update(VGet(100, 100, 0), VGet(101, 101, 1));
			VECTOR va = VGet(200, 0, 0);
			VECTOR vb = VGet(0, -200, 0);
			Assert::IsTrue(CollisionDetection::testMove(a, va, b, vb));
			Assert::IsTrue(CollisionDetection::testMove(b, vb, a, va));
		}
		TEST_METHOD(MoveOvertake) {
			AABB a, b;
			a.update(VGet(0, 0, 0), VGet(1, 1, 1));
			b.update(VGet(0, 0, 100), VGet(1, 1, 101));
			VECTOR va = VGet(0, 0, -10);
			VECTOR vb = VGet(0, 0, -1000 );
			Assert::IsTrue(CollisionDetection::testMove(a, va, b, vb));
			Assert::IsTrue(CollisionDetection::testMove(b, vb, a, va));
		}
		TEST_METHOD(MoveCollisionOtherStop) {
			AABB a, b;
			a.update(VGet(0, 0, 0), VGet(1, 1, 1));
			b.update(VGet(100, 100, 100), VGet(101, 101, 101));
			VECTOR va = VGet(0, 0, 0);
			VECTOR vb = VGet(-1000, -1000, -1000);
			Assert::IsTrue(CollisionDetection::testMove(a, va, b, vb));
			Assert::IsTrue(CollisionDetection::testMove(b, vb, a, va));
		}
		TEST_METHOD(MoveCollisionStopAndStop) {
			AABB a, b;
			a.update(VGet(0, 0, 0), VGet(2, 2, 2));
			b.update(VGet(1, 1, 1), VGet(4, 4, 4));
			VECTOR va = VGet(0, 0, 0);
			VECTOR vb = VGet(0, 0, 0);
			Assert::IsTrue(CollisionDetection::testMove(a, va, b, vb));
			Assert::IsTrue(CollisionDetection::testMove(b, vb, a, va));
		}
		TEST_METHOD(MoveCannotOvertake) {
			AABB a, b;
			a.update(VGet(0, 0, 0), VGet(1, 1, 1));
			b.update(VGet(0, 0, 100), VGet(1, 1, 101));
			VECTOR va = VGet(0, 0, -1000);
			VECTOR vb = VGet(0, 0, -1000);
			Assert::IsFalse(CollisionDetection::testMove(a, va, b, vb));
			Assert::IsFalse(CollisionDetection::testMove(b, vb, a, va));
		}
		TEST_METHOD(MoveNotCollisionOtherStop) {
			AABB a, b;
			a.update(VGet(0, 0, 0), VGet(1, 1, 1));
			b.update(VGet(100, 100, 100), VGet(101, 101, 101));
			VECTOR va = VGet(0, 0, 0);
			VECTOR vb = VGet(1000, 1000, 1000);
			Assert::IsFalse(CollisionDetection::testMove(a, va, b, vb));
			Assert::IsFalse (CollisionDetection::testMove(b, vb, a, va));
		}
		TEST_METHOD(MoveNotCollisionStopAndStop) {
			AABB a, b;
			a.update(VGet(0, 0, 0), VGet(1, 1, 1));
			b.update(VGet(2, 2, 2), VGet(4, 4, 4));
			VECTOR va = VGet(0, 0, 0);
			VECTOR vb = VGet(0, 0, 0);
			Assert::IsFalse(CollisionDetection::testMove(a, va, b, vb));
			Assert::IsFalse(CollisionDetection::testMove(b, vb, a, va));
		}
		TEST_METHOD(MoveToOtherSide) {
			AABB a, b;
			a.update(VGet(0, 0, 0), VGet(1, 1, 1));
			b.update(VGet(2, 2, 2), VGet(4, 4, 4));
			VECTOR va = VGet(-10, -10, -10);
			VECTOR vb = VGet(10, 10, 10);
			Assert::IsFalse(CollisionDetection::testMove(a, va, b, vb));
			Assert::IsFalse(CollisionDetection::testMove(b, vb, a, va));
		}
	};
}
