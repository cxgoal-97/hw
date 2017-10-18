#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>    //ipc 和 shm 是 shmget,
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/time.h>   //gettimeofday()
#include <stdlib.h>
#include <errno.h>

void exe_with_n_process(int** matrix_A, int** martix_B, int n_process, int matrix_dimension,unsigned int *sum);
int ** init_square_martix(int matrix_dimension);
bool clear_mem_martix(int ** matrix);
void show_martix(int **matrix, int matrix_dimension);
int get_ij(int i, int j, int **matrix_A, int **martix_B, int matrix_dimension);

int main(){
    int matrix_dimension;
    struct timeval start,end;
    int max_process=2;
    unsigned int checksum=0;
    int sec=0, usec=0;
    printf("Input the matrix dimension:");
    scanf("%d", &matrix_dimension);

    int ** matrix_A = init_square_martix(matrix_dimension);
    int ** matrix_B = init_square_martix(matrix_dimension);


    //printf("%d", get_ij(0, 0, matrix_A, matrix_B, matrix_dimension));
    for(int n_process=1; n_process<max_process+1; n_process++){
        printf("Multiplying matrices using %d process",n_process);
        if(n_process!=1)
            printf("es\n");
        else
            printf("\n");
        gettimeofday(&start,0);
        exe_with_n_process(matrix_A,matrix_B,n_process,matrix_dimension, &checksum);
        gettimeofday(&end,0);
        sec = end.tv_sec-start.tv_sec;
        usec = end.tv_usec-start.tv_usec;
        printf("elapsed %f ms, Checksum:%d\n", sec*1000+(usec/1000.0), checksum);
    }
}

void exe_with_n_process(int** matrix_A, int** matrix_B, int n_process, int matrix_dimension, unsigned int * sum){
    //理解一下sizeof 在二维指针上的问题
    int shm_id = shmget(IPC_PRIVATE, matrix_dimension*matrix_dimension*sizeof(int), IPC_CREAT|0600);
    int len_of_each_process = (int)matrix_dimension/n_process;
    int len_of_last_process = matrix_dimension-(n_process-1)*len_of_each_process;
    struct shmid_ds buf;

    /*
    printf("matrix_dimension is %d.\n", matrix_dimension);
    printf("len_of_each_process is %d.\n", len_of_each_process);
    printf("len_of_last_process is %d.\n", len_of_last_process);
    printf("shm_id is %d\n",shm_id);
    */

    for(int i=0; i<n_process; i++){
        pid_t pid = fork();
        if(pid<0){
            printf("ERROR");
        }else if(pid==0){   //child process

            int * shm = (int *)shmat(shm_id,NULL,0);
            if(i!=n_process-1){
                for(int p=0; p<len_of_each_process; p++){
                    for(int q=0; q<matrix_dimension; q++){
                        *(shm+matrix_dimension*(p+i*len_of_each_process)+q) = get_ij(p+i*len_of_each_process,q,matrix_A,matrix_B, matrix_dimension);
                    }
                }
            }else if(i==n_process-1){
                for(int p=0; p<len_of_last_process; p++){
                    for(int q=0; q<matrix_dimension; q++){
                        *(shm+matrix_dimension*(p+i*len_of_each_process)+q) = get_ij(p+i*len_of_each_process,q,matrix_A,matrix_B, matrix_dimension);
                    }
                }
            }
            shmdt(shm);
            //想想为什么要这个exit
            exit(1);
        }else{  //parent process
                //waitpid(pid,NULL,0);
                if(i!=n_process-1)
                    waitpid(pid,NULL,WNOHANG);
                if(i==n_process-1){
                    waitpid(pid,NULL,0);
                    int * shm = (int *)shmat(shm_id,NULL,0);
                    *sum = 0;
                    for(int p=0; p<matrix_dimension*matrix_dimension; p++)
                        //printf("%d ",*(shm+p));
                        *sum = *(shm+p) + *sum;
                    shmdt(shm);
                    shmctl(shm_id, IPC_RMID, &buf);
                }
        }
    }
}

int ** init_square_martix(int matrix_dimension){
    int ** matrix = new int *[matrix_dimension];
    for(int i=0; i<matrix_dimension; i++){
        matrix[i] = new int [matrix_dimension];
        for(int j=0; j<matrix_dimension; j++){
            matrix[i][j] = i*matrix_dimension+j;
        }
    }
    return matrix;
}

void show_martix(int ** martix, int matrix_dimension){
    for(int i=0; i<matrix_dimension; i++){
        for(int j=0; j<matrix_dimension; j++){
            printf("%5d",martix[i][j]);
        }
        printf("\n");
    }
}

int get_ij(int i, int j, int ** matrix_A, int** martix_B, int matrix_dimension){
    //c_ij = \sum_{p=0}^{matrix_dimension}a_{ip}b_{pj}
    //a_{ip} = *(*(A+i)+p)
    //b_{pj} = *(*(B+p)+j)
    int c_ij=0 ;
    for(int p=0; p<matrix_dimension; p++)
        c_ij += *(*(matrix_A+i)+p)**(*(martix_B+p)+j);

    return c_ij;
}
