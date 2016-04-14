#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

/* INTRODUCTORY PARAGRAPH
 * ----------------------
 * In this MP, I implemented various functions for storing a sparse matrix in a linked list using the standard COO format. My 'load tuples' function reads a file of this format line by line and calls 'set tuples' to create the 
 * corresponding linked list. In addition to creating the linked list, the 'set tuples' function overwrites nodes corresponding to co-ordinates that have previously come up as well as removing nodes that contain a value of zero. I 
 * added a function called 'non-zeroes' to count the number of non-zero elements in the matrix after the linked list has been created by counting the number of nodes in the list. The 'get value' function simply returns the value at a
 * specific point within the matrix. The 'add' and 'multiply' functions parse the linked list and perform the relevant operations, storing the result into a new matrix. Finally, 'destroy tuples' frees all memory associated with the
 * linked list and matrix structure.
*/ 



sp_tuples * load_tuples(char* input_file)
{
	int a, b;
	double c;

	char line[256];	
	
	FILE *myFile;

	myFile = fopen(input_file, "r"); //open file for reading

	sp_tuples * myTuples = (sp_tuples*)malloc(sizeof(sp_tuples)); //allocate memory for structure

	myTuples->tuples_head = NULL; //initialise head of linked list 

	fscanf(myFile, "%d %d\n", &(myTuples->m), &(myTuples->n)); //set row and column parameters in structure

	while(fgets(line, sizeof(line), myFile))
	{
		sscanf(line, "%d %d %lf\n", &a, &b, &c); //set each parameter in the node structure 
		set_tuples(myTuples, a, b, c);           //create new node for each line       
 	}

	non_zero(myTuples); //set number of non-zero elements

	fclose(myFile);

	return myTuples;
}

void non_zero(sp_tuples * mat_t)
{
	sp_tuples_node * current = mat_t->tuples_head;
	mat_t->nz = 0;
	
	while(current != NULL) //count non-zero elements
	{
		mat_t->nz++;
		current = current->next;
	}
}

double gv_tuples(sp_tuples * mat_t,int row,int col)
{
	sp_tuples_node * current = mat_t->tuples_head;
	
	while(current != NULL)
	{
		if(current->row == row && current->col == col)
		{
			return current->value;
		}
		else
		{
			current = current->next;
		}
	}
	return 0;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{

	sp_tuples_node * current = mat_t->tuples_head;
	sp_tuples_node * newNode = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
	int width = mat_t->n;
	int index = row*width + col;
	
	if(value == 0) 
	{
		if(current != NULL)
		{
			while(current->next != NULL) //parse linked list
			{
				sp_tuples_node * temp = current->next;
				if(temp->row == row && temp->col == col) //see if there is a node corresponding to given row and column
				{
					current->next = temp->next; 
					free(temp);
					break;
				}
				current = current->next;
			}
		}
		return; //return to caller function as we do not want to store a zero in our linked list
	}
	else if(current == NULL) //linked list is currently empty
	{
		newNode->row = row;
		newNode->col = col;
		newNode->value = value;
		mat_t->tuples_head = newNode;
		newNode->next = NULL;		
	}
	else if(index <  (current->row)*width + current->col) //see if new node should be placed before head
	{
		newNode->row = row;
		newNode->col = col;
		newNode->value = value;
		newNode->next = current; //re-route new node to point to head
		mat_t->tuples_head = newNode;
	}
	else
	{
		while(current->next != NULL)
		{
			if(current->row == row && current->col == col)
			{
				current->value = value; //replace old value if co-ordinates already exist
				return;
			}
			else if(index < (current->next->row)*width + current->next->col) //insert new node
			{				
				sp_tuples_node * temp = current->next;
				newNode->row = row;
				newNode->col = col;
				newNode->value = value;
				current->next = newNode;
				newNode->next = temp;
				return;	
			}
			current = current->next;	
		}
		newNode->row = row; //insert at end of linked list
		newNode->col = col;
		newNode->value = value;
		current->next = newNode;
		newNode->next = NULL;
					
	}
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
	FILE *outFile = fopen(file_name, "w");
	
	fwrite(mat_t, sizeof(sp_tuples), sizeof(mat_t), outFile);

	fclose(outFile);
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB)
{
	sp_tuples * matC = (sp_tuples*)malloc(sizeof(sp_tuples)); //initialising the matrix C
	matC->m = matA->m;
	matC->n = matA->n;
	matC->tuples_head = NULL;
	int i, j;

	if(matA->m == matB->m && matA->n == matB->n) //begin addition algorithm
	{
		sp_tuples_node * currentA = matA->tuples_head;
		sp_tuples_node * currentB = matB->tuples_head;
		double sum_A = 0; //initialise variables to hold sum of all values
		double sum_B = 0;		

		while(currentA != NULL) 
		{
			i = currentA->row;
			j = currentA->col;

			sum_A = gv_tuples(matC, i, j) + currentA->value;

			set_tuples(matC, i, j, sum_A); //set new node in matrix C
			
			currentA = currentA->next;
		}
		while(currentB != NULL)
		{
			i = currentB->row;
			j = currentB->col;

			sum_B = gv_tuples(matC, i, j) + currentB->value;

			set_tuples(matC, i, j, sum_B); //set new node in matrix C

			currentB = currentB->next;
		}

		non_zero(matC);
		
		return matC;	
	}
	else
	{
		return NULL; //incompatible dimensions
	}	
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB) 
{ 
	if(matA->n == matB->m)
	{
		sp_tuples * matC = (sp_tuples*)malloc(sizeof(sp_tuples)); //initialising the matrix C
		matC->m = matA->m;
		matC->n = matA->n;
		matC->nz = 0;
		matC->tuples_head = NULL;

		sp_tuples_node * currentA = matA->tuples_head;

		int iA, jA, iB, jB;
		double product = 0;

		while(currentA != NULL) //begin multiplication algorithm
		{
			iA = currentA->row;
			jA = currentA->col;
			
			sp_tuples_node * currentB = matB->tuples_head;

			while(currentB != NULL)
			{
				iB = currentB->row;
				jB = currentB->col;
			
				if(iB == jA)
				{
					product = gv_tuples(matC, iA, jB) + currentA->value*currentB->value;
				
					set_tuples(matC, iA, jB, product);
				}

				currentB = currentB->next;
			}

			currentA = currentA->next;
		}

		non_zero(matC);

		return matC;				
	}
	else
	{
		return NULL; //incompatible dimensions
	}
}


	
void destroy_tuples(sp_tuples * mat_t) 
{
	sp_tuples_node * delete = mat_t->tuples_head;
	sp_tuples_node * temp;

	while(delete != NULL)
	{
		temp = delete;
		delete = delete->next;
		free(temp);
	}
	mat_t->tuples_head = NULL;
	free(mat_t);	
}  




