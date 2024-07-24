#ifndef CGAMESPRITE_H
#define CGAMESPRITE_H

#include <CommonClass.h>


class CGameSprite : public CSprite
{
    public:
         int m_iHp;
         int m_iDamage;
         int m_iScore;
         int m_iType;
         CGameSprite(const char* szName);
         virtual ~CGameSprite();

         int GetHp() { return m_iHp; }
         void SetHp( int val) { m_iHp = val; }
         int GetDamage() { return m_iDamage; }
         void SetDamage( int val) { m_iDamage = val; }
         int GetScore() { return m_iScore; }
         void SetScore( int val) { m_iScore = val; }
         int GetType() { return m_iType; }
         void SetType( int val) { m_iType = val; }
         bool IsDead()
         {
             return (GetHp()<=0);
         }
         virtual bool IsMyBullet(){return false;}
         virtual bool IsMyFighter(){return false;}
         virtual void OnColOtherSprite(CGameSprite* pOther);
    protected:

    private:
};

#endif // CGAMESPRITE_H
