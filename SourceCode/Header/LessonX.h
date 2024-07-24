#ifndef _LESSON_X_H_
#define _LESSON_X_H_
//
#include <Windows.h>
#include <vector>
#include "CMyFighter.h"
#include "CSpriteList.h"
using namespace std;

// ��Ϸ�ܹ��ࡣ��������Ϸ��ѭ������Ϸ��ʼ���������ȹ���
class	CGameMain
{
private:
	int				m_iGameState;
	int             m_iCreatedSpriteCount;
	int             m_iMaxScore;

    CGameSprite* m_pBeginSprite;//�ո�ʼ���顢
	CTextSprite* m_pCurScoreText;//��ʾ��ǰ���֡�
    CTextSprite* m_pMaxScoreText;//��ʾ��߻��֡�

    CMyFighter* m_pMyFighter;

public:
	CGameMain();            //���캯��
	~CGameMain();           //��������
	CEffect* m_pSmallExplosion;
	CEffect* m_pPlayerExplode;
	CEffect* m_penemyExplode;
    CSpriteList     m_SpriteList;
	void            OnKeyUp(const int ikey);
	void            OnKeyDown(const int ikey,const int iAltPress,const int ishiftpress,const int iCtrlPress);
	void            AddSprite(CGameSprite* pSprite);
    // Get����
	int				GetGameState() { return m_iGameState; }
	// Set����
	void			SetGameState(const int iState) { m_iGameState = iState; }
	// ��Ϸ��ѭ����
	void			GameMainLoop(float	fDeltaTime);
	void			GameInit();
	void			GameRun(float fDeltaTime);
	void			GameEnd();
	//��������߽���ײ�������Զ��庯��
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
