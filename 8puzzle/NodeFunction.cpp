#include "NodeFunction.h"
#include <algorithm>//sortͷ�ļ�

#define MAXDEP 5
/*����ڵ�*/
void CNode::printNode()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			cout <<"\t"<< nine[i][j];
		cout << endl;
	}
}
/*ƥ��ڵ�*/
bool CNode::matchNode(CNode & node1, CNode & node2)
{
	int i, j;
	bool result = true;
	for (i = 0; i<3; i++)
		for (j = 0; j<3; j++)
		{
			if (node1.nine[i][j] != node2.nine[i][j])
			{
				result = false;
				break;
			}

		}
	return result;
}
/*����*/
bool CNode::isExist(deque<CNode> &openStack, vector<CNode>& closedList, CNode &node)
{
	bool result = false;
	deque<CNode>::iterator qit = openStack.begin();
	vector<CNode>::iterator vit = closedList.begin();
	CNode temp;
	while (qit != openStack.end())
	{
		if (temp.matchNode(*qit++, node))
		{
			result = true;
			break;
		}
	}
	while (vit != closedList.end())
	{
		if (temp.matchNode(*vit++, node))
		{
			result = true;
			break;
		}
	}

	return result;
}
/*��ȡ����ֵ�����+��Ŀ��ڵ㲻ͬ�����ָ���*/
int CNode::getHeuristic(CNode& node, CNode &des)
{
	int i, j;
	int result = 0;
	for (i = 0; i<3; i++)
		for (j = 0; j<3; j++)
		{
			if (node.nine[i][j] != des.nine[i][j])
				result++;
		}
	return result+node.dep;
}
/*�ж����ҵ�·��*/
bool CNode::existSolution(CNode & start, CNode & end)
{
	bool result = false;
	int i, j, count1 = 0, count2 = 0;
	int a[3 * 3];
	int b[3 * 3];
	for (i = 0; i<3; i++)
		for (j = 0; j<3; j++)
		{
			if (start.nine[i][j] != 0)
				a[count1++] = start.nine[i][j];
			if (end.nine[i][j] != 0)
				b[count2++] = end.nine[i][j];
		}
	int rsum = 0, tsum = 0;
	for (i = 0; i<8; i++)
		for (j = 0; j<i; j++)
		{
			if (a[j]<a[i])
				rsum++;
			if (b[j]<b[i])
				tsum++;
		}
	if (rsum % 2 == tsum % 2)
		result = true;
	return result;
}

bool CNode::findSolution(CNode &initilNode, CNode &targetNode, deque<CNode> &openList, vector<CNode> &closedList,string modu)
{
	int parent = -1;//parentָʾ���ڵ��±�
	bool flag = false;//�����־
	openList.push_back(initilNode);//��ʼ�ڵ���ջ������
									//�������
	CNode temp;
	while ((!openList.empty()) && (!flag))//��open��Ϊ�ջ�û���ҵ�Ŀ��ڵ�ʱ
	{
		if (modu == "dfs") {//�������ʱ��open��ջ��
			temp = openList.back();//open���нڵ㸳����ʱ�ڵ�temp
			openList.pop_back();//ջ���ڵ��վ
		}
		//������Ⱥ�����ʱ��open��������	
		else if (modu == "bfs" || modu == "heuristic") {//������Ⱥ�����ʱ��open��������
			temp = openList.front();//ȡ����ֵ��С�Ľڵ�
			openList.pop_front();
		}

		closedList.push_back(temp);//tempѹ��close����
		parent = closedList.size() - 1;

		if (temp.matchNode(temp, targetNode))//�ж���ʱ�ڵ�temp��Ŀ��ڵ�targetNode�Ƿ�һ��
		{
			flag = true;//һ���򽫽����־��Ϊtrue
			break;//����ѭ��
		}

		//���������ʱ��Ȳ����������� �� ������� �� ����ʱ
		if ((modu=="dfs"&&temp.dep < MAXDEP)||modu=="bfs"||modu=="heuristic")
		{
			if (temp.j>0)//�հ׸������в�Ϊ0�������ƶ�
			{
				CNode left = temp;
				left.nine[temp.i][temp.j] = left.nine[temp.i][temp.j - 1];
				left.nine[temp.i][temp.j - 1] = 0;//Ԫ�ؽ���
				left.parent = parent;
				left.i = temp.i;
				left.j = temp.j - 1;
				left.step = "��";
				if (!temp.isExist(openList, closedList, left))//�жϽڵ��Ƿ����
				{
					if (modu == "heuristic") {//����ģʽʱ ��Ҫ������Ⱥ�����ֵ
						left.dep++;
						left.heuristic = getHeuristic(left, targetNode);
					}
					else if (modu=="dfs")//�������ʱ����¼���
						left.dep++;//����չ�Ľڵ����+1
					openList.push_back(left);//����ģʽ��Ҫѹ��open��
				}			
			}
			if (temp.i>0)//�հ׸������в�Ϊ0�������ƶ�
			{
				CNode up = temp;
				up.nine[temp.i][temp.j] = up.nine[temp.i - 1][temp.j];
				up.nine[temp.i - 1][temp.j] = 0;//Ԫ�ؽ���
				up.parent = parent;
				up.i = temp.i - 1;
				up.j = temp.j;
				up.step = "��";
				if (!temp.isExist(openList, closedList, up))//�жϽڵ��Ƿ����
				{
					if (modu == "heuristic") {//����ģʽʱ ��Ҫ������Ⱥ�����ֵ
						up.dep++;
						up.heuristic = getHeuristic(up, targetNode);
					}
					else if (modu == "dfs")//�������ʱ����¼���
						up.dep++;//����չ�Ľڵ����+1
					openList.push_back(up);//����ģʽ��Ҫѹ��open��
				}
			}
			if (temp.j<2)//�հ׸������в�Ϊ2�������ƶ�
			{
				CNode right = temp;
				right.nine[temp.i][temp.j] = right.nine[temp.i][temp.j + 1];
				right.nine[temp.i][temp.j + 1] = 0;
				right.parent = parent;
				right.i = temp.i;
				right.j = temp.j + 1;
				right.step = "��";
				if (!temp.isExist(openList, closedList, right))//�жϽڵ��Ƿ����
				{
					if (modu == "heuristic") {//����ģʽʱ ��Ҫ������Ⱥ�����ֵ
						right.dep++;
						right.heuristic = getHeuristic(right, targetNode);
					}
					else if (modu == "dfs")//�������ʱ����¼���
						right.dep++;//����չ�Ľڵ����+1
					openList.push_back(right);//ѹ��open��
				}	
			}
			if (temp.i < 2)//�հ׸������в�Ϊ2�������ƶ�
			{
				CNode down = temp;
				down.nine[temp.i][temp.j] = down.nine[temp.i + 1][temp.j];
				down.nine[temp.i + 1][temp.j] = 0;
				down.parent = parent;
				down.i = temp.i + 1;
				down.j = temp.j;
				down.step = "��";
				if (!temp.isExist(openList, closedList, down))//�жϽڵ��Ƿ����
				{
					if (modu == "heuristic") {//����ģʽʱ ��Ҫ������Ⱥ�����ֵ
						down.dep++;
						down.heuristic = getHeuristic(down, targetNode);
					}
					else if (modu == "dfs")//�������ʱ����¼���
						down.dep++;//����չ�Ľڵ����+1
					openList.push_back(down);//ѹ��open��
				}
			}
			if(modu=="heuristic")//����ģʽ�£������а���������ֵ�Ĵ�С��С�����Ŷ�
				sort(openList.begin(), openList.end(), isLess);//����,��������
		}
	}
	return flag;
}

void CNode::printSolution(bool flag, vector<CNode> &closedList)
{
	stack<CNode> movepath;
	if (!flag)//�޷����Ŀ��ڵ�
	{
		cout << "�޷��ӳ�ʼ�ڵ��ƶ���Ŀ��ڵ�" << endl;
	}
	else//�����ƶ���Ŀ��ڵ㣬�����н�
	{
		CNode last = closedList.back();//�����ڵ��ظ�ָ��������
		while (last.parent != -1)
		{
			movepath.push(last);//�Ƚ����
			last = closedList[last.parent];
		}
		cout << "Ŀ��ɽ�,�ƶ���������:" << endl;
		string step;
		cout << "������" << movepath.size() << endl;
		while (!movepath.empty())
		{
			step = movepath.top().step;
			//movepath.top().printNode();
			cout << step ;
			movepath.pop();
		}
		cout << endl;
	}
}

bool isLess(const CNode & node1, const CNode & node2)
{
	return node1.heuristic<node2.heuristic;
}