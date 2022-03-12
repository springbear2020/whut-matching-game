#include "pch.h"
#include "CGameControl.h"

//开始游戏
void CGameControl::StartGame(void)
{
	CGameLogic gameLogic;
	gameLogic.InitMap(m_anMap);
}

//返回元素信息
int CGameControl::GetElement(int nRow, int nCol)
{
	return m_anMap[nRow][nCol];
}

//设置第一个点
void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_svSelFirst.row = nRow;
	m_svSelFirst.col = nCol;
}

//设置第二个点
void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_svSelSec.row = nRow;
	m_svSelSec.col = nCol;
}

//连线
bool CGameControl::Link(Vertex avPath[2])
{
	//判断两次选中的是否是同一个点
	if (m_svSelFirst.row == m_svSelSec.row && m_svSelFirst.col == m_svSelSec.col)
	{
		return false;
	}

	//判断两次选择的图片是否相同图片
	if (m_anMap[m_svSelFirst.row][m_svSelFirst.col] != m_anMap[m_svSelSec.row][m_svSelSec.col])
	{
		return false;
	}

	//判断是否连通
	CGameLogic logic;
	if (logic.IsLink(m_anMap, m_svSelFirst, m_svSelSec))
	{
		//消子
		logic.Clear(m_anMap, m_svSelFirst, m_svSelSec);

		//返回路径顶点
		avPath[0] = m_svSelFirst;
		avPath[1] = m_svSelSec;
		return true;
	} 
	return false;
}