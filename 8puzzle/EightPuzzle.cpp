#include"NodeFunction.h"
#include<ctime>

using namespace std;
int main()
{
	/*
	����deque��������������������ջ������
	openջ/���dfs
	open����/���bfs+����
	*/
	deque<CNode> openList;
	vector<CNode> closedList;//closed�б�
	int i, j;	
	clock_t start, end;//����ʱ��
	CNode initilNode, targetNode;//��ʼ�ڵ��Ŀ��ڵ�
	cout << "�������ʼ�ڵ�״̬:";
	
	//˫ѭ������ʼ�ڵ�initiNode��ֵ
	for (i = 0; i<3; i++)
		for (j = 0; j<3; j++)
		{
			cin >> initilNode.nine[i][j];
			if (0 == initilNode.nine[i][j])
			{
				initilNode.i = i;
				initilNode.j = j;
			}
		}
	initilNode.parent = -1;//��ʼ�ڵ�Ϊ���ڵ㣬û�и��ڵ�
	initilNode.dep = 0;//��ʼ�ڵ����Ϊ0


	cout << "������Ŀ��ڵ�״̬:";
	//˫ѭ����Ŀ��ڵ�targetNode��ֵ
	for (i = 0; i<3; i++)
		for (j = 0; j<3; j++)
		{
			cin >> targetNode.nine[i][j];
			//����¼�հ׸����ڵ��к���
			if (0 == targetNode.nine[i][j])
			{
				targetNode.i = i;
				targetNode.j = j;
			}
		}
	targetNode.parent = -1;
	bool flag = true;
	double endtime = 0.0;

	cout << "\n***************������ȣ�***************" << endl;
	start = clock();
	if (initilNode.existSolution(initilNode, targetNode))
		flag = initilNode.findSolution(initilNode, targetNode, openList, closedList, "bfs");
	end = clock();
	endtime = (double)(end - start) / CLOCKS_PER_SEC;
	initilNode.printSolution(flag, closedList);//��ӡ����
	cout << "time:" << endtime * 1000 << "ms" << endl;
	cout << "open:" << openList.size() << "\tclosed:" << closedList.size();

	openList.clear();
	closedList.clear();//���

	cout << "\n***************������ȣ�***************" << endl;
	start = clock();
	flag=initilNode.findSolution(initilNode,targetNode,openList,closedList,"dfs");
	end = clock();
	endtime = (double)(end - start) / CLOCKS_PER_SEC;
	initilNode.printSolution(flag,closedList);//��ӡ����
	cout << "time:" << endtime * 1000 << "ms" << endl;
	cout <<"open:"<< openList.size()<<"\tclosed:" << closedList.size();

	openList.clear();
	closedList.clear();//���

	cout << "\n***************�����㷨��***************" << endl;
	start = clock();
	if (initilNode.existSolution(initilNode, targetNode))
		flag = initilNode.findSolution(initilNode, targetNode, openList, closedList,"heuristic");
	end = clock();
	endtime = (double)(end - start) / CLOCKS_PER_SEC;
	initilNode.printSolution(flag, closedList);//��ӡ����
	cout << "time:" << endtime * 1000 << "ms" << endl;
	cout << "open:" << openList.size() << "\tclosed:" << closedList.size() << endl;
	
	return 0;

}