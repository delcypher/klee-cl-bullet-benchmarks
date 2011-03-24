include Makefile.config

CPPFLAGS = -I$(KLEE_PATH)/include -I$(BULLET_PATH)/src -I$(BULLET_PATH)/Demos/SharedOpenCL -I$(BULLET_PATH)/Demos/OpenCLClothDemo -ggdb3
LDFLAGS = -lOpenCL

LLVM_LDFLAGS = -L$(BULLET_BUILD_PATH)/src/BulletMultiThreaded/GpuSoftBodySolvers/OpenCL/NVidia -lBulletSoftBodySolvers_OpenCL_NVidia

all: TemplateC TemplateC.bc softbody.exe

softbody.exe: softbody.bc clstuff.bc btOclCommon.bc btOclUtils.bc
	$(LLVM_BUILD_PATH)/bin/llvm-ld -o $@ $^ $(LLVM_LDFLAGS)

clstuff.bc: $(BULLET_PATH)/Demos/OpenCLClothDemo/clstuff.cpp
	$(LLVM_BUILD_PATH)/bin/clang++ $(CPPFLAGS) -D__KLEE -emit-llvm -c -o $@ $<

btOclCommon.bc: $(BULLET_PATH)/Demos/SharedOpenCL/btOclCommon.cpp
	$(LLVM_BUILD_PATH)/bin/clang++ $(CPPFLAGS) -D__KLEE -emit-llvm -c -o $@ $<

btOclUtils.bc: $(BULLET_PATH)/Demos/SharedOpenCL/btOclUtils.cpp
	$(LLVM_BUILD_PATH)/bin/clang++ $(CPPFLAGS) -D__KLEE -emit-llvm -c -o $@ $<

%.bc: %.cpp
	$(LLVM_BUILD_PATH)/bin/clang++ $(CPPFLAGS) -D__KLEE -emit-llvm -c -o $@ $<

%.bc: %.c
	$(LLVM_BUILD_PATH)/bin/clang $(CPPFLAGS) -D__KLEE -emit-llvm -c -o $@ $<
