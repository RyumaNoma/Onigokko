#include "pch.h"
#include "AABB.hpp"
#include "ModelResource.hpp"
#include "ModelInstance.hpp"
#include <cassert>
#include <stdexcept>

namespace game {
	using ModelInstancePtr = std::shared_ptr<ModelInstance>;
	using ModelInstanceRef = std::shared_ptr<const ModelInstance>;

	TEST_CLASS(AABBTest)
	{
	public:
		TEST_METHOD(DefaultConstructor) {
			AABB aabb;
			Assert::AreEqual(0.0f, aabb.getMinX());
			Assert::AreEqual(1.0f, aabb.getMaxX());
			Assert::AreEqual(0.0f, aabb.getMinY());
			Assert::AreEqual(1.0f, aabb.getMaxY());
			Assert::AreEqual(0.0f, aabb.getMinZ());
			Assert::AreEqual(1.0f, aabb.getMaxZ());
		}
		TEST_METHOD(AABBFromModel) {
			ModelResourcePtr mr(new ModelResource("../../Onigokko/item.txt"));
			ModelInstancePtr mi(new ModelInstance(mr));
			AABB aabb;
			aabb.update(mi);

		}
		TEST_METHOD(UpdateDefaultModel) {
			ModelResourcePtr mr(new ModelResource("../../Onigokko/item.txt"));
			ModelInstancePtr mi(new ModelInstance(mr));
			AABB aabb;
			aabb.update(mi);
			Assert::AreEqual(0.0f, aabb.getMinX());
			Assert::AreEqual(1.0f, aabb.getMaxX());
			Assert::AreEqual(-1.0f, aabb.getMinY());
			Assert::AreEqual(1.0f, aabb.getMaxY());
			Assert::AreEqual(0.0f, aabb.getMinZ());
			Assert::AreEqual(1.0f, aabb.getMaxZ());
		}
		TEST_METHOD(UpdateRotatedModel) {
			ModelResourcePtr mr(new ModelResource("../../Onigokko/item.txt"));
			ModelInstancePtr mi(new ModelInstance(mr));
			mi->move(VGet(3.0f, 4.0f, 5.0f));
			AABB aabb;
			aabb.update(mi);

			const float minX = aabb.getMinX();
			const float maxX = aabb.getMaxX();
			const float minY = aabb.getMinY();
			const float maxY = aabb.getMaxY();
			const float minZ = aabb.getMinZ();
			const float maxZ = aabb.getMaxZ();

			assert(-0.7072f < minX && minX < -0.7071f);
			assert(0.7071f < maxX && maxX < 0.7072f);
			Assert::AreEqual(-1.0f, aabb.getMinY());
			Assert::AreEqual(1.0f, aabb.getMaxY());
			Assert::AreEqual(0.0f, minZ);
			assert(1.4142f < maxZ && maxZ < 1.4143f);
		}
		TEST_METHOD(UpdateMovedModel) {
			ModelResourcePtr mr(new ModelResource("../../Onigokko/item.txt"));
			ModelInstancePtr mi(new ModelInstance(mr));
			mi->rotate(DX_PI_F / 8.0f);
			AABB aabb;
			aabb.update(mi);

			Assert::AreEqual(3.0f, aabb.getMinX());
			Assert::AreEqual(4.0f, aabb.getMaxX());
			Assert::AreEqual(3.0f, aabb.getMinY());
			Assert::AreEqual(5.0f, aabb.getMaxY());
			Assert::AreEqual(5.0f, aabb.getMinZ());
			Assert::AreEqual(6.0f, aabb.getMaxZ());
		}
		TEST_METHOD(UpdateScaledModel) {
			ModelResourcePtr mr(new ModelResource("../../Onigokko/item.txt"));
			ModelInstancePtr mi(new ModelInstance(mr));
			mi->setScale(VGet(123, 456, 789));
			AABB aabb;
			aabb.update(mi);

			Assert::AreEqual(0.0f, aabb.getMinX());
			Assert::AreEqual(123.0f, aabb.getMaxX());
			Assert::AreEqual(-456.0f, aabb.getMinY());
			Assert::AreEqual(456.0f, aabb.getMaxY());
			Assert::AreEqual(0.0f, aabb.getMinZ());
			Assert::AreEqual(789.0f, aabb.getMaxZ());
		}
		TEST_METHOD(UpdateMultipleChangedModel) {
			ModelResourcePtr mr(new ModelResource("../../Onigokko/item.txt"));
			ModelInstancePtr mi(new ModelInstance(mr));
			mi->move(VGet(3.0f, 4.0f, 5.0f));
			mi->setScale(VGet(123, 456, 789));
			mi->rotate(DX_PI_F / 8.0f);
			AABB aabb;
			aabb.update(mi);

			const float minX = aabb.getMinX();
			const float maxX = aabb.getMaxX();
			const float minY = aabb.getMinY();
			const float maxY = aabb.getMaxY();
			const float minZ = aabb.getMinZ();
			const float maxZ = aabb.getMaxZ();

			assert(-0.7072f * 123 + 3.0f < minX && minX < -0.7071f * 123 + 3.0f);
			assert( 0.7071f * 123 + 3.0f < maxX && maxX <  0.7072f * 123 + 3.0f);
			Assert::AreEqual(-1.0f * 456 + 4.0f, aabb.getMinY());
			Assert::AreEqual(1.0f * 456 + 4.0f, aabb.getMaxY());
			Assert::AreEqual(0.0f * 789 + 5.0f, minZ);
			assert(1.4142f * 789 + 5.0f < maxZ && maxZ < 1.4143f * 789 + 5.0f);
		}
		TEST_METHOD(SetValidAABB) {
			AABB aabb;
			aabb.update(VGet(0, 4, 23), VGet(5, 34, 1000));

			Assert::AreEqual(0.0f, aabb.getMinX());
			Assert::AreEqual(5.0f, aabb.getMaxX());
			Assert::AreEqual(4.0f, aabb.getMinY());
			Assert::AreEqual(34.0f, aabb.getMaxY());
			Assert::AreEqual(23.0f, aabb.getMinZ());
			Assert::AreEqual(1000.0f, aabb.getMaxZ());
		}
		TEST_METHOD(setMinBiggerThanMax) {
			AABB aabb;
			try {
				aabb.update(VGet(5, 34, 1000), VGet(0, 4, 23));
			}
			catch (std::invalid_argument) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}
		TEST_METHOD(setZeroWidth) {
			AABB aabb;
			aabb.update(VGet(5, 36, 1004), VGet(5, 36, 1004));

			Assert::AreEqual(5.0f, aabb.getMinX());
			Assert::AreEqual(5.0f, aabb.getMaxX());
			Assert::AreEqual(36.0f, aabb.getMinY());
			Assert::AreEqual(36.0f, aabb.getMaxY());
			Assert::AreEqual(1004.0f, aabb.getMinZ());
			Assert::AreEqual(1004.0f, aabb.getMaxZ());
		}
		TEST_METHOD(Intersect) {
			AABB a, b;
			a.update(VGet(20, 20, 20), VGet(100, 100, 100));
			b.update(VGet(0, 0, 0), VGet(80, 80, 80));
			Assert::IsTrue(a.intersect(b));
			Assert::IsTrue(b.intersect(a));
		}
		TEST_METHOD(NotIntersect) {
			AABB a, b;
			a.update(VGet(0, 0, 0), VGet(20, 20, 20));
			b.update(VGet(80, 80, 80), VGet(100, 100, 100));
			Assert::IsFalse(a.intersect(b));
			Assert::IsFalse(b.intersect(a));
		}
		TEST_METHOD(IntersectOnlyPoint) {
			AABB a, b;
			a.update(VGet(-50, 0, 0), VGet(60, 60, 60));
			b.update(VGet(20, 20, 20), VGet(100, 100, 100));
			Assert::IsTrue(a.intersect(b));
			Assert::IsTrue(b.intersect(a));
		}
		TEST_METHOD(IntersectOnlyLine) {
			AABB a, b;
			a.update(VGet(-50, 0, 0), VGet(0, 20, 60));
			b.update(VGet(0, -60, 40), VGet(10, 0, 100));
			Assert::IsTrue(a.intersect(b));
			Assert::IsTrue(b.intersect(a));
		}
		TEST_METHOD(IntersectOnlySurface) {
			AABB a, b;
			a.update(VGet(-50, 10, 0), VGet(0, 20, 60));
			b.update(VGet(0, -60, 40), VGet(10, 15, 100));
			Assert::IsTrue(a.intersect(b));
			Assert::IsTrue(b.intersect(a));
		}
		TEST_METHOD(IntersectOnlyXY) {
			AABB a, b;
			a.update(VGet(-50, -100, 0), VGet(0, 20, 60));
			b.update(VGet(-20, 10, 100), VGet(1000, 30, 120));
			Assert::IsFalse(a.intersect(b));
			Assert::IsFalse(b.intersect(a));
		}
		TEST_METHOD(IntersectOnlyYZ) {
			AABB a, b;
			a.update(VGet(0, -100, -50), VGet(60, 20, 0));
			b.update(VGet(100, 10, -20), VGet(120, 30, 1000));
			Assert::IsFalse(a.intersect(b));
			Assert::IsFalse(b.intersect(a));
		}
		TEST_METHOD(IntersectOnlyZX) {
			AABB a, b;
			a.update(VGet(-50, 0, -100), VGet(0, 60, 20));
			b.update(VGet(-20, 100, 10), VGet(1000, 120, 30));
			Assert::IsFalse(a.intersect(b));
			Assert::IsFalse(b.intersect(a));
		}
	};
}
