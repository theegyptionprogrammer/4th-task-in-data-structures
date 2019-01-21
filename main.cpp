#include <iostream>
#include <queue>
#define COUNT 10

using  namespace std;
struct Node
{
    int key;
    struct Node *left , *right;
};

struct Node *newnode(int item){

     Node *temp = new Node;
     temp->key   = item;
     temp->left  = NULL;
     temp->right = NULL;
    return  temp;
}

void printTree(struct Node * root , int space){

    if (root==NULL){
        return ;
    }
    printTree(root->right , space);

    space += COUNT;
    cout<<endl;
    for (int i =  COUNT ; i < space ; i++)
        cout<<" ";
        cout<<endl<<root->key;
    printTree(root->left , space);
}

void print2D(struct Node * root){
    printTree(root , 0);
}

struct Node *insert(struct Node * node , int key){

    if (node==NULL){
        return newnode(key);
    }
    else if (key < node->key){
        node->left = insert(node->left, key);
    }
    else if (key > node->key){
        node->right = insert(node->right, key);
    }
    return node;

}

struct Node *search(struct Node * root , int key){

        if (root == NULL || root->key == key ){
            return  root;
        }
        else if (root->key > key){
            root = root->left;
            return search(root , key);
        }
        else if (root->key < key){
            root = root->right;
            return search(root , key);
        }
    return root;
}

int minValueLeaf(struct Node * root){

    struct Node * current = root;
    while (current->left != NULL){
        current = current->left;
    }
    return (current->key);
}

struct Node * minValue(struct Node * root){

    struct Node * current = root;
    while (current->left != NULL){
        current = current->left;
    }
    return current;
}


int maxValueLeaf(struct Node * root){

    struct Node * current = root;
    while (current->right != NULL){
        current = current->right;
    }
    return (current->key);
}

struct Node *Delete(struct Node * root , int key){

    if (root == NULL){
        return root;
    }
    else if (key > root->key){
        root->right = Delete(root->right , key);
    }
    else if (key < root->key){
        root->left = Delete(root->left , key);
    }
    else {
        if (root->right == NULL){
            struct Node *obj = root->left;
            delete(root);
            return obj;
        }
        else if (root->left == NULL){
            struct Node *obj = root->right;
            delete(root);
            return obj;
        }
        struct Node *obj = minValue(root->left);

        root->key = obj->key;

        root->left = Delete(root->left , key);

    }
    return root;
}

int maxHeight(struct Node * node){

    if (node == NULL){
        return 0;
    } else {
        int lheight;
        int rheight;
        lheight = maxHeight(node->left);
        rheight = maxHeight(node->right);
        if (lheight > rheight){
            return lheight+1;
        } else {
            return rheight+1;
        }
    }

}

int getCount(struct Node * root){

    if (!root){
        return 0;
    }
    queue<Node *> Q;
    int count = 0;
    Q.push(root);
    while (!Q.empty()){
        struct Node * temp = Q.front();
        Q.pop();
        if (temp->left && temp->right){
            count++;
        }
        if (temp->left != NULL){
            Q.push(temp->left);
        }
        if (temp->right != NULL){
            Q.push(temp->right);
        }

    }
    return count;
}

void loop (struct Node * root);

void menu(struct Node * root){
    int choice = 0;

    int searchElement;
    int deleteElement;
    cout<<" 1 : search element in bst"<<endl;
    cout<<" 2 : delete element in bst"<<endl;
    cout<<" 3 : print the tree"<<endl;
    cout<<" 4 : get the smallest value in the tree"<<endl;
    cout<<" 5 : get the largest value in the tree"<<endl;
    cout<<" 6 : get the height of the tree"<<endl;
    cout<<" 7 : get the element's count in the tree"<<endl;
    cout<<"enter your choice"<<endl;
    cin>>choice;
    cout<<endl;
    switch (choice){
        case 1:
            cout<<"enter element which you want to search"<<endl;
            cin>>searchElement;
            cout<<endl;
            if (search(root , searchElement)){
                cout<<"this element is in the tree";
            } else {
                cout<<"this element is not in the tree";
            }
            cout<<endl;
            loop(root);
            break;

        case 2:
            cout<<"enter element which you want to delete"<<endl;
            cin>>deleteElement;
            cout<<endl;
            Delete(root , deleteElement);
            print2D(root);
            cout<<endl;
            loop(root);
            break;

        case 3:
            cout<<"binary search tree"<<endl;
            print2D(root);
            cout<<endl;
            loop(root);
            break;

        case 4:
            cout<<"the smallest element in the tree is"<<endl;
            cout<<minValueLeaf(root);
            cout<<endl;
            loop(root);
            break;

        case 5:
            cout<<"the largest element in the tree is"<<endl;
            cout<<maxValueLeaf(root);
            cout<<endl;
            loop(root);
            break;

        case 6:
            cout<<"the height of the tree " <<endl;
            cout<<maxHeight(root);
            cout<<endl;
            loop(root);
            break;

        case 7:
            cout<<"element's count of the tree"<<endl;
            cout<<getCount(root);
            cout<<endl;
            loop(root);
            break;

        default:
            cout<<"sorry your choice is not here try another choice"<<endl;
            menu(root);
            break;

    }

}


int main() {
    struct Node *root;
    root = new Node;
    int elements[100];
    int Size = 0;
    int searchElement;
    int deleteElement;
    cout<<"enter elements number of the tree"<<endl;
    cin>>Size;
    cout<<endl;
    cout<<"enter tree's elements"<<endl;
    for (int i = 0; i < Size; i++) {
        cin>>elements[i];
        insert(root , elements[i]);
    }
    menu(root);

}


void loop(struct Node * root)
{
    char choice ;
    cout<<" f : Continue to the functions"<<endl;
    cout<<" t : create new tree"<<endl;
    cout<<" n : Exit"<<endl;
    cout<<"enter your choice"<<endl;
    cin>>choice;
    cout<<endl;
    while (true){
        if (choice == 'f'){
            menu(root);
        }
        else if (choice == 't'){
            main();
        }
        else if (choice == 'n'){
            return;
        } else {
            cout<<"sorry your choice is not here try another choice"<<endl;
            loop(root);
        }
    }

}