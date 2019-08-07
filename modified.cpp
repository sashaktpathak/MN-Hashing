#include<iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <list>
#define ssi 80000
using namespace std;

class Hash
{
    int BUCKET;
    list<int> *table;
    list<int> *table2[3];
public:
    Hash(int V);
    void insertItem(int x);

    void deleteItem(int key);

    int search_key(int val);

    int search_key2(int val);

    void insertItem2(int x);

    void deleteItem2(int key);

    int hashFunction(int x) {
        return (x % BUCKET);
    }
    int hashFunction2(int x) {
        return (x % 3);
    }

    void displayHash();

    void displayHash2();

};

Hash::Hash(int b)
{
    this->BUCKET = b;
    table = new list<int>[BUCKET];
    table2[0] = new list<int>[BUCKET];
    table2[1] = new list<int>[BUCKET];
    table2[2] = new list<int>[BUCKET];
}

void Hash::insertItem(int key)
{
    int index = hashFunction(key);
    table[index].push_back(key);
}

void Hash::deleteItem(int key)
{
  int index = hashFunction(key);

  list <int> :: iterator i;
  for (i = table[index].begin();
           i != table[index].end(); i++) {
    if (*i == key)
      break;
  }

  if (i != table[index].end())
    table[index].erase(i);
}

void Hash::insertItem2(int key)
{
    int index = hashFunction(key);
    int index2 = hashFunction2(key);
    table2[index2][index].push_back(key);
}

void Hash::deleteItem2(int key)
{
  int index = hashFunction(key);
  int index2 = hashFunction2(key);
  list <int> :: iterator i;
  for (i = table2[index2][index].begin();
           i != table2[index2][index].end(); i++) {
    if (*i == key)
      break;
  }

  if (i != table2[index2][index].end())
    table2[index2][index].erase(i);
}

int Hash::search_key2(int val) {
    int index = hashFunction(val);
    int index2 = hashFunction2(val);
    for(auto x : table2[index2][index])
        if(x == val)
            return 1;
    return 0;
}
int Hash::search_key(int val) {
    int index = hashFunction(val);
    for(auto x : table[index])
        if(x == val)
            return 1;
    return 0;
}
void Hash::displayHash() {
  for (int i = 0; i < BUCKET; i++) {
    cout << i;
    for (auto x : table[i])
      cout << " --> " << x;
    cout << endl;
  }
}
void Hash::displayHash2() {
  for (int i = 0; i < BUCKET; i++) {
    cout << i;
    cout << " 1 => ";
    for (auto x : table2[0][i])
      cout << " --> " << x;

    cout << " 2 => ";
    for (auto x : table2[1][i])
      cout << " --> " << x;
    cout << " 3 => ";
    for (auto x : table2[2][i])
      cout << " --> " << x;
    cout << endl;
  }
}
//=============================***********************************************========================================================

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
    if(ar[index].values[index2].value == INT_MIN)
        return 0;
    if(ar[index].values[index2].value == val)
        return 1;
    else
    {
        Node *ptr = ar[index].values[index2].next;
        if(ptr->key == val)
            return 1;
        while(ptr != NULL && ptr->key != val)
        {

            if(ptr->key > val)
                ptr = ptr->left;
            else
                ptr = ptr->right;
            if(ptr->key == val)
                return 1;
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
//=================================================================%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%-------------------------------
int lpa[ssi]={-1},lpa2[ssi]={-1};
void insertLinearProbing(int val)
{
    int hv = val % 10;
    int i=0;
    while(lpa[(hv+i)%ssi]!=-0&&i<ssi)
    {
        i++;

    }
    //cout<<hv+i;
    lpa[(hv+i)%ssi] = val;
}
int searchLinearProbing(int val)
{
int hv = val % 10;
    int i = 0,cnt=0;
    while(cnt<=ssi&&lpa[(hv+i)%ssi]!=val)
        {
            //cout<<hv+i<<"->"<<lpa[hv+i]<<"\n";
            i++,cnt++;
        }
    if(lpa[(hv+i)%ssi]==val)
        return 1;
    else
        return 0;
}
void insertQuadraticProbing(int val)
{
    int hv = val % 10;
    int i=0;
    while(lpa2[(hv+(i*i))%ssi]!=-0&&i<ssi)
    {
        i++;

    }
    //cout<<hv+i;
    lpa2[(hv+(i*i))%ssi] = val;
}
int searchQuadraticProbing(int val)
{
    int hv = val % 10;
    int i = 0,cnt=0;
    while(cnt<=ssi&&lpa2[(hv+(i*i))%ssi]!=val)
        {
            //cout<<hv+i<<"->"<<lpa[hv+i]<<"\n";
            i++,cnt++;
        }
    if(lpa2[(hv+(i*i))%ssi]==val)
        return 1;
    else
        return 0;
}
//-------------------------------==========================%%%%%%%%%%%%%%%%%%%%%%%%%%===================------------------------------------
//-==-==-==-=---------------------------------------------------------------------==========================================================--

int linear_array[ssi];
int find_linear_array(int value)
{
    for(int i=0;i<ssi;i++)
    {
        if(linear_array[i]==value)
            return i;
    }
    return 0;
}
void insert_linear(int a)
{
    static int i =0;
    linear_array[i++]= a;
}
//-=========================----=================================================================---------------------------============-----------
int main()
{
  srand(time(NULL));
  int a[ssi];
  int i = 1;
  for(int j = 0 ;j<ssi;j++,i+=10)
      a[j] = j;
  int n = sizeof(a)/sizeof(a[0]);
  cout<<n<<endl;
  Hash h(10);

  for (int i = 0; i < n; i++)
    h.insertItem(a[i]), h.insertItem2(a[i]), insertItem3(a[i]),insertLinearProbing(a[i]),insertQuadraticProbing(a[i]),insert_linear(a[i]);

  int val = ssi-3;
  auto start = std::chrono::high_resolution_clock::now();
  int result = find_linear_array(val);
  for(int i = 0;i<ssi;i++)
    result = find_linear_array(val);
  auto elapsed = std::chrono::high_resolution_clock::now() - start;
  long long microseconds0 = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
  cout<<"TIME Linear : "<<microseconds0<<"-o>"<<result<<endl;

  start = std::chrono::high_resolution_clock::now();
  for(int i = 0;i<ssi;i++)
    result = h.search_key(val);
  elapsed = std::chrono::high_resolution_clock::now() - start;
  long long microseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
  cout<<"TIME SC : "<<microseconds;
  float perc = ((microseconds0 - microseconds)*100.0)/microseconds0;
  cout<<"\n Improved by:\t"<<perc;
  if(result == 1)
    cout<<" Found\n";

  start = std::chrono::high_resolution_clock::now();
  result =  h.search_key(val);
  for(int i = 0;i<ssi;i++)
    result = h.search_key2(val);
  elapsed = std::chrono::high_resolution_clock::now() - start;
  long long microseconds2 = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
  //cout<<"TIME 2 : "<<microseconds2;
   perc = ((microseconds0 - microseconds2)*100.0)/microseconds0;
  //cout<<"\n Improved by:\t"<<perc;
    //if(result == 1)
    //cout<<" Found\n";
    //else
    //cout<<"Not Found\n";
    //cout<<"--";
  start = std::chrono::high_resolution_clock::now();

  for(int i = 0;i<ssi;i++)
    result = search_key3(val);
  elapsed = std::chrono::high_resolution_clock::now() - start;

  long long microseconds3 = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
  cout<<"TIME PA: "<<microseconds3;
  perc = ((microseconds0 - microseconds3)*100.0)/microseconds0;
  cout<<"\n Improved by:\t"<<perc;
  if(result == 1)
    cout<<" Found\n";

  start = std::chrono::high_resolution_clock::now();
  for(int i = 0;i<ssi;i++)
    searchLinearProbing(val);
  elapsed = std::chrono::high_resolution_clock::now() - start;
  long long microseconds4 = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
  cout<<"TIME LP : "<<microseconds4;
  perc = ((microseconds0 - microseconds4)*100.0)/microseconds0;
  cout<<"\n Improved by:\t"<<perc;

start = std::chrono::high_resolution_clock::now();
  for(int i = 0;i<ssi;i++)
    searchQuadraticProbing(val);
  elapsed = std::chrono::high_resolution_clock::now() - start;
  long long microseconds5 = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
  cout<<"TIME QP : "<<microseconds5;
  perc = ((microseconds0 - microseconds5)*100.0)/microseconds0;
  cout<<"\n Improved by:\t"<<perc;



  return 0;
}
