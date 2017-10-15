#include<iostream>
#include<algorithm>
#include<vector>
#include<stdio.h>

using std::vector;
using std::remove;

class task{
    private:
        int tag;
        int preocessing_length;
        int due_date;
    public:
        task(int i_index=0, int i_preocessing_length=0, int i_due_date=0){
            tag= i_index;
            preocessing_length = i_preocessing_length;
            due_date = i_due_date;
        };
        int get_tag() {return tag;};
        int get_preocessing_length()    {return preocessing_length;};
        int get_due_date() {return due_date;};
};

class single_machine_schedule{
    private:
        int num_of_task;
        int num_of_tardy_task;
        class task** data_of_task;
        void init(int num) {num_of_task=num; data_of_task=(class task**)malloc(num*sizeof(class task*));};
    public:
        single_machine_schedule(int num){init(num);};
        int get_num_of_task(){return num_of_task;};
        int get_num_of_tardy_task(){return num_of_tardy_task;};
        void add_p_task(int index, class task* i_task){data_of_task[index] = i_task;};
        class task* get_p_task(int index) { return data_of_task[index];};
        void spt_based_algorithm();
        void edd_based_algotithm();
        void show_all_task();
        void exchange(int index1, int index2);
        //quick sort
        int partion_by_pl(int l,int r);
        int partion_by_dd(int l,int r);
        void quick_sort_by_pl(int l, int r);
        void quick_sort_by_dd(int l, int r);
};

void single_machine_schedule::edd_based_algotithm(){
    //index the order by due_date
    //Buble sort is too slow, we may ues the quick sort
    quick_sort_by_dd(0,num_of_task-1);
    /*
    for(int i=0; i<15 ; i++){
        class task* temp_task = get_p_task(i);
        printf("第%d个任务编号为 %d: p_time is %d  d_time is %d.\n",
            i, temp_task->get_tag(), temp_task->get_preocessing_length(), temp_task->get_due_date());
    }*/

    int L = 0;
    vector<int> taskIndex_list;   //store the index of task
    for(int i=0; i<get_num_of_task(); i++){
        class task *temp = get_p_task(i);
        taskIndex_list.push_back(i);
        L += temp->get_preocessing_length();
        if(L > temp->get_due_date()){
            // find the longest job in the new set and we named it as k
            // delete k
            int longest_time = 0;
            int longest_index = 0;
            for(int p=0 ; p<(int)taskIndex_list.size(); p++){
                class task * p_task = get_p_task(*(taskIndex_list.begin()+p));
                if(p_task->get_preocessing_length()>longest_time){
                    longest_time = p_task->get_preocessing_length();
                    longest_index = *(taskIndex_list.begin()+p);
                }
            }
            // delete the longest_index
            remove(taskIndex_list.begin(), taskIndex_list.end(), longest_index);
            taskIndex_list.pop_back();
            L -= longest_time;
        }
    }

    num_of_tardy_task = num_of_task - (int)taskIndex_list.size();
    printf("Tardy_task is %d\n",num_of_tardy_task);
    for(int i=0; i<15 ; i++){
        int index = taskIndex_list[i];
        class task* temp_task = get_p_task(index);
        printf("第%d个任务编号为 %d: p_time is %d  d_time is %d.\n",
            i, temp_task->get_tag(), temp_task->get_preocessing_length(), temp_task->get_due_date());
    }

    //show_all_task();
}
void single_machine_schedule::spt_based_algorithm(){
    printf("Step 1 is begin, and the num of task is %d\n",num_of_task);
    //index the order by preocessing_length
    quick_sort_by_pl(0, num_of_task-1);
    /*for(int i=0; i<15 ; i++){
        class task* temp_task = get_p_task(i);
        printf("第%d个任务编号为 %d: p_time is %d  d_time is %d.\n",
            i, temp_task->get_tag(), temp_task->get_preocessing_length(), temp_task->get_due_date());
    }*/

    // show_all_task();
    int L = 0;

    printf("Step 1 is finshed.\n");
    vector<int> taskIndex_list;   //store the index of task
    vector<int> po_taskIndex_list;
    for(int i=0; i<get_num_of_task(); i++){
        class task* i_task = get_p_task(i);
        // pre_set, it may be ok.
        po_taskIndex_list.assign(taskIndex_list.begin(), taskIndex_list.end());
        // 上面这句话改

        //insert the new task by edd order
        if((int)po_taskIndex_list.size()==0){
            po_taskIndex_list.insert(po_taskIndex_list.begin(),0);
        }else{
            for(int j=0; j<(int)po_taskIndex_list.size(); j++){
                if(i_task->get_due_date()<get_p_task(*(po_taskIndex_list.begin()+j))->get_due_date()){
                    po_taskIndex_list.insert(po_taskIndex_list.begin()+j, i);
                    break;
                }
                if(j==(int)po_taskIndex_list.size()-1){
                    po_taskIndex_list.push_back(i);
                    // 如果去掉这个break， 会死循环， 思考一下为什么
                    break;
                }
            }
        }

        // check the pre_set is feasible or not
        bool feasible_tag = true;
        L = 0;
        for(int j=0; j<(int)po_taskIndex_list.size(); j++){
            class task* temp_j = get_p_task(*(po_taskIndex_list.begin()+j));
            L += temp_j->get_preocessing_length();
            if(L > temp_j->get_due_date())
                feasible_tag = false;
        }
        if(feasible_tag == true){
            taskIndex_list.assign(po_taskIndex_list.begin(), po_taskIndex_list.end());
        }
    }
    num_of_tardy_task = num_of_task - (int)taskIndex_list.size();
    // show the result
    // show_all_task();
    printf("Tardy task is %d.\n", num_of_tardy_task);
    for(int i=0; i<15 ; i++){
    int index = taskIndex_list[i];
        class task* temp_task = get_p_task(index);
        printf("第%d个任务编号为 %d: p_time is %d  d_time is %d.\n",
            i, temp_task->get_tag(), temp_task->get_preocessing_length(), temp_task->get_due_date());
    }


}
void single_machine_schedule::show_all_task(){
    for(int i=0; i<num_of_task; i++){
        class task* temp_task = get_p_task(i);
        printf("第%d个任务编号为 %d: p_time is %d  d_time is %d.\n",
            i, temp_task->get_tag(), temp_task->get_preocessing_length(), temp_task->get_due_date());

   }
}
int single_machine_schedule::partion_by_pl(int l, int r){
    class task* p = get_p_task(r);
    int i = l-1;
    for (int j=l; j<r; j++){
        if(get_p_task(j)->get_preocessing_length() < p->get_preocessing_length() ){
            i++;
            exchange(i, j);
        }
    }
    exchange(i+1, r);
    return i+1;
}
int single_machine_schedule::partion_by_dd(int l, int r) {
    class task* p = get_p_task(r);
    int i = l-1;
    for (int j=l; j<r; j++){
        if(get_p_task(j)->get_due_date() < p->get_due_date() ){
            i++;
            exchange(i, j);
        }
    }
    exchange(i+1, r);
    return i+1;
}
void single_machine_schedule::exchange(int index1, int index2) {
    class task * temp = get_p_task(index1);
    add_p_task(index1, get_p_task(index2));
    add_p_task(index2,temp);
}
void single_machine_schedule::quick_sort_by_pl(int l, int r) {
    if (l<r){
        int q = partion_by_pl(l,r);
        quick_sort_by_pl(l, q-1);
        quick_sort_by_pl(q+1, r);
    }

}
void single_machine_schedule::quick_sort_by_dd(int l, int r) {
    if (l<r){
        int q = partion_by_dd(l,r);
        quick_sort_by_dd(l, q-1);
        quick_sort_by_dd(q+1, r);
    }

}
