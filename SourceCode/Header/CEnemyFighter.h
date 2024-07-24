#ifndef CENEMYFIGHTER_H
#define CENEMYFIGHTER_H
#include <CommonClass.h>
#include "CGameSprite.h"

class CEnemyFighter : public CGameSprite
{
    public:
        CEnemyFighter(const char* szName);
        virtual ~CEnemyFighter();

        static float GetCreateTime() { return m_fCreateTime; }
        static int Getm_iCreatedSpriteCount() { return m_iCreatedSpriteCount; }
        void static ClassTick ( float fDeltaTime );
        void LoopTick(float fDeltatime);
        void OnColOtherSprite(CGameSprite* pOther);
    protected:

    private:
        static float m_fCreateTime;
        static int m_iCreatedSpriteCount;
        float m_fCanFileAfterCreated;
        float m_fBulletCreateTime;
        float m_fFloatTime;
        bool  m_bFloatUp;
};

#endif // CENEMYFIGHTER_H
