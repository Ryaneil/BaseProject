#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<string.h>
#define qdo 262
#define qre 294
#define qmi 330   //q�r�����C���A1�r���������As�r�����b����
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
		printf("�ثe�ǷŬ�:%.1f\n",roomt);
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
		printf("�ثe�ǷŬ�:%.1f\n",roomt);
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

bluetooth bt;//�Ū޳s���\�� 

void reset_bluetooth(bluetooth bt)//�Ūު�l�� 
{
	bt.flag=0;
}
int main(){
	int command;
	int timer=0;//�Y�Ū޳s�����ѹL�h���h���X���\�श�� 
	srand(time(NULL));
	float roomt = ((rand()%35)+175)/7.0;
	int situation=(rand()%100)+1;
	int temperature_feedback_flag=0;
	float nice_t;
	
			SYSTEMTIME time;
			SYSTEMTIME clock;
			GetLocalTime(&time);
	
	printf("--------------------------------------------------------------------------------------------\n");
	printf("|\t\t\t\t\t�ūױ���\t\t\t\t\t    |\n");
	printf("--------------------------------------------------------------------------------------------\n");
	
	reset_bluetooth(bt);
	
	while(1)
	{
		if(temperature_feedback_flag == 1 && bt.flag == 1)
		{	
			printf("��e�Ƿ�:%.1f�CC ",roomt);
			printf("�п�J�ۨ����:");
			scanf("%f",&u_s.body_temperature);
			printf("�п�J���d���A (sickness/healthy):");
			scanf("%s",u_s.user_situation);
			while(1)
			{
				printf("�Ш̷Ӷq���J�ثe�惡�ūת��P�� (0���ܧN 5���A�� 10���ܼ�):");
				scanf("%d",&u_s.user_feel);
				if(u_s.user_feel <= 10 && u_s.user_feel >= 0)
					break;
				else
				{
					printf("�z��J�W�L�d�򪺷P�� �ڨS��k �ЦA����J\n");
					continue;
				}
			}
			//Compare(u_s.user_situation[0]);
			printf("�z��J����Ŭ�: %.1f �z��J�����d���A��: %s �z���ū׷P���q��:%d\n",u_s.body_temperature,u_s.user_situation,u_s.user_feel);
			printf("Please confirm your body temperature and health situation\t");
			SetColor(12);
			printf("�O [Y]");
			SetColor(7);
			SetColor(10);
			printf("\t�_ [N]\n");
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
							printf("�̨���P�ū׬� : %.1f",nice_t);
		            		SlowControll_0(roomt,nice_t);
							}
		            	else if(roomt < nice_t && u_s.user_feel != 5)
		            		{
								printf("�̨���P�ū׬� : %.1f",nice_t);
		            			SlowControll_1(roomt,nice_t);
							}
						else
		            		{
		            			SetColor(13);
								printf("�A�ΪA�ڴN���ʤF �n��<3\n");
		            			SetColor(7);
							}
		            	SetColor(10);
						printf("�ūױ����! �^��ű��D����\n");
						SetColor(7);
		            	
						break;
		            case 110: 
						temperature_feedback_flag=0;
		            	u_s.body_temperature=0;
		            	u_s.user_feel=5;
		            	bt.flag=0;
		            	printf("�w���m�ϥΪ̷s�W�����e\n");
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
		printf("\t��J[1]: �}���Ūިö}�l�ﱵ\n \t��J[2]: �T�{�ثe�Ū޳s�����p\n \t��J[3]: �ūױ���^�X\n \t��J[4]: �����Ū�\n \t��J[5]: �]�w�x��(�`�N!�]�w��Y�����^���)\n");
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
			SlowPrint("�T�{�Ūޱ��p...\n",100);
			
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
				printf("�Ūީ|���s�� �ЦA������\n");
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
			SlowPrint("�ثe�Ū޳s�����p...",100);
			if(bt.flag == 0)
			{ 
				SetColor(12);
				printf("�ثe�|���s��\n");
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
			printf("�O [Y]");
			SetColor(7);
			SetColor(10);
			printf("\t�_ [N]\n");
			SetColor(7);
			int ch;
		    while( (ch=getch())!=0x1B)
		    {
		    
		        switch(ch)
		        {
		            case 121: 	
						printf("--------------------------------------------------------------------------------------------\n");
						printf("|\t\t\t\t\t�ūױ���^�X\t\t\t\t\t    |\n");
						printf("--------------------------------------------------------------------------------------------\n");
						temperature_feedback_flag=1;
						break;
		            case 110: 
						printf("�h�X�ūױ���^�X\n"); 
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
			printf("�Ūީ|���s�� �Х��s���Ū�\n");
			SetColor(7);
		}
		else if(command == 4)
		{
			bt.flag=0;
		}
		else if(command == 5 && bt.flag == 1)
		{
			printf("�ثe�ɶ���(��/��/��)�G%2d:%2d:%2d\n",time.wHour,time.wMinute,time.wSecond);
			printf("�нT�{�x���ɶ��G\n");
			
			printf("�ɡG");
			scanf("%2d",&clock.wHour);
			
			printf("���G");
			scanf("%2d",&clock.wMinute);
		
			printf("�x���]�w���� ���ݾx���T�_�~�i�^����\n");	
			
			while(1)
			{
				Sleep(1000);
				GetLocalTime(&time);
				if((time.wHour==clock.wHour)&&(time.wMinute==clock.wMinute))
				{
					printf("�_�ɰ�~ �O�o���Ž��o!!!\n");
								
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
			printf("�Ūީ|���s�� �Х��s���Ū�\n");
			SetColor(7);	
		}
		else
		{
			printf("�L�ī��O\n");
				}		
	}
}
