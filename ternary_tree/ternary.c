Given a ternary tree, implement insertion and search

Questions to ask: 
- How to handle duplicate insertions
- 


- Psuedo code

typedef struct node 
{
  node *left;
  node *middle;
  node *right;
  char  key;
} node;

boolean insertTernary(char *word, node *root)
{
  if (root == NULL || word[0] == root)
  {
    if (root == NULL)
    {
      // allocate and initialize root
      root = allocNode(word[0]);
      if (n == NULL)
        signal_exception();
    }

    // Recursively add the next character starting from the root
    insertTernary(&word[1], root);
  }
  else if (root->middle != NULL && root->middle->key == word[0])
  {
    insertTernary(&word[1], );
  }




  {
    if (root->middle->key > word[0])
    {
      // left insertion
    }
    else if ()
  }

}

searchTernary()
{

}
