#include "ModelInstance.hpp"
#include "VectorOperator.hpp"
#include <stdexcept>

namespace game {
	ModelInstance::ModelInstance(ModelResourceRef modelResource)
		: _scale(VGet(1.0f, 1.0f, 1.0f))
		, _translate(VGet(0.0f, 0.0f, 0.0f))
		, _rotate(VGet(0.0f, 0.0f, 1.0f))
		, _modelResource(modelResource)
	{}

	void ModelInstance::setScaleX(float scale) {
		if (scale <= 0.0f) { throw std::invalid_argument("x scale must plus"); }
		_scale.x = scale;
	}

	void ModelInstance::setScaleY(float scale) {
		if (scale <= 0.0f) { throw std::invalid_argument("y scale must plus"); }
		_scale.y = scale;
	}

	void ModelInstance::setScaleZ(float scale) {
		if (scale <= 0.0f) { throw std::invalid_argument("z scale must plus"); }
		_scale.z = scale;
	}

	void ModelInstance::setScale(float scale) {
		setScaleX(scale);
		setScaleY(scale);
		setScaleZ(scale);
	}

	void ModelInstance::setScale(VECTOR scale) {
		setScaleX(scale.x);
		setScaleY(scale.y);
		setScaleZ(scale.z);
	}

	void ModelInstance::move(VECTOR difference) {
		_translate += difference;
	}

	void ModelInstance::moveTo(VECTOR destination) {
		_translate = destination;
	}

	void ModelInstance::lookAt(VECTOR fixation) {
		_rotate = fixation - _translate;
	}
}
