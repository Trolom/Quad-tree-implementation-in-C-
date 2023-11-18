#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;
//I created a class for a quad tree, similar to that of a binary tree from the laboratory
class QuadTree {
    public:
        char *pinfo;
        QuadTree *left_top_son, *right_top_son, *left_bottom_son,  *right_bottom_son, *parent, *root;

        QuadTree() {
            pinfo = NULL;
            left_top_son = right_top_son = left_bottom_son = right_bottom_son = parent = NULL;
            root = this;
        }

        void setInfo(char info) {
            pinfo = new char;
            *pinfo = info;
        }

		void setRoot(QuadTree *r) {
            root = r;
        }

        void insert(char s[]) {//used only for initializing the first node with a value and calling insert_rec
                setInfo(s[0]);
                insert_rec(s);
        }

		void insert_rec(char s[]) {// this is a function which translates the input string into a quad tree
            //this recursive function keeps calling itself only if the string starts with the letter 'p'
            if (s[0] == 'p') {
                strcpy (s, s+1);//eliminate the p from the string and recall function for each child node
                char p[10];
                strncpy(p, s, 4);//this a string which takes the following four characters regardless if any of them are parent
                p[4] = '\0';     //this string will be modified until it contains the four children of the parent node


                init(&right_top_son, p[0]);
                if (p[0] == 'p') {//after initializing the node with the value of p[0], we check if that value is p for parent
                    right_top_son->insert_rec(s);
                    strncpy(p + 1, s, 3);
                    p[4] = '\0';
                } else strcpy(s, s+1);


                init(&left_top_son, p[1]);
                if (p[1] == 'p') {//left_top
                    left_top_son->insert_rec(s);
                    strncpy(p + 2, s, 2);
                    p[4] = '\0';
                } else strcpy(s, s+1);


                init(&left_bottom_son, p[2]);
                if (p[2] == 'p') {//left_bottom
                    left_bottom_son->insert_rec(s);
                    strncpy(p + 3, s, 1);
                    p[4] = '\0';
                } else strcpy(s, s+1);


                init(&right_bottom_son, p[3]);
                if (p[3] == 'p') {//right_bottom
                        right_bottom_son->insert_rec(s);
                } else strcpy(s, s+1);//here we dont change p anymore because its value is not relevant anymore

            }
            else cout<<"Invalid string"<<endl;
        }


        void show(int level)//function for displaying the quad tree
		{
            for (int i = 0; i < level; i++)
                cout<<"-";

          cout<<*pinfo<<endl;

        if (right_top_son != NULL)
            right_top_son->show(level + 1);
        if (left_top_son != NULL)
            left_top_son->show(level + 1);
        if (left_bottom_son != NULL)
            left_bottom_son->show(level + 1);
        if (right_bottom_son != NULL)
            right_bottom_son->show(level + 1);
		}

		void makeParent () {//this a function used in the ovelapping of two graphs which creates four child nodes in the case of parent and colour
		    if (*(pinfo) == 'w' || *(pinfo) == 'b') {

                init(&right_top_son, *(pinfo));
                init(&left_top_son, *(pinfo));
                init(&left_bottom_son, *(pinfo));
                init(&right_bottom_son, *(pinfo));

                *pinfo = 'p';
		    }
		}

		void init(QuadTree **x, char info)//this function is used for initializing a node of the quad tree and giving it a value
    {
        *x = new QuadTree;
        (*x)->pinfo = new char;
        *((*x)->pinfo) = info;
        (*x)->right_top_son = (*x)->left_top_son = (*x)->left_bottom_son = (*x)->right_bottom_son = NULL;
        (*x)->parent = this;
        (*x)->root = root;
    }


    void ovl(QuadTree **r1, QuadTree **r2)//same as insert function
        {
                setInfo('p');
                overlap(&(*r1), &(*r2));
        }

//it should be called for an empty quad tree
    void overlap (QuadTree **r1, QuadTree **r2) {//this function will check for the three possible cases when overlapping two quad trees
    //first case: both nodes from the trees have the value black or white
        if (*((*r1)->pinfo) != 'p' && *((*r2)->pinfo) != 'p') {
            if (*((*r1)->pinfo) == 'b' || *((*r2)->pinfo) == 'b') {
                *pinfo = 'b';
            } else {
                *pinfo = 'w';
            }
        }//second case: one node is parent and the other one is colour; if the colour node is black, the other noede doesnt matter
        else if ((*((*r1)->pinfo) == 'p' && *((*r2)->pinfo) != 'p') || (*((*r1)->pinfo) != 'p' && *((*r2)->pinfo) == 'p')) {
             if (*((*r1)->pinfo) == 'b' || *((*r2)->pinfo) == 'b') {
                *pinfo = 'b';
             }else {//if one node is white, then we have to make it a parent in order to compare
                if (*((*r2)->pinfo) != 'p') {
                    (*r2)->makeParent();
                } else if (*((*r1)->pinfo) != 'p'){
                    (*r1)->makeParent();
                }
                *pinfo = 'p';

                init(&right_top_son, 'x');//for the resultant graph, we create four child nodes with the value x which will be changed after
                init(&left_top_son, 'x');
                init(&left_bottom_son, 'x');
                init(&right_bottom_son, 'x');

                right_top_son->overlap(&((*r1)->right_top_son), &((*r2)->right_top_son));//each recalling of the overlap function will check again but for each child of the actual node
                left_top_son->overlap(&((*r1)->left_top_son), &((*r2)->left_top_son));
                left_bottom_son->overlap(&((*r1)->left_bottom_son), &((*r2)->left_bottom_son));
                right_bottom_son->overlap(&((*r1)->right_bottom_son), &((*r2)->right_bottom_son));
             }
        }//third case: both are parents and overlap is called for every child
        else if (*((*r1)->pinfo) == 'p' && *((*r2)->pinfo) == 'p') {

            *pinfo = 'p';

            init(&right_top_son, 'x');
            init(&left_top_son, 'x');
            init(&left_bottom_son, 'x');
            init(&right_bottom_son, 'x');

            right_top_son->overlap(&((*r1)->right_top_son), &((*r2)->right_top_son));
            left_top_son->overlap(&((*r1)->left_top_son), &((*r2)->left_top_son));
            left_bottom_son->overlap(&((*r1)->left_bottom_son), &((*r2)->left_bottom_son));
            right_bottom_son->overlap(&((*r1)->right_bottom_son), &((*r2)->right_bottom_son));
        }
}
    void pixels(int level, int &px) {//recursive function in the case of the parent node, else check the level and divides 1024 pixels by 4 to the power of the level
        level++;

        if (*pinfo == 'p') {
            right_top_son->pixels(level, px);
            left_top_son->pixels(level, px);
            left_bottom_son->pixels(level, px);
            right_bottom_son->pixels(level, px);
        } else if (*pinfo == 'b'){
            px += 1024/pow(4, level-1);
        }
    }

};







int main() {

    int px = 0, pxres = 0, choice;//initializing all the variables needed
    char s[100] = {'\0'}, s1[100] = {'\0'}, s2[100] = {'\0'};
    QuadTree *q = new QuadTree;
    QuadTree *q1 = new QuadTree;
    QuadTree *q2 = new QuadTree;
    QuadTree *finq = new QuadTree;
    finq->setRoot(finq);
    q->setRoot(q);
    q1->setRoot(q1);
    q2->setRoot(q2);
    int ok1 = false, ok2 = false;

      do {//interaction menu which allows for checking all the functionalities
        cout<<"Choose:\n";
        cout<<"1. Convert the preorder transversal of an image and display the graph\n";
        cout<<"2. Overlap two images into a final quad tree\n";
        cout<<"3. Compute the number of black pixels for an image(you have to insert using the first option)\n";
        cout<<"4. Compute the number of black pixels for an the overlapped final quad tree(you have to insert using the second option)\n";
        cout<<"5. Exit\n";
        cout<<"Your choice: ";
        cin>>choice;

        switch(choice) {
            case 1:
                cout<<"Enter the preorder transversal: ";
                cin>>s;
                q->insert(s);
                q->show(0);
                cout<<endl;
                ok1 = true;
                break;
            case 2:
                cout<<"Enter the preorder transversal of the first image: ";
                cin>>s1;
                q1->insert(s1);
                cout<<"Enter the preorder transversal of the second image: ";
                cin>>s2;
                cout<<"Final quad tree: "<<endl;
                q2->insert(s2);
                finq->ovl(&q1, &q2);
                finq->show(0);
                ok2 = true;
                break;
            case 3:
                px = 0;
                if (!ok1) cout<<"Error"<<endl;
                else {
                cout<<endl;
                q->pixels(0, px);
                cout << "Number of black pixels: "<<px<<endl;
                }
                break;

                case 4:
                if (!ok2) cout<<"Error"<<endl;
                else {
                pxres = 0;
                cout<<endl;
                finq->pixels(0, pxres);
                cout << "Number of black pixels of the final image: "<<pxres<<endl;
                }
                break;

            case 5:
                cout<<endl;
                cout<<"Exiting..."<<endl;
                break;

            default:
                cout<<endl;
                cout<<"Invalid choice, please try again"<<endl;
                break;
        }

    } while(choice != 5);



    return 0;
}

