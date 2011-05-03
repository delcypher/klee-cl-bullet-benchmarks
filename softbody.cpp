#include <BulletMultiThreaded/GpuSoftBodySolvers/CPU/btSoftBodySolver_CPU.h>
#include <BulletMultiThreaded/GpuSoftBodySolvers/OpenCL/btSoftBodySolver_OpenCL.h>
#include <BulletSoftBody/btSoftBody.h>
#include <BulletSoftBody/btSoftBodySolverVertexBuffer.h>
#include <clstuff.h>
#ifdef __KLEE
#include <klee/klee.h>
#else
#include <stdio.h>
#endif

#include "klee-bits.h"

extern cl_context                       g_cxMainContext;
extern cl_device_id                     g_cdDevice;
extern cl_command_queue         g_cqCommandQue;

#ifdef __KLEE
using namespace klee;
#endif

void runTestProblem(btSoftBodySolver *solver, btSoftBodySolverOutput *output, float out[9],
                    btScalar air_density, btScalar water_density, btScalar water_offset,
                    const btVector3 &water_normal, const btVector3 &m_gravity,
                    btScalar kLST, btScalar kAST, btScalar kVST,
                    const btVector3 &velocity, btScalar friction,
                    btScalar kVCF, btScalar kDP, btScalar kDG, btScalar kLF,
                    float solverdt) {
  solver->checkInitialized();
  
  btSoftBodyWorldInfo worldInfo;
  worldInfo.air_density = air_density;
  worldInfo.water_density = water_density;
  worldInfo.water_offset = water_offset;
  worldInfo.water_normal = water_normal;
  worldInfo.m_gravity = m_gravity;

  btVector3 x[3] = {
    btVector3(1, 2, 3),
    btVector3(4, 5, 6),
    btVector3(7, 8, 9)
  };
  btSoftBody body1(&worldInfo, 3, x, 0);
  body1.setSoftBodySolver(solver);

  btSoftBody::Material *mat = body1.appendMaterial();
  mat->m_kLST = kLST;
  mat->m_kAST = kAST;
  mat->m_kVST = kVST;

  body1.appendLink(0, 1, mat);
  body1.appendLink(1, 2, mat);
  body1.appendLink(2, 0, mat);

  body1.addVelocity(velocity);
  body1.setFriction(friction);

  body1.m_cfg.kVCF = kVCF;
  body1.m_cfg.kDP = kDP;
  body1.m_cfg.kDG = kDG;
  body1.m_cfg.kLF = kLF;

  btAlignedObjectArray<btSoftBody *> bodies;
  bodies.push_back(&body1);
  solver->optimize(bodies);
  solver->solveConstraints(solverdt);

  btCPUVertexBufferDescriptor outDesc(out, 0, 3);
  output->copySoftBodyToVertexBuffer(&body1, &outDesc);
}

int main(int argc, char **argv) {
  initCL(0, 0);

  float cpuout[9], gpuout[9];
  
#ifdef __KLEE
  symbolic<btScalar> air_density("air_density");
  symbolic<btScalar> water_density("water_density");
  symbolic<btScalar> water_offset("water_offset");
  symbolic<btVector3> water_normal("water_normal");
  symbolic<btVector3> m_gravity("m_gravity");

  symbolic<btScalar> kLST("kLST");
  symbolic<btScalar> kAST("kAST");
  symbolic<btScalar> kVST("kVST");

  symbolic<btVector3> velocity("velocity");
  symbolic<btScalar> friction("friction");

  symbolic<btScalar> kVCF("kVCF");
  symbolic<btScalar> kDP("kDP");
  symbolic<btScalar> kDG("kDG");
  symbolic<btScalar> kLF("kLF");

  symbolic<float> solverdt("solverdt");
#else
  btScalar air_density = drand48() * 100.;
  btScalar water_density = drand48() * 100.;
  btScalar water_offset = drand48() * 100.;
  btVector3 water_normal(drand48() * 100., drand48() * 100., drand48() * 100.);
  btVector3 m_gravity(drand48() * 100., drand48() * 100., drand48() * 100.);

  btScalar kLST = drand48() * 100.;
  btScalar kAST = drand48() * 100.;
  btScalar kVST = drand48() * 100.;

  btVector3 velocity(drand48() * 100., drand48() * 100., drand48() * 100.);
  btScalar friction = drand48() * 100.;

  btScalar kVCF = drand48() * 100.;
  btScalar kDP = drand48() * 100.;
  btScalar kDG = drand48() * 100.;
  btScalar kLF = drand48() * 100.;

  float solverdt = drand48() * 100.;
#endif
  
  btCPUSoftBodySolver cpuSolver;
  btSoftBodySolverOutputCPUtoCPU cpu2cpu;
  runTestProblem(&cpuSolver, &cpu2cpu, cpuout,
                 air_density, water_density, water_offset, water_normal, m_gravity,
                 kLST, kAST, kVST,
                 velocity, friction,
                 kVCF, kDP, kDG, kLF,
                 solverdt);
 
  btOpenCLSoftBodySolver clSolver(g_cqCommandQue, g_cxMainContext);
  btSoftBodySolverOutputCLtoCPU cl2cpu;
  runTestProblem(&clSolver, &cl2cpu, gpuout,
                 air_density, water_density, water_offset, water_normal, m_gravity,
                 kLST, kAST, kVST,
                 velocity, friction,
                 kVCF, kDP, kDG, kLF,
                 solverdt);

#ifdef __KLEE
  for (unsigned i = 0; i != 9; ++i)
    klee_print_expr("cpuout[i] == gpuout[i]", float_bitwise_eq(cpuout[i], gpuout[i]));
#else
  for (unsigned i = 0; i != 9; ++i)
    printf("cpuout[%d] / gpuout[%d] : %f / %f\n", i, i, cpuout[i], gpuout[i]);
#endif
}
