#include "single_machine_schedule.cpp"
#include <ctime>

#include <fstream>  //read the file
#include <stdio.h>  //string to int
/*
 * 采用 clock()函数用于计时
 *
*/

int main(){
    std::ifstream file;
    file.open("data/10000data_1.txt");
    char input[50];
    file>>input;
    int num_of_task = 0;
    sscanf(input,"%d",  &num_of_task);
    printf("num_of_task is %d\n",num_of_task);
    single_machine_schedule task_set(num_of_task);
    // add the task
    int p_l=0,d_d=0;
    class task* task_p_list =(class task *)malloc(num_of_task*sizeof(class task));
    // from txt file
    for(int i=0; i<num_of_task; i++){
        file>>input;
        sscanf(input,"%d", &p_l);
        file>>input;
        sscanf(input,"%d", &d_d);
        task_p_list[i] = task(i, p_l, d_d);
        task_set.add_p_task(i, task_p_list+i);
    }
    file.close();
    /*
    for(int i=0; i<num_of_task; i++){
        scanf("%d %d", &p_l, &d_d);
        task_p_list[i] = task(i, p_l, d_d);
        task_set.add_p_task(i, task_p_list+i);
    }
    */

    // task_set.show_all_task();
    clock_t begin_time=0, end_time=0;
    // the first way
    begin_time = clock();
    printf("\n\nSpt_based_algorithm.\n");
    task_set.spt_based_algorithm();
    end_time = clock();
    printf("The of spt algorithm is %lf.\n", (double)(end_time-begin_time)/CLOCKS_PER_SEC);

    // the second way
    begin_time = clock();
    printf("\n\nEdd_based_algorithm.\n");
    task_set.edd_based_algotithm();
    end_time = clock();
    printf("The of edd algorithm is %lf.\n", (double)(end_time-begin_time)/CLOCKS_PER_SEC);

    return 0;
}

