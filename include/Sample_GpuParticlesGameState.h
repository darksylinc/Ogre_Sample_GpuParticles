
#ifndef _Demo_Sample_GpuParticlesGameState_H_
#define _Demo_Sample_GpuParticlesGameState_H_

#include "OgrePrerequisites.h"
#include "TutorialGameState.h"

class GpuParticleSystem;
class GpuParticleSystemWorld;

namespace Demo
{
    class Sample_GpuParticlesGameState : public TutorialGameState
    {
        float mTimeOfDay;
        int mEmitterInstancesCount;
        GpuParticleSystemWorld* mGpuParticleSystemWorld;
        GpuParticleSystem* mFireParticleSystem;
        GpuParticleSystem* mSparksParticleSystem;
        std::vector<Ogre::uint64> mFireParticleInstances;

        Ogre::Light *mDirectionalLight;

        virtual void generateDebugText( float timeSinceLast, Ogre::String &outText );

    public:
        Sample_GpuParticlesGameState( const Ogre::String &helpDescription );

        virtual void createScene01(void);
        void registerParticleEmitters();
        virtual void destroyScene(void);

        void recreateEmitterInstances();

        virtual void update( float timeSinceLast );

        virtual void keyReleased( const SDL_KeyboardEvent &arg );
    };
}

#endif
