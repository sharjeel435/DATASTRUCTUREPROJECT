#include<iostream>
#include<fstream>
#include<Windows.h>
#include<string.h>
#include<sstream>
using namespace std;
int MenuOption;
bool check = true;
int PageDataLimit = 10;
int PageLimit = 5;

void OpenMenu();
void CloseProgram();
void BackMenu();

void PageOptions();

class Productnode 
{
public:
	char ProductName[100];
	int ProductPrice;
	int ProductQuantity;
	int ExpiryDay, ExpiryMonth, ExpiryYear;

	Productnode* next;

	Productnode() 
	{
		next = NULL;
	}

	char* getProductName() 
	{
		return ProductName;
	}

	void setProductName(string ProductName) 
	{
		strncpy(this->ProductName, ProductName.c_str(), 100);
	}

	Productnode(string Name, int Price, int Quantity, int Day, int Month, int Year, Productnode* nextValue) 
	{
		setProductName(Name);
		//	ProductName = Name;
		ProductPrice = Price;
		ProductQuantity = Quantity;
		ExpiryDay = Day;
		ExpiryMonth = Month;
		ExpiryYear = Year;
		next = NULL;//nextValue;
	}

};

class Employeenode 
{
public:
	char EmmployeeAddress[100];
	char EmployeeName[100];
	int EmployeeNumber, EmployeeAge, EmployeePhone;

	Employeenode* next;

	void setName(string EmployeeName) 
	{
		strncpy(this->EmployeeName, EmployeeName.c_str(), 100);
	}

	void setAddress(string EmmployeeAddress) 
	{
		strncpy(this->EmmployeeAddress, EmmployeeAddress.c_str(), 100);
	}

	char* getName() 
	{
		return EmployeeName;
	}

	char* getAddress() 
	{
		return EmmployeeAddress;
	}

	Employeenode() 
	{
		next = NULL;
	}

	Employeenode(string Name, string Address, int Number, int Age, int Phone, Employeenode* nextValue) 
	{
		setName(Name);
		setAddress(Address);
		EmployeeNumber = Number;
		EmployeeAge = Age;
		EmployeePhone = Phone;
		next = NULL;//nextValue;
	}

};

int CurrentProductPage = 1;

class ProductPagesNode 
{
private:
	int CurrentData = 0;
	Productnode** ProductData;

public:

	int Num;
	ProductPagesNode* next;
	ProductPagesNode* prev;

	ProductPagesNode() 
	{
		ProductData = new Productnode * [PageDataLimit];
	}
//priority-queue<int,vector<int> > pq;


	ProductPagesNode(int val) 
	{
		Num = val;
		next = NULL;
		prev = NULL;
	}

	bool InsertData(Productnode* NewData) 
	{
		if (CurrentData != PageDataLimit) 
		{
			ProductData[CurrentData] = NewData;
			CurrentData += 1;
			return true;
		}
		if (CurrentProductPage != PageLimit) 
		{
			PageLimit += 1;
			return false;
		}
		cout << "Product Pages Full!";
	}

	void Display() 
	{
		system("cls");
		
		cout << "\nNAME\t\tPRICE\t\tQUANTITY\t\tEXPIRY DATE\n";
		for (int i = 0; i < CurrentData; i++) 
		{
			cout << ProductData[i]->ProductName << "\t\t" << ProductData[i]->ProductPrice << "\t\t" << ProductData[i]->ProductQuantity << "\t\t\t" << ProductData[i]->ExpiryDay << "/" << ProductData[i]->ExpiryMonth << "/" << ProductData[i]->ExpiryYear << endl;
		}
		
		cout << "\nPage: " << CurrentProductPage;
		
		PageOptions();
	}
};

//PagesNode *ProductPages = new PagesNode(5);
ProductPagesNode ProductPages[5];

void PageOptions() 
{
	FurtherOptions:
		cout << "\n\n1: Next Page \n2: Previous Page \n0: Return To Menu \n";
		cin >> MenuOption;
	
		//system("cls");
	
		if (MenuOption == 1)
		{
			if (CurrentProductPage == PageLimit)
			{
				cout << "\nThis is the Last page, you can't go further.";
				goto FurtherOptions;
			}
			CurrentProductPage += 1;
			ProductPages[CurrentProductPage].Display();
		}
		else if (MenuOption == 2)
		{
			if (CurrentProductPage == 1)
			{
				cout << "\nThis is the first page, you can't go back.";
				goto FurtherOptions;
			}
			CurrentProductPage -= 1;
			ProductPages[CurrentProductPage].Display();
		}
		else if (MenuOption == 0) 
		{
			OpenMenu();
		}
		else 
		{
			cout << "\nInvalid Option!\a";
			goto FurtherOptions;
		}
}


void HideCursor() 
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void fordelay(int j) 
{
	int i, k;
	for (i = 0; i < j; i++)
		k = i;
}

fstream EmpFile;
Employeenode NewEmployee;

fstream StockFile;
Productnode NewProduct;

fstream InvoiceFile;
Productnode InvoiceReport;


void AscendingPrice(Productnode* head) 
{
	Productnode* i, * j;
	int temp_data;
	for (i = head; i->next != NULL; i = i->next)
	{
		for (j = i->next; j != NULL; j = j->next)
		{
			if (i->ProductPrice > j->ProductPrice)
			{

				temp_data = j->ProductPrice;

				j->ProductPrice = i->ProductPrice;
				i->ProductPrice = temp_data;

			}
		}
	}
	Productnode* temp = head;

	system("cls");
	cout << "\t\t\tPRODUCT RECORDS";
	cout << "\n\nNAME\t\tPRICE\t\tQUANTITY\t\tEXPIRY DATE\n";

	while (temp != NULL) 
	{
		cout << temp->ProductName << "\t\t" << temp->ProductPrice << "\t\t" << temp->ProductQuantity << "\t\t\t" << temp->ExpiryDay << "/" << temp->ExpiryMonth << "/" << temp->ExpiryYear << endl;
		temp = temp->next;
	}
}

void DescendingPrice(Productnode* head) 
{
	Productnode* i, * j;
	int temp_data;
	for (i = head; i->next != NULL; i = i->next)
	{
		for (j = i->next; j != NULL; j = j->next)
		{
			if (i->ProductPrice < j->ProductPrice)
			{
				temp_data = j->ProductPrice;

				j->ProductPrice = i->ProductPrice;
				i->ProductPrice = temp_data;

			}
		}
	}
	Productnode* temp = head;

	system("cls");
	cout << "\t\t\tPRODUCT RECORDS";
	cout << "\n\nNAME\t\tPRICE\t\tQUANTITY\t\tEXPIRY DATE\n";

	while (temp != NULL) 
	{
		cout << temp->ProductName << "\t\t" << temp->ProductPrice << "\t\t" << temp->ProductQuantity << "\t\t\t" << temp->ExpiryDay << "/" << temp->ExpiryMonth << "/" << temp->ExpiryYear << endl;
		temp = temp->next;
	}
}

void DefaultSort(Productnode* head) 
{
	Productnode* temp = head;

	system("cls");
	cout << "\t\t\tPRODUCT RECORDS";
	cout << "\n\nNAME\t\tPRICE\t\tQUANTITY\t\tEXPIRY DATE\n";

	while (temp != NULL) 
	{
		cout << temp->ProductName << "\t\t" << temp->ProductPrice << "\t\t" << temp->ProductQuantity << "\t\t\t" << temp->ExpiryDay << "/" << temp->ExpiryMonth << "/" << temp->ExpiryYear << endl;
		temp = temp->next;
	}
}

void DefaultEmployeeSort(Employeenode* head) 
{
	Employeenode* temp = head;

	system("cls");
	cout << "\t\t\tEMPLOYEE RECORDS";
	cout << "\n\nNUMBER\t\tNAME\t\tAGE\t\tADDRESS\t\tPHONE\n";

	while (temp != NULL) 
	{
		cout << temp->EmployeeNumber << "\t\t" << temp->EmployeeName << "\t\t" << temp->EmployeeAge << "\t\t" << temp->EmmployeeAddress << "\t\t" << temp->EmployeePhone << endl;
		temp = temp->next;
	}
}

void ViewProducts(Productnode* head) 
{

	cout << "\n\n\t\t1.Sort Products by Price (Low to High)\n\t\t2.Sort Products by Price (High to Low)\n\t\t3.Default Sorting\n\t\t4.View as Pages\n\nPlease Enter your choice: ";
	cin >> MenuOption;

	switch (MenuOption) 
	{

	case 1:AscendingPrice(head);
		break;

	case 2:DescendingPrice(head);
		break;

	case 3:DefaultSort(head);
		break;
	
	case 4:ProductPages[CurrentProductPage].Display();
		break;
	}

	BackMenu();
}

void ViewEmployee(Employeenode* head) 
{
	
	DefaultEmployeeSort(head);

	BackMenu();
}

void AddProduct(Productnode*& head) 
{

	Productnode* NewProd = new Productnode;
	Productnode* temp = head;

	char PName[100];


StockOptions:
	system("cls");

	cout << "\t\t\t ADD NEW STOCK RECORD  ";
	cout << "\n\nPlease Enter Product Name: ";


	cin >> PName;

	while (temp != NULL) 
	{
		if ((strcmp(PName, temp->getProductName())) == 0) {
			cout << "This Product already exists! Please enter a new name!";
			Sleep(1000);
			goto StockOptions;
		}
		temp = temp->next;
	}

	fflush(stdin);

	NewProd->setProductName(PName);

	cout << "\nEnter Product Price: ";
	cin >> NewProd->ProductPrice;

	fflush(stdin);

	cout << "\nEnter Product Quantity: ";
	cin >> NewProd->ProductQuantity;

	fflush(stdin);

	cout << "\nEnter Product Expiry Day: ";
	cin >> NewProd->ExpiryDay;

	fflush(stdin);

	cout << "\nEnter Product Expiry Month: ";
	cin >> NewProd->ExpiryMonth;

	cout << "\nEnter Product Expiry Year: ";
	cin >> NewProd->ExpiryYear;

	if (head == NULL) 
	{
		head = NewProd;
	}
	else 
	{
		temp = head;

		while (temp->next != NULL) 
		{
			temp = temp->next;
		}

		temp->next = NewProd;
	}

	bool Success = ProductPages[CurrentProductPage].InsertData(NewProd);

	if (Success == false) 
	{
		CurrentProductPage += 1;
		Success = ProductPages[CurrentProductPage].InsertData(NewProd);
	}

	cout << "\n\n****STOCK HAS BEEN ADDED SUCCESSFULLY****";

	BackMenu();
}

void AddEmployee(Employeenode*& head) 
{

	Employeenode* NewEmp = new Employeenode;
	Employeenode* temp = head;

	char EName[100];

EmployeeOptions:
	system("cls");

	cout << "\t\t\t REGISTER NEW EMPOYEE ";
	fflush(stdin);
	cout << "\n\nPlease Enter the account Name of Employee:";

	cin.getline(EName, 50);

	while (temp != NULL) 
	{
		if ((strcmp(EName, temp->getName())) == 0) 
		{
			cout << "This Employeee already exists! Please enter a new employee name!";
			Sleep(1000);
			goto EmployeeOptions;
		}
    temp = temp->next;
	}

	fflush(stdin);

	NewEmp->setName(EName);
	string EAddress;

	cout << "\nEnter Employee Number: ";
	cin >> NewEmp->EmployeeNumber;

	fflush(stdin);

	cout << "\nEnter Employee Age: ";
	cin >> NewEmp->EmployeeAge;

	fflush(stdin);

	cout << "\nEnter Employee Phone Number: ";
	cin >> NewEmp->EmployeePhone;

	fflush(stdin);

	cout << "\nEnter Employee Address: ";
	cin >> EAddress;
	NewEmp->setAddress(EAddress);

	if (head == NULL)
		head = NewEmp;
	else 
	{
		temp = head;

		while (temp->next != NULL) 
		{
			temp = temp->next;
		}

		temp->next = NewEmp;
	}

	//	bool Success = ProductPages[CurrentProductPage].InsertData(NewProd);
	//
	//	if (Success == false) {
	//		CurrentProductPage += 1;
	//		Success = ProductPages[CurrentProductPage].InsertData(NewProd);
	//	}

		//ProductPages[CurrentProductPage].Display();

	cout << "\n\n****EMPLOYEE HAS BEEN ADDED SUCCESSFULLY****";
	//	getchar();
	BackMenu();

}

void UpdateProduct(Productnode*& head) 
{

	Productnode* temp = head;

	bool Found = false;

	char PName[100];

	cout << "\nEnter the Product Name that you want to update: ";
	cin >> PName;

	while (temp != NULL && Found == false) 
	{
		if ((strcmp(PName, temp->getProductName()) == 0)) 
		{
			system("cls");

			cout << PName << " Current Details: ";
			cout << "\n\nName: "<< temp->getProductName();
			cout << "\nPrice: "<< temp->ProductPrice;
			cout << "\nQuantity: " <<  temp->ProductQuantity;
			cout << "\nExpiry Date: "<< temp->ExpiryDay << "/" << temp->ExpiryMonth <<"/"<< temp->ExpiryYear;

			string PItemName;

			cout << "\n\nEnter the New Name: ";
			cin >> PItemName;
			temp->setProductName(PItemName);

			cout << "Enter the New Price: ";
			cin >> temp->ProductPrice;

			cout << "Enter the New Quantity: ";
			cin >> temp->ProductQuantity;

			cout << "Enter the New Expiry Day: ";
			cin >> temp->ExpiryDay;

			cout << "Enter the New Expiry Month: ";
			cin >> temp->ExpiryMonth;

			cout << "Enter the New Expiry Year: ";
			cin >> temp->ExpiryYear;

			Found = true;

			system("cls");
			cout << "\n\n\nChanges saved!";

		}

		temp = temp->next;

	}

	if (Found == false) 
	{
		system("cls");
		cout << "\nITEM RECORDS NOT FOUND!\a\a\a";
		Sleep(100000);
	}

	cout << "\n****RECORD UPDATED SUCCESSFULLY****";
	//	getchar();	
	BackMenu();

}

void DeleteProduct(Productnode*& head) 
{

	char name[100];
	cout<<"Enter a Product name to delete: \n";
	cin>>name;
	Productnode * temp = NULL;
    Productnode * prevptr = head;
	Productnode * currentptr = head->next ;
	if(strcmp(head->getProductName(),name)==0){
		head=head->next;
		cout<<"Product has been deleted successfully!";
	}
	else
	{
																										
	while(currentptr !=NULL)
	{
			if ((strcmp(name,currentptr->getProductName()))==0){
				cout<< "Product has been deleted successfully!";
				temp = currentptr -> next;
				prevptr->next=temp;
				delete currentptr;
				break;      	
			}
			else
			{
				prevptr = prevptr -> next;
	            currentptr = currentptr -> next;		
			}
		}
		
	}
	cout << "\n****PRODUCT RECORD DELETED SUCCESSFULLY****";
	BackMenu();
}

void DeleteEmployee(Employeenode* &head)
{
	char name[100];
	cout<<"Enter a Employee name to delete: \n";
	cin>>name;
	Employeenode * temp = NULL;
    Employeenode * prevptr = head;
	Employeenode * currentptr = head->next ;
	if(strcmp(head->getName(),name)==0)
	{
		head=head->next;
		cout<<"Employee has been deleted successfully!";
	}
	else
	{
																										
	while(currentptr !=NULL)
	{
			if ((strcmp(name,currentptr->getName()))==0){
				cout<<"Employee has been deleted successfully!";
				temp = currentptr -> next;
				prevptr->next=temp;
				delete currentptr;
				break;      	
			}
			else
			{
				prevptr = prevptr -> next;
	            currentptr = currentptr -> next;		
			}
		}
		
	}
	cout << "\n****EMPLOYEE RECORD DELETED SUCCESSFULLY****";
	BackMenu();
}

void SearchProduct(Productnode*& head) 
{

	system("cls");

	if (head == NULL) 
	{
		cout << "No Products Exist";
		return;
	}

	Productnode* temp = head;

	bool Found = false;

	char PName[100];

	cout << "\nEnter the Product Name to search: ";
	cin >> PName;

	while (temp != NULL && Found == false) 
	{
		if ((strcmp(PName, temp->getProductName()) == 0)) 
		{
			Found = true;
			break;
		}
		temp = temp->next;
	}

	if (Found == false) 
	{
		cout << "RECORD NOT FOUND !";
		BackMenu();
	}
	
	cout << "\n Product Name: ";
	cout << temp->ProductName;

	cout << "\n Product Price: ";
	cout << temp->ProductPrice;

	cout << "\n Product Quantity: ";
	cout << temp->ProductQuantity;

	cout << "\n Product Expiry Day/Date/Month: ";
	cout << temp->ExpiryDay; 
	cout << "/" << temp->ExpiryMonth;
	cout << "/" << temp->ExpiryYear;

	BackMenu();
}
//END OF SEARCH PRODUCT FUNCTION

//START OF SEARCH EMPLOYEE FUNCTION
void SearchEmployee(Employeenode*& head)
{

	system("cls");

	if (head == NULL) 
	{
		cout << "No Employees Exist";
		return;
	}

	Employeenode* temp = head;

	bool Found = false;

	char EName[100];

	cout << "\nEnter the Employee Name to search: ";
	cin >> EName;

	while (temp != NULL && Found == false) 
	{
		if ((strcmp(EName, temp->getName()) == 0)) {
			Found = true;
			break;
		}
		temp = temp->next;
	}

	if (Found == false) 
	{
		cout << "RECORD NOT FOUND !";
		BackMenu();
	}

	cout << "\n Employee Number:- ";
	cout << temp->EmployeeNumber;

	cout << "\n Employee Name:- ";
	cout << temp->EmployeeName;

	cout << "\n Employee Age:- ";
	cout << temp->EmployeeAge;

	cout << "\n Employee Address:- ";
	cout << temp->EmmployeeAddress;

	cout << "\n Employee Phone Number:- ";
	cout << temp->EmployeePhone;

	BackMenu();
}
//END OF SEARCH EMPLOYEE FUNCTION

void LoadData(Productnode*& head, Employeenode*& Ehead) 
{

	StockFile.open("StockRecord.txt", ios::in);

	while (StockFile.read((char*)&NewProduct, sizeof(NewProduct))) 
	{
		Productnode* NewProd = new Productnode(NewProduct.getProductName(), NewProduct.ProductPrice, NewProduct.ProductQuantity, NewProduct.ExpiryDay, NewProduct.ExpiryMonth, NewProduct.ExpiryYear, NewProduct.next);
		if (head == NULL) 
		{
			head = NewProd;
		}
		else 
		{
			Productnode* temp = head;

			while (temp->next != NULL) 
			{
				temp = temp->next;
			}

			temp->next = NewProd;
		}
		
		bool Success = ProductPages[CurrentProductPage].InsertData(NewProd);

		if (Success == false) 
		{
			CurrentProductPage += 1;
			Success = ProductPages[CurrentProductPage].InsertData(NewProd);
		}
	}

	StockFile.close();

	Employeenode* Etemp = Ehead;
	EmpFile.open("EmployeeRecord.txt", ios::in);

	while (EmpFile.read((char*)&NewEmployee, sizeof(NewEmployee)))
	{
		Employeenode* NewEmp = new Employeenode(NewEmployee.getName(), NewEmployee.getAddress(), NewEmployee.EmployeeNumber, NewEmployee.EmployeeAge, NewEmployee.EmployeePhone, NewEmployee.next);
		if (Ehead == NULL) 
		{
			Ehead = NewEmp;
		}
		else 
		{
			Employeenode* Etemp = Ehead;
	
			while (Etemp->next != NULL) 
			{
				Etemp = Etemp->next;
			}
	
			Etemp->next = NewEmp;
		}
	}
	EmpFile.close();

}

void SaveData(Productnode* head, Employeenode* Ehead) 
{
	Productnode* temp = head;

	StockFile.open("StockRecord.txt",ios::out);
	StockFile.close();
	
	StockFile.open("StockRecord.txt", ios::out | ios::app);

	while (temp != NULL) {
		NewProduct.setProductName(temp->ProductName);
		NewProduct.ProductPrice = temp->ProductPrice;
		NewProduct.ProductQuantity = temp->ProductQuantity;
		NewProduct.ExpiryDay = temp->ExpiryDay;
		NewProduct.ExpiryMonth = temp->ExpiryMonth;
		NewProduct.ExpiryYear = temp->ExpiryYear;
		NewProduct.next = temp->next;
		StockFile.write((char*)&NewProduct, sizeof(Productnode));
		temp = temp->next;
	}

	StockFile.close();

	Employeenode* Etemp = Ehead;

	EmpFile.open("EmployeeRecord.txt",ios::out);
	EmpFile.close();
	
	EmpFile.open("EmployeeRecord.txt", ios::out | ios::app);

	while (Etemp != NULL) 
	{
		NewEmployee.setName(Etemp->EmployeeName);
		NewEmployee.setAddress(Etemp->EmmployeeAddress);
		NewEmployee.EmployeeNumber = Etemp->EmployeeNumber;
		NewEmployee.EmployeeAge = Etemp->EmployeeAge;
		NewEmployee.EmployeePhone = Etemp->EmployeePhone;
		NewEmployee.next = Etemp->next;
		EmpFile.write((char*)&NewEmployee, sizeof(Employeenode));
		Etemp = Etemp->next;
	}

	EmpFile.close();


}

void Transaction(Productnode* head)
{
  int option;
  float TotalPrice = 0;
  int Count = 0;
  char ItemName[100];
  int Quantity;
  int NumItem = 0;
  bool Found = false;
  bool CheckFile = false;
  
  cout<<"\n\t\tGENERATE TRANSACTION [ENTER END TO COMPLETE THE TRANSACTION]";
 // cout<<"\n Enter End To Generate Invoice!";
  
  int SetQuantity;
  
  remove("InvoiceFile.txt");
  
  while(((strcmp(ItemName,"End"))!=0))
  {
    StockFile.open("StockRecord.txt",ios::in|ios::out);
    InvoiceFile.open("InvoiceFile.txt",ios::out|ios::app);
    
    CheckFile = false;
    
    cout<<"\n\nName of item: ";
    cin >> ItemName;
    
    if (((strcmp(ItemName,"End")) == 0)){
    		break;
		}
    
    SetQuantity = 0;
    
    int Day, Month, Year;
    
    cout << "\n\t\t\tENTER TRANSACTION DETAILS";
		cout << "\nEnter Today Day: ";
    	cin >> Day;
    
		cout << "Enter Today Month: ";
    	cin >> Month;
		
		cout << "Enter Today Year: ";
    	cin >> Year;	
    
    while(StockFile.read((char*)&NewProduct,sizeof(NewProduct)))
    {
    	if ((strcmp(ItemName,NewProduct.getProductName())) == 0)
		{
       			
       			CheckFile = true;
       			
       			cout << "Enter the Quantity of Item: ";
       				
       			EnterQuantity:
    				cin>>Quantity;
       			
       				if ((Quantity <= NewProduct.ProductQuantity) && (Quantity > 0))
					   {
       					
						SetQuantity = NewProduct.ProductQuantity - Quantity;
						
						Productnode* temp = head;
					
						while (temp != NULL) 
						{
							if ((strcmp(ItemName, temp->getProductName()) == 0)) 
							{
								temp->ProductQuantity = SetQuantity;
							}
							temp = temp->next;
						}
						
       					NewProduct.ProductQuantity = SetQuantity;
       			}
					   else
					   {
					   	int ch;
					   	if (NewProduct.ProductQuantity == 0)
					   		cout << "Sorry, the stock for this product has finished!";
						else
							cout<<"Quantity is invalid:- ";
        				
						cout<<"\nPress 1 to return to Menu ";
        				cin>>ch;
        				
        				if(ch == 1)
        				{
        					BackMenu();
        					break;
						}
				      					
					}
       			
       			TotalPrice += NewProduct.ProductPrice * Quantity;
    			InvoiceReport.setProductName(NewProduct.getProductName());
    			InvoiceReport.ProductPrice = NewProduct.ProductPrice;
    			InvoiceReport.ProductQuantity = Quantity;
    			InvoiceReport.ExpiryDay = NewProduct.ExpiryDay;
    			InvoiceReport.ExpiryMonth = NewProduct.ExpiryMonth;
    			InvoiceReport.ExpiryYear = NewProduct.ExpiryYear;
    				
    			int Position = -1*sizeof(NewProduct);
				StockFile.seekp(Position,ios::cur);
				StockFile.write((char*)&NewProduct,sizeof(Productnode));
				
				InvoiceFile.write((char*)&InvoiceReport,sizeof(Productnode));
				Found = true;
				
				InvoiceFile.close();
				StockFile.close();
			}
		}
    
    	if (CheckFile == false)
			cout << "Item doesn't exist in the Database! Enter a new item!";
			break;
	}
	InvoiceFile.close();
	StockFile.close();

    if(Found == false){ 
		system("cls");
        cout<<"\nITEM RECORDS NOT FOUND!\a\a\a";
        Sleep(100000);
        BackMenu();
   	}
	
    cout<<"\n\n\t\t\t CUSTOMER INVOICE";
	
	int i;
    
    InvoiceFile.open("InvoiceFile.txt",ios::in);
	
	cout<<"\n\nNAME\t\tPRICE\t\tQUANTITY\t\tEXPIRY DATE\n";

	while(InvoiceFile.read((char*)&InvoiceReport,sizeof(Productnode))){
  		cout << InvoiceReport.getProductName() << "\t\t"<< InvoiceReport.ProductPrice << "\t\t" << InvoiceReport.ProductQuantity << "\t\t\t" << InvoiceReport.ExpiryDay << "/" << InvoiceReport.ExpiryMonth <<"/"<< InvoiceReport.ExpiryYear;
    }
		
	printf("\n\n\t\tTotal Price: %f",TotalPrice);
	
	BackMenu();
	
}

void DisplayNode(Productnode* head) 
{

	Productnode* temp = head;

	cout << "NULL <--> ";

	while (temp != NULL) 
	{
		cout << temp->ProductName << " --> ";
		temp = temp->next;
	}

	cout << "NULL" << endl;

}

void CloseProgram() 
{
	printf("\n\n\n\nLogged Off!");
}

const int T_S = 200;
class HashTableEntry 
{
public:
	int k;
	int v;
	HashTableEntry(int k, int v) 
	{
		this->k = k;
		this->v = v;
	}
};
class HashMapTable 
{
private:
	HashTableEntry** t;
public:
	HashMapTable() {
		t = new HashTableEntry * [T_S];
		for (int i = 0; i < T_S; i++) 
		{
			t[i] = NULL;
		}
	}
	int HashFunc(int k) 
	{
		return k % T_S;
	}
	void Insert(int k, int v) 
	{
		int h = HashFunc(k);
		while (t[h] != NULL && t[h]->k != k) 
		{
			h = HashFunc(h + 1);
		}
		if (t[h] != NULL)
			delete t[h];
		t[h] = new HashTableEntry(k, v);
	}
	int SearchKey(int k) 
	{
		int h = HashFunc(k);
		while (t[h] != NULL && t[h]->k != k) 
		{
			h = HashFunc(h + 1);
		}
		if (t[h] == NULL)
			return -1;
		else
			return t[h]->v;
	}
};


Productnode* Phead = NULL;
Employeenode* Ehead = NULL;

void BackMenu() 
{
FutherOptions:
	cout << "\n\n1: Main Menu \n0: Exit \n";
	cin >> MenuOption;

	system("cls");

	if (MenuOption == 1)
		OpenMenu(); //menu
	else if (MenuOption == 0) 
	{
		SaveData(Phead, Ehead);
		CloseProgram(); //close	
	}
	else 
	{
		cout << "\nInvalid Option!\a";
		goto FutherOptions;
	}

}

void OpenMenu() 
{


	int MenuOption;

	system("cls");
	system("color 2");

	cout << "\n\n\t\t\t\t CHILL MARKET MANAGEMENT";

	cout << "\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2";
	cout << "\n\n\t\t1.Add Product\n\t\t2.Add Employee\n\t\t3.View Products\n\t\t4.View Employees\n\t\t5.Update A Product\n\t\t6.Delete A Product\n\t\t7.Delete A Employee\n\t\t8.Transaction\n\t\t9.Search Product\n\t\t10.Search Employee\n\t\t11.Exit Program\n\nPlease Enter your choice: ";

	cin >> MenuOption;

	system("cls");

	switch (MenuOption) 
	{

	case 1:AddProduct(Phead);
		break;

	case 2:AddEmployee(Ehead);
		break;

	case 3:ViewProducts(Phead);//SearchProduct(Phead, root);
		break;

	case 4:ViewEmployee(Ehead);//SearchEmployee(Ehead);
		break;

	case 5:UpdateProduct(Phead);
		break;

	case 6:DeleteProduct(Phead);
		break;
      
	case 7:DeleteEmployee(Ehead);
		break;
		
   	case 8:
   		SaveData(Phead, Ehead);
	   	Transaction(Phead);
		break;   
	
	case 9:SearchProduct(Phead);
		break;
		
	case 10:SearchEmployee(Ehead);
		break;
		
	case 11:
		SaveData(Phead, Ehead);
		CloseProgram();
		break;
	}
}

int main() 
{

	HideCursor();
	system("Color 9");

	int GetPass;
	int Password = 12345;
	char Password2[20] = "E";

	HashMapTable hash;

	hash.Insert(Password, Password);
pass:
	cout << "\n\n\t\t\t******* SHARJEEL TULAIB SUHAIB INVENTORY AND MARKETING SYSTEM *******";
	cout << "\n\n\t\t\t----------------------------";
	cout << "\n\n\t\t\tEnter the Password to login: ";
	cin >> GetPass;
	cout << "\n\n\t\t\t----------------------------";

	if (hash.SearchKey(GetPass) == Password) {//(strcmp(GetPass, Password1) == 0) {

		cout << "\n\n\n\t\t\t   ^^^Password Match!^^^\n\n\n\t\t\tLOADING";

		LoadData(Phead, Ehead);

		int i;

		for (i = 0; i <= 6; i++) 
		{
			fordelay(100000000);
			printf(".");
		}

		system("cls");
		OpenMenu();
	}
	else 
	{
		cout << "\n\n\t\t\t**Error: Invalid Password!**\a\a\a";

		goto pass;
	}
	return 0;
}
