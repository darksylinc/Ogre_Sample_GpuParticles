/*
 * File: HlmsParticleDatablock.h
 * Author: Przemysław Bągard
 * Created: 2021-5-15
 *
 */

#ifndef HLMSPARTICLEDATABLOCK_H
#define HLMSPARTICLEDATABLOCK_H

#include <OgreHlmsUnlitDatablock.h>

class HlmsParticleDatablock : public Ogre::HlmsUnlitDatablock
{
    friend class HlmsParticle;

public:

    class Sprite
    {
    public:
        Ogre::uint32 mLeft;
        Ogre::uint32 mBottom;
        Ogre::uint32 mSizeX;
        Ogre::uint32 mSizeY;

        /// Used only if flipbook mode
        Ogre::int32 mFlipbookX = -1;
        Ogre::int32 mFlipbookY = -1;
    };
    typedef std::map<Ogre::String, Sprite> SpriteMap;

public:
    HlmsParticleDatablock(Ogre::IdString name,
                          Ogre::HlmsUnlit *creator,
                          const Ogre::HlmsMacroblock *macroblock,
                          const Ogre::HlmsBlendblock *blendblock,
                          const Ogre::HlmsParamVec &params );

    void addSprite(const Ogre::String& spriteName, const Sprite& sprite);
    const Sprite* getSprite(const Ogre::String& spriteName) const;
    const SpriteMap& getSprites() const;

    void recalculateInvTextureSize();

    Ogre::Vector2 getInvTextureSize() const;

    bool getIsFlipbook() const;
    void setIsFlipbook(bool isFlipbook);

    void setFlipbookSize(const Ogre::uint32& flipbookSizeX, const Ogre::uint32& flipbookSizeY);

private:
    bool mIsFlipbook;
    Ogre::uint32 mFlipbookSizeX;
    Ogre::uint32 mFlipbookSizeY;
    Ogre::Vector2 mInvTextureSize;
    SpriteMap mSprites;
};

#endif
