#include "pch.h"
#include "ModelInstance.hpp"
#include "ModelResource.hpp"
#include "VectorOperator.hpp"

namespace game {
	TEST_CLASS(ModelInstanceTest) {
		public:
		TEST_METHOD(Constructor) {
			ModelResourcePtr mr(new ModelResource());
			ModelInstance mi(mr);

			Assert::AreEqual(VGet(1, 1, 1), mi.getScale());
			Assert::AreEqual(VGet(0, 0, 0), mi.getTranslate());
			Assert::AreEqual(VGet(0, 0, 1), mi.getRotate());
			Assert::AreEqual(static_cast<ModelResourceRef>(mr), mi.getModelResource());
		}
		TEST_METHOD(CopyConstructor) {
			ModelResourcePtr mr(new ModelResource());
			ModelInstance mi(mr);
			ModelInstance mi2 = mi;

			Assert::AreEqual(VGet(1, 1, 1), mi2.getScale());
			Assert::AreEqual(VGet(0, 0, 0), mi2.getTranslate());
			Assert::AreEqual(VGet(0, 0, 1), mi2.getRotate());
			Assert::AreEqual(static_cast<ModelResourceRef>(mr), mi2.getModelResource());
		}
		TEST_METHOD(InputOperator) {
			ModelResourcePtr mr(new ModelResource());
			ModelResourcePtr mr2(new ModelResource());
			ModelInstance mi(mr);
			ModelInstance mi2(mr2);
			mi2 = mi;

			Assert::AreEqual(VGet(1, 1, 1), mi2.getScale());
			Assert::AreEqual(VGet(0, 0, 0), mi2.getTranslate());
			Assert::AreEqual(VGet(0, 0, 1), mi2.getRotate());
			Assert::AreEqual(static_cast<ModelResourceRef>(mr), mi2.getModelResource());
		}
		TEST_METHOD(SetScaleEachVector) {
			ModelResourcePtr mr(new ModelResource());
			ModelInstance mi(mr);

			mi.setScaleX(2.0f);
			mi.setScaleY(3.0f);
			mi.setScaleZ(4.0f);

			Assert::AreEqual(VGet(2, 3, 4), mi.getScale());
			Assert::AreEqual(VGet(0, 0, 0), mi.getTranslate());
			Assert::AreEqual(VGet(0, 0, 1), mi.getRotate());
			Assert::AreEqual(static_cast<ModelResourceRef>(mr), mi.getModelResource());
		}
		TEST_METHOD(SetScaleWithVector) {
			ModelResourcePtr mr(new ModelResource());
			ModelInstance mi(mr);

			mi.setScale(VGet(2.0f, 3.0f, 4.0f));

			Assert::AreEqual(VGet(2, 3, 4), mi.getScale());
			Assert::AreEqual(VGet(0, 0, 0), mi.getTranslate());
			Assert::AreEqual(VGet(0, 0, 1), mi.getRotate());
			Assert::AreEqual(static_cast<ModelResourceRef>(mr), mi.getModelResource());
		}
		TEST_METHOD(SetScaleSameScale) {
			ModelResourcePtr mr(new ModelResource());
			ModelInstance mi(mr);

			mi.setScale(5.0f);

			Assert::AreEqual(VGet(5, 5, 5), mi.getScale());
			Assert::AreEqual(VGet(0, 0, 0), mi.getTranslate());
			Assert::AreEqual(VGet(0, 0, 1), mi.getRotate());
			Assert::AreEqual(static_cast<ModelResourceRef>(mr), mi.getModelResource());
		}
		TEST_METHOD(SetMinusScaleX) {
			ModelResourcePtr mr(new ModelResource());
			ModelInstance mi(mr);

			try {
				mi.setScaleX(-2.0f);
			}
			catch (std::invalid_argument) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}
		TEST_METHOD(SetMinusScaleY) {
			ModelResourcePtr mr(new ModelResource());
			ModelInstance mi(mr);

			try {
				mi.setScaleY(-2.0f);
			}
			catch (std::invalid_argument) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}
		TEST_METHOD(SetMinusScaleZ) {
			ModelResourcePtr mr(new ModelResource());
			ModelInstance mi(mr);

			try {
				mi.setScaleZ(-2.0f);
			}
			catch (std::invalid_argument) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}
		TEST_METHOD(SetMinusScaleVector) {
			ModelResourcePtr mr(new ModelResource());
			ModelInstance mi(mr);

			try {
				mi.setScale(VGet(-4.0, 5.0, 2));
			}
			catch (std::invalid_argument) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}
		TEST_METHOD(SetMinusSameScale) {
			ModelResourcePtr mr(new ModelResource());
			ModelInstance mi(mr);

			try {
				mi.setScale(-5.0);
			}
			catch (std::invalid_argument) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}
		TEST_METHOD(SetZeroScaleX) {
			ModelResourcePtr mr(new ModelResource());
			ModelInstance mi(mr);

			try {
				mi.setScaleX(0);
			}
			catch (std::invalid_argument) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}
		TEST_METHOD(SetZeroScaleY) {
			ModelResourcePtr mr(new ModelResource());
			ModelInstance mi(mr);

			try {
				mi.setScaleY(0);
			}
			catch (std::invalid_argument) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}
		TEST_METHOD(SetZeroScaleZ) {
			ModelResourcePtr mr(new ModelResource());
			ModelInstance mi(mr);

			try {
				mi.setScaleZ(0);
			}
			catch (std::invalid_argument) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}
		TEST_METHOD(SetZeroScaleVector) {
			ModelResourcePtr mr(new ModelResource());
			ModelInstance mi(mr);

			try {
				mi.setScale(VGet(2, 0, 5));
			}
			catch (std::invalid_argument) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}
		TEST_METHOD(SetZeroSameScale) {
			ModelResourcePtr mr(new ModelResource());
			ModelInstance mi(mr);

			try {
				mi.setScale(0);
			}
			catch (std::invalid_argument) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}
		TEST_METHOD(MoveDifference) {
			ModelResourcePtr mr(new ModelResource());
			ModelInstance mi(mr);

			mi.move(VGet(2, 4, 0.5));
			mi.move(VGet(-4, -1, -0.5));

			Assert::AreEqual(VGet(-2.0, 3, 0), mi.getTranslate());
		}
		TEST_METHOD(MoveToDestination) {
			ModelResourcePtr mr(new ModelResource());
			ModelInstance mi(mr);

			mi.moveTo(VGet(2, 4, 5));
			mi.moveTo(VGet(-4, -1, -4.6));

			Assert::AreEqual(VGet(-4, -1, -4.6), mi.getTranslate());
		}
		TEST_METHOD(LookAt) {
			ModelResourcePtr mr(new ModelResource());
			ModelInstance mi(mr);

			mi.lookAt(VGet(1, 4, -6));
			mi.lookAt(VGet(2,2,2));

			Assert::AreEqual(VGet(0, 0, 0), mi.getTranslate());
			Assert::AreEqual(VGet(2,2,2), mi.getRotate());
		}
	};
}
