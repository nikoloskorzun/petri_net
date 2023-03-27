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
переход
1 соединение с состоянием
	массив индексов состояний и количество соединений
2 индекс
3 текст
4 функция показывает возможность выполнения этого перкхода->boolean
5 функция выболнения перехода:
   отнимает и прибавляет у связаных состояний фишки


состояние
1 число меток
2 соединение с переходом :
	массив индексов переходов и количество соединений
3 индекс
4 текст
5 add фишка
6 sub фишка
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