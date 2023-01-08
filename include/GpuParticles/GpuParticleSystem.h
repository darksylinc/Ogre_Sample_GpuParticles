#ifndef GPUPARTICLESYSTEM_H
#define GPUPARTICLESYSTEM_H

#include <GpuParticles/GpuParticleEmitter.h>

#include <OgreVector3.h>

class GpuParticleSystem
{
public:

    void addEmitter(GpuParticleEmitter* particleEmitter);
    const std::vector<GpuParticleEmitter*>& getEmitters() const;

private:
    std::vector<GpuParticleEmitter*> mEmitters;
};

#endif
