/*************************************************************************
  > File Name: shem.h
  > Author: yuhaitao
  > Mail:acer_yuhaitao@163.com 
  > Created Time: Sat 25 Jun 2016 01:21:16 AM PDT
 ************************************************************************/

#define BUF_SIZE 2048

struct shm_buff{
	int pid;
	char buffer[BUF_SIZE];
};

/* semctl操作要用的结构体  */
union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

/* 信号量的初始化函数 */
int init_sem(int sem_id, int init_value);

/* 从系统中删除信号量  */
int del_sem(int sem_id);

/* P操作函数  */
int sem_p(int sem_id);

/* V操作函数  */
int sem_v(int sem_id);

