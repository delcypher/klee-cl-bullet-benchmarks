#include <BulletMultiThreaded/GpuSoftBodySolvers/OpenCL/btSoftBodySolver_OpenCL.h>
#include <BulletSoftBody/btSoftBody.h>
#include <BulletSoftBody/btSoftBodySolverVertexBuffer.h>
#include <clstuff.h>
#include <klee/klee.h>

extern cl_context                       g_cxMainContext;
extern cl_device_id                     g_cdDevice;
extern cl_command_queue         g_cqCommandQue;

using namespace klee;

int main(int argc, char **argv) {
  initCL(0, 0);
  btOpenCLSoftBodySolver cls(g_cqCommandQue, g_cxMainContext);
  cls.checkInitialized();
  cls.setNumberOfVelocityIterations(1);
//  cls.solveConstraints(1.0);
  
  btSoftBodyWorldInfo worldInfo;
  worldInfo.air_density = symbolic<btScalar>("air_density");
  worldInfo.water_density = symbolic<btScalar>("water_density");
  worldInfo.water_offset = symbolic<btScalar>("water_offset");
  worldInfo.water_normal = symbolic<btVector3>("water_normal");
  worldInfo.m_gravity = symbolic<btVector3>("m_gravity");

  btVector3 x[3] = {
    btVector3(1, 2, 3),
    btVector3(4, 5, 6),
    btVector3(7, 8, 9)
  };
  // btSoftBody body1(&worldInfo, 3, x, symbolic<btScalar[3]>("m"));
  btSoftBody body1(&worldInfo, 3, x, 0);
  body1.setSoftBodySolver(&cls);
  body1.appendLink(0, 1);
  body1.appendLink(1, 2);
  body1.appendLink(2, 0);
  body1.addVelocity(symbolic<btVector3>("velocity"));

  btAlignedObjectArray<btSoftBody *> bodies;
  bodies.push_back(&body1);
  cls.optimize(bodies);
  cls.solveConstraints(symbolic<float>("solverdt"));

  float out[9];
  btCPUVertexBufferDescriptor outDesc(out, 0, 3);

  btSoftBodySolverOutputCLtoCPU cl2cpu;
  cl2cpu.copySoftBodyToVertexBuffer(&body1, &outDesc);
  for (unsigned i = 0; i != 9; ++i)
    klee_print_expr("out[i]", out[i]);
}
