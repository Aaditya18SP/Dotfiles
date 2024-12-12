#define TRUE 1 
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

int power(int number, int power){

    if(power==0){
        return 1;
    }

    int result=number;

    for(int i=1;i<power;i++){
        result*=number;
    }
    return result;
}

int main(){

   //while(TRUE){
    ///sys/class/power_supply/bat0/uevent
    FILE *f = fopen("/sys/class/power_supply/BAT0/uevent", "r");
    char ch;
    char *search_string_1 = "POWER_SUPPLY_ENERGY_FULL_DESIGN";
    char *search_string_2 = "POWER_SUPPLY_ENERGY_NOW";
    char *search_string_3 = "POWER_SUPPLY_STATUS";
    char search_result_1[50]="", search_result_2[50]="",search_result_3[50]="";
    int string_idx=0;// the index for the search result array
    int is_result_on_this_line =1; //initially we assume it is
    int s1_found=0,s2_found=0, s3_found=0;

    while((ch=getc(f))!=EOF){
        if(ch!='\n'){   
            if(string_idx<18 && ch==search_string_3[string_idx]&& is_result_on_this_line){
                search_result_3[string_idx]=ch;
                string_idx++;
            }
            else if(string_idx>=18){
                s3_found=1;
                search_result_3[string_idx]=ch;
            string_idx++;
            }
            else{
                is_result_on_this_line =0;
                string_idx=0;
                s3_found=0;
            }
        }
        else{
            if(s3_found){
                break;
            }
            is_result_on_this_line=1;
            string_idx=0;
        }
    }

    int s3=string_idx;
    is_result_on_this_line =1;
    string_idx =0;

    while((ch=getc(f))!=EOF){
        if(ch!='\n'){   
            if(string_idx<31 && ch==search_string_1[string_idx]&& is_result_on_this_line){
                search_result_1[string_idx]=ch;
                string_idx++;
            }
            else if(string_idx>=31){
                s1_found=1;
                search_result_1[string_idx]=ch;
            string_idx++;
            }
            else{
                is_result_on_this_line =0;
                string_idx=0;
                s1_found=0;
            }
        }
        else{
            if(s1_found){
                break;
            }
            is_result_on_this_line=1;
            string_idx=0;
        }
    }


    int s1 = string_idx;
    string_idx =0;
    is_result_on_this_line=1;

    while((ch=getc(f))!=EOF){
        if(ch!='\n'){   
            //Search string 2
            if(string_idx<22 && ch==search_string_2[string_idx]&& is_result_on_this_line){
                search_result_2[string_idx]=ch;
                string_idx++;

            }
            else if(string_idx>=22){
                s2_found=1;
                search_result_2[string_idx]=ch;
                string_idx++;
            }
            else{

                is_result_on_this_line =0;
                string_idx=0;
                s2_found=0;
            }
        }
        else{
            if(s2_found){
                break;
            }
                is_result_on_this_line =1;
                string_idx=0;
        }
    }


    int s2= string_idx;


//    if(s1_found){
//        printf("\nS1:%s\n", search_result_1);
//    }
//   if(s2_found){
//        printf("S2:%s\n", search_result_2);
//    }
//    if(s3_found){
//        printf("S3:%s\n", search_result_3);
//    }

    char *discharging = "Discharging";
    int is_discharging =0;
    //determine whether it is charging or discharging
    for(int i=20;i<=30;i++){

        
       if(search_result_3[i]==discharging[i-20]){
           is_discharging = 1;
       
       }
       else{
           is_discharging=0;
       }
       
    }

    unsigned int current_energy =0;
    int exponent=0;
    for(int i = s2-1;i>=24;i--){

        current_energy+=(search_result_2[i]-48)*power(10,exponent);
        exponent++;

    }
    unsigned int total_energy =0;
    exponent=0;
    for(int i = s1-1;i>=32;i--){

        total_energy+=(search_result_1[i]-48)*power(10,exponent);
        exponent++;

    }

    unsigned int battery_percent = (current_energy *100)/total_energy;
    //printf("\n%u\n", battery_percent);

    if(battery_percent <=30 && is_discharging){
        system("notify-send \"Low Battery. Please plug in\"");
    }

    struct timeval timeInterval = {300, 0}; //sleep for 5 minutes ie 300 seconds and 0 microseconds

    //more reliable than sleep according to GNU C docs than 'sleep'
    select(0, NULL, NULL, NULL,&timeInterval);
   
    //sleep(300);
    fclose(f);

   //}
    return 0;
}
