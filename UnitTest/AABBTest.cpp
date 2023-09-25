#include "pch.h"
#include "AABB.hpp"
#include "ModelResource.hpp"
#include "ModelInstance.hpp"
#include <cassert>
#include <stdexcept>

namespace game {
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
			mi->rotate(-DX_PI_F / 4.0f);
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
			Assert::AreEqual(-1.0f, minY);
			Assert::AreEqual(1.0f, maxY);
			Assert::AreEqual(0.0f, minZ);
			assert(1.4142f < maxZ && maxZ < 1.4143f);
		}
		TEST_METHOD(UpdateMovedModel) {
			ModelResourcePtr mr(new ModelResource("../../Onigokko/item.txt"));
			ModelInstancePtr mi(new ModelInstance(mr));
			mi->move(VGet(3.0f, 4.0f, 5.0f));
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
			mi->setScale(VGet(123, 456, 123));
			mi->rotate(-DX_PI_F / 4.0f);
			AABB aabb;
			aabb.update(mi);

			const float minX = aabb.getMinX();
			const float maxX = aabb.getMaxX();
			const float minY = aabb.getMinY();
			const float maxY = aabb.getMaxY();
			const float minZ = aabb.getMinZ();
			const float maxZ = aabb.getMaxZ();

			assert(-0.708f * 123 + 3.0f < minX && minX < -0.707f * 123 + 3.0f);
			assert( 0.707f * 123 + 3.0f < maxX && maxX <  0.708f * 123 + 3.0f);
			Assert::AreEqual(-1.0f * 456 + 4.0f, aabb.getMinY());
			Assert::AreEqual(1.0f * 456 + 4.0f, aabb.getMaxY());
			Assert::AreEqual(0.0f * 789 + 5.0f, minZ);
			assert(1.41f * 123 + 5.0f < maxZ && maxZ < 1.42f * 123 + 5.0f);
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
	};
}
