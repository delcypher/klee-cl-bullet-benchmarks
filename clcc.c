#include <stdint.h>
#include <stdio.h>
#include <CL/cl.h>

static cl_int dump_binaries(cl_program prog, const char *prefix) {
  cl_int errcode;
  cl_uint num_binaries, i;

  size_t *binary_sizes;
  unsigned char **binaries;

  if ((errcode = clGetProgramInfo(prog, CL_PROGRAM_NUM_DEVICES, sizeof(cl_uint), &num_binaries, NULL)) != CL_SUCCESS)
    return errcode;

  binary_sizes = malloc(sizeof(size_t) * num_binaries);
  binaries = malloc(sizeof(unsigned char *) * num_binaries);

  if ((errcode = clGetProgramInfo(prog, CL_PROGRAM_BINARY_SIZES, sizeof(size_t) * num_binaries, binary_sizes, NULL)) != CL_SUCCESS)
    return errcode;

  for (i = 0; i != num_binaries; ++i)
    binaries[i] = malloc(binary_sizes[i]);

  if ((errcode = clGetProgramInfo(prog, CL_PROGRAM_BINARIES, sizeof(unsigned char *) * num_binaries, binaries, NULL)) != CL_SUCCESS)
    return errcode;

  for (i = 0; i != num_binaries; ++i) {
    char name[64];
    sprintf(name, "%s.bin%lu", prefix, (unsigned long) i);

    FILE *f = fopen(name, "w");
    fwrite(binaries[i], binary_sizes[i], 1, f);
    fclose(f);
    free(binaries[i]);
  }

  free(binary_sizes);
  free(binaries);
  return CL_SUCCESS;
}

int main(int argc, char **argv) {
  cl_platform_id platform;
  cl_device_id device;
  cl_context ctx;
  cl_program prog;
  cl_int errcode;
  FILE *bin;
  char *opencl_code_ptr;
  size_t opencl_code_len;
  char *flags = "";

  if (argc <= 1) {
    puts("usage: clcc input [flags] [output]");
    return 1;
  }

  if (clGetPlatformIDs(1, &platform, NULL) != CL_SUCCESS)
    return 1;

  if (clGetDeviceIDs(platform, CL_DEVICE_TYPE_DEFAULT, 1, &device, NULL) != CL_SUCCESS)
    return 2;

  ctx = clCreateContext(NULL, 1, &device, NULL, NULL, &errcode);
  if (!ctx)
    return 3;

  bin = fopen(argv[1], "r");
  if (!bin)
    return 4;

  fseek(bin, 0, SEEK_END);
  opencl_code_len = (size_t) ftell(bin);
  fseek(bin, 0, SEEK_SET);

  opencl_code_ptr = malloc(opencl_code_len);
  fread(opencl_code_ptr, opencl_code_len, 1, bin);
  fclose(bin);

  prog = clCreateProgramWithSource(ctx, 1, &opencl_code_ptr, &opencl_code_len, &errcode);
  if (!prog)
    return 5;

  free(opencl_code_ptr);

  if (argc > 2)
    flags = argv[2];

  if (clBuildProgram(prog, 1, &device, flags, NULL, NULL) != CL_SUCCESS) {
    size_t log_size;
    char *log;
    if (clGetProgramBuildInfo(prog, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size) != CL_SUCCESS)
      return 6;
    log = malloc(log_size);
    if (clGetProgramBuildInfo(prog, device, CL_PROGRAM_BUILD_LOG, log_size, log, NULL) != CL_SUCCESS)
      return 7;
    puts(log);
    return 8;
  }

  if (argc > 3) {
    if (dump_binaries(prog, argv[3]) != CL_SUCCESS)
      return 9;
  }

  return 0;
}
