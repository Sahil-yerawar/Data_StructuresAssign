/*Name:- Sahil Yerawar
  Roll No:- CS15BTECH11044
  Assignment:- 9
  Problem :- Implementing 5-way btree*/

#include<iostream>
using namespace std;


struct node{                                                    //defining node for a btree

  int fillcount;
  struct node* children[6];
  int keys[5];
  bool isLeaf;                                      //0 for not leaf, 1 for leaf
};

class btree{                                                    // class for implementing btree
  private:
      struct node* root;


  public:
      btree(){                                                  //constructor for initializing btree
          root = createNode();

      }
      struct node* createNode(){                                //function to create a node
        struct node* x = (struct node*)new (struct node);
        x->fillcount = 0;
        x->isLeaf = true;
        for(int i = 0; i < 5; i++){
          x->keys[i] = -1;

        }
        for(int i = 0; i < 6; i++){
          x->children[i] = NULL;
        }
      }

      void insert(int x){                                       //function to insert a node in a btree

        if(root == NULL){                                       // check for empty case
            root = createNode();//(struct node*)new node();
			      root->isLeaf = true;
            root->keys[0] = x;
            root->fillcount = 1;
        }
        else{
          //struct node* r = root;
          if(root->fillcount == 5){
            struct node* s = (struct node*)new node();
            s->children[0] = root;
            s->isLeaf = false;

            insert_split_child(s,root,0);
			      int i=0;
			      if(s->keys[0]<x)
				        i++;
            insert_nonfull(s->children[i],x);
            root = s;
          }
          else insert_nonfull(root,x);
        }
      }

	//Split node a
      void insert_split_child(struct node* a,struct node *y, int c)  // sub function to split child in insertion
	  {
        struct node* z = createNode();//(struct node*)new node();
        //int temp;
        z->isLeaf = y->isLeaf;
        z->fillcount = 2;
        //z->keys[0] = y->keys[3];
        //z->keys[1] = y->keys[4];

		for(int temp =0;temp<2;temp++)
			z->keys[temp]=y->keys[temp+3];



		if(y->isLeaf == false)
		{
         for(int temp=0;temp<3;temp++)
			 z->children[temp] = y->children[temp+3];
        }

		y->fillcount = 2;

		for(int i = a->fillcount;i >= c+1;i--)
		{
          a->children[i+1] = a->children[i];
        }
        a->children[c+1] = z;

		for(int i = a->fillcount-1; i >=c; i--)
		{
          a->keys[i+1] = a->keys[i];

        }
        a->keys[c] = y->keys[2];
        a->fillcount +=1 ;

      }

      void insert_nonfull(struct node* a, int c){               //sub function to insert child in the non full node
        int y = a->fillcount -1;
        if(a->isLeaf==true){

          while(y >=0 && c < a->keys[y]){
            a->keys[y+1] = a->keys[y];
            y--;
          }
          a->keys[y+1]  = c;
          a->fillcount +=1;
        }
        else{
          while(y >= 0 && c < a->keys[y])
			  y--;
          if(a->children[y+1]->fillcount == 5)
		  {
            insert_split_child(a,a->children[y+1],y+1);
            if(c > a->keys[y+1])
				y++;
          }
          insert_nonfull(a->children[y+1],c);

        }
      }

      void traverse(struct node* a){                            //function to traverse and subsequently print the btree
        int i;
        if( a == NULL){
          cout << "No starting point to begin with" << endl;
          return;
        }
        for(i = 0; i < a->fillcount; i++)
		{
          if(a->isLeaf == 0){
            traverse(a->children[i]);
          }

          cout << " "<< a->keys[i];
        }
        if(a->isLeaf == 0)traverse(a->children[i]);
      }

      struct node* getRoot(){return root;}                      //get function to access the root
      struct node* search(int x,struct node* t){                // function to check whether the value is present or not, thereby giving the node address
        int i = 0;
        while(i < t->fillcount && x > t->keys[i]){
          i++;
        }
        if(x == t->keys[i]){
          return t;
        }
        else if(t->isLeaf==1)return NULL;
        return search(x,t->children[i]);
      }

      struct node* getParent(int x,struct node* parent,struct node* child){   //function to get the parent of concerned node
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
  void del(int x,struct node* a){                           //function to delete a value
    int i=0;
    bool flag;
    while(i < a->fillcount && a->keys[i] < x)
	{
        ++i;
    }

      if(i < a->fillcount && a->keys[i] == x){
        if(a->isLeaf)remLeaf(i,a);
        else remNLeaf(i,a);
      }
      else{
        if(a->isLeaf){cout << "The value "<<x<<" is not present in the tree"<<endl;return;}


		if(i==a->fillcount) // if not leaf and
			flag =true;
		else
			flag = false;


        if((a->children[i])->fillcount < 3)
			refill(i,a);


        if(flag &&  i > a->fillcount){
          del(x,a->children[i-1]);
        }
        else del(x,a->children[i]);
      }
    }

    void remLeaf(int u,struct node* y){                             //function to remove the value from a leaf
      for(int i = u+1;i < y->fillcount;++i){
        y->keys[i-1] = y->keys[i];
      }
      y->fillcount--;
    }

    void remNLeaf(int u, struct node* y){                           //function to remove from non leaf node
      int p = y->keys[u];
      if(y->children[u]->fillcount >= 3)
	  {
        int pre = presor(u,y);
        y->keys[u] = pre;
        del(pre,y->children[u]);
      }
      else if(y->children[u+1]->fillcount >= 3){
        int suc = sucor(u,y);
        y->keys[u] = suc;
        del(suc,y->children[u+1]);
      }
      else{
        merge(u,y);
        del(p,y->children[u]);
      }
    }

int presor(int a, struct node*b){                               //function to get the predecessor node of the concerned node
  struct node* t = b->children[a];
  while(!(t->isLeaf))
  {
    t = t->children[t->fillcount];
  }
  return t->keys[t->fillcount-1];
}


int sucor(int a, struct node*b){                                //function to find the successor node of the concerned node
  struct node* t = b->children[a+1];
  while(!(t->isLeaf)){
    t = t->children[0];
  }
  return t->keys[0];
}

void refill(int u, struct node* a){                            //function to refill the concerned node
  if(u!=0 && a->children[u-1]->fillcount >=3){
    borrPre(u,a);
  }
  else if(u!=a->fillcount && a->children[u+1]->fillcount >= 3){
    borrSuc(u,a);
  }
  else{
    if(u != a->fillcount)
		merge(u,a);
    else
		merge(u-1,a);
  }
  return;
}

void borrPre(int x, struct node*y){                             //function to borrow from the successor node
  struct node* child = y->children[x],*sibling = y->children[x-1];
  for(int i = child->fillcount-1; i >=0;--i)
  {
    child->keys[i+1] = child->keys[i];
  }

  if(!(child->isLeaf))
  {
    for(int i = child->fillcount; i >=0; --i)
	{
      child->children[i+1] = child->children[i];
    }
  }
  child->keys[0] = y->keys[x-1];
  if(!(y->isLeaf)){
    child->children[0] = sibling->children[sibling->fillcount];
  }
  y->keys[x-1] = sibling->keys[(sibling->fillcount)-1];
  sibling->fillcount -= 1;
  child->fillcount += 1;
  return;
}

void borrSuc(int x, struct node*y){                             //function to borrow from successor node
  struct node* child = y->children[x],*sibling = y->children[x+1];
  child->keys[child->fillcount] = y->keys[x];
  if(!(child->isLeaf)){
    child->children[(child->fillcount)+1] = sibling->children[0];
  }
  y->keys[x] = sibling->keys[0];
  for(int i = 1; i < sibling->fillcount; ++i){
    sibling->keys[i-1] = sibling->keys[i];
  }
  if(!(sibling->isLeaf)){
    for(int i = 1; i <=sibling->fillcount;++i){
      sibling->children[i-1] = sibling->children[i];
    }
  }
  sibling->fillcount -= 1;
  child->fillcount +=1;
  return;
}

void merge(int x,struct node* y){                               // function to merge two nodes if they are below the certain value
  struct node* child = y->children[x],*sibling = y->children[x+1];
  child->keys[2] = y->keys[x];
  for(int i = 0; i < sibling->fillcount; ++i){
    child->keys[i+3] = sibling->keys[i];
  }
  if(!(child->isLeaf)){
    for(int i = 0; i <=sibling->fillcount;++i){
      child->children[i+3] = sibling->children[i];
    }
  }
  for(int i = x+1; i < y->fillcount;++i){
    y->keys[i-1] = y->keys[i];
  }
  for(int i = x+2; i <= y->fillcount;++i){
    y->children[i-1] = y->children[i];
  }
  child->fillcount += ((sibling->fillcount)  + 1);
  y->fillcount--;
  delete(sibling);
}
void del_ele(int x){
  if(!root){
    cout << "The tree is empty" << endl;return;
  }
  del(x,root);
  if(root->fillcount == 0){
    struct node* temp = root;
    if(root->isLeaf)root = NULL;
    else root = root->children[0];
    delete temp;
  }
  return;
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
        cout<<"********"<<endl;
        bin.traverse(bin.getRoot());
        cout << endl;
        cout<<"********"<<endl;
        break;

      case 2:

      cout<<"********"<<endl;
      bin.traverse(bin.getRoot());
      cout << endl;
      cout<<"********"<<endl;break;


      case 3:
      cout << "Enter integer to be searched" << endl;
      cin >> x;
      bin.search(x,bin.getRoot());

      cout<<"********"<<endl;
      bin.traverse(bin.getRoot());
      cout << endl;
      cout<<"********"<<endl;
      break;

      case 4:
      cout << "Enter integer to be deleted" << endl;
      cin >> x;
      bin.del_ele(x);

      cout<<"********"<<endl;
      bin.traverse(bin.getRoot());
      cout << endl;
      cout<<"********"<<endl;
      break;

      default:
        return 0;
    }
  }
}
