#include <iostream>

#include "definitions.h"



#include "app.h"


using namespace std;


/*
* file format
*
*
*/



/*
�������
1 ���������� � ����������
	������ �������� ��������� � ���������� ����������
2 ������
3 �����
4 ������� ���������� ����������� ���������� ����� ��������->boolean
5 ������� ���������� ��������:
   �������� � ���������� � �������� ��������� �����


���������
1 ����� �����
2 ���������� � ��������� :
	������ �������� ��������� � ���������� ����������
3 ������
4 �����
5 add �����
6 sub �����
*/


int main()
{
	App app;
	app.print_logo();
	app.print_contributors();
	app.print_version();

	while (app.menu());
	//app.

}