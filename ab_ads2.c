	/* Author Aaron Bermingham
	*  Student number: C17738539
	*/
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdbool.h>
	#include<string.h>
	#include<ctype.h>
	#include <time.h>
	#define SIZE 10
	
	// Global Variables
	struct LinearNode *front = NULL; //variable for first linear node in the list
	struct LinearNode *last = NULL;	//variable for lasr linear node in the list
	int bookCount; // variable to keep track of number of books in the library 
	char line[] = "\n============================"; // String used for formatting purposes
	FILE *fp; // file variable, used for file handling, writing to and reading from a file
	
	//Book structure
	struct Book{
		char bookID[10]; // variable for book identifier, 10 characters long to allow for 8 digits, a dash and null terminater
		char bookTitle[50]; // variable for book title
		char author[25]; // variable for author name
		int yearPub; // variable for book year of publication
		bool loan; // boolean value for whether book is on loan or not
		char customerName[25]; // variable to hold customer name
		int numLoans; // variable to hold number of book loans per book
		time_t loanDate; // date the book is loaned out
		time_t returnDate; // date the book is returned
		int diffTime; // variable to hold the difference between the two dates
	};
	
	//Stucture template for one node
	struct LinearNode {
		struct Book *element; // This point to the data held in the book structure
		struct LinearNode *next; // This points to the next node in the linked list
	};
	
	
	
	// function prototypes
	int menu();
	// 1 Add a book
	void addBook();
	/* Two functions to format user inputted book id so it conforms to the pattern
	xxxx-xxxx, 
	*/
	char *substring(char *, int , int ); 
	void insert_substring(char *, char *, int );
	// 2 Loan a book
	void loanBook();
	// 3 Return a book
	void returnBook();
	// 4 Delete a book
	void deleteBook();
	// 5 Vuew all books
	void viewAll();
	// 6 Search for a specific book
	void searchView();
	// 7 Display most/least popular book
	void displaySmallest();
	void displayLargest();
	// 8 Read/write files
	void saveFile(FILE*);
	void readFile(FILE*);
	// 9 Personal feature menu
	int reportMenu();
	// 9.1 Personal feature = calculates late fee
	float calFine(int *diff);
	// 9.4 Books that are on loan
	void booksOnLoan();
	// 9.7 Bubble Sort to sort nodes by number of loans
	void bubbleSort(struct LinearNode *start); 
  	//Function to swap data of two nodes a and b
	void swap(struct LinearNode *a, struct LinearNode *b);
	// Function prototype for checking if the list is empty
	bool isEmpty();
	bool search(char*);
	
	
	
	
	
	// main function
	int main(int argc, char *argv[]) {
		/* Checks if there is a books.dat to open and populate linked list with,
		otherwise user must input books 
		*/
		if((fp = fopen("books.dat","rb"))==NULL){
			printf("There are no books inputted in the library system, please choose menu option 1 to add books");
		}
		else
			readFile(fp); // Call to read file function, passing fp as a parameter
		menu(); // Call to menu function
		return 0;
		getchar();
		getchar();
	}

	//Menu function
	int menu(){
		int option; // variable to take user menu option input
		printf("\nLibrary Stock System");
		printf(line);
		do{
		// Message to display various menu options
	    printf("\n\nPress 1 to add a book\n"); 
	    printf("Press 2 to loan a book\n"); 
	    printf("Press 3 to return a book\n"); 
	    printf("Press 4 to delete a book\n");
	    printf("Press 5 to view all books\n");
	    printf("Press 6 to view a specific book\n"); 
	    printf("Press 7 to view the most popular and least book\n"); 
	    printf("Press 8 for an exciting personal feature\n"); 
	    printf("Press 9 to close the system\n");
	    printf("Enter your choice:\n"); 
	    printf(line);
	   fflush(stdin);
	   scanf("%d", &option); // User input set to option variable
	   getchar();
	   // Switch case with calls to relevant functions
	   switch(option) {
	      case 1 :
	      	printf("Add a new book\n" );
	      	 addBook(); // Call to addBook function
	         break;
	      case 2 :
	      	 printf("Loan a book\n" );
	      	 loanBook();
	         break;
	      case 3 :
	         printf("Return a book\n" );
	         returnBook();
	         break;
	      case 4 :
	      	 printf("Delete a book\n" );
	        deleteBook();
	         break;
	      case 5 :
	         printf("View all books\n" );
	         viewAll();
	         break;
	         case 6 :
	         printf("View a specific book\n" );
	         searchView();
	         break;
	      case 7 :
	      	 displaySmallest();
	      	 printf(line);
	         displayLargest();
			 
	         break;
	      case 8 :
	         printf("Reports\n" );
	         reportMenu();
	         break;
	      case 9 :
	         printf("Exit the system\n\n" );
	         saveFile(fp); // On exiting the linked list is saved by calling the saveFile function
	         exit(0);
	         break;
	      default :
	         printf("Invalid option\n" );
	         break;
	   }  
	}while (option != 9);
	   
	   return 0;
	   
	   
	}
	
	// 1 Add a book function
	void addBook(){
		
		struct LinearNode *aNode;
		struct Book *anElement;
		char bookID[10];
		int position = 4;
		char dashString[] = "-";
		bool valID=true;
		
			//Create space for Book struct
			anElement = (struct Book *)malloc(sizeof(struct Book));
			// Only allow user to input a book if the book count is greater than or equal to 10
			if (bookCount >= 10 ){
				// Message to notify user of the 10 book constraint
				printf("The library can holds a maximum of 10 books please delete a book before you add a new one");
			}
			else
			{
			
			if (anElement == NULL)
			
				printf("Error - no space for the new element\n");
			else
			
				//Input value into the Book part of the node
				// Error check xxxx-xxxx
				printf("Book ID must consist of 8 numbers.\n Enter an ID for the book:" ); // User prompted to enter a book id
				scanf("%s",bookID );
				//getchar();
				//Validating user input, checking for length book id an if it is all numbers
				for (int i = 0; i <strlen(bookID); i++){
					if(isdigit(bookID[i])!=1 || strlen(bookID)!=8)
						valID = false; // If the input is invalid, valID is set to false
					else 
						valID = true; // Otherwise it is true and the book id is accepted
				}
				// User is trapped in a loop intil they input a valid book id
				while(valID == false){
				printf("****NB-Books ID must be numeric and consist of eight numbers ****"); // Error message prompts user to correctly input the book id
				printf("Enter an ID for the book:" );
				scanf("%s",bookID );
				//getchar();
				for (int i = 0; i <strlen(bookID); i++){
					if(isdigit(bookID[i])!=1)
						valID = false;
					else 
						valID = true;
				}
				}
				if(valID = true){ // IF the user has satisfied the book id validations conditions
					insert_substring(bookID, "-", 5); // Function that inserts dash into the user inputted book id, eliminates the need to prompt user to input the dash
					strcpy(anElement->bookID,bookID); // Sets the book struct book id to what the user has inputted
					printf("%s", bookID);
				}

				getchar();
				printf("Enter the book title " ); // Prompt user for book title
				fgets (anElement->bookTitle, 100, stdin); // Used fgets as the title may have spaces 
				
				printf("Enter the book author " ); // Prompt user to input the author
				fgets (anElement->author, 100, stdin); // Used fgets as the author name will have spaces 
				
				// Error check, while <2008
				printf("Enter the year the book was published " );
				scanf("%d", &anElement->yearPub);
				// Library does not allow books older than 2008, user is trapped in loop until they enter a year > 2007
				while((anElement->yearPub) < 2008){
					printf("****NB-Only books from 2008 or later may be added to the library****"); // Error message to prompt user
					printf("Enter the year the book was published " );
					scanf("%d", &anElement->yearPub);
				}
				anElement->loan = false; // book loan set to false
				anElement->numLoans = 0; // number of loans set to zero
				
				// create space for new node that will contain data
				aNode = (struct LinearNode *)malloc(sizeof(struct LinearNode));
	
				if (aNode == NULL)
					printf("Error - no space for the new node\n");
				else { 
					aNode->element = anElement; // add data part to the node
					aNode->next = NULL; // next node set to null
	
					//add node to end of the list
					if (isEmpty())
					{
						front = aNode; // Both the front and last node are the only one in the list
						last = aNode;
					}
					else {
						last->next = aNode; // the last node in the list points to the new node being added
						last = aNode; // the node being added is set as the last node
					} //end else
				}//end else
				bookCount ++; // increment book count
				//printf("Book count is: %d", bookCount);
			}//end else 

 } //end addNodes
	
	
	
	// 2 Loan a book function
	void loanBook(){
		char aBookID[10];
		struct LinearNode *current, *previous;
		bool notFound = true;
		printf("Enter an ID for the book to loan:" );
		scanf("%s", aBookID); 
		printf("\n");
		getchar();
		if (isEmpty())
			printf("Error - there are no books in the library\n");
		else {		
			current = previous = front;
			while (notFound && current != NULL) {
				if (strcmp(aBookID, current->element->bookID)==0){
					printf("Book id %s equals current %s \n", aBookID, current->element->bookID);
					notFound = false;
				}
				else {
					printf("Book id %s NOT equals current %s \n", aBookID, current->element->bookID);
					previous = current;
					current = current->next;
				}//end if
			} //end while
			if (notFound)
				printf("Error - there is not such book with book ID %s\n", aBookID);
			else if(current->element->loan== true)
				printf("%s is on loan at the moment",current->element->bookTitle);
			else{
				printf("Enter the customers name " );
				fgets (current->element->customerName, 100, stdin);
				printf("\n%s has been successfully loaned\n", current->element->bookTitle);
				current->element->loan = true;
				current->element->numLoans ++;
				current->element->loanDate = time(NULL);
		}		
	}
}


	// 3 Return a book function
	void returnBook(){
		int diff_t;
		char aBookID[10];
		char aPerson[50];
		struct LinearNode *current, *previous;
		bool notFound = true;
		printf("Enter an ID for the book to return:" );
		scanf("%s", aBookID); 
		printf("Enter name of person who has loaned the book:" );
		scanf("%s", aPerson); 
		getchar();
		printf("\n");
		getchar();
		if (isEmpty())
			printf("Error - there are no books in the library\n");
		else {		
			current = previous = front;
			while (notFound && current != NULL) {
				printf("Name %s equals current %s \n", aPerson, current->element->customerName);
				if ((strcmp(aBookID, current->element->bookID)==0)){ //(strcmp(aBookID, current->element->bookID)==0) && (strcmp(aPerson,current->element->customerName)==0)
					//printf("Name %s equals current %s \n", aPerson, current->element->customerName);
					printf("Book id %s equals current %s \n", aBookID, current->element->bookID);
					notFound = false;
				}
				else {
					//printf("Name %s NOT equals current %s \n", aPerson, current->element->customerName);
					printf("Book id %s NOT equals current %s \n", aBookID, current->element->bookID);
					previous = current;
					current = current->next;
				}//end if
			} //end while
	
			if (notFound)
				printf("Error - there is not such node with value %s\n", aBookID);
			else{
				
				memset(current->element->customerName, 0, sizeof(current->element->customerName));
				//current->element->customerName = '';
				current->element->loan = false;
				current->element->returnDate = time(NULL);
				// https://www.tutorialspoint.com/c_standard_library/c_function_difftime.htm
				diff_t = difftime(current->element->returnDate, current->element->loanDate);
				current->element->diffTime = diff_t;
			}
		
		}
				
				
				if (diff_t > 1){
					float fineDays = current->element->diffTime = diff_t;
					calFine(&fineDays);
					printf("\nIn FUNCTION Fine is %f",calFine(&fineDays) );
				}	
				
	}
	//4 Delete a book function
	void deleteBook(){
			char aBookID[10];
		struct LinearNode *current, *previous;
		bool notFound = true;
		printf("Enter an ID for the book to delete:" );
		scanf("%s", aBookID); 
		printf("\n");
		getchar();
		if (isEmpty())
			printf("Error - there are no books in the library\n");
		else {		
			current = previous = front;
			while (notFound && current != NULL) {
				if (strcmp(aBookID, current->element->bookID)==0){
					printf("Book id %s equals current %s \n", aBookID, current->element->bookID);
					notFound = false;
				}
				else {
					printf("Book id %s NOT equals current %s \n", aBookID, current->element->bookID);
					previous = current;
					current = current->next;
				}//end if
			} //end while
	
			if (notFound)
				printf("Error - there is not such node with value %s\n", aBookID);
			else if (current->element->yearPub >2009)
				printf("Error - only books older than 2010 can be deleted!");
			else {
				if (current == front) { //delete front node
					front = front->next;
					free(current);
				} //end else
				else if (current == last) {//delete last node
					free(current);
					previous->next = NULL;
					last = previous;
				}
				else {//delete node in middle of list
					previous->next = current->next;
					free(current);
				} //end else
				printf("Node with value %s has been deleted\n", aBookID);
			}//end else
		}//end else
	}
	
	//5 View all function
	void viewAll(){
		char* loanDateStr;
		
		struct LinearNode *current;
		//printf("\n");
		if (isEmpty())
			printf("Error - there are no nodes in the list\n");
		else {
			current = front;
			while (current != NULL) {
				loanDateStr = ctime(&current->element->loanDate);
				printf("\nBook ID is %s\n", current->element->bookID);
				printf("Book name is %s", current->element->bookTitle);
				printf("Book author is %s", current->element->author);
				printf("Year published %d", current->element->yearPub);
				printf("\nNumber of loans %d", current->element->numLoans);
				if(current->element->loan == true){
				printf("\nBook is loaned by %s", current->element->customerName);
				printf("Date of loan: %s\n", ctime(&current->element->loanDate));
				printf(line);
				
			}
			else 
			printf("\nBook is not on loan\n");
			printf(line);
				current = current->next;
			} //end while
		}//end else
	}
	
	
	//6 View a specific book
	void searchView(){
	struct LinearNode *current, *previous;
	char aBookID[10];
		bool notFound = true;
		printf("Enter an ID for the book to view : " );
		scanf("%s", aBookID); 
		printf("\n");

		if (isEmpty())
			printf("Error - there are no books in the list\n");
		else {
				
			current = previous = front;
			
			while (notFound && current != NULL) {
				if ( strcmp(aBookID, current->element->bookID)==0)
					notFound = false;
				else {
					previous = current;
					current = current->next;
				}//end else
			} //end while
	
			if (notFound)
				printf("Error - there is not such book with value %s\n", aBookID);
			else {
			{
			char loanDateStr = ctime(&current->element->loanDate);
				printf("\nBook ID is %s\n", current->element->bookID);
				printf("Book name is %s", current->element->bookTitle);
				printf("Book author is %s", current->element->author);
				printf("Year published %d", current->element->yearPub);
				printf("\nNumber of loans %d", current->element->numLoans);
				if(current->element->loan == true){
				printf("\nBook is loaned by %s", current->element->customerName);
				printf("Date of loan: %s\n", ctime(&current->element->loanDate));
				printf(line);
				
			}
		
			else 
			printf("\nBook is not on loan\n\n");
			printf(line);
				current = current->next;
			} 
		}
	}
}
		
	bool isEmpty() {
		if (front == NULL)
			return true;
		else
			return false;
	}
	
//	bool search(char *aBookID) {
//		struct LinearNode *current, *previous;
//		bool notFound = true;
//		if (isEmpty())
//			printf("Error - there are no books in the library\n");
//		else {
//		printf("Enter an ID for the book to search for : " );
//		scanf("%s", aBookID); 
//		printf("\n");
//		
//				
//			current = previous = front;
//			
//			while (notFound && current != NULL) {
//				if ( strcmp(aBookID, current->element->bookID)==0)
//					notFound = false;
//				else {
//					previous = current;
//					current = current->next;
//				}//end else
//			} //end while
//			
//}return notFound;
//}
	//7 View the least popular book
		void displaySmallest() {
		struct LinearNode *current, *smallest; // current is a pointer
		current = front; // set current to first node in the list
		int min = current->element->numLoans; // Integer min is set to the value current points to 
		while (current != NULL) {
			if (min > current->element->numLoans) {
				min = current->element->numLoans;
				smallest = current;
				}
			current = current->next;
		}
		printf("\Least popular book is %s with %d loans\n",smallest->element->bookTitle, min);
	}
	//7 View the most popular book
	void displayLargest() {
		struct LinearNode *current, *largest; // current is a pointer
		current = front; // set current to first node in the list
		int max = current->element->numLoans; // Integer min is set to the value current points to 
		while (current != NULL) {
			if (max < current->element->numLoans) {
				max = current->element->numLoans;
				largest = current;
				}
			current = current->next;
		}
		printf("\nMost popular book is %s with %d loans\n",largest->element->bookTitle, max);
	}
	

	

	
	void insert(char *id, char *insert, int postion){
	
	}
	
	void saveFile(FILE *fp){
		printf("Saving files to database.....");
		fp = fopen("books.dat", "wb");
		struct Book *anElement;
		struct LinearNode *current; // current is a pointer
		current = front; // set current to first node in the list
		while (current != NULL) {
			fwrite(current->element, sizeof(struct Book),1,fp);
		//	printf("\nSaving title %s\n",current->element->bookTitle);
//			getchar();
//			getchar();
			current = current->next;
			}
		fclose(fp);
	}
		
	void readFile(FILE *fp){
		
		struct LinearNode *aNode;
		struct Book *anElement;
		anElement = (struct Book *)malloc(sizeof(struct Book));
		printf("Reading in Book information");
	
	while(fread(anElement, sizeof(struct Book), 1, fp)!= NULL){ 
			aNode = (struct LinearNode *)malloc(sizeof(struct LinearNode));

				if (aNode == NULL)
					printf("Error - no space for the new book\n");
				else { 
					aNode->element = anElement; // add data part to the node
					aNode->next = NULL;
	
					//add node to end of the list
					if (isEmpty())
					{
						front = aNode;
						last = aNode;
					}
					else {
						last->next = aNode;
						last = aNode;
					} //end else
				}//end else
				bookCount ++;
				//printf("Book count is: %d", bookCount);
					anElement = (struct Book *)malloc(sizeof(struct Book));
			}//end else 
				fclose(fp);
		}
	
	

// 9 Personal feature - Report menu, displays information/reports about books
int reportMenu(){
		int option;
		printf("\nReport Menu");
		printf(line);
		do{
	    printf("\n\nPress 1 to view books by genre\n"); 
	    printf("Press 2 to view average book loans\n"); 
	    printf("Press 3 to view outstanding fines\n"); 
	    printf("Press 4 to view total fines\n");
	    printf("Press 5 to view all books on loan\n");
	    printf("Press 6 to view all book not on loan\n"); 
	    printf("Press 7 to view the books ranked most to least popular\n"); 
	    printf("Press 8 to view books eligible for deletion\n"); 
	    printf("Press 9 to exit the report menu\n");
	    printf("Enter your choice:\n"); 
	    printf(line);
	   fflush(stdin);
	   scanf("%d", &option);
	   getchar();
	   switch(option) {
	      case 1 :
	      	printf("Books by genre\n" );
	      	 //booksGenre();
	         break;
	      case 2 :
	      	 printf("Average loans by genre\n" );
	      	 //loanBook();
	         break;
	      case 3 :
	         printf("Oustanding fines due\n" );
	         
	         break;
	      case 4 :
	      	 printf("Total fines due\n" );
	        
	         break;
	      case 5 :
	         printf("View all books on loan\n" );
	         
	         break;
	         case 6 :
	         printf("View all book in stock\n" );
	         
	         break;
	      case 7 :
	      	printf("View book from most to least popular\n" );
	      	bubbleSort(front);
	      	viewAll();
			 
	         break;
	      case 8 :
	         printf("View books eligible for deletion\n" );
	         break;
	      case 9 :
	         printf("Exit the Report menu\n\n" );
	         return menu();
	         break;
	      default :
	         printf("Invalid option\n" );
	         break;
	   }  
	}while (option != 9);
	   
	   return 0;
	   
	   
	}
	
	// Function to calculate fee for books returned late
	float calFine(int *diff){
		float fine = .5;
		printf("diff is %d", diff);
		printf("Fine is %f",fine);
		if(diff >= 3){
			fine = fine * 5;
		}
		else if(diff >1 && diff <3){
			fine = fine*2;
		}
		else if (diff == 1){
			fine = fine;
		}
		else if (diff < 1){
			printf("No fine");
		}
			
		else 
		printf("Fine is %f",fine);
		return fine;
	}
	
	//	void searchView(){
//		struct LinearNode *current, *previous;
//		bool notFound = search(&delBook);
//		
//			if (notFound != true)
//				printf("Error - there is not such node with value %s\n", &delBook);
//			else 
//			{
//				printf("Book ID is %s", current->element->bookID);
//				printf("\nBook name is %s", current->element->bookTitle);
//				printf("Book author is %s", current->element->author);
//				printf("Year published %d", current->element->yearPub);
//				if(current->element->loan == true){
//				printf("\nBook is loaned by %s", current->element->customerName);
//				printf("Number of loans %d\n\n", current->element->numLoans);
//			}
//			else 
//			printf("\nBook is not on loan\n\n");
//				current = current->next;
//			} 
//			}
	
	

	
	void sort() {
		struct LinearNode *aNode; // current is a pointer
		aNode = front; // set current to first node in the list
		int min = aNode->element->numLoans; // Integer min is set to the value current points to numLoans
		while (aNode != NULL) {
	
			if (min < aNode->next->element->numLoans) {
				front = aNode->next;
				aNode = front->next;
	
			}
			aNode = aNode->next;
			
		}
	
	}
	


//	void displayLargest() {
//		struct LinearNode *current, *largest; // current is a pointer
//		current = front; // set current to first node in the list
//		int max = current->element->numLoans; // Integer min is set to the value current points to 
//		while (current != NULL) { // While current is not null
//				if (max > current->element->numLoans) { // Min greater than the current 
//					max = current->element->numLoans;
//					largest = current;
//				}
//				largest = current->next;
//		}
//		printf("Most popular book is %s with %d loans\n",largest->element->bookTitle, max);
//		//return min;
//	}

//https://www.programmingsimplified.com/c/source-code/c-program-insert-substring-into-string
void insert_substring(char *a, char *b, int position)
{
	//printf("iSubstring");
   char *f, *e;
   int length;
   
   length = strlen(a);
   
   f = substring(a, 1, position - 1 );      
   e = substring(a, position, length-position+1);
 
   strcpy(a, "");
   strcat(a, f);
   free(f);
   strcat(a, b);
   strcat(a, e);
   free(e);
   
}
 
char *substring(char *string, int position, int length)
{
	printf("sub");
   char *pointer;
   int c;
 
   pointer = (char*)(malloc(length+1));
   
   if( pointer == NULL )
       exit(EXIT_FAILURE);
 
   for( c = 0 ; c < length ; c++ )
      *(pointer+c) = *((string+position-1)+c);      
       
   *(pointer+c) = '\0';
   return pointer;
}
//https://www.geeksforgeeks.org/c-program-bubble-sort-linked-list/
/* Bubble sort the given linked list */
void bubbleSort(struct LinearNode *front) 
{ 
    int swapped, i; 
    struct LinearNode *ptr1; 
    struct LinearNode *lptr = NULL; 
  
    /* Checking for empty list */
    if (front == NULL) 
        return; 
  
    do
    { 
        swapped = 0; 
        ptr1 = front; 
  
        while (ptr1->next != lptr) 
        { 
            if (ptr1->element->numLoans < ptr1->next->element->numLoans) 
            {  
                swap(ptr1, ptr1->next); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    } 
    while (swapped); 
} 
  
/* function to swap data of two nodes a and b*/
void swap(struct LinearNode *a, struct LinearNode *b) 
{ 
    int temp = a->element; 
    a->element = b->element; 
    b->element = temp; 
} 

void booksOnLoan(){
}


	
	

	

