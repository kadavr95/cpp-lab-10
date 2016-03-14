#include <conio.h>
#include <iostream.h>

void OutputMenu();
int InputArray(int *ArraySize, int **Array);
int OutputArray(int ArraySize, int *Array);
int ArithmeticMeanCalculation(int ArraySize, int *Array, float *ArithmeticMean);
int ElementDeletion(int *ArraySize, int **Array);
void AboutProgramme();
void ErrorHandler(int ErrorCode);
int InputNumber(int *EnteredNumber);

void main()
{
	short OperationCode;
	int *Array;
	int ArraySize=0, ErrorCode;
	float ArithmeticMean;
	OutputMenu();
	while(1)
	{
		OperationCode=getch();
		system("cls");
		ErrorCode=0;
		switch (OperationCode)
		{
			case 49:
				ErrorCode=InputArray(&ArraySize, &Array);
				break;
			case 50:
				ErrorCode=ArithmeticMeanCalculation(ArraySize, Array, &ArithmeticMean);
				break;
			case 51:
				ErrorCode=ElementDeletion(&ArraySize, &Array);
				break;
			case 52:
				ErrorCode=OutputArray(ArraySize, Array);
				break;
			case 53:
				AboutProgramme();
				break;
			default:
				OutputMenu();
		}
		if (ErrorCode!=0)
		{
			ErrorHandler(ErrorCode);
		}
	}
}

void OutputMenu()
{
	cout<<"MAIN MENU\n";
	cout<<"Choose operation:\n";
	cout<<"Press 1 to input array\n";
	cout<<"Press 2 to calculate arithmetic mean of array elements\n";
	cout<<"Press 3 to delete element preceding the last maximum element\n";
	cout<<"Press 4 to output array\n";
	cout<<"Press 5 to get info about the program\n\n";
}

int InputArray(int *ArraySize, int **Array)
{
	int Counter, EnteredNumber, ErrorCode=0;
	cout<<"ARRAY INPUT\n";
	cout<<"Enter quantity of elements in array\n";
	ErrorCode=InputNumber(&EnteredNumber);
	*ArraySize=EnteredNumber;
	if (ErrorCode!=0)
	{
		return ErrorCode;
	}
	//delete [] *Array;
	*Array=new int[*ArraySize];
	cout<<"\nEnter array elements\n";
	for (Counter = 0; Counter < *ArraySize; Counter++)
	{
		 ErrorCode=InputNumber(&EnteredNumber);
		(*Array)[Counter]=EnteredNumber;
		if (ErrorCode!=0)
		{
			return ErrorCode;
		}
	}
	cout<<"\nDone!\n\n";
	return 0;


}

int InputNumber(int *EnteredNumber)
{
	int EnteredSymbol;
	bool ExitCondition=false, NegativeValue=true;
	*EnteredNumber=0;
	while (ExitCondition==false)
	{

		EnteredSymbol=getch()-48;
		if ((EnteredSymbol>=0)&&(EnteredSymbol<=9))
		{
				*EnteredNumber*=10;
				*EnteredNumber+=EnteredSymbol;
				cout<<EnteredSymbol;

				NegativeValue=false;
		}
		else
		{
			if ((EnteredSymbol==-3) && (NegativeValue))
			{
				cout<<(char)45;
				NegativeValue=false;
			}
			if ((EnteredSymbol==-16) || (EnteredSymbol==-35))
			{
				cout<<(char)32;
				return 0;
			}
		}
	}
}
int OutputArray(int ArraySize, int *Array)
{
	int Counter;
	cout<<"ARRAY OUTPUT\n";
	if (ArraySize>0)
	{
		cout<<"Array of "<<ArraySize<<" elements\n";
		for (Counter = 0; Counter < ArraySize; Counter++)
		{
			cout<<Array[Counter]<<" ";
		}
		cout<<"\nDone!\n\n";
	}
	else
		return 1;
	return 0;
}

int ArithmeticMeanCalculation(int ArraySize, int *Array, float *ArithmeticMean)
{
	int Counter, ElementsSum=0;
	cout<<"ARITHMETIC MEAN CALCULATION\n";
	if (ArraySize>0)
	{
		for (Counter = 0; Counter < ArraySize; Counter++)
		{
			ElementsSum+=Array[Counter];
		}
		*ArithmeticMean=(float)ElementsSum/ArraySize;
		cout<<"Arithmetic mean of array elements is: "<<*ArithmeticMean;
	}
	else
		return 1;
	return 0;
}

int ElementDeletion(int *ArraySize, int **Array)
{
	int Counter, MaximumElementIndex, MaximumElement;
	int *ArrayCut;
	cout<<"ELEMENT DELETION\n";
	if (*ArraySize>0)
	{
		MaximumElementIndex=0;
		MaximumElement=(*Array)[0];
		for (Counter = 1; Counter < *ArraySize; Counter++)
		{
			if ((*Array)[Counter]>=MaximumElement)
			{
				MaximumElement=(*Array)[Counter];
				MaximumElementIndex=Counter;
			}
		}
		if (MaximumElementIndex>0)
		{
			cout<<"Last maximum element is number "<<(MaximumElementIndex+1)<<", with value "<<MaximumElement<<"\n";
			cout<<"Preceding element with value "<<(*Array)[MaximumElementIndex-1]<<" has been removed.\n";
			(*ArraySize)--;
			MaximumElementIndex--;
			ArrayCut=new int[*ArraySize];
			for (Counter = 0; Counter < MaximumElementIndex; Counter++)
			{
				(ArrayCut)[Counter]=(*Array)[Counter];
			}
			for (Counter = MaximumElementIndex; Counter < *ArraySize; Counter++)
			{
			  (ArrayCut)[Counter]=(*Array)[Counter+1];
			}
			delete [] *Array;
			*Array=ArrayCut;
		}
		else
			return 2;
	}
	else
		return 1;
	return 0;
}

void AboutProgramme()
{
	cout<<"ABOUT PROGRAMME\n\n";
	cout<<"Lab 10: Modular programming\n";
	cout<<"Variant 4\n\n";
	cout<<"Version 1.0 build 20160313200000\n\n";
	cout<<"Development and testing: Yaskovich Dmitry (ISBO-05-15)\n\n";
	cout<<"Dimini Inc, 2016\n\n";
}

void ErrorHandler(int ErrorCode)
{
	cout<<"\nError "<<ErrorCode<<"\n";
	switch (ErrorCode)
		{
			case 1:
				cout<<"No array found! Enter array first.";
				break;
			case 2:
				cout<<"The first element of array is the only one maximum. Preceding element can not be deleted.";
				break;
			default:
				cout<<"Unknown error";
		}
}
