#ifndef CBULLET_H
#define CBULLET_H

#include <CommonClass.h>
#include "CGameSprite.h"

class CBullet : public CGameSprite
{
    public:
        CBullet(const int iType,const char* szName);
        virtual ~CBullet();
        bool IsMyBullet();
        void OnColOtherSprite(CGameSprite* pOther);
    protected:

    private:
       int m_iType;
};

#endif // CBULLET_H
