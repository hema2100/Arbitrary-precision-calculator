#include "apc.h"

int subtraction(node *tail1, node *tail2, node **headR, node **tailR)
{
    node *head1;                                  // Head of the first operand
    node *head2;                                 // Head of the second operand
    node *temp;                                 // Temporarily stores a tail pointer when operands are swapped
    int borrow = 0;                            // Stores the borrow between digit positions
    int diff;                                 // Stores the current digit difference
    int sign = 1;                            // Stores the sign of the result

    if (headR == NULL || tailR == NULL)    // Checks result pointer arguments
        return FAILURE;                   // Rejects invalid result pointers
    *headR = NULL;                       // Initializes the result head
    *tailR = NULL;                      // Initializes the result tail
    if (tail1 == NULL || tail2 == NULL)// Checks operand tails
        return FAILURE;               // Rejects missing operands

    head1 = tail1;                  // Starts at the first operand tail
    head2 = tail2;                 // Starts at the second operand tail
    while (head1->prev != NULL)   // Finds the first operand head
        head1 = head1->prev;     // Moves toward the head
    while (head2->prev != NULL) // Finds the second operand head
        head2 = head2->prev;   // Moves toward the head

    if (compare_list(head1, head2) == OPERAND2)     // Checks whether the second operand is larger
    {
        sign = -1;                                // Marks the result as negative
        temp = tail1;                            // Saves the first operand tail
        tail1 = tail2;                          // Uses the larger operand as the minuend
        tail2 = temp;                          // Uses the smaller operand as the subtrahend
    }

    while (tail1 != NULL)                    // Processes digits from right to left
    {
        diff = tail1->data - borrow;       // Applies the previous borrow
        if (tail2 != NULL)                // Checks whether a second operand digit remains
            diff -= tail2->data;         // Subtracts the matching digit
        if (diff < 0)                   // Checks whether borrowing is required
        {
            diff += 10;               // Adds ten to the current digit
            borrow = 1;              // Sets the borrow for the next digit
        }
        else
            borrow = 0;             // Clears the borrow when it is not needed

        if (insert_first(headR, tailR, diff) == FAILURE)             // Prepends the result digit
        {
            delete_list(headR, tailR);                             // Frees the partial result
            return FAILURE;                                       // Reports allocation failure
        }
        tail1 = tail1->prev;                                     // Moves to the previous minuend digit
        if (tail2 != NULL)                                      // Checks whether the subtrahend has another digit
            tail2 = tail2->prev;                               // Moves to the previous subtrahend digit
    }

    remove_pre_zeros(headR);                                   // Removes leading zeros from the result
    if (sign == -1 && *headR != NULL && (*headR)->data != 0)  // Applies a negative sign to a nonzero result
        (*headR)->data *= -1;                                // Stores the sign in the first digit for printing
    return SUCCESS;                                         // Reports successful subtraction
}
