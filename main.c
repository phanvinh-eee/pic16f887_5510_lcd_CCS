#include <main.h>
//#include <lcd.c>
#include <ds1302.c>
#include <ds18b20.c>
#include <stdlib.h> // for atoi32
void main()
{
   byte n=0;
   setup_adc_ports(NO_ANALOGS|VSS_VDD);
   setup_adc(ADC_OFF);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   rtc_init(); 
   nokia_init();
   nokia_clean_ddram() ;
//   rtc_set_datetime(day,mth,yea,dow,h,m);      
   
  while(TRUE) 
  {   
    rtc_get_time(h, m, s); 
    rtc_get_date(day,mth,yea,dow);
      control_time();
      if(clock_mode==0){
         temp=ds18b20_read(temp);         
      }
      //clock_screen();
      //menu_screen();
      display_screen();
      for(n=0;n<5;n++)
      if(set_alarm[n]==1)
         if(h==h_alarm[n])
           if(m==m_alarm[n])
            if(s==0){
               alarm_warning();
               set_alarm[n]=0;
            }            
//      printf("day: %d, month: %d, year: %d, day of week: %d\n",day,mth,yea,dow);     
  }
}

