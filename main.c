#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Ibrahim Irshaid 1231870 s1
typedef struct tree_node *tree_ptr;
struct tree_node
{
int TaskID;
char TaskName [100];
char TaskDate [15];
float TaskDuration;
int isUnDone;
tree_ptr left;
tree_ptr right;
};
typedef tree_ptr BST;

BST loadTasks(BST T);
tree_ptr find_min(BST T);
tree_ptr find_max(BST T);
tree_ptr deleteTask (BST T, int id);
BST restructTree (T);
BST searchById (int id, BST T);
BST rebuildByName(BST T, BST newT);

BST Make_null ()
{
return NULL;
}

int main()
{
    BST T = Make_null();
    BST newT = Make_null();

    printf("Welcome to Task Management System\n\n");
    int op =0;

    while(op!=10)
    {
    displayMainMenu();
    scanf("%d",&op);

    switch( op )
{
case 1: T = loadTasks(T);
        printInOrder(T);
    break;
case 2: addTask(T);
    break;
case 3: {   int id;
            printf("Enter Task's ID To Delete:");
            scanf("%d",&id);
            T = deleteTask(T, id);
        }
    break;
case 4: SearchTask(T);
    break;
case 5: performTask(T);
    break;
case 6: ViewUnperformed(T);
    break;
case 7: ViewPerformed(T);
    break;
case 8: T = restructTree(T, newT);
    break;
case 9: printInOrder(T);
    break;
case 10: printf("\nExiting... GoodBye!");
    break;
default: printf( "No such Operation!\tPLease try again.\n\n" );
break;
}
    }
    return 0;

}

void displayMainMenu()
{

    printf("\nPlease Select an Operation <1-10>:\n");
    printf("1. Load Tasks File\n2. Add a New Task\n3. Delete a Task\n4. Search for a Task\n");
    printf("5. Perform a Task\n6. View Unperformed Tasks\n7. View Performed Tasks\n8. Restructure the Tasks BST\n9. View the tasks BST info\n10. Exit\n\n");


}

BST insert ( BST T, int id, char name[100], char date[15], float duration,int done)
{
      if ( T == NULL )//Tree empty, insert first element
      {
            T = ( BST) malloc (sizeof(struct tree_node));
        if ( T == NULL )
            printf ("Out of space!!!");
        else
        {
            T->TaskID = id;
            strcpy (T->TaskName, name);
            strcpy (T->TaskDate, date);
            T->TaskDuration = duration;
            T->isUnDone = done;
            T->left = T->right = NULL;
        }
      }
else if ( id < T->TaskID)//Tree not empty, check to insert to left or right.

         T->left = insert ( T->left , id, name, date, duration, done);

else if ( id > T->TaskID)

    T->right = insert(T->right, id, name, date, duration, done);

return T;
}
void printInOrder(BST T)
{
   if ( T == NULL)
        return ;
      printInOrder(T->left);
         printf("ID: %d\tTask Name: %-30s\t Task Date: %-15s\t Task Duration: %.2f\n",T->TaskID, T->TaskName, T->TaskDate, T->TaskDuration);
      printInOrder(T->right);
}


void freeBST(BST T) {
    if (T == NULL)
        return;

    freeBST(T->left);
    freeBST(T->right);

    free(T);
}

BST loadTasks (BST T)
{

    FILE* f = fopen("tasks.txt", "r");
    if (f == NULL)
    {
        printf("Error opening file tasks.txt\n");
        return;
    }
    printf("Task File Loaded:\n\n");
    char line[256];
    while (fgets(line, sizeof(line), f))
        {

                char* token = strtok(line, "#");
                int id = atoi(token);

                token = strtok(NULL, "#");

                char name[100];
                strcpy(name, token);

                token = strtok(NULL, "#");

                char date[15];
                strcpy(date, token);

                token = strtok(NULL, "#");

                float duration = atof(token);

                if(searchById(id, T) != NULL)
                {
                    printf("Conflicting ID for Task [ID: %d\tName: %s\tDate: %s\tDuration: %f\nTask not loaded from the file\n", id,name,date,duration);
                    continue;
                }

                T = insert(T, id, name, date, duration,0);


        }
     fclose(f);
     return T;
}
BST searchById (int id, BST T)
{
      if( T == NULL)
        return NULL;

     else if( id < T->TaskID )
        return searchById( id, T->left );
     else if( id > T->TaskID )
        return searchById( id, T->right );
     else
     return T;
 }

 BST SearchByName (char name [100] , BST T)
 {
      if( T == NULL)
        return NULL;

     else if( strcmp(name, T->TaskName) < 0 )
        return SearchByName(name, T->left );
     else if( strcmp(name, T->TaskName) > 0 )
        return SearchByName(name,  T->right );
     else
     return T;
 }
 void SearchTask(BST T)// searches the performed and unperformed lists both by either name or id
 {
     BST temp;

     int method = 0;
     while(method != 1 || method != 2)
     {
        printf("To Search Task by ID Enter 1, To Search Task By Name Enter 2 or Enter 3 to Exit Search\n");
        scanf("%d", &method);

        if(method == 1)
        {
            int id;
            printf("Enter Task ID:\n");
            scanf("%d", &id);
            temp = searchById(id,T);
            if(temp != NULL)
            {
                if (temp->isUnDone == 0)
                    printf("Task Found: Task ID: %d\tTask Name: %-30s\tTask Date: %-15s\tTask Duration: %.2f\tTask is Unperformed\n",temp->TaskID, temp->TaskName, temp->TaskDate, temp->TaskDuration);
                else
                    printf("Task Found: Task ID: %d\tTask Name: %-30s\tTask Date: %-15s\tTask Duration: %.2f\tTask is Performed\n",temp->TaskID, temp->TaskName, temp->TaskDate, temp->TaskDuration);
            }
            else
              printf("Task With ID: %d Does Not Exist! Could not Find Task! Try Again\n", id);
        }

        else if(method == 2)
        {
            char name[100];
            printf("Enter Task Name to Search:\n");
            scanf("%s", &name);
            temp = SearchByName(name, T);
            if(temp != NULL)
            {
                if (temp->isUnDone == 0)
                    printf("Task Found: Task ID: %d\tTask Name: %-30s\tTask Date: %-15s\tTask Duration: %.2f\tTask is Unperformed\n",T->TaskID, T->TaskName, T->TaskDate, T->TaskDuration);
                 else
                    printf("Task Found: Task ID: %d\tTask Name: %-30s\tTask Date: %-15s\tTask Duration: %.2f\tTask is Performed\n",T->TaskID, T->TaskName, T->TaskDate, T->TaskDuration);
            }
            else
              printf("Could not Find Task! Try Again\n");
        }
         else if(method == 3)
            break;

        else
            printf("Invalid Input! Try Again\n");
     }
 }
   void addTask(BST T)
 {
     int id;
     char name[100];
     char date[15];
     float dueration;

     printf("Please Enter The Task's ID:\n");
     scanf("%d",&id);

     if(searchById(id, T) != NULL)//to check if the task already exists
     {
         printf("Task with ID: %d already exist! Unable to add Task\n",id);
         return;
     }
         printf("Please Enter The Task's Name:\n");
         scanf("%s",&name);
         printf("Please Enter The Task's Date:\n");
         scanf("%s",&date);
         printf("Please Enter The Task's Duration:\n");
         scanf("%f",&dueration);

         T = insert(T,id, name, date,dueration,0);// new tasks has the isUndone flag = 0 by default
         printf("\nTask has been added successfully\n");
 }
tree_ptr find_min(BST T)
{
    if (T == NULL)
        return NULL;
    else if (T->left == NULL)
        return T;
    else
        return find_min(T->left);
}

 tree_ptr deleteTask ( BST T, int id)
{
     tree_ptr    tmp_cell, child;
     if ( T == NULL )
     {
            printf("Task not found\n");
            return NULL;

     }

     else if ( id < T->TaskID)
            T->left = deleteTask(T->left, id);

     else if ( id > T->TaskID)
            T->right = deleteTask(T->right, id);

     else if ( T->left && T->right )  //found element and has (right ,left) elements
           {
              tmp_cell = find_min(T->right);
              T->TaskID = tmp_cell->TaskID;
              strcpy(T->TaskName, tmp_cell->TaskName);
              strcpy(T->TaskDate, tmp_cell->TaskDate);
              T->TaskDuration = tmp_cell->TaskDuration;
              T->isUnDone = tmp_cell->isUnDone;

             T->right = deleteTask(T->right, tmp_cell->TaskID);
           }
     else
    {
      tmp_cell = T;
      if ( T->left == NULL)
            child = T->right;

      if (T->right == NULL)
            child = T->left;
      free ( tmp_cell);
      return child;
    }
return T;
}

void performTask (BST T)
{
    printf("Enter Task's Id to Perform:\n");
    int id;
    scanf("%d", &id);

    if (searchById(id, T) == NULL)
        printf("Task Not Found!\n");
    else
    {
        searchById(id, T)->isUnDone = 1;
        printf("\nTask Performed Successfully\n");
    }
}
 void ViewUnperformed(BST T)
{
    BST newT = Make_null();
    newT = rebuildByName(T, newT);
    if ( newT == NULL)
        return ;
      ViewUnperformed(newT->left);
         if(newT->isUnDone == 0)
            printf("ID: %d\tTask Name: %-30s\t Task Date: %-15s\t Task Duration: %.2f\n",T->TaskID, T->TaskName, T->TaskDate, T->TaskDuration);
      ViewUnperformed(newT->right);
}
 void ViewPerformed(BST T)
{
   if ( T == NULL)
        return ;
      ViewPerformed(T->left);
         if(T->isUnDone == 1)
            printf("ID: %d\tTask Name: %-30s\t Task Date: %-15s\t Task Duration: %.2f\n",T->TaskID, T->TaskName, T->TaskDate, T->TaskDuration);
      ViewPerformed(T->right);
}
 BST insertById(BST T, tree_ptr node) {
    if (T == NULL) {
        BST newT = (BST)malloc(sizeof(struct tree_node));
        if (newT == NULL) {
            printf("Out of memory!\n");
            return NULL;
        }
        newT->TaskID = node->TaskID;
        strcpy(newT->TaskName, node->TaskName);
        strcpy(newT->TaskDate, node->TaskDate);
        newT->TaskDuration = node->TaskDuration;
        newT->isUnDone = node->isUnDone;
        newT->left = newT->right = NULL;
        return newT;
    }

    if (node->TaskID < T->TaskID)
        T->left = insertById(T->left, node);
    else
        T->right = insertById(T->right, node);

    return T;
}
BST rebuildById(BST T, BST newT) {
    if (T == NULL)
        return newT;

    newT = rebuildById(T->left, newT);
    newT = insertById(newT, T);
    newT = rebuildById(T->right, newT);

    return newT;
}
 BST insertByName(BST T, tree_ptr node) {
    if (T == NULL) {
        BST newT = (BST)malloc(sizeof(struct tree_node));
        if (newT == NULL) {
            printf("Out of memory!\n");
            return NULL;
        }
        newT->TaskID = node->TaskID;
        strcpy(newT->TaskName, node->TaskName);
        strcpy(newT->TaskDate, node->TaskDate);
        newT->TaskDuration = node->TaskDuration;
        newT->isUnDone = node->isUnDone;
        newT->left = newT->right = NULL;
        return newT;
    }

    if (strcmp(node->TaskName, T->TaskName) < 0)
        T->left = insertByName(T->left, node);
    else
        T->right = insertByName(T->right, node);

    return T;
}
BST rebuildByName(BST T, BST newT) {
    if (T == NULL)
        return newT;

    newT = rebuildByName(T->left, newT);
    newT = insertByName(newT, T);
    newT = rebuildByName(T->right, newT);

    return newT;
}
 int checkDate(char date1[15], char date2[15])
 {
     char* token1 = strtok(date1, "/");
     int year1 = atoi(token1);
     token1 = strtok(NULL, "/");

     char* token2 = strtok(date2, "/");
     int year2 = atoi(token2);
     token2 = strtok(NULL, "/");

     int month1 = atoi(token1);
     int month2 = atoi(token2);

     token1 = strtok(NULL, "/");
     token2 = strtok(NULL, "/");

     int day1 = atoi(token1);
     int day2 = atoi(token2);

     if(year2 > year1)
        return -1;
     else if(year2 < year1)
        return 1;
     else
     {
         free(year1);
         free(year2);
         if (month2 > month1 )
            return -1;
         else if(month2 < month1)
            return 1;
         else
         {
         free(month1);
         free(month2);
         if (day2 > day1 )
            return -1;
         else if(day2 < day1)
            return 1;
         }
         free(day1);
         free(day2);
     }
     return 0;

 }
  BST insertByDate ( BST T, tree_ptr node)
{
    if (T == NULL) {
        BST newT = (BST)malloc(sizeof(struct tree_node));
        if (newT == NULL) {
            printf("Out of memory!\n");
            return NULL;
        }
        newT->TaskID = node->TaskID;
        strcpy(newT->TaskName, node->TaskName);
        strcpy(newT->TaskDate, node->TaskDate);
        newT->TaskDuration = node->TaskDuration;
        newT->isUnDone = node->isUnDone;
        newT->left = newT->right = NULL;
        return newT;
    }

    if (checkDate(node->TaskDate, T->TaskDate) == -1)
        T->left = insertByDate(T->left, node);
    else
        T->right = insertByDate(T->right, node);

    return T;
}
BST rebuildByDate(BST T, BST newT) {
    if (T == NULL)
        return newT;

    newT = rebuildByDate(T->left, newT);
    newT = insertByDate(newT, T);
    newT = rebuildByDate(T->right, newT);

    return newT;
}
 BST insertByDuration(BST T, tree_ptr node) {
    if (T == NULL) {
        BST newT = (BST)malloc(sizeof(struct tree_node));
        if (newT == NULL) {
            printf("Out of memory!\n");
            return NULL;
        }
        newT->TaskID = node->TaskID;
        strcpy(newT->TaskName, node->TaskName);
        strcpy(newT->TaskDate, node->TaskDate);
        newT->TaskDuration = node->TaskDuration;
        newT->isUnDone = node->isUnDone;
        newT->left = newT->right = NULL;
        return newT;
    }

    if (node->TaskDuration < T->TaskDuration)
        T->left = insertByDuration(T->left, node);
    else
        T->right = insertByDuration(T->right, node);

    return T;
}
BST rebuildByDuration(BST T, BST newT) {
    if (T == NULL)
        return newT;

    newT = rebuildByDuration(T->left, newT);
    newT = insertByDuration(newT, T);
    newT = rebuildByDuration(T->right, newT);

    return newT;
}
 BST restructTree (BST T, BST newT)
 {

    int choice = 0;
    while (choice != 1 || choice != 2 || choice !=3 || choice != 4)
    {
        printf("To Rebuild By Task Id Enter 1\nTo Rebuild By Task Name Enter 2\nTo Rebuild By Task Duration Enter 3\nTo Rebuild By Task Duration Enter 4\n");
        scanf("%d", &choice);
        if (choice == 1)
        {
            newT = rebuildById(T, newT);
            printf("Tree Restructured By Task ID Successfully.\n");
            freeBST(T);
            return newT;

        }
        else if (choice == 2)
        {
            newT = rebuildByName(T, newT);
            printf("Tree Restructured By Task Name Successfully.\n");
            freeBST(T);
            return newT;
        }
        else if(choice == 3)
        {
            newT = rebuildByDate(T, newT);
            printf("Tree Restructured By Task Date Successfully.\n");
            freeBST(T);
            return newT;

        }
        else if (choice == 4)
        {
            newT = rebuildByDuration(T, newT);
            printf("Tree Restructured By Task Duration Successfully.\n");
            freeBST(T);
            return newT;
        }
        else
            printf("Invalid Input Try Again\n");


 }
        return T;
 }
 int findHeight(BST T){
    if(T==NULL)
        return 0;
    int leftHeight = findHeight(T->left);
    int rightHeight = findHeight(T->right);
    if(leftHeight > rightHeight)
        return leftHeight +1;
    else
         return rightHeight +1;
}
int findNodes(BST T){
    if(T==NULL)
        return 0;
    return 1+findNodes(T->left)+findNodes(T->right);
}
int findLeaves(BST T){
    if(T == NULL)
        return 0;
    if(T->left && T->right)
        return 1;
    return findLeaves(T->left)+ findLeaves(T->right) +1;
}
int findInternalNodes(BST T){
    if(T==NULL)
        return 0;
    if(T->left!=NULL || T->right!=NULL){
        return 1+findInternalNodes(T->left)+findInternalNodes(T->right);
    }
    return 0;
}
 void viewBSTinfo (BST T)
 {
     printf("Tree Height: %d\n", findNodes(T));
     printf("Number of Tree Nodes: %d\n", findNodes(T));
     printf("Number of leaves: %d\n", findLeaves(T));
     printf("Number of Internal Nodes: %d\n", findInternalNodes(T));

 }
