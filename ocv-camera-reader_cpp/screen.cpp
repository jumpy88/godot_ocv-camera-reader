#include "screen.h"

using namespace godot;
using namespace cv;

const uint32_t Screen::WIDTH = 640;
const uint32_t Screen::HEIGHT = 480;

void Screen::_register_methods(){
	register_method("_ready", &Screen::_ready);
	register_method("_process", &Screen::_process);
}

Screen::Screen():
	cam(0){
	cam.set(CAP_PROP_FRAME_WIDTH, WIDTH);
	cam.set(CAP_PROP_FRAME_HEIGHT, HEIGHT);
}

Screen::~Screen(){
	// add your cleanup here
}

void Screen::_init(){
	// initialize any variables here
	_frameBuffer = Ref<Image>(Image::_new());
	_frameBuffer->create(WIDTH, HEIGHT, true, Image::FORMAT_RGB8);
	_frameBuffer->fill(Color(0.54, 0.17, 0.89, 1));
	_frameBuffer->lock();
	for(int32_t i = 0; i < _frameBuffer->get_width(); ++i){
		_frameBuffer->set_pixel(i, 0, Color(1, 0, 0));
		_frameBuffer->set_pixel(i, 1, Color(1, 0, 0));
		_frameBuffer->set_pixel(i, 2, Color(1, 0, 0));
		_frameBuffer->set_pixel(i, HEIGHT - 1, Color(1, 0, 0));
		_frameBuffer->set_pixel(i, HEIGHT - 2, Color(1, 0, 0));
		_frameBuffer->set_pixel(i, HEIGHT - 3, Color(1, 0, 0));
	}
	for(int32_t i = 0; i < _frameBuffer->get_height(); ++i){
		_frameBuffer->set_pixel(0, i, Color(1, 0, 0));
		_frameBuffer->set_pixel(1, i, Color(1, 0, 0));
		_frameBuffer->set_pixel(2, i, Color(1, 0, 0));
		_frameBuffer->set_pixel(WIDTH - 1, i, Color(1, 0, 0));
		_frameBuffer->set_pixel(WIDTH - 2, i, Color(1, 0, 0));
		_frameBuffer->set_pixel(WIDTH - 3, i, Color(1, 0, 0));
	}
	_frameBuffer->unlock();

	_texture = Ref<ImageTexture>(ImageTexture::_new());
	_texture->create_from_image(_frameBuffer);

	_material = Ref<SpatialMaterial>(SpatialMaterial::_new());
	_material->set_texture(SpatialMaterial::TEXTURE_ALBEDO, _texture);

	set_surface_material(0, _material);
}

void Screen::_ready(){
}

void Screen::_process(float delta){
	(void)delta;
	if(!cam.read(_frame)){
		_frame = Mat(HEIGHT, WIDTH, CV_8UC3);
	}
	cvtColor(_frame, _frame, COLOR_BGR2RGB);

	PoolByteArray buffer;
	buffer.resize(WIDTH * HEIGHT * 3);
	PoolByteArray::Write bufferWriter = buffer.write();
	memcpy(bufferWriter.ptr(), _frame.data, WIDTH * HEIGHT * 3);

	_frameBuffer->create_from_data(WIDTH, HEIGHT, false, Image::FORMAT_RGB8, buffer);
	_texture->set_data(_frameBuffer);
}
