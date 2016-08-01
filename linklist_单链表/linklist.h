/*************************************************************************
    > File Name: linklist.h
    > Author: yuhaitao
    > Mail:acer_yuhaitao@163.com 
    > Created Time: Tue 14 Jun 2016 04:24:24 AM PDT
 ************************************************************************/

//#define err_log(errlog) do{perror(errlog);exit(1);}while(0)
typedef int datatype;
typedef struct linknode {
	datatype data;
	struct linknode *next;
}linknode, *linklist;

linknode *linklist_create(void);
int linklist_head_insert(linknode *H, int value);
int linklist_show(linknode *H);
int linklist_chose_insert(linklist H, int pos, int value);
