#include <iostream>
using namespace std;
struct List {
    int value;
    List* xor1;

};


List* XOR(List* a, List* b)
{
    return (List*)((unsigned int)(a) ^ (unsigned int)(b));
}

List* ADD_BEG(List** firstel, int val)
{
    List* newlist = new List();
    newlist->value = val;
    //tworzymy xor dla elememntu ktorego prev to null i next to pierwszy element
    newlist->xor1 = XOR(NULL, *firstel);

    if (*firstel != NULL)
    {
        List* next = XOR((*firstel)->xor1, NULL);
        (*firstel)->xor1 = XOR(newlist, next);
    }
    *firstel = newlist;

    return *firstel;
}


List* GetLast(List** firstel) {


    List* curr = *firstel;
    List* prev = NULL;
    List* next;

    if (*firstel == NULL)return NULL;


    while (curr != NULL)
    {
        next = XOR(prev, curr->xor1);
        prev = curr;
        curr = next;
    }

    return prev;
}




List* add_last(List** firstEl, int val) {
    List* curr = *firstEl;
    List* prev = NULL;
    List* next;


    if (*firstEl == NULL) {
        *firstEl = new List();
        (*firstEl)->value = val;
        (*firstEl)->xor1 = XOR(NULL, NULL);
        return *firstEl;
    }
    else {

        List* newlist = new List();
        List* last = NULL;

        while (true)
        {
            if (curr == NULL) {
                break;
            }
            next = XOR(prev, curr->xor1);
            if (next == NULL)last = prev;

            prev = curr;
            curr = next;


        }

        newlist->value = val;

        newlist->xor1 = XOR(GetLast(firstEl), NULL);
        GetLast(firstEl)->xor1 = XOR(last, newlist);



        return newlist;
    }
}


void PRINT_FORWARD(List* firstEl)
{
    List* act = firstEl;
    List* prev = NULL;
    List* next;

    while (true)
    {
        if (act == NULL)break;
        printf("%d ", act->value);
        next = XOR(prev, act->xor1);
        prev = act;
        act = next;
    }
}

void PRINT_BACKWARD(List** head) {
    List* backwards = NULL;
    List* act = *head;
    List* prev = NULL;
    List* next;

    while (act != NULL) {
        next = XOR(prev, act->xor1);

        ADD_BEG(&backwards, act->value);
        prev = act;
        act = next;

    }
    PRINT_FORWARD(backwards);

}

List* getpos(List* head, int x) {
    List* act = head;
    List* prev = NULL;
    List* next;
    while (act != NULL) {
        if (x == 0) {
            return act;
        }
        x = x - 1;
        next = XOR(prev, act->xor1);
        prev = act;
        act = next;
    }
    return NULL;
}
void DEL_END(List** firstEl) {

    if (*firstEl != NULL) {
        List* act = *firstEl;
        List* prev = NULL;
        List* next;

        while (act != 0) {
            next = XOR(prev, act->xor1);
            if (XOR(act->xor1, prev) == NULL) {
                if (prev != NULL) {
                    prev->xor1 = XOR(XOR(prev->xor1, act), NULL);
                    break;
                }
                else if (prev == NULL) {
                    *firstEl = NULL;
                    break;

                }
            }
            prev = act;
            act = next;
        }
    }

}


void DEL_BEG(List** firstEl) {

    List* act = *firstEl;
    *firstEl = XOR(NULL, act->xor1);

    if (*firstEl != NULL) {
        List* next = XOR(act, (*firstEl)->xor1);
        (*firstEl)->xor1 = XOR(NULL, next);

    }
}
void DEL_ACT(List** firstEl, int currpos, int count) {
    List* torem = getpos(*firstEl, currpos);

    List* curr = *firstEl;
    List* prev = NULL;
    List* next;

    while (curr != 0) {

        next = XOR(prev, curr->xor1);


        if (curr == torem) {
            if (next == NULL) {
                DEL_END(firstEl);
                //cout << "end";
                break;

            }
            else if (curr == *firstEl) {
                DEL_BEG(firstEl);
                //cout << "beg";
                break;
            }
            else if (prev != NULL && curr != *firstEl && next != NULL) {
                while (next != 0) {
                    curr->value = next->value;
                    next = XOR(prev, curr->xor1);
                    prev = curr;
                    curr = next;
                }
                DEL_END(firstEl);

            }



        }


        prev = curr;
        curr = next;
    }

}




void DEL_VAL(List** firstEl, int val, int& rep) {
    if (*firstEl != NULL) {
        List* act = *firstEl;
        List* prev = NULL;
        List* next;

        int licznik = 0;


        while (act != NULL) {

            next = XOR(prev, act->xor1);


            if (act->value == val && next != NULL) {

                DEL_ACT(firstEl, licznik, 0);
                if (rep == 0) break;
                else {
                    rep--;
                    continue;
                }
            }
            else if (next == NULL) {
                DEL_END(firstEl);

                break;
            }
            else if (act == *firstEl) {
                if (val == act->value) {
                    DEL_BEG(firstEl);

                    break;
                }
            }
            //

            licznik++;
            prev = act;

            act = next;

        }

    }
}







List* ADD_ACT(List** head, int value, int position) {
    List* curr = *head;
    List* prev = NULL;
    List* next = XOR(prev, curr->xor1);

    if (*head == NULL) {
        ADD_BEG(head, value);
        //  cout << "tu";
    }
    else {
        int x = 1;

        for (int i = 1; i < position - 1; i++) {
            if (next != NULL) {
                prev = curr;
                curr = next;
                next = XOR(prev, curr->xor1);
                x++;
            }
        }

        if (x == position - 1) {
            List* node = new List();
            List* temp = XOR(curr->xor1, next);
            curr->xor1 = XOR(temp, node);

            if (next != NULL) {
                next->xor1 = XOR(node, XOR(next->xor1, curr));
            }
            node->xor1 = XOR(curr, next);
            node->value = value;
        }
        else if (position == 1) {

            ADD_BEG(head, value);
        }

    }
    return *head;

}
void countreps(List** firstEl, int val, int& licznik) {

    List* act = *firstEl;
    List* next;
    List* prev = NULL;

    while (act != 0) {
        next = XOR(prev, act->xor1);

        if (act->value == val)licznik++;

        prev = act;
        act = next;
    }
}

int main() {
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);

    List* lista = new List();
    lista = NULL;



    char opt[20];
    int val;
    int currnposition = 0;
    int count = 0;
    int repeats = 0;

    while (cin >> opt)
    {


        if (strcmp(opt, "ADD_BEG") == 0) {
            if (lista != NULL)currnposition++;

            cin >> val;

            ADD_BEG(&lista, val);
            count++;

        }
        else if (strcmp(opt, "ACTUAL") == 0) {

            if (getpos(lista, currnposition) == NULL) {
                printf("NULL\n");
            }
            else {
                printf("%d\n", getpos(lista, currnposition)->value);
            }

        }
        else if (strcmp(opt, "NEXT") == 0) {
            currnposition++;
            if (currnposition == count)currnposition = 0;
            if (getpos(lista, currnposition) == NULL) {
                printf("NULL\n");
            }
            else {
                printf("%d\n", getpos(lista, currnposition)->value);
            }

        }
        else if (strcmp(opt, "PREV") == 0) {
            currnposition--;
            if (currnposition == -1)currnposition = count - 1;
            if (lista == NULL)currnposition = 0;
            if (getpos(lista, currnposition) == NULL) {
                printf("NULL\n");
            }
            else {
                printf("%d\n", getpos(lista, currnposition)->value);
            }

        }
        else if (strcmp(opt, "ADD_END") == 0) {
            cin >> val;
            add_last(&lista, val);
            count++;

        }
        else if (strcmp(opt, "ADD_ACT") == 0) {
            cin >> val;


            ADD_ACT(&lista, val, ++currnposition);
            count++;
        }
        else if (strcmp(opt, "DEL_BEG") == 0) {
            DEL_BEG(&lista);
            currnposition--;
            count--;

        }
        else if (strcmp(opt, "DEL_END") == 0) {
            DEL_END(&lista);
            count--;
        }
        else if (strcmp(opt, "DEL_VAL") == 0) {
            cin >> val;
            countreps(&lista, val, repeats);
            repeats = repeats - 1;
            DEL_VAL(&lista, val, repeats);



        }
        else if (strcmp(opt, "DEL_ACT") == 0) {
            DEL_ACT(&lista, currnposition, count);
        }
        else if (strcmp(opt, "PRINT_FORWARD") == 0) {
            PRINT_FORWARD(lista);
            printf("\n");


        }
        else if (strcmp(opt, "PRINT_BACKWARD") == 0) {
            //
            PRINT_BACKWARD(&lista);
            printf("\n");

        }
        //cout << endl << currnposition << endl;
    }



    return 0;
}