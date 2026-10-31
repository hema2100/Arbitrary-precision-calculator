
#include "apc.h"

// Performs addition of two numbers stored in reverse digit order.
int addition(node *tail1, node *tail2, node **headR, node **tailR)
{
    int carry = 0;
    int sum;

    while (tail1 != NULL || tail2 != NULL || carry != 0)
    {
        sum = carry;

        if (tail1 != NULL)
        {
            sum += tail1->data;
            tail1 = tail1->prev;
        }

        if (tail2 != NULL)
        {
            sum += tail2->data;
            tail2 = tail2->prev;
        }

        carry = sum / 10;

        if (insert_first(headR, tailR, sum % 10) == FAILURE)
        {
            delete_list(headR, tailR);
            return FAILURE;
        }
    }

    if (*headR == NULL)
    {
        if (insert_first(headR, tailR, 0) == FAILURE)
            return FAILURE;
    }

    return SUCCESS;
}
