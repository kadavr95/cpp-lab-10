#include <conio.h>//including input/output libraries
#include <iostream.h>

void OutputMenu();//functions prototypes
int InputArray(int *, int **,bool *);
int OutputArray(int, int *);
int ArithmeticMeanCalculation(int , int *, float *);
int ElementDeletion(int *, int **);
void AboutProgramme();
void ErrorHandler(int);
int InputNumber(int *);

void main()//main function
{
	short OperationCode;//defining variables
	int *Array;
	int ArraySize=0, ErrorCode;
	float ArithmeticMean;
	bool FirstLaunch=true;
	OutputMenu();//show menu of available commands
	while(1)//endless repeat
	{
		OperationCode=getch();//get command
		system("cls");//clear console screen
		ErrorCode=0;//reset error code
		switch (OperationCode)//command choice
		{
			case 49:
				ErrorCode=InputArray(&ArraySize, &Array, &FirstLaunch);//array input
				break;
			case 50:
				ErrorCode=ArithmeticMeanCalculation(ArraySize, Array, &ArithmeticMean);//calculation of arithmetic mean
				break;
			case 51:
				ErrorCode=ElementDeletion(&ArraySize, &Array);//deletion of element preceding the last maximum element
				break;
			case 52:
				ErrorCode=OutputArray(ArraySize, Array);//array output
				break;
			case 53:
				AboutProgramme();//information about the programme
				break;
			default://case of pressing button not assigned to commands
				OutputMenu();//show menu of available commands
		}
		if (ErrorCode!=0)//checking correctness of performed operations
			ErrorHandler(ErrorCode);//show error message
	}
}

void OutputMenu()//show menu of available commands
{
	cout<<"MAIN MENU\n";
	cout<<"Choose operation:\n";
	cout<<"Press 1 to input array\n";
	cout<<"Press 2 to calculate arithmetic mean of array elements\n";
	cout<<"Press 3 to delete element preceding the last maximum element\n";
	cout<<"Press 4 to output array\n";
	cout<<"Press 5 to get info about the program";
}

int InputArray(int *ArraySize, int **Array, bool *FirstLaunch)//array input
{
	int Counter, EnteredNumber, ErrorCode=0;
	cout<<"ARRAY INPUT\n";
	cout<<"Enter quantity of elements in array\n";
	ErrorCode=InputNumber(&EnteredNumber);//input quantity of elements in array
	*ArraySize=EnteredNumber;
	if (*ArraySize<=0)//quantity is zero or below
		return 3;
	if (ErrorCode!=0)//checking correctness of performed operation
		return ErrorCode;
	if (!*FirstLaunch)//checking existance of array
		delete [] *Array;//delete old array
	else
		*FirstLaunch=false;
	*Array=new int[*ArraySize];//create array
	cout<<"\nEnter array elements\n";
	for (Counter = 0; Counter < *ArraySize; Counter++)//input of array elements
	{
		 ErrorCode=InputNumber(&EnteredNumber);
		(*Array)[Counter]=EnteredNumber;
		if (ErrorCode!=0)//checking correctness of performed operations
			return ErrorCode;
	}
	cout<<"\nDone!";
	return 0;
}

int InputNumber(int *EnteredNumber) //number input
{
	int EnteredSymbol, SymbolsQuantity=0;
	bool NegativeValue=false;
	*EnteredNumber=0;//reset number
	while (1)//endless repeat
	{
		EnteredSymbol=getch()-48;//get code of pressed button and bring it to form of number
		if ((EnteredSymbol>=0)&&(EnteredSymbol<=9))//if numbers was pressed
		{
				*EnteredNumber*=10;//increase order of magnitude of previous digits
				*EnteredNumber+=EnteredSymbol;//add new digit
				cout<<EnteredSymbol;//show new digit
				SymbolsQuantity++;//increase quantity of symbols
		}
		else
		{
			if ((EnteredSymbol==-3) && (SymbolsQuantity==0))//first symbol is minus sign
			{
				cout<<(char)45;//show symbol
				NegativeValue=true;//flag what number is now negative
				SymbolsQuantity++;//increase quantity of symbols
			}
			if ((EnteredSymbol==-40)&&(SymbolsQuantity>0))//deleting symbol
			{
				cout<<(char)8;//delete symbol
				cout<<" ";
				cout<<(char)8;
				*EnteredNumber/=10;//decrease entered number
				if ((NegativeValue==true)&&(SymbolsQuantity==1))//delete minus sign
				{
					NegativeValue=false;
				}
				SymbolsQuantity--;//decrease quantity of elements
			}
			if (((EnteredSymbol==-16) || (EnteredSymbol==-35))&& ((SymbolsQuantity>1)||((SymbolsQuantity==1) && (!NegativeValue))))//end of number input
			{
				cout<<(char)32;//show space instead of space and enter
				if (NegativeValue==true)//checking number negativity
					*EnteredNumber*=-1;
				return 0;
			}
		}
	}
}
int OutputArray(int ArraySize, int *Array)//array output
{
	int Counter;
	cout<<"ARRAY OUTPUT\n";
	if (ArraySize>0)//checking what array has been inputed
	{
		cout<<"Array of "<<ArraySize<<" elements\n";//show info about array
		for (Counter = 0; Counter < ArraySize; Counter++)//output array elements
			cout<<Array[Counter]<<" ";
		cout<<"\nDone!";
	}
	else
		return 1;//array has not been inputed
	return 0;
}

int ArithmeticMeanCalculation(int ArraySize, int *Array, float *ArithmeticMean)//calculating of arithmetic mean
{
	int Counter, ElementsSum=0;
	cout<<"ARITHMETIC MEAN CALCULATION\n";
	if (ArraySize>0)//checking what array has been inputed
	{
		for (Counter = 0; Counter < ArraySize; Counter++)//sum all elements
			ElementsSum+=Array[Counter];
		*ArithmeticMean=(float)ElementsSum/ArraySize;//calculate average
		cout<<"Arithmetic mean of array elements is: "<<*ArithmeticMean<<"";
	}
	else
		return 1;//array has not been inputed
	return 0;
}

int ElementDeletion(int *ArraySize, int **Array)//deletion of element preceding the last maximum element
{
	int Counter, MaximumElementIndex, MaximumElement;
	int *ArrayCut;
	cout<<"ELEMENT DELETION\n";
	if (*ArraySize>0)//checking what array has been inputed
	{
		MaximumElementIndex=0;//setting first element as maximum
		MaximumElement=(*Array)[0];
		for (Counter = 1; Counter < *ArraySize; Counter++)//checking all elements
			if ((*Array)[Counter]>=MaximumElement)//replacing maximum elemnt
			{
				MaximumElement=(*Array)[Counter];
				MaximumElementIndex=Counter;
			}
		if (MaximumElementIndex>0)//checking position of first element
		{
			cout<<"Last maximum element is number "<<(MaximumElementIndex+1)<<", with value "<<MaximumElement<<"\n";//show what will be done
			cout<<"Preceding element with value "<<(*Array)[MaximumElementIndex-1]<<" has been removed.";
			(*ArraySize)--;//shrink array size
			MaximumElementIndex--;//get index of element to remove
			ArrayCut=new int[*ArraySize];//new array of less size
			for (Counter = 0; Counter < MaximumElementIndex; Counter++)//move elements before removed element to the new array
				(ArrayCut)[Counter]=(*Array)[Counter];
			for (Counter = MaximumElementIndex; Counter < *ArraySize; Counter++)//move elements after removed element to the new array with shift
			  	(ArrayCut)[Counter]=(*Array)[Counter+1];
			delete [] *Array;//delete old array
			*Array=ArrayCut;//give old array pointer to new array
		}
		else
			return 2;//first element is a maximum
	}
	else
		return 1;//array has not been inputed
	return 0;
}

void AboutProgramme()//show info about the programme
{
	cout<<"ABOUT PROGRAMME\n\n";
	cout<<"Lab 10: Modular programming\n";
	cout<<"Variant 4\n\n";
	cout<<"Version 1.1 build 20160315191800\n\n";
	cout<<"Development and testing: Yaskovich Dmitry (ISBO-05-15)\n\n";
	cout<<"Dimini Inc, 2016";
}

void ErrorHandler(int ErrorCode)//show error message
{
	cout<<"\nError "<<ErrorCode<<"\n";//show error code
	switch (ErrorCode)//show error  description
		{
			case 1:
				cout<<"No array found! Enter array first.";
				break;
			case 2:
				cout<<"The first element of array is the only one maximum. Preceding element can not be deleted.";
				break;
			case 3:
				cout<<"Quantity of elements in array can not be zero or less";
				break;
			default:
				cout<<"Unknown error";
		}
}
