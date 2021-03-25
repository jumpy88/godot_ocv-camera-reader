CC             = $(ANDROID_NDK_ROOT)/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++
TARGET         = --target=aarch64-linux-android24
ARCH           = -march=armv8-a
DIR            = ../ocv-camera-reader/bin/lib/android/arm64-v8a
GODOT_INCLUDE  = -I$(GODOT_HOME)/godot_headers -I$(GODOT_HOME)/include -I$(GODOT_HOME)/include/core -I$(GODOT_HOME)/include/gen
GODOT_LINK     = -L$(GODOT_HOME)/bin/ -lgodot-cpp.android.release.arm64v8
OPENCV_LINK    = -L$(OPENCV_ANDROID_HOME)/native/libs/arm64-v8a -lopencv_java4
OPENCV_INCLUDE = -I$(OPENCV_ANDROID_HOME)/native/jni/include

$(DIR)/libocvcr.so: $(DIR)/screen.o $(DIR)/ocvcr.o
	$(CC) $(TARGET) $(ARCH) -shared -o $(DIR)/libocvcr.so $(DIR)/screen.o $(DIR)/ocvcr.o $(GODOT_LINK) $(OPENCV_LINK)

$(DIR)/screen.o: screen.cpp screen.h
	$(CC) $(TARGET) $(ARCH) -c -fPIC -o $(DIR)/screen.o screen.cpp $(GODOT_INCLUDE) $(OPENCV_INCLUDE)

$(DIR)/ocvcr.o: ocv-camera-reader.cpp screen.h
	$(CC) $(TARGET) $(ARCH) -c -fPIC -o $(DIR)/ocvcr.o ocv-camera-reader.cpp $(GODOT_INCLUDE) $(OPENCV_INCLUDE)

clean:
	rm -f $(DIR)/screen.o
	rm -f $(DIR)/ocvcr.o
