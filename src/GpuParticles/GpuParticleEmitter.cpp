/*
 * File: GpuParticleEmitter.cpp
 * Author: Przemysław Bągard
 * Created: 2021-5-4
 *
 */

#include "GpuParticles/GpuParticleEmitter.h"

const float GpuParticleEmitter::Epsilon = 0.001f;

GpuParticleEmitter::GpuParticleEmitter()
{

}

float GpuParticleEmitter::getTimeToSpawnParticle() const
{
    if(mBurstMode) {
        return !isImmediate() ? 1.0f / (mEmitterLifetime * mBurstParticles) : 0.0f;
    }
    else {
        return 1.0f / mEmissionRate;
    }
}

float GpuParticleEmitter::getEmissionRate() const
{
    if(mBurstMode) {
        return !isImmediate() ? mBurstParticles / mEmitterLifetime : 0.0f;
    }
    return mEmissionRate;
}

bool GpuParticleEmitter::isImmediateBurst() const
{
    return mBurstMode && isImmediate();
}
