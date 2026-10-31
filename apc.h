/*
Project Name        : Arbitrary Precision Calculator (APC)
Description : Performs arithmetic operations on large non-negative integers
              using doubly linked lists, with each node storing one digit.

Return Type : Integer (int) for status-returning functions;
              void for arithmetic functions that do not return a value.

Input File  : None (operands and operator are provided through command-line arguments).

Output File : None (the arithmetic result is displayed on the console).
*/

#ifndef APC_H
#define APC_H

#include <stdio.h>   // Provides input and output functions
#include <string.h>  // Provides string handling functions
#include <stdlib.h>  // Provides memory allocation and process status constants

typedef struct node
{
    struct node *prev;  // Points to the previous digit node
    int data;           // Stores one decimal digit or a negative leading digit for a negative subtraction result
    struct node *next;  // Points to the next digit node
} node;

#define SUCCESS 1   // Indicates that an operation completed successfully
#define FAILURE 0   // Indicates that an operation failed
#define SAME 0      // Indicates that two numbers are equal
#define OPERAND1 1  // Indicates that the first number is greater
#define OPERAND2 2  // Indicates that the second number is greater

int addition(node *tail1, node *tail2, node **headR, node **tailR);  // Adds two numbers
int subtraction(node *tail1, node *tail2, node **headR, node **tailR);  // Subtracts the second number from the first
int multiplication(node *tail1, node *tail2, node **headR, node **tailR);  // Multiplies two numbers
int division(node *head1, node *head2, node **headR, node **tailR);  // Calculates the integer quotient
int cla_validation(int argc, char *argv[]);  // Validates command-line arguments
int create_list(char *operand, node **head, node **tail);  // Converts a decimal string into a digit list
int insert_first(node **head, node **tail, int data);  // Inserts a digit at the beginning
int insert_last(node **head, node **tail, int data);  // Inserts a digit at the end
int delete_list(node **head, node **tail);  // Frees all nodes in a list
void print_list(node *head);  // Prints the number represented by a list
int multiply_by_digit(node *tail, int digit, node **headR, node **tailR);  // Multiplies a number by one digit
int compare_list(node *head1, node *head2);  // Compares two normalized non-negative numbers
int list_len(node *head);  // Counts the nodes in a list
void remove_pre_zeros(node **head);  // Removes unnecessary leading zeros

#endif
