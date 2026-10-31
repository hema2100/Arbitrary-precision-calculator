#include "apc.h"

int cla_validation(int argc, char *argv[])
{
    int i;  // Loop counter

    if (argc != 4)  // Requires two operands and one operator
    {
        fprintf(stderr, "Error: Invalid arguments\n");  // Reports missing or extra arguments
        return FAILURE;  // Stops validation
    }

    if (argv[1][0] == '\0' || argv[3][0] == '\0')  // Checks for empty operands
    {
        fprintf(stderr, "Error: Invalid operand\n");  // Reports an empty operand
        return FAILURE;  // Stops validation
    }

    for (i = 0; argv[1][i] != '\0'; i++)  // Checks every character in the first operand
    {
        if (argv[1][i] < '0' || argv[1][i] > '9')  // Allows decimal digits only
        {
            fprintf(stderr, "Error: Invalid operand\n");  // Reports an invalid first operand
            return FAILURE;  // Stops validation
        }
    }

    for (i = 0; argv[3][i] != '\0'; i++)  // Checks every character in the second operand
    {
        if (argv[3][i] < '0' || argv[3][i] > '9')  // Allows decimal digits only
        {
            fprintf(stderr, "Error: Invalid operand\n");  // Reports an invalid second operand
            return FAILURE;  // Stops validation
        }
    }

    if (strlen(argv[2]) != 1)  // Requires a single-character operator
    {
        fprintf(stderr, "Error: Invalid operator\n");  // Reports an invalid operator
        return FAILURE;  // Stops validation
    }

    if (argv[2][0] != '+' && argv[2][0] != '-' && argv[2][0] != 'x' && argv[2][0] != 'X' && argv[2][0] != '/')  // Checks supported operators
    {
        fprintf(stderr, "Error: Invalid operator\n");  // Reports an unsupported operator
        return FAILURE;  // Stops validation
    }

    if (argv[2][0] == '/')  // Checks the divisor before division
    {
        for (i = 0; argv[3][i] == '0'; i++)  // Skips leading zeros in the divisor
            ;  // Advances to the first nonzero digit

        if (argv[3][i] == '\0')  // Detects a divisor containing only zeros
        {
            fprintf(stderr, "Error: Division by zero\n");  // Reports division by zero
            return FAILURE;  // Stops validation
        }
    }

    return SUCCESS;  // Confirms that the arguments are valid
}

int create_list(char *operand, node **head, node **tail)
{
    int i;  // Loop counter

    if (operand == NULL || head == NULL || tail == NULL)  // Checks function arguments
        return FAILURE;  // Rejects invalid pointers

    *head = NULL;  // Initializes the list head
    *tail = NULL;  // Initializes the list tail

    for (i = 0; operand[i] != '\0'; i++)  // Traverses the operand from left to right
    {
        if (insert_last(head, tail, operand[i] - '0') == FAILURE)  // Converts the character to a digit and appends it
        {
            delete_list(head, tail);  // Frees the partially created list
            return FAILURE;  // Reports list creation failure
        }
    }

    return SUCCESS;  // Reports successful list creation
}

int insert_first(node **head, node **tail, int data)
{
    node *new_node;  // Stores the newly allocated node

    if (head == NULL || tail == NULL)  // Checks pointer arguments
        return FAILURE;  // Rejects invalid pointers

    new_node = malloc(sizeof(node));  // Allocates memory for the new node
    if (new_node == NULL)  // Checks allocation failure
        return FAILURE;  // Reports insertion failure

    new_node->data = data;  // Stores the digit
    new_node->prev = NULL;  // Sets the previous link to NULL
    new_node->next = *head;  // Links the new node to the current head

    if (*head == NULL)  // Checks whether the list is empty
    {
        *head = new_node;  // Sets the new node as the head
        *tail = new_node;  // Sets the new node as the tail
    }
    else
    {
        (*head)->prev = new_node;  // Links the old head back to the new node
        *head = new_node;  // Updates the head pointer
    }

    return SUCCESS;  // Reports successful insertion
}

int insert_last(node **head, node **tail, int data)
{
    node *new_node;  // Stores the newly allocated node

    if (head == NULL || tail == NULL)  // Checks pointer arguments
        return FAILURE;  // Rejects invalid pointers

    new_node = malloc(sizeof(node));  // Allocates memory for the new node
    if (new_node == NULL)  // Checks allocation failure
        return FAILURE;  // Reports insertion failure

    new_node->data = data;  // Stores the digit
    new_node->next = NULL;  // Sets the next link to NULL
    new_node->prev = *tail;  // Links the new node to the current tail

    if (*tail == NULL)  // Checks whether the list is empty
    {
        *head = new_node;  // Sets the new node as the head
        *tail = new_node;  // Sets the new node as the tail
    }
    else
    {
        (*tail)->next = new_node;  // Links the old tail to the new node
        *tail = new_node;  // Updates the tail pointer
    }

    return SUCCESS;  // Reports successful insertion
}

int delete_list(node **head, node **tail)
{
    node *temp;  // Temporarily stores the node being deleted

    if (head == NULL || tail == NULL)  // Checks pointer arguments
        return FAILURE;  // Rejects invalid pointers

    while (*head != NULL)  // Continues until all nodes are freed
    {
        temp = *head;  // Saves the current head node
        *head = (*head)->next;  // Advances the head pointer
        free(temp);  // Releases the old head node
    }

    *tail = NULL;  // Resets the tail pointer
    return SUCCESS;  // Reports successful deletion
}

void print_list(node *head)
{
    if (head == NULL)  // Checks whether the result list is empty
    {
        printf("0\n");  // Prints zero for an empty result
        return;  // Stops printing
    }

    while (head != NULL)  // Traverses the result from left to right
    {
        printf("%d", head->data);  // Prints the current digit
        head = head->next;  // Advances to the next node
    }

    printf("\n");  // Ends the output line
}

int list_len(node *head)
{
    int count = 0;  // Initializes the node count

    while (head != NULL)  // Traverses the linked list
    {
        count++;  // Counts the current node
        head = head->next;  // Advances to the next node
    }

    return count;  // Returns the number of nodes
}

int compare_list(node *head1, node *head2)
{
    int len1;  // Stores the first number's digit count
    int len2;  // Stores the second number's digit count

    if (head1 == NULL || head2 == NULL)  // Checks whether either list is missing
        return SAME;  // Avoids dereferencing an invalid list

    len1 = list_len(head1);  // Counts the first number's digits
    len2 = list_len(head2);  // Counts the second number's digits

    if (len1 > len2)  // Checks whether the first number has more digits
        return OPERAND1;  // Indicates that the first number is larger
    if (len2 > len1)  // Checks whether the second number has more digits
        return OPERAND2;  // Indicates that the second number is larger

    while (head1 != NULL && head2 != NULL)  // Compares digits from left to right
    {
        if (head1->data > head2->data)  // Checks the first differing digit
            return OPERAND1;  // Indicates that the first number is larger
        if (head1->data < head2->data)  // Checks the first differing digit
            return OPERAND2;  // Indicates that the second number is larger
        head1 = head1->next;  // Advances the first list
        head2 = head2->next;  // Advances the second list
    }

    return SAME;  // Indicates equal numbers
}

void remove_pre_zeros(node **head)
{
    node *temp;  // Temporarily stores a leading-zero node

    if (head == NULL)  // Checks the head pointer argument
        return;  // Stops for an invalid pointer

    while (*head != NULL && (*head)->data == 0 && (*head)->next != NULL)  // Preserves one zero for zero itself
    {
        temp = *head;  // Saves the leading-zero node
        *head = (*head)->next;  // Advances the head pointer
        (*head)->prev = NULL;  // Clears the new head's previous link
        free(temp);  // Frees the removed leading-zero node
    }
}

