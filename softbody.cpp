#include <BulletMultiThreaded/GpuSoftBodySolvers/CPU/btSoftBodySolver_CPU.h>
#include <BulletMultiThreaded/GpuSoftBodySolvers/OpenCL/btSoftBodySolver_OpenCL.h>
#include <BulletSoftBody/btSoftBody.h>
#include <BulletSoftBody/btSoftBodySolverVertexBuffer.h>
#include <clstuff.h>
#include <klee/klee.h>

extern cl_context                       g_cxMainContext;
extern cl_device_id                     g_cdDevice;
extern cl_command_queue         g_cqCommandQue;

using namespace klee;

void runTestProblem(btSoftBodySolver *solver, btSoftBodySolverOutput *output, float out[9],
                    btScalar air_density, btScalar water_density, btScalar water_offset,
                    const btVector3 &water_normal, const btVector3 &m_gravity,
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
  body1.appendLink(0, 1);
  body1.appendLink(1, 2);
  body1.appendLink(2, 0);
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
  
  symbolic<btScalar> air_density("air_density");
  symbolic<btScalar> water_density("water_density");
  symbolic<btScalar> water_offset("water_offset");
  symbolic<btVector3> water_normal("water_normal");
  symbolic<btVector3> m_gravity("m_gravity");

  symbolic<btVector3> velocity("velocity");
  symbolic<btScalar> friction("friction");

  symbolic<btScalar> kVCF("kVCF");
  symbolic<btScalar> kDP("kDP");
  symbolic<btScalar> kDG("kDG");
  symbolic<btScalar> kLF("kLF");

  symbolic<float> solverdt("solverdt");
  
  btCPUSoftBodySolver cpuSolver;
  btSoftBodySolverOutputCPUtoCPU cpu2cpu;
  runTestProblem(&cpuSolver, &cpu2cpu, cpuout,
                 air_density, water_density, water_offset, water_normal,
                 m_gravity, velocity, friction,
                 kVCF, kDP, kDG, kLF,
                 solverdt);
 
  btOpenCLSoftBodySolver clSolver(g_cqCommandQue, g_cxMainContext);
  btSoftBodySolverOutputCLtoCPU cl2cpu;
  runTestProblem(&clSolver, &cl2cpu, gpuout,
                 air_density, water_density, water_offset, water_normal,
                 m_gravity, velocity, friction,
                 kVCF, kDP, kDG, kLF,
                 solverdt);

  for (unsigned i = 0; i != 9; ++i) {
    klee_print_expr("cpuout[i]", cpuout[i]);
    klee_print_expr("gpuout[i]", gpuout[i]);
  }
}
