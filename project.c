#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Post
{
    char  * content;
    int likenum;
    int postID;
    struct Post* nextpost;
}post;
typedef struct User
{
    char* username;
    char* password;
    post* userpost;
    struct User* nextuser;   
}user;

post* newpost(char* content)
{
    post* new_post = (post*)malloc(sizeof(post));
    new_post->content = content;
    new_post->likenum = 0;
    new_post->nextpost = NULL;
    return new_post;
}
void addpost(user* this_user, post* new_post)
{  
    int i = 0; 
    post* cur = this_user->userpost;
    while (cur->nextpost != NULL)
    {
        i++;
        cur = cur->nextpost;
    }
    i++;
    cur->nextpost = new_post;
    new_post->postID = i;
    printf("posted sucsessfuly\n");
}


void like(user* head, char* username, int postID)
{
    user* cur = head;
    while (cur != NULL)
    {
        if (strcmp(cur->username, username) == 0)
        {
            break;
        }
        cur = cur->nextuser;
    }
    if (cur == NULL)
    {
        printf("no such user\n");
    }
    
    
    
    if (cur != NULL)
    {
        post* curr = cur->userpost;
        while (curr!= NULL)
       {
        if(curr->postID == postID)
         break;
            curr = curr->nextpost;
       }
        if (curr == NULL )
        {
            printf("no such post\n");
        }
        
        if (curr != NULL)
        {
            curr->likenum++;
            printf("you liked this post\n");
            
        }
    }
}
void delete(user* this_user, int index)
{
    post* hold;
    post* cur = this_user->userpost;
    while (cur != NULL)
    {
        if (cur->postID == index)
        {
            break;
        }
        
        cur = cur->nextpost;
    }
    if (cur == NULL)
    {
        printf("no such post\n");
    }
    else
    {
        hold = cur->nextpost;
        cur->nextpost = cur->nextpost->nextpost;
        free(hold);
        printf("deleted sucsessfuly\n");
    }
    
}
void search(user* head, char* username)
{
    user* cur = head;
    while (cur != NULL)
    {
        if (strcmp(cur->username, username) == 0)
        {
            break;
        }
        cur = cur->nextuser;
    }
    if (cur == NULL)
    {
        printf("no such user\n");
    }
    
    if (cur != NULL)
    {
        cur->userpost = cur->userpost->nextpost;
        printf("user found\n");
        while (cur->userpost != NULL)
        {
            printf("postID:%d\n", cur->userpost->postID);
            printf("post:%s\n", cur->userpost->content);
            printf("likes:%d\n", cur->userpost->likenum);
            printf("\n\n");
            cur->userpost = cur->userpost->nextpost;
        }
    }
}


user* newUser(char* inUsername, char* inPassword)
{
    user* new_user = (user*)malloc(sizeof(user));
    new_user->userpost=(post *)malloc(sizeof(post));
    new_user->username=inUsername;
    new_user->password=inPassword;
    new_user->userpost->nextpost =  NULL;
    new_user->nextuser = NULL;
    return new_user;
}
void signup(user* userhead, user* newuser)
{
    user* cur = userhead;
    while (cur != NULL)
    {
        if (strcmp(cur->username, newuser->username) == 0)
        {
            printf("usename already taken\n");
            break;
        }

        cur = cur->nextuser;    
    }
    if (cur == NULL)
    {
        cur = userhead;
        while (cur->nextuser != NULL)
        {
            cur = cur->nextuser;
        }
        cur->nextuser = newuser;
        printf("signed up sucsessfuly\n");

    }
    
    
}
user* login(user* userhead, char* inUsername, char* inPassword)
{   
    user* thisUser;
    user* cur = userhead;
    while (cur != NULL)
    {
        if (strcmp(cur->username, inUsername) == 0 && strcmp(cur->password, inPassword) == 0)
        {
            printf("loged in sucsessfuly\n");
            thisUser = cur;
            return thisUser;
            break;
        }
        cur = cur->nextuser;
    }
    if (cur == NULL)
    {
     printf("sth is wrong\ntry again\n");
        return NULL;
    }
    
        
}



char* stringer()
{
    int i =  - 1;
    char* temp = (char*)malloc(sizeof(char));

    while (temp[i] != ' ' && temp[i] != '\n')
    {
        i++;
        temp = (char*)realloc(temp, sizeof(char)* (i + 1));
        temp[i] = getchar();
    }
    temp[i] = '\0';
    return temp;
    
}
char* stringer2()
{
    int i = - 1;
    char* temp = (char*)malloc(sizeof(char));
    while ( temp[i] != '\n')
    {
        i++;
        temp = (char*)realloc(temp, sizeof(char)* (i + 1));
        temp[i] = getchar();
    }
    temp[i] = '\0';
    return temp;
    
}
int ASCII(char* string)
{
    int sum = 0, i = 0;
    while (string[i] != '\0')
    {
        sum = sum + (int)string[i];
        i++;
    }
    return sum;
}

int main()
{
    user* user_head = newUser("0", "0");
    user* this_user;
    int true ;
    char* content;
    int index;
    char* username;
    char* password;
    char* order = (char*)malloc(sizeof(char) * 50);
    order = stringer();
     
    while (1)
    {
        order = stringer();
        if (strcmp(order ,"signup") == 0)
        {
            username = stringer();
            password = stringer2();
            signup(user_head, newUser(username, password));
        }
        
        else if (strcmp(order, "login") == 0)
        {
            username = stringer();
            password = stringer2();
            this_user =  login(user_head, username, password);
            if (this_user != NULL)
            { true = 1;
                while (true)
                {
                    order = stringer();
                    switch (ASCII(order))
                    {
                        case 454:
                            content = stringer2();
                            addpost(this_user, newpost(content));
                            break;
                        case 421:
                            username = stringer();
                            index = atoi(stringer2());
                            like(user_head, username, index);
                            break;
                        case 627:
                            index = atoi(stringer2());
                            delete(this_user, index);
                            break;
                        case 630:
                            username = stringer2();
                            search(user_head, username);
                            break;
                        case 428:
                            search(user_head, this_user->username);
                            break;
                        case 666:
                            printf("logged out sucsessfuly\n");
                            this_user = NULL;
                            true = 0;
                            break;
                        default:
                            printf("no such order. try again\n");
                            break;
                    }
                    
                }
                
            }
            else
            printf("sth wrong\n try again");
        }
        else
        {
            printf("no such order. try again\n");
        }
    }
    
        
        
}
    
