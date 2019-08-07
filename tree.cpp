#include<iostream>
#include<cstdlib>
using namespace std;


struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};


struct segments{
    int value = INT_MIN;
    Node *next = NULL;
};
struct segments_array
{
    segments values[3];
};


//---------------------------------------------------------------------------------------------------------



    int height(struct Node *N)
    {
        if (N == NULL)
            return 0;
        return N->height;
    }

    int max(int a, int b)
    {
        return (a > b)? a : b;
    }

    struct Node* newNode(int key)
    {
        struct Node* node = (struct Node*)
                            malloc(sizeof(struct Node));
        node->key   = key;
        node->left   = NULL;
        node->right  = NULL;
        node->height = 1;  // new node is initially added at leaf
        return(node);
    }

    struct Node *rightRotate(struct Node *y)
    {
        struct Node *x = y->left;
        struct Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right))+1;
        x->height = max(height(x->left), height(x->right))+1;

        return x;
    }

    struct Node *leftRotate(struct Node *x)
    {
        struct Node *y = x->right;
        struct Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right))+1;
        y->height = max(height(y->left), height(y->right))+1;

        return y;
    }

    int getBalance(struct Node *N)
    {
        if (N == NULL)
            return 0;
        return height(N->left) - height(N->right);
    }

    struct Node* insert(struct Node* node, int key)
    {
        if (node == NULL)
            return(newNode(key));

        if (key < node->key)
            node->left  = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else // Equal keys are not allowed in BST
            return node;

        node->height = 1 + max(height(node->left),
                           height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        if (balance > 1 && key > node->left->key)
        {
            node->left =  leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }
    void preOrder(struct Node *root)
    {
        if(root != NULL)
        {
            cout<<root->key<<"--";
            preOrder(root->left);
            preOrder(root->right);
        }
    }

//=============================================================================================================================
segments_array ar[10];
int hashFunction(int x) {
    return (x % 10);
}
int hashFunction2(int x) {
    return (x % 3);
}



void insertItem3(int key)
{
    int index = hashFunction(key);
    int index2 = hashFunction2(key);
    if(ar[index].values[index2].value == INT_MIN)
        ar[index].values[index2].value = key;
    else
    {
        ar[index].values[index2].next = insert(ar[index].values[index2].next,key);
    }
}

int search_key3(int val) {
    int index = hashFunction(val);
    int index2 = hashFunction2(val);
    cout<<"flag1"<<index<<index2;
    if(ar[index].values[index2].value == INT_MIN)
        return 0;
    if(ar[index].values[index2].value == val)
        return 1;
    else
    {
        Node *ptr = ar[index].values[index2].next;
        if(ptr->key == val)
            return 1;
        cout<<"flag3";
        while(ptr != NULL && ptr->key != val)
        {
            if(ptr->key > val)
                ptr = ptr->left;
            else
                ptr = ptr->right;
            if(ptr->key == val)
                return 1;
            cout<<"flag4";
        }
    }
    return 0;
}
void displayHash3() {
  for (int i = 0; i <10; i++) {
    cout << i;
    cout << " 1 => ";
    cout<<ar[i].values[0].value<<" ";
    if(ar[i].values[0].next != NULL)
        preOrder(ar[i].values[0].next);
    cout << " 2 => ";
    cout<<ar[i].values[1].value<<" ";
    if(ar[i].values[1].next != NULL)
        preOrder(ar[i].values[1].next);
    cout << " 3 => ";
    cout<<ar[i].values[2].value<<" ";
    if(ar[i].values[2].next != NULL)
        preOrder(ar[i].values[2].next);
    cout << endl;
  }
}
int main()
{

    insertItem3(13);
    insertItem3(43);
    insertItem3(73);
    insertItem3(103);
    insertItem3(133);
    insertItem3(143);
    insertItem3(173);
    insertItem3(203);
    displayHash3();
    if(search_key3(173))
        cout<<"Found";
    return 0;
}
/*
//================================================================================================================================

index <- hashFunction(key)
index2 <- hashFunction2(key)

if isEmpty(segments_array[index]->segment_value[index2]->value):
        segments_array[index]->segment_value[index2]->value = key
else:
        insert_Node(segments_array[index]->segment_value[index2]->next_node, key)


//---------------------===========================================================================------------------------------

function insert_Node( node, key )
{
    if node == NULL:
            node = newNode(key)
            return node

    if key < node->key:
            insert_Node(node->left, key)
    else if key > node->key:
            insert_Node(node->right, key)
    else:
            return node

    if balance_of_tree > 1 and key < node->left->key:
            return rightRotate(node)

    if balance_of_tree < -1 and key > node->right->key:
            return leftRotate(node)

    if balance_of_tree > 1 and key > node->left->key:
            node->left =  leftRotate(node->left)
            return rightRotate(node)
    if balance_of_tree < -1 and key < node->right->key:
            node->right = rightRotate(node->right)
            return leftRotate(node)
    return node
}

//===========================************************************************============================================================

function leftRotate( node )
{
    x = node
    y = x->right
    z = y->left

    y->left = x
    x->right = z

    return y
}

//========================================================================================================================================

index <- hashFunction(key)
index2 <- hashFunction2(key)

if isEmpty(segments_array[index]->segment_value[index2]->value):
        return False
if segments_array[index]->segment_value[index2]->value == key:
        return True
else:
        ptr = segments_array[index]->segment_value[index2]->next_node
        if ptr->key == key:
            return True
        while ptr != NULL and ptr->key != key:
            if ptr->key > key:
                ptr = ptr->left
            else:
                ptr = ptr->right
            if ptr->key == key
                return True

return False

//--------------------------------------------------------------------------------------------===============================================
*/
