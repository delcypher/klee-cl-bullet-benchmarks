include Makefile.config

CPPFLAGS = -I$(KLEE_PATH)/include -ggdb3
LDFLAGS = -lOpenCL
   
all: TemplateC TemplateC.bc

%.bc: %.cpp
	$(LLVM_BUILD_PATH)/bin/clang++ $(CPPFLAGS) -D__KLEE -emit-llvm -c -o $@ $<

%.bc: %.c
	$(LLVM_BUILD_PATH)/bin/clang $(CPPFLAGS) -D__KLEE -emit-llvm -c -o $@ $<
