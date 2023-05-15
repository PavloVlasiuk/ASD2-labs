#include "circList.c"


int main() {
    unsigned int n;
    unsigned int k;

    printf("Enter the number of elements in the list: ");
    scanf("%d", &n);

    if (n == 0) {
        printf("You've entered wrong number of elements");
        return 0;
    }

    printf("Enter the number of elements to shift: ");
    scanf("%d", &k);

    if (k > n) {
        printf("You've entered wrong number of elements to shift");
        return 0;
    }

    node *tail = createCircList(n);
    printf("Initial view of the list:\n");
    printList(tail->next);

    node *head = displaceElements(tail, k);
    printf("View of the list after shifting:\n");
    printList(head);

    listFree(head);
    printf("The list has been cleared");

    return 0;
}
