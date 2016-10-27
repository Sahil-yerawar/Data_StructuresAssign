#include<iostream>
using namespace std;
#include<stdlib.h>

struct node{
  //struct node* backptr;
  int fillcount;
  struct node* children[6];
  int keys[5];/*
  struct node*child1;
  int v1;
  struct node*child2;
  int v2;
  struct node*child3;
  int v3;
  struct node*child4;
  int v4;
  struct node*child5;
  int v5;
  struct node*child6;*/
  int isLeaf;
};

class btree{
  private:
      struct node* root;


  public:
      btree(){
          root = createNode();

      }
      struct node* createNode(){
        struct node* x = (struct node*)new node();
        x->fillcount = 0;
        x->isLeaf = 1;
        for(int i = 0; i < 5; i++){
          x->keys[i] = -1;

        }
        for(int i = 0; i < 6; i++){
          x->children[i] = NULL;
        }
      }

      void insert(int x){

        if(root == NULL){
            root = (struct node*)new node();
            root->keys[0] = x;
            root->fillcount = 1;
        }
        else{
          struct node* r = root;
          if(root->fillcount == 4){
            struct node* s = (struct node*)new node();
            root = s;
            s->isLeaf = 0;
            s->fillcount = 0;
            s->children[0] = r;

            insert_split_child(s,0);
            insert_nonfull(s,x);
          }
          else insert_nonfull(r,x);
        }
      }

      void insert_split_child(struct node* a, int c){
        struct node* z = (struct node*)new node();
        struct node* y = a->children[c];      // the concerned filled node
        z->isLeaf = y->isLeaf;
        z->fillcount = 1;
        z->keys[0] = y->keys[3];

        if(y->isLeaf == 0){
          z->children[0] = y->children[4];
          z->children[1] = y->children[5];
        }
        y->fillcount = 2;
        for(int i = 5;i > c;i--){
          a->children[i] = a->children[i-1];
        }
        a->children[c+1] = z;
        for(int i = 4; i >=c; i--){
          a->keys[i] = a->keys[i-1];

        }
        a->keys[c] = y->keys[2];
        a->fillcount++;

      }

      void insert_nonfull(struct node* a, int c){
        int index = a->fillcount;
        int y = index-1;
        if(a->isLeaf){

          while(y >=0 && c < a->keys[y]){
            a->keys[y+1] = a->keys[y];
            y--;
          }
          a->keys[y+1]  = c;
          a->fillcount++;
        }
        else{
          while(y >= 0 && c < a->keys[y])y--;
          y++;
          if(a->children[y]->fillcount == 4){
            insert_split_child(a,y);
            if(c > a->keys[y])y++;
          }
          insert_nonfull(a->children[y],c);

        }
      }

      void traverse(struct node* a){
        int i;
        if( a == NULL){
          cout << "No starting point to begin with" << endl;
        }
        for(i = 0; i < a->fillcount; i++){
          if(a->isLeaf == 0){
            traverse(a->children[i]);
          }

          cout << " "<< a->keys[i];
        }
        if(a->isLeaf == 0)traverse(a->children[i]);
      }

      struct node* getRoot(){return root;}
      struct node* search(int x,struct node* t){
        int i = 0;
        while(i < t->fillcount && x > t->keys[i]){
          i++;
        }
        if(i <t->fillcount && x == t->keys[i]){
          return t;
        }
        else if(t->isLeaf)return NULL;
        else return search(x,t->children[i]);
      }

      struct node* getParent(int x,struct node* parent,struct node* child){
        int i = 0;
        //struct node*base = NULL,b = root;
        while(i < child->fillcount && x > child->keys[i]){
          i++;
        }
        if(i <child->fillcount && x == child->keys[i]){
          return parent;
        }
        else if(child->isLeaf)return NULL;
        else {
          parent = child;
          child = child->children[i];
          return getParent(x,parent,child);
        }
      }
      void del(int x,struct node* a){/*
        struct node* a = search(x,root);
        if(a != NULL){
          if(a->isLeaf){
            if(a->fillcount != 2){
              int i;
              for(i = 0; i < a->fillcount; i++){
                if(a->keys[i] == x){
                  a->keys[i] = -1;

                  break;
                }
              }
              while(i < a->fillcount-1){
                a->keys[i] = a->keys[i+1];
                i++;
              }
              a->fillcount--;
            }
            else{
              struct node* ui = NULL;
              struct node* parent = getParent(x,ui,root);
              int i,j;
              for( j = 0; j  < a->fillcount;j++){
                if(a->keys[j] == x){
                  break;
                }
              }
              if(parent == NULL){
                for(int p = j; p < a->fillcount-1;p++){
                  a->keys[j] = a->keys[j+1];
                }
                a->fillcount--;
              }
              else{
              for( i = 0; i < (parent->fillcount)+1; i++){
                if(parent->children[i] == a){
                  break;
                }

              }

              int pred = -1,succ = -1;
              if(i+1 <= 4) succ = (parent->children[i+1])->keys[0];
              if(i-1 >= 0) pred = (parent->children[i-1])->keys[(parent->children[i-1])->fillcount-1];
              if(pred != -1){
                if((parent->children[i-1])->fillcount != 2){
                  for(int k = 0; k < j; k++){
                    a->keys[k+1] = a->keys[k];
                  }
                  a->keys[0] = parent->keys[i-1];
                  parent->keys[i-1] = (parent->children[i-1])->keys[(parent->children[i-1])->fillcount-1];

                    parent->children[i-1]->keys[(parent->children[i-1])->fillcount-1] = -1;
                    (parent->children[i-1])->fillcount -= 1;

                }
                else{
                  a->keys[j] = -1;
                  if(j == 0)a->keys[0] = a->keys[1];
                  a->fillcount--;
                  (parent->children[i-1])->keys[2] = parent->keys[i-1];
                  (parent->children[i-1])->keys[3] = a->keys[0];
                  a = NULL;
                  //del(parent->keys[i-1]);
                  for(int o = i; o < parent->fillcount; o++){
                    parent->keys[o-1] = parent->keys[o];
                  }

                  for(int o = i+1; o < parent->fillcount+1;o++){
                    parent->children[o-1] = parent->children[o];
                  }
                  parent->fillcount--;
                  (parent->children[i-1])->fillcount += 2;
                }
              }
              else{
                if((parent->children[i+1])->fillcount != 2){
                  for(int k = j; k < a->fillcount-1; k++){
                    a->keys[k] = a->keys[k+1];
                  }
                  a->keys[a->fillcount-1] = parent->keys[i];
                  parent->keys[i] = (parent->children[i+1])->keys[0];

                    for(int h = 1; h < parent->children[i+1]->fillcount; h++){
                      parent->children[i+1]->keys[h-1] = parent->children[i+1]->keys[h-1];
                    }
                    (parent->children[i+1])->fillcount -= 1;

                }
                else{
                  a->keys[j] = -1;
                  if(j == 0)a->keys[0] = a->keys[1];
                  a->fillcount--;


                  (parent->children[i+1])->keys[2] = (parent->children[i+1])->keys[0];
                  (parent->children[i+1])->keys[3] = (parent->children[i+1])->keys[1];

                  (parent->children[i+1])->keys[0] = a->keys[0];
                  (parent->children[i+1])->keys[1] = parent->keys[i];

                                    a = NULL;

                  //del(parent->keys[i]);
                  for(int o = i+1; o < parent->fillcount; o++){
                    parent->keys[o-1] = parent->keys[o];
                  }

                  for(int o = i+1; o < parent->fillcount+1;o++){
                    parent->children[o-1] = parent->children[o];
                  }
                  parent->fillcount--;
                  (parent->children[i+1])->fillcount += 2;
                }
              }
            }
            }

          }
          else{
            int i;
            for( i = 0; i < a->fillcount; i++){
              if(a->keys[i] == x){
                break;
              }
            struct node* left = a->children[i+1];
            while((left->isLeaf) != 1){
              left = left->children[0];
            }
            int dummy = left->keys[0];
            left->keys[0] = x;
            x = dummy;
            del(left->keys[0]);
  /*          struct node*iou=search(x,root);
            if(iou == NULL) cout<<"NULL"<<endl;
            int h;
            for(h = 0;h < iou->fillcount-1;h++){
              if(iou->keys[h] == x ){
                break;
              }
            }
            iou->keys[h] = dummy;


          }
        }
      }

*/

int i=0;
while(i < a->fillcount && a->keys[i] < x){
  i++;
}

if(i < a->fillcount && a->keys[i] == x){
  if(a->isLeaf)remLeaf(i,a);
  else remNLeaf(i,a);
}
else{
  if(a->isLeaf){cout << "The value "<<x<<" is not present in the tree"<<endl;return;}

  if((a->children[i])->fillcount < 2)refill(i,a);

  if(i == a->fillcount && i > a->fillcount){
    del(x,a->children[i-1]);
  }
  else del(x,a->children[i]);
}
}

void remLeaf(int u,struct node* y){
  for(int i = u+1;i < y->fillcount;i++){
    y->keys[i-1] = y->keys[i];
  }
  y->fillcount--;
}

void remNLeaf(int u, struct node* y){
  int p = y->keys[u];
  if(y->children[u]->fillcount >= 2){
    int pre = presor(u,y);
    y->keys[u] = pre;
    del(pre,y->children[u]);
  }
  else if(y->children[u+1]->fillcount >= 2){
    int suc = sucor(u,y);
    y->keys[u] = suc;
    del(suc,y->children[u+1]);
  }
  else{
    merge(u,y);
    del(p,y->children[u]);
  }
}

int presor(int a, struct node*b){
  struct node* t = b->children[a];
  while(!(t->isLeaf)){
    t = t->children[t->fillcount];
  }
  return t->keys[t->fillcount-1];
}


int sucor(int a, struct node*b){
  struct node* t = b->children[a+1];
  while(!(t->isLeaf)){
    t = t->children[0];
  }
  return t->keys[0];
}

void refill(int u, struct node* a){
  if(u!=0 && a->children[u-1]->fillcount >=2){
    borrPre(u,a);
  }
  else if(u!=a->fillcount && a->children[u+1]->fillcount >= 2){
    borrSuc(u,a);
  }
  else{
    if(u != a->fillcount)merge(u,a);
    else{merge(u-1,a);}
  }
}

void borrPre(int x, struct node*y){
  struct node* child = y->children[x],*sibling = y->children[x-1];
  for(int i = child->fillcount-1; i >=0;i--){
    child->keys[i+1] = child->keys[i];
  }
  if(!(child->isLeaf)){
    for(int i = child->fillcount; i >=0; i--){
      child->children[i+1] = child->children[i];
    }
  }
  child->keys[0] = y->keys[x-1];
  if(!(y->isLeaf)){
    child->children[0] = sibling->children[sibling->fillcount];
  }
  y->keys[x-1] = sibling->keys[(sibling->fillcount)-1];
  sibling->fillcount--;
  child->fillcount++;
}

void borrSuc(int x, struct node*y){
  struct node* child = y->children[x],*sibling = y->children[x+1];
  child->keys[child->fillcount] = y->keys[x];
  if(!(child->isLeaf)){
    child->children[child->fillcount+1] = sibling->children[0];
  }
  y->keys[x] = sibling->keys[0];
  for(int i = 1; i < sibling->fillcount; i++){
    sibling->keys[i-1] = sibling->keys[i];
  }
  if(!(sibling->isLeaf)){
    for(int i = 1; i <=sibling->fillcount;i++){
      sibling->children[i-1] = sibling->children[i];
    }
  }
  sibling->fillcount--;
  child->fillcount++;
}

void merge(int x,struct node* y){
  struct node* child = y->children[x],*sibling = y->children[x+1];
  child->keys[1] = y->keys[x];
  for(int i = 0; i < sibling->fillcount; i++){
    child->keys[2+i] = sibling->keys[i];
  }
  if(!(child->isLeaf)){
    for(int i = 0; i <=sibling->fillcount;i++){
      child->children[2+i] = sibling->children[i];
    }
  }
  for(int i = x+1; i < y->fillcount;i++){
    y->keys[x-1] = y->keys[x];
  }
  for(int i = x+2; i <= y->fillcount;i++){
    y->children[i-1] = y->children[i];
  }
  child->fillcount += sibling->fillcount + 1;
  y->fillcount--;
  free(sibling);
}
};


int main(){
  int n,x;
  btree bin;
  while(1){
    cout << "1.insert\n2.traverse\n3.search\n4.delete"<<endl;
    cin>>n;
    switch (n) {
      case 1:
        cout << "Enter integer to be inserted" << endl;
        cin >> x;
        bin.insert(x);
        break;

      case 2:
        bin.traverse(bin.getRoot());
        cout << endl;break;


      case 3:
      cout << "Enter integer to be searched" << endl;
      cin >> x;
      bin.search(x,bin.getRoot());
      break;

      case 4:
      cout << "Enter integer to be deleted" << endl;
      cin >> x;
      bin.del(x,bin.getRoot());
      break;

      default:
        return 0;
    }
  }
}
