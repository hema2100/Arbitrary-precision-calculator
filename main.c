#include "apc.h"

int main(int argc, char *argv[])
{
    node *head1 = NULL;                                                 // Head of the first operand list
    node *tail1 = NULL;                                                // Tail of the first operand list
    node *head2 = NULL;                                               // Head of the second operand list
    node *tail2 = NULL;                                              // Tail of the second operand list
    node *headR = NULL;                                             // Head of the result list
    node *tailR = NULL;                                            // Tail of the result list
    int status = FAILURE;                                         // Stores the selected operation's status

    if (cla_validation(argc, argv) == FAILURE)                  // Validates command-line arguments
        return EXIT_FAILURE;                                   // Exits after a validation error message

    if (create_list(argv[1], &head1, &tail1) == FAILURE)     // Creates the first operand list
    {
        fprintf(stderr, "Error: Memory allocation failed\n");  // Reports list allocation failure
        delete_list(&head1, &tail1);                               // Frees any partially created first list
        return EXIT_FAILURE;                                                // Stops the program
    }

    if (create_list(argv[3], &head2, &tail2) == FAILURE)                  // Creates the second operand list
    {
        fprintf(stderr, "Error: Memory allocation failed\n");           // Reports list allocation failure
        delete_list(&head1, &tail1);                                   // Frees the first operand list
        delete_list(&head2, &tail2);                                  // Frees any partially created second list
        return EXIT_FAILURE;                                         // Stops the program
    }

    remove_pre_zeros(&head1);  // Normalizes the first operand
    remove_pre_zeros(&head2);  // Normalizes the second operand

    switch (argv[2][0])                                           // Selects the requested arithmetic operation
    {
        case '+':
            status = addition(tail1, tail2, &headR, &tailR);              // Adds the operands
            break;                                                     
        case '-':
            status = subtraction(tail1, tail2, &headR, &tailR);        // Subtracts the operands
            break;                                                   
        case 'x':
        case 'X':
            status = multiplication(tail1, tail2, &headR, &tailR);  // Multiplies the operands
            break;                                              
        case '/':
            status = division(head1, head2, &headR, &tailR);     // Calculates the integer quotient
            break;                                           
        default:
            status = FAILURE;                                 // Marks an unsupported operation as failed
            break;                                        
    }

    if (status == SUCCESS)                                 // Checks whether the operation completed successfully
        print_list(headR);                                // Displays the arithmetic result
    else
        fprintf(stderr, "Error: Calculation failed\n");   // Reports an arithmetic or allocation failure

    delete_list(&head1, &tail1);                         // Frees the first operand list
    delete_list(&head2, &tail2);                        // Frees the second operand list
    delete_list(&headR, &tailR);                       // Frees the result list

    return status == SUCCESS ? EXIT_SUCCESS : EXIT_FAILURE;  // Returns the process status
}
