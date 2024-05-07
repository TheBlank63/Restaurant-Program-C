#include <stdio.h>
#include <string.h>
#include <time.h>

/********************************************
Course: DCP5101 Program Design
Assignment: 1
Session: T2215

Group Name: Depression Gang

ID & Name 1: YAP HOONG HEY, 1221202641
Phone,Email: 0143474011, yaphoonghey@gmail.com

ID & Name 2: CHAN ZHI CHUNG, 1221202813
Phone,Email: 01156592989, chanzhichung101@gmail.com

ID & Name 3: SHERRY BINTI HASAN, 1221202670
Phone,Email: 01111711967, xiaqinouo@gmail.com

ID & Name 4: NUR QAMARINA BINTI MOHD ZAINI, 1221202571
Phone,Email: 0193557032, nqamarinazni@gmail.com


********************************************/

//Food Prices
const double triBurg = 23.90, softT = 17.90, chicBurit = 19.00, beefNacho = 17.00, chicR = 14.90, wonton = 12.90, snsChic = 14.90, bNoodlesp = 12.90, nsLemakfc = 23.90, nsKerabu = 17.90, aMskMrh = 17.90, nsAyKunyit = 17.90;

//Drink Prices
const double tTarik = 3.00, tO = 2.50, sirap = 4.00, sirapB = 5.50, milo = 3.00, barli = 3.00, orangeJ = 7.00,wmelonJ = 7.00, appleJ = 7.00, sDrink = 2.50, mWater = 1.90, ice = 0.90;

//Set Prices
const double set1 = 14.00, set2 = 25.00, set3 = 35.00, set4 = 29.00, set5 = 18.00;



struct Food{
	
	int ordernum = 0, ordertotal = 0;
	char name[30], couponCode[30];
	double total = 0, totalnett, discount, discountamount;

};

struct FoodList{
	
	int quantity;
	char itemName[50];
	double price;
};

void welcomeScreen();
void menuFood();
void interfaceSelection();
void interfaceAddmore();
//Menu and Welcome Screen

void receipt(int count, struct Food custDetails[]);
void orderFood(struct FoodList list[], struct Food custDetails[], int count);
void show_total(int count, struct FoodList list[], struct Food custDetails[]);
void couponFnc(struct Food custDetails[], int count);
void applyDiscount(struct Food custDetails[], int count);
void customer_Sales_Data(struct Food custDetails[], struct FoodList list[], int count);
void receipt(struct Food custDetails[], struct FoodList list[], int count);
void generate_receipt_history(struct Food custDetails[], int count, char choice);

int main()
{
	FILE *fwrite;
	
	fwrite = fopen("receipt_history.txt", "w");
	fclose(fwrite);

	welcomeScreen();

	int count = 0;
	
	struct Food custDetails[200];
	struct FoodList list[100];
	
	char choice, coupon, conReceipt, password[17];
	// Choice for while loop, coupon (Y/N) , Receipt Confirmation (Y/N)
	
	printf("Start Order? (Y/N) : ");
	scanf("%c", &choice);
	fflush(stdin);
	
	while(choice == 'Y' || choice == 'y')
	{
	printf("\nCustomer name : ");
	gets(custDetails[count].name);
	
	custDetails[count].ordernum = count+1;
		
	orderFood(list, custDetails, count);
	
	show_total(count, list, custDetails);
	
	couponFnc(custDetails, count);
	fflush(stdin);
	
	receipt(custDetails, list, count);
			
	
	printf("\nContinue? (Y/N) :");
	scanf("%c", &choice);
	fflush(stdin);
	do
	{
		if(choice != 'Y')
		{
		printf("\n\nEnter Admin Password to End.\n\nEnter Password : ");
		gets(password);
		fflush(stdin);
			if(strcmp(password, "password")==0)
			{
				break;
			}
			else
			{
				printf("Type 'N' to re-enter Password, type 'Y' to Continue Sales.\nChoice : ");
				scanf("%c", &choice);
				fflush(stdin);				
			}
		}	
	}while(choice != 'Y' );
	++count;
	}
	
	customer_Sales_Data(custDetails, list, count);
	
	printf("\n\nSales Data and Receipt History has been Generated.\nPlease extract before running the program again.\n\n");
	return 0;
}
void welcomeScreen()
{
	printf("=========================================================\n");
	printf("          WELCOME TO SIR LEE THE BEST SDN BHD!\n");
	printf("=========================================================\n");
}

void interfaceSelection() // General
{
	printf("\n 1. Order Food\n");
	printf(" 2. Order Drinks\n");
	printf(" 3. Set Meals\n");
	
	printf("\n99. End Order\n");
	// printf("\n4. Cancel Order\n");
}

void interfaceAddmore()
{
	printf("\n1. Add More?\n\n");
	printf("0. Back to Selections\n");
}
void menuFood(int choice)
{
	FILE *fp;
	
	fp = fopen("foodmenu.txt", "r");
	
	if(choice == 1)
	{
		if( fp != NULL)
		{
			char c;
			while( (c = fgetc(fp)) != EOF )
				putchar(c);
			
			fclose(fp);
			printf("\n\n");
		}
		else 
		{
			printf("Error opening file. \n");
		
		}
	}	
	
	
	else if(choice == 2)
	{
	FILE *fh;
			
	fh = fopen("drinksmenu.txt", "r");	
		if( fh != NULL)
		{
			char c;
			while( (c = fgetc(fh)) != EOF )
				putchar(c);
			
			fclose(fh);
			printf("\n\n");
		}
		else 
		{
			printf("Error opening file. \n");
			
		}
	}
	
	else if(choice == 3)
	{
	FILE *fc;
	
	fc = fopen("setmenu.txt", "r");
		if( fc != NULL)
		{
			char c;
			while( (c = fgetc(fc)) != EOF )
				putchar(c);
			
			fclose(fc);
			printf("\n\n");	
		}
		else 
		{
			printf("Error opening file. \n");
		
			
		}
	}
	
}
void hot_or_cold()
{
	printf("\n1. Hot\n");
	
	printf("2. Cold\n\n");
}
void orderFood(struct FoodList list[], struct Food custDetails[], int count)
{
	int count2 = 0, interfacechoice = 0, fChoice, selectMenu, hotorcold;
	
	printf("\n");
	
	while(interfacechoice == 0)
	{
	interfaceSelection();
	//input of Choice
	printf("\nEnter choice: ");
	scanf("%d", &interfacechoice);
	fflush(stdin);
	
	if(interfacechoice == 99)	
		break;
	else if(interfacechoice >=4 || interfacechoice == 0)
	{
		while(interfacechoice >=4 || interfacechoice == 0)
		{
		interfaceSelection();
		printf("\nInvalid choice.\nPlease re-enter Choice: ");
		scanf("%d", &interfacechoice);
		fflush(stdin);
		if(interfacechoice == 99)	
		break;
		}
		if(interfacechoice == 99)	
		break;
	}
	
		do
		{
			// selectMenu = interfacechoice;
			
			if(interfacechoice == 1)
			{
				menuFood(interfacechoice);
				
				printf("Enter Food of Choice : ");
				scanf("%d", &fChoice);
				fflush(stdin);
				
				switch(fChoice){
				case 101:
				strcpy(list[count2].itemName, "Triple Decker Burger");
				list[count2].price = triBurg;
				break;
				
				case 102:
				strcpy(list[count2].itemName, "Soft Tacos");
				list[count2].price = softT;
				break;
				
				case 103:
				strcpy(list[count2].itemName, "Chicken Burrito");
				list[count2].price = chicBurit;
				break;
				
				case 104:
				strcpy(list[count2].itemName, "Beef Nachos");
				list[count2].price = beefNacho;
				break;
				
				case 105:
				strcpy(list[count2].itemName, "Signature Chicken Rice");
				list[count2].price = chicR;
				break;
				
				case 106:
				strcpy(list[count2].itemName, "Wanton Egg Noodles");
				list[count2].price = wonton;
				break;
				
				case 107:
				strcpy(list[count2].itemName, "Sweet and Sour Chicken w Rice");
				list[count2].price = snsChic;
				break;
				
				case 108:
				strcpy(list[count2].itemName, "Beef Noodle Soup");
				list[count2].price = bNoodlesp;
				break;
				
				case 109:
				strcpy(list[count2].itemName, "Nasi Lemak w Fried Chicken");
				list[count2].price = nsLemakfc;
				break;
				
				case 110:
				strcpy(list[count2].itemName, "Nasi Kerabu");
				list[count2].price = nsKerabu;
				break;
				
				case 111:
				strcpy(list[count2].itemName, "Ayam Masak Merah w Rice");
				list[count2].price = aMskMrh;
				break;
				
				case 112:
				strcpy(list[count2].itemName, "Ayam Kunyit w Rice");
				list[count2].price = nsAyKunyit;
				break;
				default:
				printf("\nInvalid Food Code. Please Try Again.\n");
				--count2;
				break;
				
				}
				
			}
			else if(interfacechoice == 2)
			{
				
			
				menuFood(interfacechoice);
				
				printf("Enter Drinks of Choice : ");
				scanf("%d", &fChoice);
				fflush(stdin);
				if(fChoice >= 201 && fChoice <= 211)
				{
				hot_or_cold();
				printf("Choice: ");
				scanf("%d", &hotorcold);
					while(hotorcold == 0 || hotorcold >= 3)
						{
							hot_or_cold();
							printf("Invalid Choice.\n\n");
							printf("Please re-enter choice:");
							scanf("%d", &hotorcold);
						}
					
				}
				
				switch(fChoice)
				{
				case 201:
				if(hotorcold == 1)
				strcpy(list[count2].itemName, "Teh Tarik (Hot)");
				else
				strcpy(list[count2].itemName, "Teh Tarik (Ice)");
				list[count2].price = tTarik;
				break;
				
				case 202:
				if(hotorcold == 1)
				strcpy(list[count2].itemName, "Teh O  (Hot)");
				else
				strcpy(list[count2].itemName, "Teh O (Ice)");
				list[count2].price = tO;
				break;
				
				case 203:
				if(hotorcold == 1)
				strcpy(list[count2].itemName, "Sirap (Hot)");
				else
				strcpy(list[count2].itemName, "Sirap (Ice)");
				list[count2].price = sirap;
				break;
				
				case 204:
				if(hotorcold == 1)
				strcpy(list[count2].itemName, "Sirap Bandung (Hot)");
				else
				strcpy(list[count2].itemName, "Sirap Bandung (Ice)");
				list[count2].price = sirapB;
				break;
				
				case 205:
				if(hotorcold == 1)
				strcpy(list[count2].itemName, "Milo (Hot)");
				else
				strcpy(list[count2].itemName, "Milo (Ice)");
				list[count2].price = milo;
				break;
				
				case 206:
				if(hotorcold == 1)
				strcpy(list[count2].itemName, "Barli (Hot)");
				else
				strcpy(list[count2].itemName, "Barli (Ice)");
				list[count2].price = barli;
				break;
				
				case 207:
				if(hotorcold == 1)
				strcpy(list[count2].itemName, "Orange Juice (RoomTemp)");
				else
				strcpy(list[count2].itemName, "Orange Juice (Ice)");
				list[count2].price = orangeJ;
				break;
				
				case 208:
				if(hotorcold == 1)
				strcpy(list[count2].itemName, "Watermelon Juice (RoomTemp)");
				else
				strcpy(list[count2].itemName, "Watermelon Juice (Ice)");
				list[count2].price = wmelonJ;
				break;
				
				case 209:
				if(hotorcold == 1)
				strcpy(list[count2].itemName, "Apple Juice (RoomTemp)");
				else
				strcpy(list[count2].itemName, "Apple Juice (Ice)");
				list[count2].price = appleJ;
				break;
				
				case 210:
				if(hotorcold == 1)
				strcpy(list[count2].itemName, "Soft Drink (RoomTemp)");
				else
				strcpy(list[count2].itemName, "Soft Drink (Ice)");
				list[count2].price = sDrink;
				break;
				
				case 211:
				if(hotorcold == 1)
				strcpy(list[count2].itemName, "Mineral Water (RoomTemp)");
				else
				strcpy(list[count2].itemName, "Mineral Water (Ice)");
				list[count2].price = mWater;
				break;	
				default:
				printf("\nInvalid Food Code. Please Try Again.\n");
				--count2;
				break;
				}
			if(hotorcold >= 2)
				list[count2].price += ice;
			else{}
			}
			else if(interfacechoice == 3)
			{
				menuFood(interfacechoice);
				
				printf("Enter Set Meal of Choice : ");
				scanf("%d", &fChoice);
				fflush(stdin);
				
				switch(fChoice){
				case 301:
				strcpy(list[count2].itemName, "Wanton Egg Noodle and Soft Drink");
				list[count2].price = set1;
				break;
								
				case 302:
				strcpy(list[count2].itemName, "Nasi Lemak w Fried Chicken and Milo");
				list[count2].price = set2;
				break;
								
				case 303:
				strcpy(list[count2].itemName, "Triple Decker Burger and Beef Nachos");
				list[count2].price = set3;
				break;
								
				case 304: 
				strcpy(list[count2].itemName, "Signature Chicken Rice w Soft Tacos");
				list[count2].price = set4;
				break;
								
				case 305: 
				strcpy(list[count2].itemName, "Ayam Kunyit w Rice and Teh O");
				list[count2].price = set5;
				break;
				default:
				printf("\nInvalid Food Code. Please Try Again.\n");
				--count2;
				break;
				}
				
			}
			++count2;
			custDetails[count].ordertotal = count2;
			
			if(interfacechoice == 1)
				{
				interfaceAddmore();
				printf("\nSelection of Choice : ");
				scanf("%d", &interfacechoice);
				if(interfacechoice == 1)
				interfacechoice = 1;
				else
				{
					interfacechoice = 0;
				}
				}
			else if(interfacechoice == 2)
			{
				interfaceAddmore();
				printf("\nSelection of Choice : ");
				scanf("%d", &interfacechoice);
				if(interfacechoice == 1)
				interfacechoice = 2;
				else
				{
					interfacechoice = 0;
				}
			}
			else if(interfacechoice == 3)
			{
			interfaceAddmore();
			printf("\nSelection of Choice : ");
			scanf("%d", &interfacechoice);
				if(interfacechoice == 1)
				interfacechoice = 3;
				else
				{
					interfacechoice = 0;
					break;
				}
			}
		//counter test location
		}while(interfacechoice > 0);
	}

}

// void receipt(int count, struct Food custDetails[])
// {
	
	// printf("NAME : %s\n", custDetails[count].name );
	// printf("ORDER ID : %d\n", custDetails[count].ordernum);
	
// }

void show_total(int count, struct FoodList list[], struct Food custDetails[])
{
	printf("\n\nOrder ID      : # %d\n", count+1);
	printf("Customer Name : %s\n",custDetails[count].name);
	printf("\n--|Item|-------------|Product Name|-------------|Price|--\n");
	
	for( int i = 0; i < custDetails[count].ordertotal; i++)
		printf("    %-3d %-39s  RM %.2lf \n\n", i+1,list[i].itemName, list[i].price);
		
	for(int x = 0; x < custDetails[count].ordertotal; x++)
		{
		custDetails[count].total = custDetails[count].total + list[x].price;
		}
	printf("\nTotal => RM %.2lf\n\n",custDetails[count].total);
	
}
void couponFnc(struct Food custDetails[], int count)
{
	char couponCode[50], choice;
	custDetails[count].discount = 0.00;
	
    printf("\nDo you have a discount coupon? (Y/N): ");
    scanf("%c", &choice);
	fflush(stdin);
	
    if (choice == 'y' || choice == 'Y') 
	{
		
		while(choice == 'y' || choice == 'Y') 
        {
		printf("\nEnter coupon code (10OFF / 20OFF): ");
        scanf("%s", custDetails[count].couponCode);
		fflush(stdin);
			if (strcmp(custDetails[count].couponCode, "10OFF") == 0) 
			{
				custDetails[count].discount = 0.1;
				applyDiscount(custDetails, count);
				break;
			} 
			else if (strcmp(custDetails[count].couponCode, "20OFF") == 0) 
			{
				custDetails[count].discount = 0.2;
				applyDiscount(custDetails, count);
				break;
			}
			else
			{
			printf("\nThe Code you've just enter is Invalid.\nDo you want to re-enter the coupon code? (Y/N): ");
			scanf("%c", &choice);
			fflush(stdin);
			}			
		}
	
    }
	if( custDetails[count].discount == 0.00)
	{
		strcpy(custDetails[count].couponCode, "None");
		custDetails[count].totalnett = custDetails[count].total;
		printf("\n==============================================\n");
		printf("\nCoupon Code   : %s\n",custDetails[count].couponCode);
		printf("\nNett Total    : RM %.2lf\n",custDetails[count].totalnett);
		printf("\n==============================================\n");

		
	}
	
}

void applyDiscount(struct Food custDetails[], int count)
{
	custDetails[count].discountamount = custDetails[count].total * custDetails[count].discount;
	custDetails[count].totalnett = custDetails[count].total - custDetails[count].discountamount;
	
	printf("\n=============PRICE AFTER DISCOUNT=============\n");
	printf("\nCoupon Code    : %s\n",custDetails[count].couponCode);
	printf("\nDiscount (%.0lf%%) : RM %.2lf\n\n",custDetails[count].discount*100 ,custDetails[count].discountamount);
	printf("Nett Total     : RM %.2lf \n",custDetails[count].totalnett);
	printf("\n==============================================\n\n");
}

void customer_Sales_Data(struct Food custDetails[], struct FoodList list[], int count)
{
	FILE * pFile;
	double total = 0, discountT = 0;
	int quantityT = 0;
	
	pFile = fopen ("Customer_Sales_Data.txt","w");
	
	fprintf(pFile,"--|ID|----|Customer Name|----|QTY|----|Discount(RM)|---|Nett Total(RM)|---\n");
	
	for(int i = 0; i < count; i++)
	{
		fprintf(pFile,"   %d#      %-19s %-4d    %-17.2lf%-17.2lf\n",i+1, custDetails[i].name, custDetails[i].ordertotal, custDetails[i].discountamount, custDetails[i].totalnett);
	}
	for(int i = 0; i < count; i++)
	{
		quantityT = quantityT + custDetails[i].ordertotal;
		discountT = discountT + custDetails[i].discountamount;
		total = total + custDetails[i].totalnett;	
	}
	fprintf(pFile,"\n\n---SUMMARY----------------------------------------------------------------");
	fprintf(pFile,"\nTotal Customers for Service  : %d", count);
	fprintf(pFile,"\nTotal Order Quantity         : %d", quantityT);
	fprintf(pFile,"\nTotal Discounts              : RM %.2f", discountT);
	fprintf(pFile,"\nTotal Sale for Service       : RM %.2f", total);
	
	fclose (pFile);
}

void receipt(struct Food custDetails[], struct FoodList list[], int count)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	
	char choice;
	
	printf("\nPrint Receipt? (Y/N) : ");
	scanf("%c", &choice);
	fflush(stdin);
	
	FILE *pFile;

	if(choice == 'Y' || choice == 'y')
	{
		pFile = fopen ("printed_receipt.txt","w");
	}
	else{
		pFile = fopen ("receipt_history.txt", "a");
		fprintf(pFile,"\nReceipt -%d-\n", custDetails[count].ordernum);
	}
	
		if( pFile == NULL)
		{
			printf("Error opening file. \n");
		}
		else
		{
		fprintf(pFile,"\n\n");
		fprintf(pFile,"---------------------------------------------------------\n");
		fprintf(pFile,"                  Sir Lee The Best Sdn Bhd\n");
		fprintf(pFile,"              No 7,Jalan Aplease,Taman Desawaru,\n                81100,Beutiful Jaya,Somewhere");
		fprintf(pFile,"\n---------------------------------------------------------\n");
		fprintf(pFile,"                                             Order ID: #%d",custDetails[count].ordernum);
		fprintf(pFile,"\n---------------------------------------------------------\n");
		fprintf(pFile,"\n");
		
		fprintf(pFile,"Customer Name   : %s\n",custDetails[count].name);
		fprintf(pFile,"Date            : %02d-%02d-%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
		fprintf(pFile,"Time            : %02d:%02d:%02d\n",tm.tm_hour, tm.tm_min, tm.tm_sec);
		fprintf(pFile,"---------------------------------------------------------\n\n");
		fprintf(pFile,"--|Item|-------------|Product Name|------------|Price|---\n");
			//list out the item N price
		for(int i =0 ; i < custDetails[count].ordertotal ; i++)
		{
				fprintf(pFile,"   %d)   %-39s RM %.2lf\n",i+1, list[i].itemName, list[i].price);
		}
		
		fprintf(pFile,"\n\n");
		fprintf(pFile,"\n---------------------------------------------------------\n");
		fprintf(pFile,"Coupon Code                                     %s\n",custDetails[count].couponCode);
		fprintf(pFile,"Discount                                        RM %.2lf\n",custDetails[count].discountamount);
		fprintf(pFile,"Price Before Discount                           RM %.2lf\n",custDetails[count].total);
		fprintf(pFile,"Price After Discount (Subtotal)                 RM %.2lf\n\n",custDetails[count].totalnett);
		}
	fclose(pFile);
		
	generate_receipt_history(custDetails, count, choice);
	
}

void generate_receipt_history(struct Food custDetails[], int count, char choice)
{
	FILE *rAppend, *wGenerate;
	char c;
	
	if(choice == 'Y' || choice == 'y')
	{
		rAppend = fopen("printed_receipt.txt","r");
		
		wGenerate = fopen("receipt_history.txt", "a");
		
		if(rAppend == NULL || wGenerate == NULL)
		{
			printf("File Cannot be open.");
		}
		else{
			fprintf(wGenerate,"Receipt -%d-\n", custDetails[count].ordernum);
			while ((c = fgetc(rAppend)) != EOF)
			{
				fputc(c,wGenerate);
			}
			
		}
		
		fclose(rAppend);
		fclose(wGenerate);
	}
}