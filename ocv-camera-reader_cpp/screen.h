#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <Godot.hpp>
#include <MeshInstance.hpp>
#include <ImageTexture.hpp>
#include <SpatialMaterial.hpp>

#include <opencv2/opencv.hpp>

namespace godot{

class Screen : public MeshInstance{
	GODOT_CLASS(Screen, MeshInstance)

private:
	static const uint32_t WIDTH;
	static const uint32_t HEIGHT;
	cv::VideoCapture cam;
	cv::Mat _frame;

	Ref<Image> _frameBuffer;
	Ref<ImageTexture> _texture;
	Ref<SpatialMaterial> _material;

public:
	static void _register_methods();

	Screen();
	~Screen();

	void _init(); // our initializer called by Godot
	void _ready();
	void _process(float delta);
};

}

#endif
