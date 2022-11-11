/*
 * File: HlmsJsonParticleAtlas.cpp
 * Author: Przemysław Bągard
 * Created: 2021-5-15
 *
 */

#if !OGRE_NO_JSON

#include "GpuParticles/Hlms/HlmsJsonParticleAtlas.h"

#include "rapidjson/document.h"

#include <OgreTextureGpu.h>

HlmsJsonParticleAtlas::HlmsJsonParticleAtlas(Ogre::HlmsManager* hlmsManager,
                                             Ogre::TextureGpuManager* textureManager)
    : mHlmsManager( hlmsManager )
    , mTextureManager( textureManager )
{

}

void HlmsJsonParticleAtlas::loadMaterial(const rapidjson::Value& json,
                                         const Ogre::HlmsJson::NamedBlocks& blocks,
                                         Ogre::HlmsDatablock* datablock,
                                         const Ogre::String& resourceGroup)
{
    assert(dynamic_cast<HlmsParticleDatablock*>(datablock));
    HlmsParticleDatablock* particleDatablock = static_cast<HlmsParticleDatablock*>(datablock);

    rapidjson::Value::ConstMemberIterator itor = json.FindMember("atlas");
    if( itor != json.MemberEnd() && itor->value.IsObject() )
    {
        const rapidjson::Value &subobj = itor->value;
        loadAtlas( subobj, blocks, particleDatablock, resourceGroup );

//        itor = subobj.FindMember( "value" );
//        if( itor != subobj.MemberEnd() && itor->value.IsNumber() )
//            particleDatablock->setNormalMapWeight( static_cast<float>( itor->value.GetDouble() ) );
    }
    else {
        itor = json.FindMember("flipbook");
        if( itor != json.MemberEnd() && itor->value.IsArray() )
        {
            const rapidjson::Value &subobj = itor->value;
            loadFlipbook(subobj, blocks, particleDatablock, resourceGroup );
        }
    }

    particleDatablock->recalculateInvTextureSize();

//    rapidjson::Value::ConstMemberIterator itor = json.FindMember("atlas");
//    if (itor != json.MemberEnd() && itor->value.IsArray())
//    {
//        const rapidjson::Value& array = itor->value;
//        const rapidjson::SizeType arraySize = std::min(4u, array.Size());
//        ColourValue col;
//        for (rapidjson::SizeType i = 0; i<arraySize; ++i)
//        {
//            if (array[i].IsNumber())
//                col[i] = static_cast<float>(array[i].GetDouble());
//        }
//        unlitDatablock->setUseColour(true);
//        unlitDatablock->setColour(col);
//    }

}

void HlmsJsonParticleAtlas::loadAtlas(const rapidjson::Value& json,
                                      const Ogre::HlmsJson::NamedBlocks& blocks,
                                      HlmsParticleDatablock* datablock,
                                      const Ogre::String& resourceGroup)
{
    for (rapidjson::Value::ConstMemberIterator itor = json.MemberBegin(); itor != json.MemberEnd(); ++itor) {
        if (!itor->value.IsArray()) {
            continue;
        }

        const rapidjson::Value& array = itor->value;
        if(array.Size() != 4) {
            continue;
        }

        Ogre::String spriteName = itor->name.GetString();

        HlmsParticleDatablock::Sprite sprite;
        sprite.mLeft = static_cast<int>(array[0].GetInt());
        sprite.mBottom = static_cast<int>(array[1].GetInt());
        sprite.mSizeX = static_cast<int>(array[2].GetInt());
        sprite.mSizeY = static_cast<int>(array[3].GetInt());

        datablock->addSprite(spriteName, sprite);
    }
}

void HlmsJsonParticleAtlas::loadFlipbook(const rapidjson::Value& json,
                                         const Ogre::HlmsJson::NamedBlocks& blocks,
                                         HlmsParticleDatablock* datablock,
                                         const Ogre::String& resourceGroup)
{
    const rapidjson::Value& rowArray = json;
    size_t rowCount = rowArray.Size();
    size_t colCount = 0;

    for (size_t iRow = 0; iRow < rowArray.Size(); ++iRow) {
        if(!rowArray[iRow].IsArray()) {
            continue;
        }

        const rapidjson::Value& elementsArray = rowArray[iRow];
        for (size_t iCol = 0; iCol < elementsArray.Size(); ++iCol) {
            Ogre::String spriteName = elementsArray[iCol].GetString();

            if(spriteName == "") {
                continue;
            }

            HlmsParticleDatablock::Sprite sprite;
            sprite.mFlipbookX = iCol;
            sprite.mFlipbookY = iRow;
            datablock->addSprite(spriteName, sprite);
        }

        if(colCount < elementsArray.Size()) {
            colCount = elementsArray.Size();
        }
    }

    datablock->setIsFlipbook(true);
    datablock->setFlipbookSize(colCount, rowCount);
}


void HlmsJsonParticleAtlas::saveMaterial(const Ogre::HlmsDatablock* datablock,
                                         Ogre::String& outString)
{

}

#endif
