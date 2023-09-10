#include "pch.h"
#include "ModelResource.hpp"

namespace game {
	TEST_CLASS(ModelParserTest) {
	public:
		TEST_METHOD(DefaultConstructor) {
			ModelResource mr;

			Assert::IsNull(mr.getVertexBuffer());
			Assert::IsNull(mr.getIndexBuffer());
			Assert::AreEqual(0, mr.getVertexNum());
			Assert::AreEqual(0, mr.getPolygonNum());
		}

		TEST_METHOD(ConstructorWithFile) {
			ModelResource mr("../../Onigokko/sampleModel.txt");

			checkAllSampleModel(mr);
		}

		TEST_METHOD(ReloadSameFile) {
			ModelResource mr("../../Onigokko/sampleModel.txt");
			mr.reload();

			checkAllSampleModel(mr);
		}

		TEST_METHOD(ReloadFile) {
			ModelResource mr;
			mr.setFilepath("../../Onigokko/sampleModel.txt");
			mr.reload();

			checkAllSampleModel(mr);
		}
		
	private:
		void checkAllSampleModel(const ModelResource& mr) {
			Assert::AreEqual(4, mr.getVertexNum());
			Assert::AreEqual(2, mr.getPolygonNum());

			auto vertexBuffer = mr.getVertexBuffer();
			auto indexBuffer = mr.getIndexBuffer();

			Assert::IsNotNull(vertexBuffer);
			Assert::IsNotNull(indexBuffer);

			// 0
			Assert::AreEqual(VECTOR{ 100, 100, 100 }, vertexBuffer[0].pos);
			Assert::AreEqual(VECTOR{ 0, 0, -1 }, vertexBuffer[0].norm);
			Assert::AreEqual(COLOR_U8{ 255, 255, 255, 255 }, vertexBuffer[0].dif);
			Assert::AreEqual(COLOR_U8{ 0, 0, 0, 0 }, vertexBuffer[0].spc);
			Assert::AreEqual(0.0f, vertexBuffer[0].u);
			Assert::AreEqual(0.0f, vertexBuffer[0].v);
			Assert::AreEqual(0.0f, vertexBuffer[0].su);
			Assert::AreEqual(0.0f, vertexBuffer[0].sv);
			// 1
			Assert::AreEqual(VECTOR{ 250, 100, 0 }, vertexBuffer[1].pos);
			Assert::AreEqual(VECTOR{ 0, 0, -1 }, vertexBuffer[1].norm);
			Assert::AreEqual(COLOR_U8{ 255, 0, 255, 255 }, vertexBuffer[1].dif);
			Assert::AreEqual(COLOR_U8{ 0, 0, 0, 0 }, vertexBuffer[1].spc);
			Assert::AreEqual(0.0f, vertexBuffer[1].u);
			Assert::AreEqual(0.0f, vertexBuffer[1].v);
			Assert::AreEqual(0.0f, vertexBuffer[1].su);
			Assert::AreEqual(0.0f, vertexBuffer[1].sv);
			// 2
			Assert::AreEqual(VECTOR{ 100, 300, 0 }, vertexBuffer[2].pos);
			Assert::AreEqual(VECTOR{ 0, 0, -1 }, vertexBuffer[2].norm);
			Assert::AreEqual(COLOR_U8{ 0, 255, 255, 255 }, vertexBuffer[2].dif);
			Assert::AreEqual(COLOR_U8{ 0, 0, 0, 0 }, vertexBuffer[2].spc);
			Assert::AreEqual(0.0f, vertexBuffer[2].u);
			Assert::AreEqual(0.0f, vertexBuffer[2].v);
			Assert::AreEqual(0.0f, vertexBuffer[2].su);
			Assert::AreEqual(0.0f, vertexBuffer[2].sv);
			// 3
			Assert::AreEqual(VECTOR{ 400, 200, 0 }, vertexBuffer[3].pos);
			Assert::AreEqual(VECTOR{ 0, 0, -1 }, vertexBuffer[3].norm);
			Assert::AreEqual(COLOR_U8{ 255, 255, 255, 255 }, vertexBuffer[3].dif);
			Assert::AreEqual(COLOR_U8{ 0, 0, 0, 0 }, vertexBuffer[3].spc);
			Assert::AreEqual(0.0f, vertexBuffer[3].u);
			Assert::AreEqual(0.0f, vertexBuffer[3].v);
			Assert::AreEqual(0.0f, vertexBuffer[3].su);
			Assert::AreEqual(0.0f, vertexBuffer[3].sv);
		}
	};
}