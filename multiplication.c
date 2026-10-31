#include "apc.h"

int multiply_by_digit(node *tail, int digit, node **headR, node **tailR)
{
    int carry = 0;  // Stores the carry from the previous multiplication

    if (headR == NULL || tailR == NULL || digit < 0 || digit > 9)  // Checks arguments and the single digit
        return FAILURE;  // Rejects invalid arguments
    *headR = NULL;  // Initializes the result head
    *tailR = NULL;  // Initializes the result tail

    while (tail != NULL || carry != 0)  // Processes operand digits and remaining carry
    {
        int product = carry;  // Starts with the previous carry
        int result_digit;  // Stores the current result digit
        if (tail != NULL)  // Checks whether an operand digit remains
        {
            product += tail->data * digit;  // Multiplies the current digit by the single digit
            tail = tail->prev;  // Moves to the previous digit
        }
        result_digit = product % 10;  // Extracts the current result digit
        carry = product / 10;  // Calculates the next carry
        if (insert_first(headR, tailR, result_digit) == FAILURE)  // Prepends the result digit
        {
            delete_list(headR, tailR);  // Frees the partial result
            return FAILURE;  // Reports allocation failure
        }
    }

    if (*headR == NULL && insert_first(headR, tailR, 0) == FAILURE)  // Creates zero for an empty product
    {
        delete_list(headR, tailR);  // Frees the partial result
        return FAILURE;  // Reports allocation failure
    }
    remove_pre_zeros(headR);  // Removes unnecessary leading zeros
    return SUCCESS;  // Reports successful single-digit multiplication
}

int multiplication(node *tail1, node *tail2, node **headR, node **tailR)
{
    node *partialHead = NULL;  // Head of the current partial product
    node *partialTail = NULL;  // Tail of the current partial product
    node *sumHead = NULL;  // Head of the accumulated product
    node *sumTail = NULL;  // Tail of the accumulated product
    node *accHead = NULL;  // Head of the running accumulated result
    node *accTail = NULL;  // Tail of the running accumulated result
    node *digitTail;  // Traverses the second operand from right to left
    int shift = 0;  // Counts decimal-place shifts
    int i;  // Loop counter for appending positional zeros
    int status = SUCCESS;  // Tracks operation status

    if (tail1 == NULL || tail2 == NULL || headR == NULL || tailR == NULL)  // Checks function arguments
        return FAILURE;  // Rejects invalid arguments
    *headR = NULL;  // Initializes the result head
    *tailR = NULL;  // Initializes the result tail

    digitTail = tail2;  // Starts at the least significant digit of the second operand
    while (digitTail != NULL && status == SUCCESS)  // Processes each digit of the second operand
    {
        status = multiply_by_digit(tail1, digitTail->data, &partialHead, &partialTail);  // Calculates one partial product
        if (status == FAILURE)  // Checks partial multiplication status
            break;  // Stops on failure

        for (i = 0; i < shift; i++)  // Adds zeros for the decimal-place shift
        {
            status = insert_last(&partialHead, &partialTail, 0);  // Appends one positional zero
            if (status == FAILURE)  // Checks allocation status
                break;  // Stops shifting on failure
        }
        if (status == FAILURE)  // Checks whether shifting failed
            break;  // Stops multiplication on failure

        if (accHead == NULL)  // Checks whether this is the first partial product
        {
            accHead = partialHead;  // Transfers the partial product head to the accumulator
            accTail = partialTail;  // Transfers the partial product tail to the accumulator
            partialHead = NULL;  // Clears the transferred partial head
            partialTail = NULL;  // Clears the transferred partial tail
        }
        else
        {
            status = addition(accTail, partialTail, &sumHead, &sumTail);  // Adds the new partial product to the accumulator
            if (status == FAILURE)  // Checks addition status
                break;  // Stops multiplication on failure
            delete_list(&accHead, &accTail);  // Frees the previous accumulator
            delete_list(&partialHead, &partialTail);  // Frees the partial product
            accHead = sumHead;  // Transfers the sum head to the accumulator
            accTail = sumTail;  // Transfers the sum tail to the accumulator
            sumHead = NULL;  // Clears the transferred sum head
            sumTail = NULL;  // Clears the transferred sum tail
        }
        digitTail = digitTail->prev;  // Moves to the next more significant multiplier digit
        shift++;  // Increases the decimal-place shift for the next partial product
    }

    delete_list(&partialHead, &partialTail);  // Frees any partial product left after a failure
    delete_list(&sumHead, &sumTail);  // Frees any temporary sum left after a failure
    if (status == FAILURE)  // Checks whether multiplication failed
    {
        delete_list(&accHead, &accTail);  // Frees the partial accumulated result
        return FAILURE;  // Reports multiplication failure
    }

    if (accHead == NULL && insert_first(&accHead, &accTail, 0) == FAILURE)  // Creates zero if no partial product exists
        return FAILURE;  // Reports allocation failure
    remove_pre_zeros(&accHead);  // Removes unnecessary leading zeros
    *headR = accHead;  // Transfers the final result head
    *tailR = accTail;  // Transfers the final result tail
    return SUCCESS;  // Reports successful multiplication
}
