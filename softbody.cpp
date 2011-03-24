#include <BulletMultiThreaded/GpuSoftBodySolvers/OpenCL/btSoftBodySolver_OpenCL.h>
#include <clstuff.h>

extern cl_context                       g_cxMainContext;
extern cl_device_id                     g_cdDevice;
extern cl_command_queue         g_cqCommandQue;

int main(int argc, char **argv) {
  initCL(0, 0);
  btOpenCLSoftBodySolver cls(g_cqCommandQue, g_cxMainContext);
  cls.checkInitialized();
}
