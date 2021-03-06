#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <BulletCollision/CollisionDispatch/btCollisionDispatcher.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <BulletMultiThreaded/GpuSoftBodySolvers/CPU/btSoftBodySolver_CPU.h>
#include <BulletMultiThreaded/GpuSoftBodySolvers/OpenCL/btSoftBodySolver_OpenCL.h>
#include <BulletSoftBody/btSoftBody.h>
#include <BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h>
#include <BulletSoftBody/btSoftBodySolverVertexBuffer.h>
#include <BulletSoftBody/btSoftRigidDynamicsWorld.h>
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

typedef float testOut[18];

void runTestProblem(btSoftBodySolver *solver, btSoftBodySolverOutput *output, testOut &out,
                    btScalar air_density, btScalar water_density, btScalar water_offset,
                    const btVector3 &water_normal, const btVector3 &m_gravity,
                    btScalar kLST, btScalar kAST, btScalar kVST,
                    const btVector3 &velocity, btScalar friction,
                    btScalar kVCF, btScalar kDP, btScalar kDG, btScalar kLF,
                    float solverdt) {
  btSoftBodyRigidBodyCollisionConfiguration collisionConfig;
  btCollisionDispatcher dispatcher(&collisionConfig);
  btDbvtBroadphase broadphase;
  btSequentialImpulseConstraintSolver csolver;

  btSoftRigidDynamicsWorld dynWorld(&dispatcher, &broadphase, &csolver, &collisionConfig, solver);

  btSoftBodyWorldInfo &worldInfo = dynWorld.getWorldInfo();
  worldInfo.air_density = air_density;
  worldInfo.water_density = water_density;
  worldInfo.water_offset = water_offset;
  worldInfo.water_normal = water_normal;
  worldInfo.m_gravity = m_gravity;

  btVector3 body1vert[3] = {
    btVector3(1, 2, 3),
    btVector3(4, 5, 6),
    btVector3(7, 8, 9)
  };
  btSoftBody body1(&worldInfo, 3, body1vert, 0);
  body1.setSoftBodySolver(solver);

  btSoftBody::Material *mat1 = body1.appendMaterial();
  mat1->m_kLST = kLST;
  mat1->m_kAST = kAST;
  mat1->m_kVST = kVST;

  body1.appendLink(0, 1, mat1);
  body1.appendLink(1, 2, mat1);
  body1.appendLink(2, 0, mat1);

  body1.addVelocity(velocity);
  body1.setFriction(friction);

  body1.m_cfg.kVCF = kVCF;
  body1.m_cfg.kDP = kDP;
  body1.m_cfg.kDG = kDG;
  body1.m_cfg.kLF = kLF;

  dynWorld.addSoftBody(&body1);

  btVector3 body2vert[3] = {
    btVector3(1, 4, 3),
    btVector3(4, 7, 6),
    btVector3(7, 10, 9)
  };
  btSoftBody body2(&worldInfo, 3, body2vert, 0);
  body2.setSoftBodySolver(solver);

  btSoftBody::Material *mat2 = body2.appendMaterial();
  mat2->m_kLST = kLST;
  mat2->m_kAST = kAST;
  mat2->m_kVST = kVST;

  body2.appendLink(0, 1, mat2);
  body2.appendLink(1, 2, mat2);
  body2.appendLink(2, 0, mat2);

  body2.addVelocity(velocity);
  body2.setFriction(friction);

  body2.m_cfg.kVCF = kVCF;
  body2.m_cfg.kDP = kDP;
  body2.m_cfg.kDG = kDG;
  body2.m_cfg.kLF = kLF;

  dynWorld.addSoftBody(&body2);

  solver->optimize(dynWorld.getSoftBodyArray());
  dynWorld.stepSimulation(1./60.);
  solver->solveConstraints(solverdt);

  btCPUVertexBufferDescriptor out1Desc(out, 0, 3);
  output->copySoftBodyToVertexBuffer(&body1, &out1Desc);

  btCPUVertexBufferDescriptor out2Desc(out+9, 0, 3);
  output->copySoftBodyToVertexBuffer(&body2, &out2Desc);
}

int main(int argc, char **argv) {
  initCL(0, 0);

  testOut cpuout, gpuout;
  
  const double scale = 10.;

#ifdef __KLEE
  symbolic<btScalar> air_density("air_density");
  // btScalar air_density = drand48() * scale;
  symbolic<btScalar> water_density("water_density");
  symbolic<btScalar> water_offset("water_offset");
  symbolic<btVector3> water_normal("water_normal");
  // symbolic<btVector3> m_gravity("m_gravity");
  btVector3 m_gravity(drand48() * scale, drand48() * scale, drand48() * scale);

  symbolic<btScalar> kLST("kLST");
  // btScalar kLST = drand48() * scale;
  symbolic<btScalar> kAST("kAST");
  symbolic<btScalar> kVST("kVST");

  symbolic<btVector3> velocity("velocity");
  symbolic<btScalar> friction("friction");

  symbolic<btScalar> kVCF("kVCF");
  symbolic<btScalar> kDP("kDP");
  symbolic<btScalar> kDG("kDG");
  symbolic<btScalar> kLF("kLF");
  // btScalar kDG = drand48() * scale;
  // btScalar kLF = drand48() * scale;

  symbolic<float> solverdt("solverdt");
#else
  btScalar air_density = drand48() * scale;
  btScalar water_density = drand48() * scale;
  btScalar water_offset = drand48() * scale;
  btVector3 water_normal(drand48() * scale, drand48() * scale, drand48() * scale);
  btVector3 m_gravity(drand48() * scale, drand48() * scale, drand48() * scale);

  btScalar kLST = drand48() * scale;
  btScalar kAST = drand48() * scale;
  btScalar kVST = drand48() * scale;

  btVector3 velocity(drand48() * scale, drand48() * scale, drand48() * scale);
  btScalar friction = drand48() * scale;

  btScalar kVCF = drand48() * scale;
  btScalar kDP = drand48() * scale;
  btScalar kDG = drand48() * scale;
  btScalar kLF = drand48() * scale;

  float solverdt = drand48() * scale;
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
  for (unsigned i = 0; i != sizeof(cpuout)/sizeof(cpuout[0]); ++i) {
    klee_print_expr("cpuout[i] == gpuout[i]", float_bitwise_eq(cpuout[i], gpuout[i]));
  }
#else
  for (unsigned i = 0; i != sizeof(cpuout)/sizeof(cpuout[0]); ++i)
    printf("cpuout[%d] / gpuout[%d] : %f / %f\n", i, i, cpuout[i], gpuout[i]);
#endif
}
