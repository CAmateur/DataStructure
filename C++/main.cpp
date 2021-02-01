#include"DynamicLineList.h"


int main()
{
	LineList<int> List;
	for (int i = 1; List.ListInsert(i, 2); i++);

	List.PrintList();

	List.IncreaseSize(50);

	for (int i = 1; List.ListInsert(i, 2); i++);

	List.PrintList();
	try {
		List.GetElem(0);
	}
	catch (MyException e)
	{
		printf("%s", e.what());
	}

	LineList<int> List1(List);
	List.PrintList();
	List1.PrintList();


	LineList<int> List2 = List;
	List.PrintList();
	List2.PrintList();



	LineList<int> List3;
	List3 = List;
	List.PrintList();
	List3.PrintList();




	LineList<int> List5(move(List));

	List.PrintList();
	List5.PrintList();

	LineList<int> List4;
	List4 = move(List5);
	List5.PrintList();		
	List4.PrintList();

	cout << List4 << endl;

	//if (Empty(SqList))
	//	printf("List is empty.That indicate the list Init success!\n");


	//if (ListInsert(SqList, 0, 1))
	//	printf("Inserted at place:%d,the number:%d is inserted successfully!\n", 0, 1);
	//else
	//	printf("Inserted at place:%d,the number:%d is inserted failedly!\n", 0, 1);


	//if (ListInsert(SqList, 1, 2))
	//	printf("Inserted at place:%d,the number:%d is inserted successfully!\n", 1, 2);
	//else
	//	printf("Inserted at place:%d,the number:%d is inserted failedly!\n", 1, 2);




	//PrintList(SqList);


	//IncreaseSize(SqList, 2);

	//for (int i = 1; i <= InitSize; i++)
	//	if (ListInsert(SqList, i, i))
	//		printf("Inserted at place:%d,the number:%d is inserted successfully!\n", i, i);
	//	else
	//		printf("Inserted at place:%d,the number:%d is inserted failedly!\n", i, i);

	//if (ListInsert(SqList, 1, 2))
	//	printf("Inserted at place:%d,the number:%d is inserted successfully!\n", 1, 2);
	//else
	//	printf("Inserted at place:%d,the number:%d is inserted failedly!\n", 1, 2);




	//PrintList(SqList);
	//int temp = 0;

	//if (ListDelete(SqList, 1, temp))
	//	printf("Deleted at place:%d,the number:%d is deleted successfully!\n", 1, temp);
	//else
	//	printf("Deleted at place:%d,the number:%d is deleted failedly!\n", 1, temp);

	//PrintList(SqList);

	//if (ListDelete(SqList, 9, temp))
	//	printf("Deleted at place:%d,the number:%d is deleted successfully!\n", 9, temp);
	//else
	//	printf("Deleted at place:%d,the number:%d is deleted failedly!\n", 9, temp);

	//PrintList(SqList);


	return 0;
}