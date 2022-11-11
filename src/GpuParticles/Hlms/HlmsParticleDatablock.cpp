/*
 * File: HlmsParticleDatablock.cpp
 * Author: Przemysław Bągard
 * Created: 2021-5-15
 *
 */

#include "GpuParticles/Hlms/HlmsParticleDatablock.h"

#include <OgreTextureGpu.h>

HlmsParticleDatablock::HlmsParticleDatablock(Ogre::IdString name,
                                             Ogre::HlmsUnlit* creator,
                                             const Ogre::HlmsMacroblock* macroblock,
                                             const Ogre::HlmsBlendblock* blendblock,
                                             const Ogre::HlmsParamVec& params)
    : HlmsUnlitDatablock(name, creator, macroblock, blendblock, params)
    , mIsFlipbook(false)
    , mFlipbookSizeX(1)
    , mFlipbookSizeY(1)
    , mInvTextureSize(Ogre::Vector2::ZERO)
{

}

void HlmsParticleDatablock::addSprite(const Ogre::String& spriteName, const HlmsParticleDatablock::Sprite& sprite)
{
    mSprites.insert(std::make_pair(spriteName, sprite));
}

const HlmsParticleDatablock::Sprite* HlmsParticleDatablock::getSprite(const Ogre::String& spriteName) const
{
    std::map<Ogre::String, Sprite>::const_iterator it = mSprites.find(spriteName);
    if(it != mSprites.end()) {
        return &(it->second);
    }
    return nullptr;
}

const HlmsParticleDatablock::SpriteMap& HlmsParticleDatablock::getSprites() const
{
    return mSprites;
}

void HlmsParticleDatablock::recalculateInvTextureSize()
{
    Ogre::TextureGpu* texture = getTexture(0);
    if(texture) {

        texture->scheduleTransitionTo( Ogre::GpuResidency::OnSystemRam );
//        texture->scheduleTransitionTo( Ogre::GpuResidency::Resident );

        texture->waitForMetadata();
        mInvTextureSize.x = 1.0f / texture->getWidth();
        mInvTextureSize.y = 1.0f / texture->getHeight();


        if(getIsFlipbook()) {
            Ogre::uint32 spriteSizeX = texture->getWidth() / mFlipbookSizeX;
            Ogre::uint32 spriteSizeY = texture->getHeight() / mFlipbookSizeY;
            std::map<Ogre::String, Sprite>::iterator it = mSprites.begin();
            for(; it != mSprites.end(); ++it) {
                Sprite& sprite = it->second;
                sprite.mLeft = sprite.mFlipbookX * spriteSizeX;
                sprite.mBottom = sprite.mFlipbookY * spriteSizeY;
                sprite.mSizeX = spriteSizeX;
                sprite.mSizeY = spriteSizeY;
            }
        }
    }
}

Ogre::Vector2 HlmsParticleDatablock::getInvTextureSize() const
{
    return mInvTextureSize;
}

bool HlmsParticleDatablock::getIsFlipbook() const
{
    return mIsFlipbook;
}

void HlmsParticleDatablock::setIsFlipbook(bool isFlipbook)
{
    mIsFlipbook = isFlipbook;
}

void HlmsParticleDatablock::setFlipbookSize(const Ogre::uint32& flipbookSizeX, const Ogre::uint32& flipbookSizeY)
{
    mFlipbookSizeX = flipbookSizeX;
    if(mFlipbookSizeX < 1) {
        mFlipbookSizeX = 1;
    }
    mFlipbookSizeY = flipbookSizeY;
    if(mFlipbookSizeY < 1) {
        mFlipbookSizeY = 1;
    }
}
