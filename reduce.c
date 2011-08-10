#include <stdint.h>
#include <stdio.h>
#include <CL/cl.h>
#include <klee/klee.h>

typedef enum {OP_READ, OP_WRITE, OP_RW, OP_INC, OP_MIN, OP_MAX} op_access;

int main(int argc, char **argv) {
  cl_platform_id platform;
  cl_device_id device;
  cl_context ctx;
  cl_program prog;
  cl_kernel kern;
  cl_command_queue cmdq;
  cl_mem in, out;
  cl_int errcode;
  FILE *bin;
  char *opencl_code_ptr;
  size_t opencl_code_len;

  size_t local_size = 16, num_groups = 16,
         global_size = local_size*num_groups;
  unsigned reduction = OP_INC;

  float *in_data = malloc(global_size*sizeof(float));

  if (clGetPlatformIDs(1, &platform, NULL) != CL_SUCCESS)
    return 1;

  if (clGetDeviceIDs(platform, CL_DEVICE_TYPE_DEFAULT, 1, &device, NULL) != CL_SUCCESS)
    return 2;

  ctx = clCreateContext(NULL, 1, &device, NULL, NULL, &errcode);
  if (!ctx)
    return 3;

  cmdq = clCreateCommandQueue(ctx, device, 0, &errcode);
  if (!cmdq)
    return 35;

  bin = fopen("reduce.cl", "r");
  if (!bin)
    return 4;

  /*
  fseek(bin, 0, SEEK_END);
  opencl_code_len = (size_t) ftell(bin);
  fseek(bin, 0, SEEK_SET);
  */
  opencl_code_len = 1848;

  opencl_code_ptr = malloc(opencl_code_len);
  fread(opencl_code_ptr, opencl_code_len, 1, bin);
  fclose(bin);

  prog = clCreateProgramWithSource(ctx, 1, &opencl_code_ptr, &opencl_code_len, &errcode);
  if (!prog)
    return 5;

  free(opencl_code_ptr);

  if (clBuildProgram(prog, 1, &device, "", NULL, NULL) != CL_SUCCESS) {
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

  kern = clCreateKernel(prog, "reduce", &errcode);
  if (!kern)
    return 9;

  klee_make_symbolic(in_data, global_size*sizeof(float), "in_data");

  out = clCreateBuffer(ctx, CL_MEM_WRITE_ONLY, num_groups*sizeof(float), NULL,
                       &errcode);
  clSetKernelArg(kern, 0, sizeof(cl_mem), &out);

  in = clCreateBuffer(ctx, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                      global_size*sizeof(float), in_data, &errcode);
  clSetKernelArg(kern, 1, sizeof(cl_mem), &in);

  clSetKernelArg(kern, 2, sizeof(unsigned), &reduction);

  clSetKernelArg(kern, 3, local_size*sizeof(float), NULL);

  clEnqueueNDRangeKernel(cmdq, kern, 1, NULL, &global_size, &local_size, 0, NULL, NULL);

  clFinish(cmdq);

  return 0;
}
