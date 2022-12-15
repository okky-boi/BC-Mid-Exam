#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
char a;
const int TableSize = 100;

struct dish{
	char dishName[1001];
	int dishPrice;
	int dishQuantity;
	dish *next, *prev;
} *head, *tail;

struct Customer{
	char customerName[1001];
	long long int sum;
} *table[TableSize];

dish *createDish(const char *dishName, int dishPrice, int dishQuantity){
	dish *newDish = (dish *)malloc(sizeof(dish));
	strcpy(newDish->dishName, dishName);
	newDish->dishPrice = dishPrice;
	newDish->dishQuantity = dishQuantity;
	newDish->next = NULL;
    newDish->prev = NULL;
	return newDish;
}

int hashKey(char name[])
{
	int len = strlen(name);
	unsigned long hash = 5381;
	for (int i = 0; i < len; i++)
	{
		int ascii = int(name[i]);
		hash = (hash << 5) + hash + ascii;
	}
	return hash % TableSize;
}

Customer *newCustomer(char name[]){
	Customer *newCustomer = (Customer *)malloc(sizeof(Customer));
	strcpy(newCustomer->customerName, name);
	newCustomer->sum = NULL;
	return newCustomer;
}

void push(char name[]){
	int key = hashKey(name);
	if (table[key] == NULL){
		table[key] = newCustomer(name);
	}
	else{
		for (int j = key + 1; j != key; j++){
			j%=TableSize;
			if (table[key] == NULL)	{
				table[key] = newCustomer(name);
				break;
			}
		}
	}
}

void AddCust(){
	int BoolAddCustomer = true;
	int count2;
	char namaCust[1010];
	system("clear");
	while (BoolAddCustomer == true){
		count2 = 0;
		printf("Insert the customer's name [Without space]: ");
		scanf("%[^\n]", namaCust);
		getchar();
		for (int i = 0; i < strlen(namaCust); i++){
			if (namaCust[i] >= 'a' && 'z' >= namaCust[i]){
				count2++;
				if (count2 == strlen(namaCust)){
					BoolAddCustomer = false;
				}
			}
			if (namaCust[i] >= 'A' && 'Z' >= namaCust[i]){
				count2++;
				if (count2 == strlen(namaCust)){
					BoolAddCustomer = false;
				}
			}
			if (namaCust[i] == ' '){
				BoolAddCustomer = true;
			}
		}
	}
	push(namaCust);
	printf("\nCustomer has been added!\n");
	printf("\nPress enter to continue...");
	getchar();
}

void SchCust(){
	system("clear");
	char str1[1010]={"-"};
	int find = 1;
	printf("Insert the customer's name to be searched: ");
	scanf("%[^\n]", str1);
	getchar();
	for(int ii=0; ii<TableSize; ii++){
		Customer *temp = table[ii];
		if(temp != NULL){
			if(strcmp(temp->customerName, str1)){
				printf("%s is present.\n", str1);
				find = 2;
				break;
			}
		}
	}
	if(find == 1){
		printf("%s is not present.\n", str1);
	}
	printf("Press enter to continue...");
	getchar();
}

void View(){
	system("clear");
	printf("Customer's List\n\n");
	for(int i=0; i<TableSize; i++){
		Customer * curr = table[i];
		if(curr != NULL){
			printf("%d. %s\n\n", i, curr->customerName);
		}
	}
	printf("Press enter to continue...");
	getchar();
}

void AddDish(){
    system("clear");
    int BoolDishName = true;
    char DName[1010];
	while (BoolDishName == true){
		int count = 0;
        strcpy(DName, "-");
		printf("Insert the name of the dish [Lowercase letters]: ");
		scanf("%[^\n]", DName);
        getchar();
		for (int i = 0; i < strlen(DName); i++){
			if (DName[i] >= 'a' && 'z' >= DName[i] || DName[i] == ' '){
				count++;
				if (count == strlen(DName)){
					BoolDishName = false;
				}
			}
		}
	}
	int BoolDishPrice = true;
    int DPrice;
	while (BoolDishPrice == true){  
		printf("\nInsert the price of the dish [1000..50000]: ");
		scanf("%d", &DPrice);
		getchar();
		if (DPrice >= 1000 && 50000 >= DPrice)	{
			BoolDishPrice = false;
		}
	}
	int BoolDishQuantity = true;
    int DQuantity;
	while (BoolDishQuantity == true){
		printf("\nInsert the quantity of the dish [1..999]: ");
		scanf("%d", &DQuantity);
        getchar();
		if (DQuantity >= 1 && 1000 > DQuantity)
		{
			BoolDishQuantity = false;
		}
	}

	dish *temp = createDish(DName, DPrice, DQuantity);

	if (!head){
		head = tail = temp;
	}
	else{
		tail->next = temp;
        temp->prev = tail;
		tail = temp;
	}
}

void Delete(char ReDName[]){
	
    if (!head){
        return;
    }
	else if (head == tail && strcmp(ReDName, head->dishName) == 0){
		free(head);
		head = tail = NULL;
	}
    else if (strcmp(tail->dishName, ReDName) == 0){
        tail = tail->prev;
        free(tail->next);
        tail->next = NULL;
    }
    else if (strcmp(head->dishName, ReDName) == 0){
        head = head->next;
        free(head->prev);
        head->prev = NULL;
    }
	else{
        struct dish *curr = head->next;
		while (curr != tail && strcmp(curr->dishName, ReDName) != 0){
			curr = curr->next;
		}
        if(strcmp(curr->dishName, ReDName) == 1){
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            curr->prev = curr->next = NULL;
            free(curr);
            curr = NULL;
        }
	}
}

void prinLLDish(){
    struct dish *curr = head;
    int count = 1;
    puts("\tBude's Menu");
	puts("==============================");
    printf("No.\tName\tQuant\tPrice\n");
    while(curr != NULL){
        printf("%d.\t%s\t%d\t%d\n", count, curr->dishName, curr->dishQuantity, curr->dishPrice);
        curr = curr->next;
        count ++;
    }
    puts("==============================");
}

void RmDish(){
    system("clear");
    prinLLDish();
    char name[1010];
    printf("Insert dish's name to be deleted: ");
    scanf("%[^\n]", name);
    getchar();
    Delete(name);
    printf("The dish has been removed!\n"); 
    printf("Press enter to continue...");
    getchar();
}

void EXIT(){
    system("clear");
    printf("Please expand your terminal to full screen!\n");
    printf("Press enter to continue...");
    getchar();
    system("clear");
	char str[1010];
	FILE *exit = fopen("splash-screen.txt", "r");

	while (fscanf(exit, "%[^\n]\n", str) != EOF)
	{
		printf("%s\n", str);
	}
	fclose(exit);
    printf("\n");
    return;
}

void time(){
	time_t t = time(NULL);
	printf("%s", ctime(&t));
}

void OSsystem();

int main () {
    int pilihmenu;
    do {
        system("clear");
        OSsystem();
        time();
        printf("1. Add Dish\n");
        printf("2. Remove Dish\n");
        printf("3. Add Customer\n");
        printf("4. Search Customer\n");
        printf("5. View Warteg\n");
        printf("6. Order\n");
        printf("7. Payment\n");
        printf("8. Exit Warteg\n");
        printf(">> ");
        scanf("%d", &pilihmenu); 
        getchar();
        switch (pilihmenu) {
        case 1:
            AddDish();
            break;
        case 2:
            RmDish();
            break;
        case 3:
            AddCust();
            break;
        case 4:
            SchCust();
            break;
        case 5:
            View();
            break;
        // case 6:
        //     Order();
        //     break;
        // case 7:
        //     pay();
        //     break;
        case 8:
            EXIT();
            break;
        
        default:
            break;
        }
    } while (pilihmenu != 8);

    return 0;
}

void OSsystem(){
printf("System: ");
#ifdef _WIN32
	printf("Windows OS\n");

#elif __APPLE__
	printf("Mac OSX\n");

#elif __linux__
	printf("Linux OS\n");

#elif TARGET_OS_EMBEDDED
	printf("iOS embedded OS\n");

#elif TARGET_IPHONE_SIMULATOR
	printf("iOS simulator OS\n");

#elif TARGET_OS_IPHONE
	printf("iPhone OS\n");

#elif TARGET_OS_MAC
	printf("MAC OS\n");

#elif __ANDROID__
	printf("android OS\n");

#elif __unix__
	printf("unix OS\n");

#elif _POSIX_VERSION
	printf("POSIX based OS\n");

#elif __sun
	printf("Solaris OS\n");

#elif __hpux
	printf("HP UX OS\n");

#elif BSD
	printf("Solaris OS\n");

#elif __DragonFly__
	printf("DragonFly BSD OS\n");

#elif __FreeBSD__
	printf("FreeBSD OS\n");

#elif __NetBSD__
	printf("Net BSD OS\n");

#elif __OpenBSD__
	printf("pen BSD OS\n");

#else
	printf(" - \n");
#endif
}