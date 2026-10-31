#include "apc.h"

int division(node *head1, node *head2, node **headR, node **tailR)
{
    node *remHead = NULL;  // Head of the running remainder
    node *remTail = NULL;  // Tail of the running remainder
    node *subHead = NULL;  // Head of a temporary subtraction result
    node *subTail = NULL;  // Tail of a temporary subtraction result
    node *tail1;  // Tail of the dividend
    node *tail2;  // Tail of the divisor
    node *temp;  // Traversal pointer for divisor validation
    int count;  // Stores the current quotient digit
    int status = SUCCESS;  // Tracks whether list operations succeed

    if (headR == NULL || tailR == NULL)  // Checks result pointer arguments
        return FAILURE;  // Rejects invalid result pointers
    *headR = NULL;  // Initializes the result head
    *tailR = NULL;  // Initializes the result tail
    if (head1 == NULL || head2 == NULL)  // Checks operand lists
        return FAILURE;  // Rejects missing operands

    for (temp = head2; temp != NULL; temp = temp->next)  // Scans the divisor digits
    {
        if (temp->data != 0)  // Checks for a nonzero digit
            break;  // Confirms that the divisor is nonzero
    }
    if (temp == NULL)  // Detects a divisor containing only zeros
        return FAILURE;  // Rejects division by zero

    tail2 = head2;  // Starts at the divisor head
    while (tail2->next != NULL)  // Finds the divisor tail
        tail2 = tail2->next;  // Advances toward the tail

    while (head1 != NULL && status == SUCCESS)  // Processes dividend digits from left to right
    {
        status = insert_last(&remHead, &remTail, head1->data);  // Appends the next dividend digit to the remainder
        if (status == FAILURE)  // Checks remainder allocation
            break;  // Stops on failure
        remove_pre_zeros(&remHead);  // Normalizes the running remainder
        count = 0;  // Initializes the current quotient digit

        while (compare_list(remHead, head2) != OPERAND2)  // Repeats while the remainder is at least the divisor
        {
            tail1 = remTail;  // Uses the current remainder tail
            status = subtraction(tail1, tail2, &subHead, &subTail);  // Subtracts the divisor from the remainder
            if (status == FAILURE)  // Checks subtraction status
                break;  // Stops on failure
            delete_list(&remHead, &remTail);  // Frees the previous remainder
            remHead = subHead;  // Transfers the new remainder head
            remTail = subTail;  // Transfers the new remainder tail
            subHead = NULL;  // Clears the temporary head after transfer
            subTail = NULL;  // Clears the temporary tail after transfer
            count++;  // Increments the quotient digit
        }

        delete_list(&subHead, &subTail);  // Frees any untransferred temporary result
        if (status == FAILURE)  // Checks whether subtraction failed
            break;  // Stops division on failure
        status = insert_last(headR, tailR, count);  // Appends the quotient digit
        if (status == FAILURE)  // Checks quotient allocation
            break;  // Stops division on failure
        head1 = head1->next;  // Advances to the next dividend digit
    }

    delete_list(&remHead, &remTail);  // Frees the final remainder
    delete_list(&subHead, &subTail);  // Frees any remaining temporary result
    if (status == SUCCESS)  // Checks whether division completed
    {
        remove_pre_zeros(headR);  // Removes leading zeros from the quotient
        if (*headR == NULL)  // Checks whether a quotient digit was produced
            status = insert_first(headR, tailR, 0);  // Creates a zero quotient if necessary
    }
    if (status == FAILURE)  // Handles arithmetic or allocation failure
    {
        delete_list(headR, tailR);  // Frees the partial quotient
        return FAILURE;  // Reports division failure
    }
    return SUCCESS;  // Reports successful integer division
}
