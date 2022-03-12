#include "pch.h"
#include "CGameLogic.h"
#include"CGameDlg.h"

CGameLogic::CGameLogic(void)
{
	m_nVexNum = 0;
}

//初始化游戏地图
void CGameLogic::InitMap(int anMap[][4])
{
	int anTemp[4][4] = { 2,0,1,3, 2,2,1,3,2,1,0,0,1,3,0,3 };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			anMap[i][j] = anTemp[i][j];
		}
	}
}

//判断是否连线
bool CGameLogic::IsLink(int anMap[][4], Vertex v1, Vertex v2)
{
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	int nRow1 = v1.row;
	int nRow2 = v2.row;

	AddVertex(v1);

	//一条直线横向连通
	if (nRow1 == nRow2)
	{
		if (LinkInRow(anMap, v1, v2) == true)
		{
			AddVertex(v2);
			return true;
		}
	}

	//一条直线竖向连通
	if (nCol1 == nCol2)
	{
		if (LinkInCol(anMap, v1, v2))
		{
			AddVertex(v2);
			return true;
		}
	}

	//两条直线连通
	if (OneCornerLink(anMap, v1, v2))
	{
		AddVertex(v2);
		return true;
	}

	//三条直线连通
	if (TwoCornerLink(anMap, v1, v2))
	{
		AddVertex(v2);
		return true;
	}

	DeleteVertex();

	return false;
}

//消子
void CGameLogic::Clear(int anMap[][4], Vertex v1, Vertex v2)
{
	anMap[v1.row][v1.col] = BLANK;
	anMap[v2.row][v2.col] = BLANK;
}


//行号相同，判断横向是否连通
bool CGameLogic::LinkInRow(int anMap[][4], Vertex v1, Vertex v2)
{
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	int nRow = v1.row;

	//保证nCol1的值小于nCol2
	if (nCol1 > nCol2)
	{
		//数据交换
		int nTemp = nCol1;
		nCol1 = nCol2;
		nCol2 = nTemp;
	}

	//直通
	for (int i = nCol1 + 1; i <= nCol2; i++)
	{
		if (i == nCol2)
			return true;
		if (anMap[nRow][i] != BLANK)
			break;
	}
	return false;
}

//列号相同，判断竖向是否连通
bool CGameLogic::LinkInCol(int anMap[][4], Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	int nCol = v1.col;

	//保证nRow1的值大于nRow2
	if (nRow1 > nRow2)
	{
		//数据交换
		int nTemp = nRow1;
		nRow1 = nRow2;
		nRow2 = nTemp;
	}

	for (int i = nRow1 + 1; i <= nRow2; i++)
	{
		if (i == nRow2)
			return true;
		if (anMap[i][nCol] != BLANK)
			break;
	}
	return false;
}

//判断同行不同列的两个点是否连通
bool CGameLogic::LineX(int anMap[][4], int nRow, int nCol1, int nCol2)
{
	//判断（nRow,nCol1)到(nRow,nCol2)能否连通
	for (int nCol = nCol1; nCol <= nCol2; nCol++)
	{
		if (anMap[nRow][nCol] != BLANK)
			break;
		if (nCol == nCol2)
			return true;
	}
	return false;
}

//判断同列不同行的两个点能够连通
bool CGameLogic::LineY(int anMap[][4], int nRow1, int nRow2, int nCol)
{
	//判断(nRow1,nCol)到(nRow2,nCol)是否连通
	for (int nRow = nRow1; nRow <= nRow2; nRow++)
	{
		if (anMap[nRow][nCol] != BLANK)
			break;
		if (nRow == nRow2)
			return true;
	}
}

//判断一个拐角是否连通
bool CGameLogic::OneCornerLink(int anMap[][4], Vertex v1, Vertex v2)
{
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	int nRow1 = v1.row;
	int nRow2 = v2.row;

	if (nRow1 > nRow2)   //确保nRow1<nRow2,保证(nRow1,nCon1)始终在(nRow2,nCon2)的上方
	{
		int nTemp;
		nTemp = nRow1;
		nRow1 = nRow2;
		nRow2 = nTemp;

		nTemp = nCol1;
		nCol1 = nCol2;
		nCol2 = nTemp;
	}

	if (nCol2 < nCol1)
	{
		//判断(nRow+1,nCon1)到(nRow2,nCol2+1)能否连通(先下后左)
		if (LineY(anMap, nRow1 + 1, nRow2, nCol1) && LineX(anMap, nRow2, nCol2 + 1, nCol1))
		{
			Vertex v = { nRow2,nCol1,BLANK };
			AddVertex(v);
			return true;
		}
		//判断(nRow2-1,nCon2)到(nRow1,nCol1-1)能否连通(先上后右)
		if (LineY(anMap, nRow2 - 1, nRow1, nCol2) && LineX(anMap, nRow1, nCol2, nCol1 - 1))
		{
			Vertex v = { nRow1,nCol2,BLANK };
			AddVertex(v);
			return true;
		}
	}
	else
	{
		//判断(nRow1+1,nCon1)到(nRow2,nCol2-1能否连通(先下后右)
		if (LineY(anMap, nRow1 + 1, nRow2, nCol1) && LineX(anMap, nRow2, nCol1, nCol2 - 1))
		{
			Vertex v = { nRow2,nCol1,BLANK };
			AddVertex(v);
			return true;
		}
		//判断(nRow2-1,nCon2)到(nRow1,nCol1+1)能否连通(先上后左)
		if (LineY(anMap, nRow2 - 1, nRow1, nCol2) && LineX(anMap, nRow1, nCol2, nCol1 + 1))
		{
			Vertex v = { nRow1,nCol2,BLANK };
			AddVertex(v);
			return true;
		}
	}
	return false;
}

//判断两个拐角能否连通
bool CGameLogic::TwoCornerLink(int anMap[][4], Vertex v1, Vertex v2)
{
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	int nRow1 = v1.row;
	int nRow2 = v2.row;

	bool IsTemp = false;

	if (nRow1 > nRow2)   //确保nRow1<nRow2,保证(nRow1,nCon1)始终在(nRow2,nCon2)的上方
	{
		int nTemp;
		nTemp = nRow1;
		nRow1 = nRow2;
		nRow2 = nTemp;

		nTemp = nCol1;
		nCol1 = nCol2;
		nCol2 = nTemp;

		IsTemp = true;        //表明两个点交换
	}

	if (nCol2 < nCol1)
	{
		//找到一条与Y轴平行的连通直线段
		for (int nCol = 0; nCol < 4; nCol++)
		{
			if (anMap[nRow1][nCol] == BLANK && anMap[nRow2][nCol] == BLANK)
			{
				//判断该条y轴直线是否连通
				if (LineY(anMap, nRow1, nRow2, nCol))
				{
					if (nCol2 > nCol && LineX(anMap, nRow1, nCol - 1, nCol) && LineX(anMap, nRow2, nCol, nCol2 - 1))
					{
						//保存节点
						Vertex Vx1;
						Vertex Vx2;
						Vx1.row = nRow1;
						Vx1.col = nCol;
						Vx2.row = nRow2;
						Vx2.col = nCol;

						if (IsTemp == false)
						{
							AddVertex(Vx1);
							AddVertex(Vx2);
							return true;
						}
						else
						{
							AddVertex(Vx2);
							AddVertex(Vx1);
							return true;
						}
					}
					//连通的直线在选中的两个点的中间
					if (nCol1 > nCol && nCol > nCol2 && LineX(anMap, nRow1, nCol, nCol1 - 1) && LineX(anMap, nRow2, nCol2 + 1, nCol))
					{
						//保存节点
						Vertex Vx1;
						Vertex Vx2;
						Vx1.row = nRow1;
						Vx1.col = nCol;
						Vx2.row = nRow2;
						Vx2.col = nCol;

						if (IsTemp == false)
						{
							AddVertex(Vx1);
							AddVertex(Vx2);
							return true;
						}
						else
						{
							AddVertex(Vx2);
							AddVertex(Vx1);
							return true;
						}
					}
					//连通的直线在选中的两个点的右边
					if (nCol > nCol1 && LineX(anMap, nRow1, nCol1 + 1, nCol) && LineX(anMap, nRow2, nCol, nCol2 + 1))
					{
						//保存节点
						Vertex Vx1;
						Vertex Vx2;
						Vx1.row = nRow1;
						Vx1.col = nCol;
						Vx2.row = nRow2;
						Vx2.col = nCol;

						if (IsTemp == false)
						{
							AddVertex(Vx1);
							AddVertex(Vx2);
							return true;
						}
						else
						{
							AddVertex(Vx2);
							AddVertex(Vx1);
							return true;
						}
					}
				}
			}
		}
	
		//找到一条与X轴平行的连通直线段
		for (int nRow = 0; nRow < 4; nRow++)
		{
			if (anMap[nRow][nCol1] == BLANK && anMap[nRow][nCol2] == BLANK)
			{
				if (LineX(anMap, nRow, nCol1, nCol2)) //判断该条Y轴直线是否连通
				{
					//连通的直线在选中的两个点的上面
					if (nRow1 > nRow && LineY(anMap, nRow1 - 1, nRow, nCol1) && LineY(anMap, nRow, nRow2 - 1, nCol2))
					{
						//保存节点
						Vertex Vx1;
						Vertex Vx2;
						Vx1.row = nRow;
						Vx1.col = nCol1;
						Vx2.row = nRow;
						Vx2.col = nCol2;

						if (IsTemp == false)
						{
							AddVertex(Vx1);
							AddVertex(Vx2);
							return true;
						}
						else
						{
							AddVertex(Vx2);
							AddVertex(Vx1);
							return true;
						}
					}
					//连通的直线在选中的两个点的中间
					if (nRow2 > nRow && nRow > nRow1 && LineY(anMap, nRow1 + 1, nRow, nCol1) && LineY(anMap, nRow, nRow2 - 1, nCol2))
					{
						//保存节点
						Vertex Vx1;
						Vertex Vx2;
						Vx1.row = nRow;
						Vx1.col = nCol1;
						Vx2.row = nRow;
						Vx2.col = nCol2;

						if (IsTemp == false)
						{
							AddVertex(Vx1);
							AddVertex(Vx2);
							return true;
						}
						else
						{
							AddVertex(Vx2);
							AddVertex(Vx1);
							return true;
						}
					}
					//连通的直线在选中的两个点的下面
					if (nRow > nRow2 && LineY(anMap, nRow1 + 1, nRow, nCol1) && LineY(anMap, nRow, nRow2 + 1, nCol2))
					{
						//保存节点
						Vertex Vx1;
						Vertex Vx2;
						Vx1.row = nRow;
						Vx1.col = nCol1;
						Vx2.row = nRow;
						Vx2.col = nCol2;

						if (IsTemp == false)
						{
							AddVertex(Vx1);
							AddVertex(Vx2);
							return true;
						}
						else
						{
							AddVertex(Vx2);
							AddVertex(Vx1);
							return true;
						}
					}
				}
			}
		}
	}
	else
	{
		//找到一条与Y轴平行的连通直线段
		for (int nCol = 0; nCol < 4; nCol++)
		{
			if (anMap[nRow1][nCol] == BLANK && anMap[nRow2][nCol] == BLANK)
			{
				if (LineY(anMap, nRow1, nRow2, nCol)) //判断该条Y轴直线是否连通
				{
					//连通的直线在选中的两个左边
					if (nCol1 > nCol && LineX(anMap, nRow1, nCol1 - 1, nCol) && LineX(anMap, nRow2, nCol, nCol2 - 1))
					{

						//保存节点
						Vertex Vx1;
						Vertex Vx2;
						Vx1.row = nRow1;
						Vx1.col = nCol;
						Vx2.row = nRow2;
						Vx2.col = nCol;

						if (IsTemp == false)
						{
							AddVertex(Vx1);
							AddVertex(Vx2);
							return true;
						}
						else
						{
							AddVertex(Vx2);
							AddVertex(Vx1);
							return true;
						}
					}
					//连通的直线在选中的两个点之间
					if (nCol2 > nCol && nCol > nCol1 && LineX(anMap, nRow1, nCol1 + 1, nCol) && LineX(anMap, nRow2, nCol, nCol2 - 1))
					{
						//保存节点
						Vertex Vx1;
						Vertex Vx2;
						Vx1.row = nRow1;
						Vx1.col = nCol;
						Vx2.row = nRow2;
						Vx2.col = nCol;

						if (IsTemp == false)
						{
							AddVertex(Vx1);
							AddVertex(Vx2);
							return true;
						}
						else
						{
							AddVertex(Vx2);
							AddVertex(Vx1);
							return true;
						}
					}
					//连通的直线在选中的两个点右边
					if (nCol > nCol2 && LineX(anMap, nRow1, nCol1 + 1, nCol) && LineX(anMap, nRow2, nCol, nCol2 + 1))
					{
						//保存节点
						Vertex Vx1;
						Vertex Vx2;
						Vx1.row = nRow1;
						Vx1.col = nCol;
						Vx2.row = nRow2;
						Vx2.col = nCol;

						if (IsTemp == false)
						{
							AddVertex(Vx1);
							AddVertex(Vx2);
							return true;
						}
						else
						{
							AddVertex(Vx2);
							AddVertex(Vx1);
							return true;
						}
					}
				}
			}
		}

		//找到一条与X轴平行的连通直线段
		for (int nRow = 0; nRow < 4; nRow++)
		{
			if (anMap[nRow][nCol1] == BLANK && anMap[nRow][nCol2] == BLANK)
			{
				if (LineX(anMap, nRow, nCol1, nCol2)) //判断该条Y轴直线是否连通
				{
					//连通直线在两个点上面
					if (nRow1 > nRow && LineY(anMap, nRow1 - 1, nRow, nCol1) && LineY(anMap, nRow, nRow2 - 1, nCol2))
					{
						//保存节点
						Vertex Vx1;
						Vertex Vx2;
						Vx1.row = nRow;
						Vx1.col = nCol1;
						Vx2.row = nRow;
						Vx2.col = nCol2;

						if (IsTemp == false)
						{
							AddVertex(Vx1);
							AddVertex(Vx2);
							return true;
						}
						else
						{
							AddVertex(Vx2);
							AddVertex(Vx1);
							return true;
						}
					}
					//连通直线在两个点之间
					if (nRow2 > nRow && nRow > nRow1 && LineY(anMap, nRow1 + 1, nRow, nCol1) && LineY(anMap, nRow, nRow2 - 1, nCol2))
					{
						//保存节点
						Vertex Vx1;
						Vertex Vx2;
						Vx1.row = nRow;
						Vx1.col = nCol1;
						Vx2.row = nRow;
						Vx2.col = nCol2;

						if (IsTemp == false)
						{
							AddVertex(Vx1);
							AddVertex(Vx2);
							return true;
						}
						else
						{
							AddVertex(Vx2);
							AddVertex(Vx1);
							return true;
						}
					}
					//连通直线在两个点下面
					if (nRow > nRow2 && LineY(anMap, nRow1 + 1, nRow, nCol1) && LineY(anMap, nRow, nRow2 + 1, nCol2))
					{
						//保存节点
						Vertex Vx1;
						Vertex Vx2;
						Vx1.row = nRow;
						Vx1.col = nCol1;
						Vx2.row = nRow;
						Vx2.col = nCol2;

						if (IsTemp == false)
						{
							AddVertex(Vx1);
							AddVertex(Vx2);
							return true;
						}
						else
						{
							AddVertex(Vx2);
							AddVertex(Vx1);
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

int CGameLogic::GetVexPath(Vertex avPath[4])
{
	for (int i = 0; i < m_nVexNum; i++)
	{
		avPath[i] = m_avPath[i];
	}
	return m_nVexNum;
}

void CGameLogic::AddVertex(Vertex v)
{
	m_avPath[m_nVexNum] = v;
	m_nVexNum++;
}

void CGameLogic::DeleteVertex()
{
	m_nVexNum--;
}