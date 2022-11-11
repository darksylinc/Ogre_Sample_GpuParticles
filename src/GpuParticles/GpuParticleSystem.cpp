#include <GpuParticles/GpuParticleSystem.h>

void GpuParticleSystem::addEmitter(GpuParticleEmitter* particleEmitter)
{
    mEmitters.push_back(particleEmitter);
}

const std::vector<GpuParticleEmitter*>& GpuParticleSystem::getEmitters() const
{
    return mEmitters;
}
