#ifndef DISPLAY_C
#define DISPLAY_C

#define MODE PIN_B0
#define EDIT PIN_D0
#define INC PIN_D2
#define DEC PIN_D3
#define lcd_sclk  PIN_A0 
#define lcd_sda   PIN_A1              
#define lcd_dc    PIN_A2                     
#define lcd_cs    PIN_A3                                                                            
#define lcd_res   PIN_A5                                                                                      
                                                                                                     
#include "5110lib\3310(modified).c"
#include <string.h>
int clock_mode=0;
int setting_mode=0;
int alarm_mode=0;

int num_edit=0;
int mode_list=0;
int h_alarm[5]={0,0,0,0,0};
int m_alarm[5]={0,0,0,0,0};
const int alarm_list[5]={1,2,3,4,5};
int h=2,m=4,s=45;
int h_edit=9,m_edit=56,day_edit=18,mth_edit=6,yea_edit=16,dow_edit=2;
byte day=5,mth=4,yea=15,dow=2;
byte set_alarm[5]={0,0,0,0,0};
int set_alarm_mode=0;
int set_time_mode=0;
int set_date_mode=0;
byte temp=0;
//const char *monday[7]={"Mon","Tue","Wea","Thu","Fri","Sat","Sun"};
//char *alarm_char[2]={"ON ","OFF"};

void alarm_warning(void);
void edit_time(int h, int m);
void edit_date(int d, int m,int y,int dayow);
void clock_screen(void);
void alarm_screen(void);
void menu_screen(void);
void log_screen(int n);
void set_alarm_screen(void);
void display_screen(void);
void alarm_edit(void);
void button_ok(int n);

void alarm_warning(){
   int i=0;
   for(i=0;i<30;i++){
//      printf("second %d ",s);
      if(!input(MODE)){
         while(!input(MODE)){
            delay_ms(100);
         }
         break;
      }
      else{
         nokia_gotoxy(0,0);
         printf(nokia_printchar,"ALARM RING!");
         delay_ms(1000);
      }
   }
}
void alarm_screen(){//hien thi danh sach alarm
int i=0;
   nokia_gotoxy(0,0);
   printf(nokia_printchar,"ALARM SETTING");
   if(mode_list<4){
      for(i=0;i<4;i++){
         if(mode_list==i){
            nokia_gotoxy(0,1+i);
            printf(nokia_printchar_inverted,"ALARM %d       ",alarm_list[i]);//alarm nao dc chon thi boi den
         }else{
            nokia_gotoxy(0,1+i);
            printf(nokia_printchar,"ALARM %d",alarm_list[i]);
         }
      }
   }else if(mode_list==4){//next trang moi hien thi cac alarm khac
      for(i=1;i<5;i++){
         if(mode_list==i){
            nokia_gotoxy(0,i);
            printf(nokia_printchar_inverted,"ALARM %d       ",alarm_list[i]);
         }else{
            nokia_gotoxy(0,i);
            printf(nokia_printchar,"ALARM %d",alarm_list[i]);
         }
      }      
   }
   button_ok(1);
}
void button_ok(int n){//hien thi cac loai nut button
if(n==0){
    nokia_gotoxy (0, 5);
    printf (nokia_printchar, "MENU");
}
else if(n==1){
    nokia_gotoxy (0, 5);
    printf (nokia_printchar, "OK        BACK");
}
else if(n==2){
    nokia_gotoxy (0, 5);
    printf (nokia_printchar, "OK        NEXT");
}
else{
    nokia_gotoxy (0, 2);
    printf (nokia_printchar, "Save your     change?");
    nokia_gotoxy (0, 5);
    printf (nokia_printchar, "OK      CANCEL");
}
}
void clock_screen(){//man hinh chinh hien thi ngay thang nam, gio phut giay, nhiet do
      int i=0;//neu co bat 1 alarm ALARM ON, khong bat cai nao se la OFF
      int set=0;
       nokia_gotoxy (0, 1);
       if(day<10)
         printf (nokia_printchar, "0%d",day);
       else 
         printf (nokia_printchar, "%d",day);
       if(mth<10)
         printf (nokia_printchar, "/0%d",mth);
       else
         printf (nokia_printchar, "/%d",mth);
       if(yea<10)
         printf (nokia_printchar, "/200%d",yea);
       else
         printf (nokia_printchar, "/20%d",yea);
       nokia_gotoxy (0, 2);
       if(h<10)
         printf (nokia_printchar, "0%d",h);
       else 
         printf (nokia_printchar, "%d",h);
       if(m<10)
         printf (nokia_printchar, ":0%d",m);
       else
         printf (nokia_printchar, ":%d",m);
       if(s<10)
         printf (nokia_printchar, ":0%d",s);
       else
         printf (nokia_printchar, ":%d",s);       
       nokia_gotoxy (0, 3);
       if(temp<10)
         printf (nokia_printchar, "0%d~C",temp);
       else 
         printf (nokia_printchar, "%d~C",temp);
       nokia_gotoxy (0, 4);    
       for(i=0;i<5;i++)
       if(set_alarm[i]==1){
         set=1;
         break;
       }else set=0;
       if(set==1)
         printf (nokia_printchar,"ALARM ON"); 
       
       else printf (nokia_printchar,"ALARM OFF");
       button_ok(0);
}
void menu_screen(){//hie thi man hinh menu
       nokia_gotoxy (0, 0);
       printf (nokia_printchar, "   SETTINGS   ");
       nokia_gotoxy (0, 1);
       if(mode_list==0)
         printf (nokia_printchar_inverted, "Adjust time   ");
       else{
         printf (nokia_printchar, "Adjust time");
       }
       nokia_gotoxy (0, 2);
       if(mode_list==1)
         printf (nokia_printchar_inverted, "Adjust date   ");
       else{
         printf (nokia_printchar, "Adjust date");
       }
       nokia_gotoxy (0, 3);
       if(mode_list==2)
         printf (nokia_printchar_inverted, "Set alarm     ");
       else{
         printf (nokia_printchar, "Set alarm");
       }  
       button_ok(1);
}
void log_screen(int n){//man hinh thong bao
      nokia_clean_ddram();
      nokia_gotoxy(0,0);
   switch(n){
      case 0: printf (nokia_printchar, "Time was saved");
      break;
      case 1: printf (nokia_printchar, "Date was saved");
      break;
      case 2: printf (nokia_printchar, "Alarm was set");
      break;
      default: printf (nokia_printchar,"The action was saved in SD   card");
      break;
   }
   delay_ms(1000);
}

void display_screen(){//dieu khien viec hien thi cac man hinh

    if(clock_mode==0){ 
       clock_screen();
    }
    else{
      switch(setting_mode){
      case 0:
         menu_screen();
         break;
      case 1:   if(set_time_mode==0)//man hinh chinh thoi gian
                  edit_time(h_edit,m_edit);
               else
                  button_ok(3);//tuy chon luu thay doi
               break;
      case 2: if(set_date_mode==0)//man hinh chinh ngay
               edit_date(day_edit,mth_edit,yea_edit,dow_edit);
              else
              button_ok(3);//luu hay khong
              break;
      case 3:  alarm_edit();              
         break;
         
      }
       
    }
}
void set_alarm_screen(int i){//man hinh tuy chon luu cai dat alarm
    nokia_gotoxy (0, 0);
    printf (nokia_printchar, " EDIT ALARM %d ",i);
    if(mode_list==0){
       nokia_gotoxy (0, 1);
       printf (nokia_printchar_inverted, "Set alarm on ");
       nokia_gotoxy (0, 2);
       printf (nokia_printchar, "Set alarm off");
    }else{
       nokia_gotoxy (0, 1);
       printf (nokia_printchar, "Set alarm on ");
       nokia_gotoxy (0, 2);
       printf (nokia_printchar_inverted, "Set alarm off");    
    }
    button_ok(1);
}
void alarm_edit(){//hien thi tuy chon chinh alarm
int i=0;
   if(alarm_mode==0){
      alarm_screen();
   }else{
      for(i=1;i<6;i++){
         if(alarm_mode==i){
            if(set_alarm_mode==0){            
               nokia_gotoxy (0, 0);
               printf (nokia_printchar, " EDIT ALARM %d ",i);
               edit_time(h_alarm[i-1], m_alarm[i-1]);
               nokia_gotoxy(5,3);               
               if(set_alarm[i-1]==1)
                  printf(nokia_printchar,"Alarm on");
               else
                  printf(nokia_printchar,"Alarm off");
            }
            else 
            set_alarm_screen(alarm_mode);
         }
      }
   }
}
void edit_time(int h, int m){//man hinh chinh gio phut cho viec cai dat thoi gian, alarm
   nokia_gotoxy (5, 2);
   if(num_edit==0)
      if(h<10)
         printf (nokia_printchar_inverted, "0%d",h);
      else
         printf (nokia_printchar_inverted, "%d",h);
   else
      if(h<10)
         printf (nokia_printchar, "0%d",h);
      else 
         printf (nokia_printchar, "%d",h); 
   printf (nokia_printchar, ":");
   if(num_edit==1)
      if(m<10)
         printf (nokia_printchar_inverted, "0%d",m);
      else 
         printf (nokia_printchar_inverted, "%d",m);
   else 
      if(m<10)
         printf (nokia_printchar, "0%d",m);
      else 
         printf (nokia_printchar, "%d",m);
   button_ok(2);
}
void edit_date(int d, int m,int y,int dayow){//man hinh chinh ngay thang nam
   nokia_gotoxy (0, 0);
   printf (nokia_printchar, "   EDIT DATE   ");
   nokia_gotoxy (0, 2);
   if(num_edit==0)
      if(d<10)
         printf (nokia_printchar_inverted, "0%d",d);
      else 
         printf (nokia_printchar_inverted, "%d",d);
   else
      if(d<10)
         printf (nokia_printchar, "0%d",d);
      else 
         printf (nokia_printchar, "%d",d);
   printf (nokia_printchar, "/");
   if(num_edit==1)
      if(m<10)
         printf (nokia_printchar_inverted, "0%d",m);
      else 
         printf (nokia_printchar_inverted, "%d",m);
   else 
      if(m<10)
         printf (nokia_printchar, "0%d",m);
      else 
         printf (nokia_printchar, "%d",m);
   printf (nokia_printchar, "/");
   if(num_edit==2)
      if(y<10)
         printf (nokia_printchar_inverted, "200%d",y);
      else 
         printf (nokia_printchar_inverted, "20%d",y);
   else 
      if(y<10)
         printf (nokia_printchar, "200%d",y);
      else 
         printf (nokia_printchar, "20%d",y);
   nokia_gotoxy (0, 3);
   if(num_edit==3){
      switch(dayow){//hien thi ngay trong tuan
         case 1: 
         printf (nokia_printchar_inverted, "Sunday        ");
         break;
         case 2: 
         printf (nokia_printchar_inverted, "Monday        ");
         break;
         case 3: 
         printf (nokia_printchar_inverted, "Tuesday       ");
         break;
         case 4: 
         printf (nokia_printchar_inverted, "Wednesnday    ");
         break;
         case 5: 
         printf (nokia_printchar_inverted, "Thursday      ");
         break;  
         case 6: 
         printf (nokia_printchar_inverted, "Friday        ");
         break;
         default: 
         printf (nokia_printchar_inverted, "Saturday      ");
         break;      
      }
   }
   else{ 
       switch(dow){
         case 1: 
         printf (nokia_printchar, "Sunday         ");
         break;
         case 2: 
         printf (nokia_printchar, "Monday         ");
         break;
         case 3: 
         printf (nokia_printchar, "Tuesday        ");
         break;
         case 4: 
         printf (nokia_printchar, "Wednesnday     ");
         break;
         case 5: 
         printf (nokia_printchar, "Thursday       ");
         break;  
         case 6: 
         printf (nokia_printchar, "Friday         ");
         break;
         default: 
         printf (nokia_printchar, "Saturday       ");
         break;      
      }     
   }
   button_ok(2);
}

void control_time(){//dieu khien nut bam
      if(!input(MODE)){
         while(!input(MODE)){
            delay_ms(100);
         }
         if(clock_mode==0){//neu dang o man hinh lock thi chuyen sang menu
            clock_mode=1;
            mode_list=0;//chuyen danh sach ve 0
         }
         else if(clock_mode==1){
            if(setting_mode==0){//neu dang o man hinh danh sach thi chuyen sang man hinh khac
               setting_mode=mode_list+1;//chuyen sang man hinh con
            }else if(setting_mode==1){
            if(set_time_mode==0)
            set_time_mode=1;//chuyen sang man hinh luu cai dat
            else{
               h=h_edit;//neu dang o man hinh chinh thoi gian thi luu gio
               m=m_edit;//luu phut da chinh
               log_screen(0);//man hinh thong bao da luu               
               setting_mode=0;//chuyen ve man hinh menu
               rtc_set_datetime(day,mth,yea,dow,h,m);//luu thoi gian da chinh
               nokia_clean_ddram () ;
               set_time_mode=0;//thoat man hinh cai dat
            }
            }else if(setting_mode==2){
            if(set_date_mode==0)
               set_date_mode=1;//chuyen sang man hinh luu cai dat
            else{
               day=day_edit;//neu dang o man hinh chinh ngay thang nam thi luu
               mth=mth_edit;// lai gia tri da chinh
               yea=yea_edit;
               dow=dow_edit;
               log_screen(1);//man hinh thong bao da luu               
               setting_mode=0;//chuyen ve man hinh menu
               rtc_set_datetime(day,mth,yea,dow,h,m);//luu lai thoi gian da chinh
               set_date_mode=0;//thoat man hinh cai dat
            }
            }else if(setting_mode==3){
               if(alarm_mode==0){//neu dang o man hinh danh sach alarm thi chuyen
                  alarm_mode=mode_list+1;//sang man hinh chinh alarm                  
               }else{
                  if(set_alarm_mode==0){//neu dang o man hinh danh sach thi
                     set_alarm_mode=mode_list+1;//luu cai dat thoi gian                     
                  }
                  else if(set_alarm_mode==1){
                        set_alarm[alarm_mode-1]=1;//set alarm on
                        alarm_mode=0;//thoat man hinh chinh alarm
                        set_alarm_mode=0;//thoat man hinh set alarm
                        log_screen(2); //man hinh thong bao da luu
                  }else if(set_alarm_mode==2){ 
                        set_alarm[alarm_mode-1]=0;//set alarm off
                        alarm_mode=0;
                        set_alarm_mode=0;                        
                  }
               }
            }
         }
         mode_list=0;//chinh danh sach ve dau
         num_edit=0;//thu tu edit ve dau
         nokia_clean_ddram () ;//xoa man hinh
      }
      
      if(!input(EDIT)){
         while(!input(EDIT)){
            delay_ms(10);
            //printf("point 1\n");
         }
         if(clock_mode==1){
            if(setting_mode==0){//dang o man hinh danh sach
               clock_mode=0;//ve man hinh chinh
            }
            else if(setting_mode==1){//dang o man hinh chinh thoi gian
            if(set_time_mode==0){
               num_edit++;//thay doi so can chinh, chuyen sang chinh gio hoac phut
               if(num_edit>1)num_edit=0;
            }
            else{
               setting_mode=0;//ve man hinh danh sach
               mode_list=0;//danh sach ve dau
               set_time_mode=0;//thoat man hinh chinh thoi gian
            }
            }
            else if(setting_mode==2){//man hinh chinh ngay
            if(set_date_mode==0){//khi chua chuyen sang man hinh luu thay doi
               num_edit++;//chuyen sang chinh ngay thang hoac nam
               if(num_edit>3)num_edit=0;
            }
            else{
               set_date_mode=0;//kho
               setting_mode=0;//ve man hinh danh sach
               mode_list=1;
            }
            }
            else{
               if(alarm_mode==0){//man hinh danh sach alarm
                  setting_mode=0;//thoat man hinh
                  mode_list=2;
               }
               else{
                  if(set_alarm_mode==0){//ma hinh tuy chon set alarm hay khong
                     num_edit++;
                     if(num_edit>1)num_edit=0;                         
                  }
                  else{
                     set_alarm_mode=0;
                     alarm_mode=0;
                     setting_mode=0;
                     mode_list=2;
                  }
               }
            }
         }      
         nokia_clean_ddram () ;//xoa man hinh
//         printf("point 1\n");
//         delayled_on(1);
      }
      
      if(!input(INC)){//nut dieu chinh tang gia tri         
         while(!input(INC)){            
            if(clock_mode==1){
               if(setting_mode==0){//di chuyen danh sach len
                  mode_list++;
                  if(mode_list>2)mode_list=0;
               }            
               else if(setting_mode==1){//che do cai dat thoi gian
               if(set_time_mode==0)//khi dang o man hinh dieu chinh thoi gian
                  if(num_edit==0){
                     h_edit++;//thay doi gia tri gio
                     if(h_edit>23)h_edit=0;                     
                  }else{
                     m_edit++;//thay doi gia tri phut
                     if(m_edit>59) m_edit=0;   
                  }
               }
               else if(setting_mode==2){//che do cai dat ngay thang
               if(set_date_mode==0)//man hinh dieu chinh ngay thang
                  switch(num_edit){
                     case 0:day_edit++;//tang gia tri ngay
                           if(day_edit>31)day_edit=1;
                           break;
                     case 1:mth_edit++;//tang gia tri thang
                           if(mth_edit>12)mth_edit=0;
                           break;
                     case 2:yea_edit++;//tang gia tri nam
                           if(yea_edit>99)yea_edit=0;
                           break;
                     case 3:dow_edit++;//tang gia tri ngay trong tuan
                           if(dow_edit>7)dow_edit=1;
                           break;
                  }
               }
               else if(setting_mode==3){//che do dieu chinh alarm
                  if(alarm_mode==0){//khi dang o man hinh danh sach cac alarm
                     mode_list++;//lua chon cac alarm
                     if(mode_list>4)mode_list=0;
                  }
                  else{
                     if(set_alarm_mode==0){//khi dang chinh thoi gian
                        if(num_edit==0){
                           h_alarm[alarm_mode-1]++;//tang gia tri gio cua alarm da chon
                           if(h_alarm[alarm_mode-1]>23)h_alarm[alarm_mode-1]=0;                     
                        }else{
                           m_alarm[alarm_mode-1]++;//tang gia tri phut cua alarm da chon
                           if(m_alarm[alarm_mode-1]>59) m_alarm[alarm_mode-1]=0;   
                        }          
                     }
                     else{// khi dang tuy chon set hay khong
                        mode_list++;
                        if(mode_list>1)mode_list=0;
                        set_alarm_mode=mode_list+1;//luu tuy chon
                     }
                  }
             
               } 
            
            }
            nokia_clean_ddram () ;
            display_screen();//cap nhap gia tri moi
            delay_ms(500);
         }         
      }
      
      if(!input(DEC)){// nut dieu chinh giam gia tri
         while(!input(DEC)){                        
            if(clock_mode==1){//man hinh danh sach
               if(setting_mode==0){                  
                  if(mode_list==0)mode_list=2;
                  else mode_list--;//di chuyen danh sach xuong
               }            
               else if(setting_mode==1){//man hinh dieu chinh gio
                  if(num_edit==0){                     
                     if(h_edit==0)h_edit=23;    
                     else h_edit--;//dieu chinh gio
                  }else{
                     if(m_edit==0) m_edit=59;
                     else m_edit--;//dieu chinh ngay                        
                  }
               }
               else if(setting_mode==2){//dieu chinh ngay thang
                  switch(num_edit){
                     case 0:
                           if(day_edit==0)day_edit=31;
                           else day_edit--;//dieu chinh ngay
                           break;
                     case 1:
                           if(mth_edit==0)mth_edit=2;
                           else mth_edit--;//dieu chinh thang
                           break;
                     case 2:
                           if(yea_edit==0)yea_edit=99;
                           yea_edit--;//dieu chinh nam
                           break;
                     case 3:
                           if(dow_edit==1)dow_edit=7;
                           else dow_edit--;//dieu chinh ngay trong tuan
                           break;
                  }
               }
               else if(setting_mode==3){//man hinh danh sach alarm
                  if(alarm_mode==0){                     
                     if(mode_list==0)mode_list=4; 
                     else mode_list--;//dieu chinh danh sach alarm
                  }
                  else{
                     if(set_alarm_mode==0){
                        if(num_edit==0){                           
                           if(h_alarm[alarm_mode-1]==0)h_alarm[alarm_mode-1]=23;
                           else h_alarm[alarm_mode-1]--;//dieu chinh gio alarm da chon
                        }else{                           
                           if(m_alarm[alarm_mode-1]==0) m_alarm[alarm_mode-1]=59;   
                           else m_alarm[alarm_mode-1]--;//dieu chinh phut alarm da chon
                        }          
                     }
                     else{                        
                        if(mode_list==0)mode_list=1;
                        else mode_list--;//dieu chinh tuy chon set alarm hay khong
                        set_alarm_mode=mode_list+1;//luu luon tuy chon cho do lang nhang
                     }
                  }
             
               } 
            
            }   
            nokia_clean_ddram () ;
            display_screen();
            delay_ms(500);
         }
      }
}
#endif
