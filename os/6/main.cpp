#include<iostream>
#include<unistd.h>
#include<cstdio>
#include<dirent.h>
#include<sys/stat.h>
#include<string>
#include<vector>

using namespace std;

const int ARGV_NUM=5;
string * get_argv(int argv_num, char * argv[]);
//读入命令行参数，返回整理之后的参数数组
//若无则为空字符串.参数顺序依次为文件路径，inode，name，size_min,size_max(文件大小的单位是MB)
//输入为文件的绝对路径,输出依次为完整的文件路径，文件inode号，文件大小(单位为MB)
void search_file(const string* argv_arr);

//
const string dic[ARGV_NUM] = {"pathName", "inode", "name", "size_min","size_max"};
//MB与字节的换算
const float MBTOBYTE= 1024*1024.0;

int main(int argc, char * argv[]){

    //判断参数个数，如果缺少参数，报错并退出
    if(argc==1){
        printf("ERROR:缺少参数\n");
        return 0;
    }
    //读入参数, 参数顺序依次为文件路径，inode，name，size_min,size_max(MB);
    string* argv_arr = get_argv(argc, argv);
    search_file(argv_arr);
    return 0;
}

//读入命令行参数，返回整理之后的参数数组
//若无则为空字符串.参数顺序依次为文件路径，inode，name，size_min,size_max(文件大小的单位是MB)
//判断是否为空字符可以采用str.empty()
string * get_argv(int argv_num, char * argv[]){
    static string *argv_arr = (string *)new string[ARGV_NUM];
    int i=0;
    while(i<argv_num){
        string arg = argv[i++];
        if(i==1)
            *(argv_arr+0) = argv[i++];
        else if(arg=="-inode")
            *(argv_arr+1)= argv[i++];
        else if(arg=="-name")
            *(argv_arr+2)= argv[i++];
        else if(arg=="-size_min")
            *(argv_arr+3)= argv[i++];
        else if(arg=="-size_max")
            *(argv_arr+4)= argv[i++];
    }
    return argv_arr;
};

void search_file(const string* argv_arr){
    string pathName = argv_arr[0];
    struct stat buf;
    struct dirent *entry;
    if(pathName.empty()){   //如果路径为空，返回True
        printf("ERROR:路径为空。\n");
        return ;
    }

    chdir(pathName.c_str());        //将工作目录移到目标目录中
    DIR * dp = opendir(pathName.c_str());
    if(dp==NULL){
        return;
    }
    while((entry=readdir(dp))!=NULL){   //对当前目录下，除开.和..目录进行遍历
        string filename = entry->d_name;
        if(filename=="."||filename=="..")
            continue;
        //除开.和..，进行检查，包括目录。注意目录大小为本身的大小，不包含目录内文件的大小
        stat(filename.c_str(), &buf);
        //检查文件，判断其是否符合条件
        //以此检查inode, name, size_min, size_max.
        //其中inode,size_min,size_max是数字，其中size的单位是MB
        bool tag = true;
        //判断是否符合要求的旗标，如果符合全部要求，则为true
        //如果不符合要求则，更改为false
        //检查inode，文件索引
        if(!argv_arr[1].empty()){
            unsigned long inode;
            sscanf(argv_arr[1].c_str(), "%lu", &inode);
            tag = inode==buf.st_ino;
        }
        //检查文件名字
        if(tag&&!argv_arr[2].empty()){
            tag = filename==argv_arr[2];
        }
        //检查文件最小,最大大小
        //注意换算问题
        if(tag&&!argv_arr[3].empty()){
            long size_min;
            sscanf(argv_arr[3].c_str(), "%ld", &size_min);
            tag = (buf.st_size>=size_min*MBTOBYTE);
        }
        if(tag&&!argv_arr[4].empty()){
            long size_max;
            sscanf(argv_arr[4].c_str(), "%ld", &size_max);
            tag = (buf.st_size<=size_max*MBTOBYTE);
        }
        //判断是否符合要求，如果符合则输出
        if(tag)
           cout<<pathName+"/"+filename<<"\t\t"<<buf.st_ino<<"\t\t"<<buf.st_size/MBTOBYTE<<" MB"<<endl;
        //判断是否为文件夹,如果是文件夹，则采取递归策略
        //构造递归函数的参数时，需要注意文件名之间的链接符
        if(S_ISDIR(buf.st_mode)){
            //若原先的PathName末尾有/,则没有必要加上/，反之要加上/
            string next_pathName;
            if(pathName[pathName.size()-1]=='/')
                next_pathName = pathName+filename;
            else
                next_pathName = pathName+"/"+filename;
            const string next_argv[ARGV_NUM] ={next_pathName, argv_arr[1],argv_arr[2],argv_arr[3],argv_arr[4]};
            search_file(next_argv);
        }
        else
            //printf("这不是文件夹");
            continue;
        //cout<<filename<<"   ";
        //cout<<"大小"<<buf.st_size<<"\t路径"<<pathName.c_str()<<entry->d_name<<"\n";
    }
}

