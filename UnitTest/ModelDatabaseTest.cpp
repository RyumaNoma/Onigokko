#include "pch.h"
#include "ModelDatabase.hpp"

namespace game {
	TEST_CLASS(ModelDatabaseTest)
	{
	public:
		TEST_METHOD(DefaultConstructor) {
			ModelDatabase md;
			Assert::AreEqual(0ULL, md.getSize());
		}
		TEST_METHOD(LoadAndFetch) {
			ModelDatabase md;
			md.load("sample", "../../Onigokko/sampleModel.txt");
			Assert::IsNotNull(md.fetch("sample", "../../Onigokko/sampleModel.txt").get());
			Assert::AreEqual(1ULL, md.getSize());
		}
		TEST_METHOD(OnlyFetch) {
			ModelDatabase md;
			Assert::IsNotNull(md.fetch("sample", "../../Onigokko/sampleModel.txt").get());
			Assert::AreEqual(1ULL, md.getSize());
		}
		TEST_METHOD(FetchSameFileTwice) {
			ModelDatabase md;
			md.load("sample", "../../Onigokko/sampleModel.txt");
			Assert::IsNotNull(md.fetch("sample", "../../Onigokko/sampleModel.txt").get());
			Assert::IsNotNull(md.fetch("sample", "../../Onigokko/sampleModel.txt").get());
			Assert::AreEqual(1ULL, md.getSize());
		}
		TEST_METHOD(LoadSameFileTwice) {
			ModelDatabase md;
			md.load("sample", "../../Onigokko/sampleModel.txt");
			md.load("sample", "../../Onigokko/sampleModel.txt");
			Assert::IsNotNull(md.fetch("sample", "../../Onigokko/sampleModel.txt").get());
			Assert::AreEqual(1ULL, md.getSize());
		}
		TEST_METHOD(LoadMultipleFile) {
			ModelDatabase md;
			md.load("sample", "../../Onigokko/sampleModel.txt");
			md.load("cube", "../../Onigokko/cube.txt");
			Assert::IsNotNull(md.fetch("sample", "../../Onigokko/sampleModel.txt").get());
			Assert::IsNotNull(md.fetch("cube", "../../Onigokko/cube.txt").get());
			Assert::AreEqual(2ULL, md.getSize());
		}
		TEST_METHOD(LoadAndFetchMultipleFile) {
			ModelDatabase md;
			Assert::IsNotNull(md.fetch("sample", "../../Onigokko/sampleModel.txt").get());
			Assert::IsNotNull(md.fetch("cube", "../../Onigokko/cube.txt").get());
			Assert::AreEqual(2ULL, md.getSize());
		}
		TEST_METHOD(LoadNotExistFile) {
			ModelDatabase md;
			try {
				md.load("sample", "yo");
			}
			catch (std::invalid_argument) {
				return;
			}
			Assert::Fail();
		}
		TEST_METHOD(FetchNotExistFile) {
			ModelDatabase md;
			try {
				md.fetch("sample", "yo");
			}
			catch (std::invalid_argument) {
				return;
			}
			Assert::Fail();
		}
	};
}
