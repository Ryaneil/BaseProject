#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<string.h>
#define qdo 262
#define qre 294
#define qmi 330   //q字首為低音，1字尾為高音，s字首為半音階
#define qfa 349
#define qso 392
#define qla 440
#define qsi 494
#define do 523
#define re 578
#define mi 659
#define fa 698
#define so 784
#define la 880
#define si 988
#define do1 1046
#define re1 1175
#define mi1 1318
#define fa1 1480
#define so1 1568
#define la1 1760
#define si1 1976
#define sqdo 277
#define sqre 311
#define sqfa 370
#define sqso 415
#define sqla 466
#define sdo 554
#define sre 622
#define sfa 740
#define sso 831
#define sla 932
#define sdo1 1046
#define sre1 1245
#define sfa1 1480
#define sso1 1661
#define sla1 1865
 
void SetColor(int color)
{
  HANDLE hConsole;
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole,color);
}

void SlowPrint(char* string,int sleeptime)
{
	int i=0;
	while(string[i] != '\0')
	{
		printf("%c",string[i]);
		Sleep(sleeptime);
		i++;
	}
}

void SlowControll_0(float roomt,float nice_t)
{
	while(1)
	{
		printf("目前室溫為:%.1f\n",roomt);
		if(roomt <= nice_t)
			break;	
		roomt=roomt-0.1;
		Sleep(1000);
	}	
}
void SlowControll_1(float roomt,float nice_t)
{
	while(1)
	{
		printf("目前室溫為:%.1f\n",roomt);
		if(roomt >= nice_t)
			break;	
		roomt=roomt+0.1;
		Sleep(1000);
	}	
}

typedef struct user_status{
	float body_temperature;
	int tempetature_feedback;
	char user_situation[30];
	int user_feel;
}user_status;

user_status u_s;

typedef struct bluetooth{
	int flag;
	char ac_name[30];
}bluetooth;

bluetooth bt;//藍芽連接功能 

void reset_bluetooth(bluetooth bt)//藍芽初始化 
{
	bt.flag=0;
}
int main(){
	int command;
	int timer=0;//若藍芽連結失敗過多次則跳出此功能介面 
	srand(time(NULL));
	float roomt = ((rand()%35)+175)/7.0;
	int situation=(rand()%100)+1;
	int temperature_feedback_flag=0;
	float nice_t;
	
			SYSTEMTIME time;
			SYSTEMTIME clock;
			GetLocalTime(&time);
	
	printf("--------------------------------------------------------------------------------------------\n");
	printf("|\t\t\t\t\t溫度控制\t\t\t\t\t    |\n");
	printf("--------------------------------------------------------------------------------------------\n");
	
	reset_bluetooth(bt);
	
	while(1)
	{
		if(temperature_feedback_flag == 1 && bt.flag == 1)
		{	
			printf("當前室溫:%.1f。C ",roomt);
			printf("請輸入自身體溫:");
			scanf("%f",&u_s.body_temperature);
			printf("請輸入健康狀態 (sickness/healthy):");
			scanf("%s",u_s.user_situation);
			while(1)
			{
				printf("請依照量表輸入目前對此溫度的感受 (0為很冷 5為適中 10為很熱):");
				scanf("%d",&u_s.user_feel);
				if(u_s.user_feel <= 10 && u_s.user_feel >= 0)
					break;
				else
				{
					printf("您輸入超過範圍的感受 我沒辦法 請再次輸入\n");
					continue;
				}
			}
			//Compare(u_s.user_situation[0]);
			printf("您輸入的體溫為: %.1f 您輸入的健康狀態為: %s 您的溫度感受量表為:%d\n",u_s.body_temperature,u_s.user_situation,u_s.user_feel);
			printf("Please confirm your body temperature and health situation\t");
			SetColor(12);
			printf("是 [Y]");
			SetColor(7);
			SetColor(10);
			printf("\t否 [N]\n");
			SetColor(7);
			int ch;
		    while( (ch=getch())!=0x1B)
		    {
		    
		        switch(ch)
		        {
		            case 121:
		            	nice_t = 1.07*roomt - 2.7 - 0.4*(u_s.user_feel-5);
		            	
		            	
		            	if(roomt > nice_t && u_s.user_feel != 5)
		            	{
							printf("最佳體感溫度為 : %.1f",nice_t);
		            		SlowControll_0(roomt,nice_t);
							}
		            	else if(roomt < nice_t && u_s.user_feel != 5)
		            		{
								printf("最佳體感溫度為 : %.1f",nice_t);
		            			SlowControll_1(roomt,nice_t);
							}
						else
		            		{
		            			SetColor(13);
								printf("你舒服我就不動了 好嗎<3\n");
		            			SetColor(7);
							}
		            	SetColor(10);
						printf("溫度控制完成! 回到溫控主頁面\n");
						SetColor(7);
		            	
						break;
		            case 110: 
						temperature_feedback_flag=0;
		            	u_s.body_temperature=0;
		            	u_s.user_feel=5;
		            	bt.flag=0;
		            	printf("已重置使用者新增之內容\n");
						break;
		            default:
		            	continue;
		        }
		         	break;		        
		    }
			system("pause");
			temperature_feedback_flag = 0;
			continue;
		}
		printf("\t輸入[1]: 開啟藍芽並開始對接\n \t輸入[2]: 確認目前藍芽連接情況\n \t輸入[3]: 溫度控制回饋\n \t輸入[4]: 關閉藍芽\n \t輸入[5]: 設定鬧鐘(注意!設定後即不能返回選單)\n");
		scanf("%d",&command);
		
	
		if(timer >= 3)
		{
			printf("Bluetooth connection failed more than three times Jump out of this interface\n");
			break;
		}
		
		if(command == 0)
		{
			printf("|\t\t\t\t\tExit temperature controler\t\t\t|\n");
			break;
		}
	
		else if(command == 1 && bt.flag == 0)
		{
			SlowPrint("確認藍芽情況...\n",100);
			
			situation=(rand()%100)+1;
		//	printf("%d\n",situation);
			if(situation > 0)
				bt.flag=1;
			else
			{
				bt.flag=0;
				timer++;
			}
			
			Sleep(3000);
				
			if(bt.flag == 0)
			{
				printf("藍芽尚未連接 請再次嘗試\n");
			}
			else if(bt.flag == 1)
			{
				printf("Bluetooth conection success!! Device name:admin\n");
			}
		}
		else if(command == 1 && bt.flag == 1)
		{
			printf("Bluetooth successfully connected\n");
		}
		else if(command == 2)
		{
			SlowPrint("目前藍芽連接情況...",100);
			if(bt.flag == 0)
			{ 
				SetColor(12);
				printf("目前尚未連接\n");
				SetColor(7);
				printf("\n");
			}
			else if(bt.flag == 1)
			{
				SetColor(10);
				printf("Bluetooth successfully connected Device name:admin\n");
				SetColor(7);
				printf("\n");
			 } 
		}
		else if(command == 3 && bt.flag == 1)
		{
			printf("Please confirm whether to enter this function\t");
			SetColor(12);
			printf("是 [Y]");
			SetColor(7);
			SetColor(10);
			printf("\t否 [N]\n");
			SetColor(7);
			int ch;
		    while( (ch=getch())!=0x1B)
		    {
		    
		        switch(ch)
		        {
		            case 121: 	
						printf("--------------------------------------------------------------------------------------------\n");
						printf("|\t\t\t\t\t溫度控制回饋\t\t\t\t\t    |\n");
						printf("--------------------------------------------------------------------------------------------\n");
						temperature_feedback_flag=1;
						break;
		            case 110: 
						printf("退出溫度控制回饋\n"); 
						break;
		            default:
		            	continue;
		        }
		         	break;		        
		    }
		}
		else if(command == 3 && bt.flag == 0)
		{
        	SetColor(13);
			printf("藍芽尚未連接 請先連接藍芽\n");
			SetColor(7);
		}
		else if(command == 4)
		{
			bt.flag=0;
		}
		else if(command == 5 && bt.flag == 1)
		{
			printf("目前時間為(時/分/秒)：%2d:%2d:%2d\n",time.wHour,time.wMinute,time.wSecond);
			printf("請確認鬧鐘時間：\n");
			
			printf("時：");
			scanf("%2d",&clock.wHour);
			
			printf("分：");
			scanf("%2d",&clock.wMinute);
		
			printf("鬧鐘設定完成 等待鬧鐘響起才可回到選單\n");	
			
			while(1)
			{
				Sleep(1000);
				GetLocalTime(&time);
				if((time.wHour==clock.wHour)&&(time.wMinute==clock.wMinute))
				{
					printf("起床啦~ 記得關空調囉!!!\n");
								
			int pai=400,ban=200;
			int ting=128;
			 
			Sleep(1000);
			 
			Beep(la,ban);
			Beep(si,ban);
			Sleep(ting);
			 
			Beep(do1,pai+ban);
			Beep(si,ban);
			Sleep(ting);
			Beep(do1,pai);
			Sleep(ting);
			Beep(mi1,pai);
			Sleep(ting);
			 
			Beep(si,3*pai);
			Sleep(ting);
			Beep(mi,ban);
			Beep(mi,ban);
			 
			Beep(la,ban+pai);
			Beep(so,ban);
			Sleep(ting);
			Beep(la,pai);
			Sleep(ting);
			Beep(do1,pai);
			Sleep(ting);
			 
			Beep(so,2*pai);
			Sleep(ting);
			Sleep(pai);
			Beep(mi,ban);
			Sleep(ting/2);
			Beep(mi,ban);
			Sleep(ting/2);
			 
			Beep(fa,pai+ban);
			Beep(mi,ban);
			Sleep(ting);
			Beep(fa,ban);
			Beep(do1,ban+pai);
			Sleep(ting);
			 
			Beep(mi,2*pai);
			Sleep(ting);
			Sleep(ban);
			Beep(do1,ban);
			Sleep(ting/2);
			Beep(do1,ban);
			Sleep(ting/2);
			Beep(do1,ban);
			Sleep(ting/2);
			 
			Beep(si,ban+pai);
			Beep(sfa,ban);
			Sleep(ting);
			Beep(sfa,pai);
			Beep(si,pai);
			Sleep(ting);
			 
			Beep(si,2*pai);
			Sleep(ting);
			Sleep(pai);
			Beep(la,ban);
			Beep(si,ban);
			Sleep(ting);
			 
			Beep(do1,pai+ban);
			Beep(si,ban);
			Sleep(ting);
			Beep(do1,pai);
			Sleep(ting);
			Beep(mi1,pai);
			Sleep(ting);
			 
			Beep(si,2*pai);
			Sleep(ting);
			Sleep(pai);
			Beep(mi,ban);
			Sleep(20);
			Beep(mi,ban);
			Sleep(ting);
			 
			Beep(la,pai+ban);
			Beep(so,ban);
			Sleep(ting);
			Beep(la,pai);
			Sleep(ting);
			Beep(do1,pai);
			Sleep(ting);
			 
			Beep(so,3*pai);
			Sleep(ting+ban);
			Beep(mi,ban);
			Sleep(ting/2);
			 
			Beep(fa,pai);
			Sleep(ting);
			Beep(do1,ban);
			Beep(si,ban);
			Sleep(20);
			Beep(si,pai);
			Sleep(ting);
			Beep(do1,pai);
			Sleep(ting);
			 
			Beep(re1,ban);
			Sleep(20);
			Beep(re1,ban);
			Sleep(20);
			Beep(mi1,ban);
			Sleep(ting/2);
			Beep(do1,pai);
			Sleep(ting+pai);
			 
			Beep(do1,pai);
			Beep(si,ban);
			Sleep(ting);
			Beep(la,ban);
			Sleep(20);
			Beep(la,ban);
			Sleep(ting);
			Beep(si,pai);
			Sleep(ting);
			Beep(sso,pai);
			Sleep(ting);
			 
			Beep(sso,2*pai);
			Sleep(ting+pai);
			break;			
				}	
			}
		}
		else if(command == 5 && bt.flag == 0)
		{
        	SetColor(13);
			printf("藍芽尚未連接 請先連接藍芽\n");
			SetColor(7);	
		}
		else
		{
			printf("無效指令\n");
				}		
	}
}
