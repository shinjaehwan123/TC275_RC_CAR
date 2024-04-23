#include "main.h"
#include "Drivers/asclin.h"
#include "Drivers/gpt12.h"
#include "Sensors/Motor.h"
#include "Sensors/Ultrasonic.h"
#include "Sensors/GPIO.h"
#include "Sensors/Buzzer.h"

#define SZ 10000
int my_stack[SZ];
int top = -1;


void push(int data){
   if (top == SZ - 1) {
      return;
   }
   top++;
   delay_ms(10);
   my_stack[top] = data;
   return;
}

int pop(void) {
   int res = 0;
   if (top == -1) {
      return -1;
   }
   res = my_stack[top];
   delay_ms(10);
   top--;
   return res;
}

void init_gpt2(void);



int main(void) {
   SYSTEM_Init();
   InterruptInit();
   _init_uart3();
   Init_Bluetooth();
   init_gpt2();
   Init_DCMotors();
   Init_Ultrasonics();
   Init_Buzzer();
   Init_ToF();
   runGpt12_T6();

   char ch;

   int state=5;

   float D_rear;
   float D_left=0;
   int Lazer_distance =0; //mm
   int dir = 1;
   static int dutyA = 0;
   static int dutyB=  0;
   char change=' ';
   char change2 = ' ';
   int change_flag=0;
   int slow_flag=0;
   int speed_flag = 0;
   int Lazer_duty;

   int stop =0;
   int change_time =0;

   int top_standard = 15;



   setBeepCycle(0);
   while (1) {

      D_rear = ReadRearUltrasonic_Filt();
      D_left = ReadLeftUltrasonic_Filt();
      ch = getBluetoothByte_nonBlocked();
      Lazer_distance = getTofDistance();

      //bl_printf("%d-------------------------------------------------",ch);
      //bl_printf("%f\n", D_rear);
      //bl_printf("%d\n",Lazer_distance);


       if(ch !=-1){
        if(ch == 'w' || ch == 'W'){//전진, 가속
          state= 0;
        }
        else if(ch =='s' || ch == 'S' ){//감속
          state = 1;
        }
        else if(ch == 'd' || ch == 'D'){//우회전
          state = 2;
          change2 = 'd';
        }
        else if(ch =='a' || ch == 'A'){ //좌회전
          state = 3;
          change2 = 'a';
        }
        else if(ch == 'q' || ch =='Q'){ //후진
          state = 4;
        }
        else if(ch == 'e' || ch =='E'){ //정지
          state = 5;
        }
       }


      if ((ch >= 'A' && ch <= 'Z') || (ch >='a' && ch <='z'))
      {
         if (ch != change)
             change_flag = 1;
             change = ch;
             slow_flag=0;
      }


      switch(state){
         case 0:

           if(change2 == 'd' || change2 == 'a'){
              dutyA =0;
              dutyB= 0;
              change2=' ';
           }
            dutyA +=12;
            dutyB +=10;
            if (dutyA > 100)
            {
               dutyA = 100;
            }
            if (dutyB > 100)
            {
               dutyB = 100;
            }
            dir = 1; //전진
            speed_flag=1; //레이저모드 킬 때 주석해제
            state=6;
            break;
         case 1: //감속
            dutyA -= 10;
            dutyB -= 10;
            if (dutyA <= 0)
            {
               dutyA = 0;
            }
            if (dutyB <= 0)
            {
               dutyB = 0;
            }
            slow_flag=1;
            state=6;
            break;
         case 2: //우회전
            dutyA = 10;
            dutyB = 80;
            state=6;
            break;
         case 3: //좌회전
            dutyA = 80;
            dutyB = 10;
            state=6;
            break;
         case 4://후진
            dutyA = 30;
            dutyB = 30;
            dir = 0;
            state=6;
            break;
         case 5: //정지
            dutyA=0;
            dutyB=0;
            stopChA();
            stopChB();
            state=6;
            break;

         case 6:
            state=6;

            break;

      }


       bl_printf("distance : %.2f(cm),  top : %d, stop : %d \n",D_left, top, stop );
      //-----------------------------------------------------------------------------------------------------------------------------------------



      //p 눌렀을때 자동주차 mode임
        if(stop == 0 && change == 'p'){
           dutyA = dutyB = 20;
           dir = 1;
           if(D_left > 40.0f){
              push(1);

           }
           else{
              if(top > top_standard){
                 change_time = top;
                 bl_printf("\n\n parking space detected \n\n");
                 stop = 1;
                 stopChA();
                 stopChB();
                 delay_ms(1000);

                 movChA_PWM(80, 0);
                 movChB_PWM(80, 0);
                 delay_ms(50);
                 dutyA = dutyB = 25;
                 dir = 0;
              }
              else top = -1;
           }
        }


        else if(stop == 1 &&  change == 'p'){

           if(D_left > 40.0f){
              dutyA = dutyB = 14;
              pop();
           }

           if(top == change_time / 2 + 1){
              // 임시정지
              stopChA();
              stopChB();
              delay_ms(1000);
              bl_printf("rotation\n");
              movChA_PWM(60, 0);
              movChB_PWM(60, 1);
              delay_ms(150);
              stopChA();
              stopChB();
              delay_ms(1000);

              movChA_PWM(80, 0);
              movChB_PWM(80, 0);
              delay_ms(40);

              dir = 0;
              stop= 0;
              top = -1;
              //bl_printf("REAR Mode\n");
              dutyA = dutyB = 30;
              change = 'q';
           }
        }

//-----------------------------------------------------------------------------------------------------------------------------------------
      //후진 주차 시스템
      if ((change == 'q' || dir == 0) && D_rear < 30.0f) //30cm 이하일때 작동
           {
              int dist = (int) D_rear;

              if (D_rear >= 4.0f)
              {
                 int R_duty = (D_rear-4)*6/(30-4) +10;

                 if(dutyA !=0){
                    dutyA = R_duty;
                 }
                 if(dutyB !=0){
                    dutyB = R_duty;
                 }

              }
              else{
                 dutyA=0;
                 dutyB=0;
                 stopChA();
                 stopChB();
              }

              // 거리에 따른 부저 설정
              if (dist > 30){
                 setBeepCycle(150);
              }
              else if (dist > 20){
                 setBeepCycle(70);
              }
              else if (dist > 10){
                 setBeepCycle(30);
              }
              else{
               bl_printf("parking done\n");
                setBeepCycle(1);
              }

           }
                else{
              setBeepCycle(0);
           }


      //-----------------------------------------------------------------------------------------------------------------------------------------
      //속도 비례감속
      //bl_printf("distance : %d(mm),  speed : %d \n",Lazer_distance, Lazer_duty);

      if (((change >= 'a' && change <= 'z') && change != 's')){
       if(Lazer_distance >=0 && Lazer_distance <=400){
         if(change == 'w'){

            if(Lazer_distance >=300){
              Lazer_duty = (Lazer_distance-300)*(20)/(400-300) + 20;
              //bl_printf("distance : %d(mm),  speed : %d \n",Lazer_distance, Lazer_duty);
              if(dutyA !=0){
                dutyA = Lazer_duty;
              }
              if(dutyB !=0){
                dutyB = Lazer_duty;
              }
            }
            else if(speed_flag == 1)
            {
             movChA_PWM(90, 0);
             movChB_PWM(90, 0);
             delay_ms(20);
             dutyA =0;
             dutyB =0;
             speed_flag=0;
            }
         }
       }
     }



      //-----------------------------------------------------------------------------------------------------------------------------------------

      //모드가 바뀔 때마다 부스터
      if (change_flag == 1 && (dutyA!=0 || dutyB!=0) && slow_flag==0)//감속일때는 부스터 필요없음
      {
         movChA_PWM(90, dir);
         movChB_PWM(90, dir);
         delay_ms(20);
         change_flag = 0;
      }


      //-----------------------------------------------------------------------------------------------------------------------------------------

     movChA_PWM(dutyA, dir);
     movChB_PWM(dutyB, dir);
      //setBluetoothByte_Blocked(ch);

      delay_ms(10);
   }
   return 0;
}
