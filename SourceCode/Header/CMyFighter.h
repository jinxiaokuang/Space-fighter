#ifndef CMYFIGHTER_H
#define CMYFIGHTER_H

#include <CommonClass.h>
#include "CGameSprite.h"

class CMyFighter : public CGameSprite
{
    public:
        float m_fBulletCreateTime;
        CMyFighter(const char* szName);
        virtual ~CMyFighter();

        float GetVelocityLeft() { return m_fVelocityLeft; }
        void SetVelocityLeft( float val) { m_fVelocityLeft = val; }
        float GetVelocityRight() { return m_fVelocityRight; }
        void SetVelocityRight( float val) { m_fVelocityRight = val; }
        float GetVelocityUp() { return m_fVelocityUp; }
        void SetVelocityUp( float val) { m_fVelocityUp = val; }
        float GetVelocityDown() { return m_fVelocityDown; }
        void SetVelocityDown( float val) { m_fVelocityDown = val; }

        void OnMove(bool bKeyDown,int iKey);
        void OnFile(float fDeltaTime);
        bool GetCanFile() { return m_bCanFile; }
        void SetCanFile(bool val) { m_bCanFile = val; }
        bool IsMyFighter(){return true;}
        void OnColOtherSprite(CGameSprite* pOther);
    protected:

    private:
         float m_fVelocityLeft;
         float m_fVelocityRight;
         float m_fVelocityUp;
         float m_fVelocityDown;
         bool  m_bCanFile;
};

#endif // CMYFIGHTER_H
