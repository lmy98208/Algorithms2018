#ifndef _Node_H
#define _Node_H
#include<iostream>
#include<string>
#include<deque>
#include<vector>
#include<stack>
using namespace std;

class CNode {
public:
	int nine[3][3];//�Ź���
	int parent;//���ڵ㣬���ڵ�ĸ��ڵ�Ϊ-1
	int i;//�հ�������
	int j;//�հ�������
	string step;//����һ�ڵ��ƶ����˽ڵ��������
	int dep;//�ڵ����
	int heuristic;//��������ֵ

	void printNode();//��ӡ�ڵ�
	bool matchNode(CNode &node1,CNode &node2);//ƥ��ڵ�
	bool isExist(deque<CNode> &openStack, vector<CNode> &closedList, CNode& node);//���أ���open��closed���Ƿ���ֹ��˽ڵ�
	int getHeuristic(CNode &node, CNode &des);//�������ֵ�����+����ĸ��ӣ�
	bool existSolution(CNode &start, CNode &end);//�Ƿ���ڽ������
	//ѡ�ҽ������
	bool findSolution(CNode &initilNode,CNode &targetNode, deque<CNode> &openList, vector<CNode> &closedList,string modu);
	void printSolution(bool flag, vector<CNode> &closedList);//��ӡ�������
};

bool isLess(const CNode& node1, const CNode& node2);//�Ƚ�����ֵ

#endif // !_Node_H