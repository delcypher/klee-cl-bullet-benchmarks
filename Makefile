include Makefile.config

CPPFLAGS = -I$(KLEE_PATH)/include -I$(BULLET_PATH)/src -I$(BULLET_PATH)/Demos/SharedOpenCL -I$(BULLET_PATH)/Demos/OpenCLClothDemo -ggdb3

BULLET_LIBS = -LBULLET_BUILD_PATH/src/BulletMultiThreaded/GpuSoftBodySolvers/OpenCL/NVidia -LBULLET_BUILD_PATH/src/BulletMultiThreaded/GpuSoftBodySolvers/CPU -LBULLET_BUILD_PATH/src/BulletSoftBody -LBULLET_BUILD_PATH/src/BulletCollision -LBULLET_BUILD_PATH/src/LinearMath -LBULLET_BUILD_PATH/src/BulletDynamics -lBulletSoftBodySolvers_OpenCL_NVidia -lBulletSoftBodySolvers_CPU -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath

LDFLAGS = -lOpenCL $(subst BULLET_BUILD_PATH,$(BULLET_CONC_BUILD_PATH),$(BULLET_LIBS))
LLVM_LDFLAGS = $(subst BULLET_BUILD_PATH,$(BULLET_BUILD_PATH),$(BULLET_LIBS))

OUTPUTS = TemplateC TemplateC.bc softbody softbody.exe softbody.conc.exe softbody.opt.bc softbody.conc.opt.bc dynworld dynworld.exe dynworld.conc.exe dynworld.opt.bc dynworld.conc.opt.bc softbody-problem clcc reduce.bc
all : $(OUTPUTS)

softbody: softbody.cpp $(BULLET_PATH)/Demos/OpenCLClothDemo/clstuff.cpp $(BULLET_PATH)/Demos/SharedOpenCL/btOclCommon.cpp $(BULLET_PATH)/Demos/SharedOpenCL/btOclUtils.cpp
	g++ -DCL_PLATFORM_NVIDIA $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

dynworld: dynworld.cpp $(BULLET_PATH)/Demos/OpenCLClothDemo/clstuff.cpp $(BULLET_PATH)/Demos/SharedOpenCL/btOclCommon.cpp $(BULLET_PATH)/Demos/SharedOpenCL/btOclUtils.cpp
	g++ -DCL_PLATFORM_NVIDIA $(CPPFLAGS) -o $@ $^ $(LDFLAGS)

softbody.exe: softbody.bc clstuff.bc btOclCommon.bc btOclUtils.bc
	$(LLVM_BUILD_PATH)/bin/llvm-ld -o $@ $^ $(LLVM_LDFLAGS)

softbody.conc.exe: softbody.conc.bc clstuff.bc btOclCommon.bc btOclUtils.bc
	$(LLVM_BUILD_PATH)/bin/llvm-ld -o $@ $^ $(LLVM_LDFLAGS)

dynworld.exe: dynworld.bc clstuff.bc btOclCommon.bc btOclUtils.bc
	$(LLVM_BUILD_PATH)/bin/llvm-ld -o $@ $^ $(LLVM_LDFLAGS)

dynworld.conc.exe: dynworld.conc.bc clstuff.bc btOclCommon.bc btOclUtils.bc
	$(LLVM_BUILD_PATH)/bin/llvm-ld -o $@ $^ $(LLVM_LDFLAGS)

clstuff.bc: $(BULLET_PATH)/Demos/OpenCLClothDemo/clstuff.cpp
	$(LLVM_BUILD_PATH)/bin/clang++ $(CPPFLAGS) -D__KLEE -emit-llvm -c -o $@ $<

btOclCommon.bc: $(BULLET_PATH)/Demos/SharedOpenCL/btOclCommon.cpp
	$(LLVM_BUILD_PATH)/bin/clang++ $(CPPFLAGS) -D__KLEE -emit-llvm -c -o $@ $<

btOclUtils.bc: $(BULLET_PATH)/Demos/SharedOpenCL/btOclUtils.cpp
	$(LLVM_BUILD_PATH)/bin/clang++ $(CPPFLAGS) -D__KLEE -emit-llvm -c -o $@ $<

%.bc: %.cpp
	$(LLVM_BUILD_PATH)/bin/clang++ $(CPPFLAGS) -D__KLEE -emit-llvm -c -o $@ $<

%.conc.bc: %.cpp
	$(LLVM_BUILD_PATH)/bin/clang++ $(CPPFLAGS) -emit-llvm -c -o $@ $<

%.bc: %.c
	$(LLVM_BUILD_PATH)/bin/clang $(CPPFLAGS) -D__KLEE -emit-llvm -c -o $@ $<

%.opt.bc: %.exe
	$(LLVM_BUILD_PATH)/bin/opt -simplifycfg -phi-node-folding-threshold=1000 -unsafe-phi-node-folding $<.bc -o $@
 
# Override single-sufix rule (needed to LDFLAGS are after input file, else linking will fail)
% : %.cpp
	$(CXX) $(CPPFLAGS) $< -o $@ $(LDFLAGS)

.PHONY: clean
clean:
	rm $(OUTPUTS) *.bc
