# Quad-tree-implementation-in-C-

Firstly, we create a class for the quad tree. this class is similar to the binary tree class for lab.
We initialize the info value of each node in the *pinfo pointer and reference four other children of this node.

The function insert initializes the quad tree object root with the first character of the string and then calls
insert_rec to do the rest. This function is recursive until the string does not start with p anymore.
Another char array is used to store the following four character after p regardless of their value. If 'p'
character is found, then the function calls itself. After that, p string is changed and the actual children of the 
actual node are stored in p. This operates until the string is null.

Function init is just a function for initializing a node with a value in the quad tree object.
Function show prints the array, using the hyphen to represent the level of each node.
the make parent function is used in the overlap function for changing a white node, for example, in 
a parent node with four white children.

The function ovl should be called with the resultant quad tree object and this object should be empty.
When comparing two quad trees, we use if statements to check for the three cases: colour and colour, colour
and parent, parent and parent. 

1.If one node is black then the resultant node is black, else resultant node is white.
2.If a node is parent and the other is black, the resultant node is black, else we have to make 
the white node into a parent node with four white children and recall function.
3.If both are parents, recall functionfor each child.

Pixel function computes the pixels in function of the levels of the nodes: 1024 divided by 4 to
the power of level.

At the end we have the interaction which is a do while until it is exited.
Case 3 and 4 have to be executed after the first, respectivelly the second are called at least once.
Pixels are calculated for the last graph added.
