#ifndef _LESSON_X_H_
#define _LESSON_X_H_
//
#include <Windows.h>
#include <vector>
#include "CMyFighter.h"
#include "CSpriteList.h"
using namespace std;

// 游戏总管类。负责处理游戏主循环、游戏初始化、结束等工作
class	CGameMain
{
private:
	int				m_iGameState;
	int             m_iCreatedSpriteCount;
	int             m_iMaxScore;

    CGameSprite* m_pBeginSprite;//空格开始精灵、
	CTextSprite* m_pCurScoreText;//显示当前积分·
    CTextSprite* m_pMaxScoreText;//显示最高积分·

    CMyFighter* m_pMyFighter;

public:
	CGameMain();            //构造函数
	~CGameMain();           //析构函数
	CEffect* m_pSmallExplosion;
	CEffect* m_pPlayerExplode;
	CEffect* m_penemyExplode;
    CSpriteList     m_SpriteList;
	void            OnKeyUp(const int ikey);
	void            OnKeyDown(const int ikey,const int iAltPress,const int ishiftpress,const int iCtrlPress);
	void            AddSprite(CGameSprite* pSprite);
    // Get方法
	int				GetGameState() { return m_iGameState; }
	// Set方法
	void			SetGameState(const int iState) { m_iGameState = iState; }
	// 游戏主循环等
	void			GameMainLoop(float	fDeltaTime);
	void			GameInit();
	void			GameRun(float fDeltaTime);
	void			GameEnd();
	//处理世界边界碰撞，建立自定义函数
	void            OnSpriteColWorldLimit(const char* szName, const int iColSide);
    void            CreateBullet(int iType,const float fPosX,const float fPosY);
    CGameSprite* GetSprite(const int ilndex);
    CGameSprite* GetSprite(const char* szName);
    CMyFighter*  GetMyFighter();
    bool            IsMyFighter(const char* szName);
    bool            IsGameLost();
    void            OnSpriteColSprite(const char* szSrcName,const char* szTarName);
};

//
extern CGameMain	g_GameMain;

#endif // _LESSON_X_H_
