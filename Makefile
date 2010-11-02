include Makefile.config

CPPFLAGS = -I/usr/include/nvidia-current
LDFLAGS = -lOpenCL
   
all: TemplateC TemplateC.bc

TemplateC.bc: TemplateC.cpp
	$(LLVM_BUILD_PATH)/bin/clang++ $(CPPFLAGS) -emit-llvm -c -o $@ $<
