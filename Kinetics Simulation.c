#include <cvirte.h>		
#include <userint.h>
#include "Kinetics Simulation.h"
#include <formatio.h>
#include <advanlys.h>
#include "progressbar.h"
#include "toolbox.h"
#include <cvirte.h>     
#include <userint.h>
#define SIZE 10000

//----------------------------------Declare -----------------------------------------------------------
double A,B,K1,K_1,K2,dt,C,half_T,Ai,Bi;
double percnt_A,percnt_B,percnt_C,A_arr[SIZE],B_arr[SIZE],time_arr[SIZE],C_arr[SIZE],copy_A_arr[SIZE];
double dA, dB, dC;
int count = 0;
FILE*fp;
char data[]="Kinetics Simulation Data.txt";
int countnumber=0;
static int panel1, panelHandle, panel2;
//----------------------------------Declare func-------------------------------------------------------
int CVICALLBACK graphfunc (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2);
//----------------------------------Clean Memo---------------------------------------------------------
void cleanMat(double mat[count], int count){
	for(int i=0;i<=count;i++){
				mat[i]=0;	}}
//----------------------------------MAIN FUNC----------------------------------------------------------
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panel1 = LoadPanel (0, "Kinetics Simulation.uir", PANEL_1)) < 0)
		return -1;
	DisplayPanel (panel1);
	RunUserInterface ();
	DiscardPanel (panel1);
	return 0;
}
//----------------------------------quit program-------------------------------------------------------
int CVICALLBACK quit (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			A=B=K1=K_1=K2=dt=C=half_T=Ai=Bi=percnt_A=percnt_B=percnt_C=0.0;
			QuitUserInterface (0);
			break;
	}
	return 0;
}
int CVICALLBACK finish2 (int panel, int event, void *callbackData,
						 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			
			QuitUserInterface (0);
			break;
	}
	return 0;
}
//--------------------------------------panel1-----------------------------------------------------------
int CVICALLBACK finish (int panel, int event, void *callbackData,
						int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface (0);
			break;
	}
	return 0;
}
int CVICALLBACK QuitCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
	}
	return 0;
}
int CVICALLBACK reactionfunc (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	int ySwitch = 0;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel1,PANEL_1_REAC_TYP, &ySwitch);
			switch (ySwitch)
            {
				case 1:
					SetCtrlVal (panel1,PANEL_1_PICTUR_REC,1);	
										break;
				case 2:	
					SetCtrlVal (panel1,PANEL_1_PICTUR_REC,2);
					                    break;
                case 3:
					SetCtrlVal (panel1,PANEL_1_PICTUR_REC,3);
					                    break;
                case 4:
					SetCtrlVal (panel1,PANEL_1_PICTUR_REC,4);
					                    break;
				case 5:
					SetCtrlVal (panel1,PANEL_1_PICTUR_REC,5);
										break;
				case 6:
					SetCtrlVal (panel1,PANEL_1_PICTUR_REC,6);
                    break;
            }
			break;
	}
	return 0;
}
int CVICALLBACK continuefunc (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	int ySwitch = 0;
	switch (event)
	{
		case EVENT_COMMIT:
			panel2=LoadPanel (0, "Kinetics Simulation.uir", PANEL_2);
			DisplayPanel(panel2);
			GetCtrlVal (panel1,PANEL_1_REAC_TYP, &ySwitch);
			switch (ySwitch)
            {
				case 1:	
					SetCtrlVal	(panel2, PANEL_2_RING,1);
					break;
				case 2:	
					SetCtrlVal	(panel2, PANEL_2_RING,2);
					SetCtrlAttribute (panel2, PANEL_2_RATE_k_1, ATTR_VISIBLE,1);
                    break;
                case 3:
					SetCtrlVal	(panel2, PANEL_2_RING,3);
					SetCtrlAttribute (panel2, PANEL_2_RATE_k2, ATTR_VISIBLE,1);
                    break;
                case 4:
					SetCtrlVal	(panel2, PANEL_2_RING,4);
					SetCtrlAttribute (panel2, PANEL_2_RATE_k2, ATTR_VISIBLE,1);
                    break;
				case 5:
					SetCtrlVal	(panel2, PANEL_2_RING,5);
					break;
				case 6:
					SetCtrlVal	(panel2, PANEL_2_RING,6);
					SetCtrlAttribute (panel2, PANEL_2_conc_B, ATTR_VISIBLE,1);
                    break;
            }
			break;
	}
	return 0;
}
//--------------------------------------panel2-----------------------------------------------------------

int CVICALLBACK startfunc (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	int ySwitch = 0;
	switch (event)
	{
		case EVENT_COMMIT:
			int a=1, b=1;
			GetCtrlVal (panel1, PANEL_1_REAC_TYP,&ySwitch);	
			GetCtrlVal (panel2, PANEL_2_conc_A, &A);
			GetCtrlVal (panel2, PANEL_2_RATE_k1, &K1);
			Ai=A;
			GetCtrlVal (panel2, PANEL_2_TIME_INTERVAL, &dt);
			percnt_A=(A/Ai)*100.0;
			if (Ai<=0.0){
				b=0;
				if (Ai==0.0){
				MessagePopup ("", "Please fill Ai initail concetration");}
				else {MessagePopup ("", "Please fill valid Ai initail concetration");}
				}
			if(dt<=0.0){
				b=0;
				if (dt==0.0){
				MessagePopup ("", "Please fill Time Interval");}
				else {MessagePopup ("", "Please fill valid Time Interval");}
				}
			if(K1<=0.0){
				b=0;
				if (K1==0.0){
				MessagePopup ("", "Please fill K1 Rate");}
				else {MessagePopup ("", "Please fill valid K1 Rate");}
				}	
			if (a){
				switch (ySwitch)
					{
						case 1:
							if (K1*dt>=1){
								b=0;
								MessagePopup ("", "Invalid Values");}
								break;
						case 2:
							GetCtrlVal (panel2, PANEL_2_RATE_k_1, &K_1);
							if (K_1<=0.0){
								if (K_1==0.0){
									MessagePopup ("", "Please fill K_1 Rate");}
									else {MessagePopup ("", "Please fill valid K_1 Rate");}
								b=0;
								}
								if ((K1-K_1)*dt>=1){
								b=0;
								MessagePopup ("", "Invalid Values");}
								break;
						case 3: 
							GetCtrlVal (panel2, PANEL_2_RATE_k2, &K2);
							if (K2<=0.0){
								if (K2==0.0){
									MessagePopup ("", "Please fill K2 Rate");}
									else {MessagePopup ("", "Please fill valid K2 Rate");}
								b=0;
								}
								if ((K1-K2)*dt>=1){
								b=0;
								MessagePopup ("", "Invalid Values");}
								break;
						case 4:
							GetCtrlVal (panel2, PANEL_2_RATE_k2, &K2);
							if (K2<=0.0){
								if (K2==0.0){
									MessagePopup ("", "Please fill K2 Rate");}
									else {MessagePopup ("", "Please fill valid K2 Rate");}
								b=0;
								}
								if (K1*dt>=1){
								b=0;
								MessagePopup ("", "Invalid Values");}
								break;		
						case 5:
							if (K1*A*dt>=1){
								b=0;
								MessagePopup ("", "Invalid Values");}
								break;
						case 6:	
							GetCtrlVal (panel2, PANEL_2_conc_B, &B);
							if (B<=0.0){
								b=0;
								if (B==0.0){MessagePopup ("", "Please fill Bi initail concetration");}
								else {MessagePopup ("", "Please fill valid Bi initail concetration");}}
					if (K1*B*dt>=1){
						b=0;
						MessagePopup ("", "Invalid Values");}
					break;
					}}
			if (b)  {
				switch (ySwitch)
				{
				case 2:
					GetCtrlVal (panel2, PANEL_2_RATE_k_1, &K_1);
					break;
				case 3:	case 4:
					GetCtrlVal (panel2, PANEL_2_RATE_k2, &K2);
					break;
				case 6:	
					GetCtrlVal (panel2, PANEL_2_conc_B, &B);
						Bi=B;
					break;}
				panelHandle=LoadPanel(0, "Kinetics Simulation.uir", PANEL);
				DisplayPanel(panelHandle);
				reactionfunc3 ( panelHandle,  control,  event,
							   callbackData,  eventData1,  eventData2);
							   countnumber++;
							   SetCtrlVal (panelHandle, PANEL_NUMERICTANK_A,percnt_A);
							   SetCtrlAttribute (panel2, PANEL_2_TIMER, ATTR_ENABLED, 1);}
            }
	return 0;
}
int CVICALLBACK timerfunc (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	int ySwitch = 0;
    switch (event)
    {
        case EVENT_TIMER_TICK:
            GetCtrlVal (panel1, PANEL_1_REAC_TYP,&ySwitch);
            SetCtrlVal (panelHandle, PANEL_conc_A, A);
            percnt_A=(A/Ai)*100.0;
            SetCtrlVal (panelHandle, PANEL_NUMERICTANK_A,percnt_A);
            A_arr[count]=A;
            B_arr[count]=B;
			SetCtrlVal (panelHandle, PANEL_TIME_INTERVAL,dt);
			if (count==0)
					time_arr[count] =count;
			else
				time_arr[count]=time_arr[count-1]+dt;
			count++;
			SetCtrlAttribute (panelHandle, PANEL_NUMERICTANK_A, ATTR_VISIBLE,1);
			SetCtrlVal (panelHandle, PANEL_RATE_k1,K1);
			graphfunc (panelHandle, control, event,
						   callbackData, eventData1, eventData2);
            switch (ySwitch)
            {
                case 1:
					SetCtrlVal (panelHandle, PANEL_conc_B, B);
					SetCtrlAttribute ( panelHandle, PANEL_conc_B, ATTR_VISIBLE,1);
					SetCtrlAttribute ( panelHandle, PANEL_HALF_LIFE, ATTR_VISIBLE,1);
					SetCtrlAttribute (panelHandle, PANEL_NUMERICTANK_B, ATTR_VISIBLE,1);
                    dA=-K1*A*dt;
                    dB=-dA;
                    A=A+dA;
                    B=B+dB;
					half_T=	log(2)/K1;
					SetCtrlVal (panelHandle, PANEL_HALF_LIFE,half_T);
					percnt_B=(B/Ai)*100.0;
					SetCtrlVal (panelHandle, PANEL_NUMERICTANK_B,percnt_B);
                    break;
                case 2:
					SetCtrlVal (panelHandle, PANEL_conc_B, B);
					SetCtrlVal (panelHandle, PANEL_RATE_k_1,K_1);
					SetCtrlVal (panelHandle, PANEL_RATE_k2,K2);
					SetCtrlAttribute ( panelHandle, PANEL_conc_B, ATTR_VISIBLE,1);
					SetCtrlAttribute (panelHandle, PANEL_NUMERICTANK_B, ATTR_VISIBLE,1);
                    dA=(-K1*A+K_1*B)*dt;
                    dB=-dA;
                    A=A+dA;
                    B=B+dB;
					percnt_B=(B/Ai)*100.0;
					SetCtrlVal (panelHandle, PANEL_NUMERICTANK_B,percnt_B);
                    break;
                case 3:
					SetCtrlVal (panelHandle, PANEL_conc_B, B);
					SetCtrlVal (panelHandle, PANEL_RATE_k2,K2);
					SetCtrlAttribute ( panelHandle, PANEL_conc_B, ATTR_VISIBLE,1);
					SetCtrlAttribute ( panelHandle, PANEL_conc_C, ATTR_VISIBLE,1);
					SetCtrlAttribute (panelHandle, PANEL_NUMERICTANK_B, ATTR_VISIBLE,1);
					SetCtrlAttribute (panelHandle, PANEL_NUMERICTANK_C, ATTR_VISIBLE,1);
                    dA=(-K1-K2)*A*dt;
                    dC=K2*A*dt;
                    dB=K1*A*dt;
					A=A+dA;
                    B=B+dB;
					C=C+dC;
					C_arr[count]=C;
                    SetCtrlVal (panelHandle, PANEL_conc_C, C);
					percnt_B=(B/Ai)*100.0;
					SetCtrlVal (panelHandle, PANEL_NUMERICTANK_B,percnt_B);
					percnt_C=(C/Ai)*100.0;
					SetCtrlVal (panelHandle, PANEL_NUMERICTANK_C,percnt_C);
                    break;
                case 4:
					SetCtrlVal (panelHandle, PANEL_conc_B, B);
					SetCtrlVal (panelHandle, PANEL_RATE_k2,K2);
					SetCtrlAttribute ( panelHandle, PANEL_conc_B, ATTR_VISIBLE,1);
					SetCtrlAttribute ( panelHandle, PANEL_conc_C, ATTR_VISIBLE,1);
					SetCtrlAttribute (panelHandle, PANEL_NUMERICTANK_B, ATTR_VISIBLE,1);
					SetCtrlAttribute (panelHandle, PANEL_NUMERICTANK_C, ATTR_VISIBLE,1);
					dA=-K1*A*dt;
					dB=(K1*A-K2*B)*dt;
					dC=K2*B*dt;
					A=A+dA;
                    B=B+dB;
					C=C+dC;
					SetCtrlVal (panelHandle, PANEL_conc_C, C);
					percnt_B=(B/Ai)*100.0;
					SetCtrlVal (panelHandle, PANEL_NUMERICTANK_B,percnt_B);
					percnt_C=(C/Ai)*100.0;
					SetCtrlVal (panelHandle, PANEL_NUMERICTANK_C,percnt_C);
					C_arr[count]=C;
                    break;
                case 5:
					SetCtrlVal (panelHandle, PANEL_conc_B, B);
					SetCtrlAttribute ( panelHandle, PANEL_conc_B, ATTR_VISIBLE,1);
					SetCtrlAttribute (panelHandle, PANEL_NUMERICTANK_B, ATTR_VISIBLE,1);
					dA=-K1*A*A*dt;
					dB=-0.5*dA;
					A=A+dA;
                    B=B+dB;
					half_T=1/(K1*Ai);
					SetCtrlVal (panelHandle,PANEL_HALF_LIFE,half_T);
					SetCtrlAttribute ( panelHandle, PANEL_HALF_LIFE, ATTR_VISIBLE,1);
					percnt_B=(B/Ai)*100.0;
					SetCtrlVal (panelHandle, PANEL_NUMERICTANK_B,percnt_B);
                    break;
				case 6:
					SetCtrlVal (panelHandle, PANEL_conc_B, B);
					SetCtrlAttribute ( panelHandle, PANEL_conc_B, ATTR_VISIBLE,1);
					SetCtrlAttribute ( panelHandle, PANEL_conc_C, ATTR_VISIBLE,1);
					SetCtrlAttribute (panelHandle, PANEL_NUMERICTANK_B, ATTR_VISIBLE,1);
					SetCtrlAttribute (panelHandle, PANEL_NUMERICTANK_C, ATTR_VISIBLE,1);
					dA=-K1*A*B*dt;
					dB=dA;
					dC=-dB;
					A=A+dA;
                    B=B+dB;
					C=C+dC;
					C_arr[count]=C;
					SetCtrlVal (panelHandle, PANEL_conc_C, C);
					percnt_B=(B/Bi)*100.0;
					SetCtrlVal (panelHandle, PANEL_NUMERICTANK_B,percnt_B);
					percnt_C=(C/(Ai+Bi))*100.0;
					SetCtrlVal (panelHandle, PANEL_NUMERICTANK_C,percnt_C);
                    break;
            }
            break;
    }
    return 0;
}
int CVICALLBACK back2_func (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			DiscardPanel (panel2);
			DisplayPanel (panel1);
			break;
	}
	return 0;
}
//--------------------------------------panel3-----------------------------------------------------------
int CVICALLBACK reactionfunc3 (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	int ySwitch = 0;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel1,PANEL_1_REAC_TYP, &ySwitch);
			switch (ySwitch)
            {
				case 1:
					SetCtrlVal (panelHandle,PANEL_PICTUR_REC,1);
					SetCtrlAttribute (panelHandle, PANEL_RATE_k2, ATTR_VISIBLE,0);
					SetCtrlAttribute (panelHandle, PANEL_conc_C, ATTR_VISIBLE,0);
					SetCtrlAttribute (panelHandle, PANEL_conc_B, ATTR_VISIBLE,0);
					SetCtrlAttribute (panelHandle, PANEL_HALF_LIFE, ATTR_VISIBLE,0);
					SetCtrlAttribute (panelHandle, PANEL_RATE_k_1, ATTR_VISIBLE,0);
					break;
				case 2:	
					SetCtrlVal (panelHandle,PANEL_PICTUR_REC,2);
					SetCtrlAttribute (panelHandle, PANEL_conc_B, ATTR_VISIBLE,0);
					SetCtrlAttribute (panelHandle, PANEL_RATE_k_1, ATTR_VISIBLE,1);
					SetCtrlAttribute (panelHandle, PANEL_RATE_k2, ATTR_VISIBLE,0);
					SetCtrlAttribute (panelHandle, PANEL_conc_C, ATTR_VISIBLE,0);
					SetCtrlAttribute (panelHandle, PANEL_HALF_LIFE, ATTR_VISIBLE,0);
                    break;
                case 3:
					SetCtrlVal (panelHandle,PANEL_PICTUR_REC,3);
					SetCtrlAttribute (panelHandle, PANEL_conc_B, ATTR_VISIBLE,0);
					SetCtrlAttribute (panelHandle, PANEL_RATE_k2, ATTR_VISIBLE,1);
					SetCtrlAttribute (panelHandle, PANEL_conc_C, ATTR_VISIBLE,0);
					SetCtrlAttribute (panelHandle, PANEL_RATE_k_1, ATTR_VISIBLE,0);
					SetCtrlAttribute (panelHandle, PANEL_HALF_LIFE, ATTR_VISIBLE,0);
                    break;
                case 4:
					SetCtrlVal (panelHandle,PANEL_PICTUR_REC,4);
					SetCtrlAttribute (panelHandle, PANEL_conc_B, ATTR_VISIBLE,0);
					SetCtrlAttribute (panelHandle, PANEL_RATE_k2, ATTR_VISIBLE,1);
					SetCtrlAttribute (panelHandle, PANEL_conc_C, ATTR_VISIBLE,0);
					SetCtrlAttribute (panelHandle, PANEL_RATE_k_1, ATTR_VISIBLE,0);
					SetCtrlAttribute (panelHandle, PANEL_HALF_LIFE, ATTR_VISIBLE,0);
                    break;
				case 5:
					SetCtrlVal (panelHandle,PANEL_PICTUR_REC,5);
					SetCtrlAttribute (panelHandle, PANEL_conc_B, ATTR_VISIBLE,0);
					SetCtrlAttribute (panelHandle, PANEL_RATE_k2, ATTR_VISIBLE,0);
					SetCtrlAttribute (panelHandle, PANEL_conc_C, ATTR_VISIBLE,0);
					SetCtrlAttribute (panelHandle, PANEL_HALF_LIFE, ATTR_VISIBLE,0);
					SetCtrlAttribute (panelHandle, PANEL_RATE_k_1, ATTR_VISIBLE,0);
					break;
				case 6:
					SetCtrlVal (panelHandle,PANEL_PICTUR_REC,6);
					SetCtrlAttribute (panelHandle, PANEL_conc_B, ATTR_VISIBLE,1);
					SetCtrlAttribute (panelHandle, PANEL_conc_C, ATTR_VISIBLE,1);
					SetCtrlAttribute (panelHandle, PANEL_RATE_k2, ATTR_VISIBLE,0);
					SetCtrlAttribute (panelHandle, PANEL_RATE_k_1, ATTR_VISIBLE,0);
					SetCtrlAttribute (panelHandle, PANEL_HALF_LIFE, ATTR_VISIBLE,0);
                    break;
            }
			break;
	}
	return 0;
}
int CVICALLBACK stopfunc (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	int ySwitch = 0;
    switch (event)
    {
        case EVENT_COMMIT:
            SetCtrlAttribute (panel2, PANEL_2_TIMER, ATTR_ENABLED, 0);
			if (A_arr[0]!=0.0){
			SetCtrlAttribute (panelHandle, PANEL_FILE, ATTR_VISIBLE,1);}
			GetCtrlVal (panel1,PANEL_1_REAC_TYP, &ySwitch);
			SetCtrlAttribute (panelHandle, PANEL_CONTINUE, ATTR_VISIBLE,1);
			SetCtrlAttribute (panelHandle, PANEL_BACK, ATTR_VISIBLE,1);
			switch (ySwitch){
				case 2:
					for(int j=count-1;j>=0;j--){
						copy_A_arr[j]=log(A_arr[j]-A);}
					PlotXY (panelHandle, PANEL_GRAPH_2, time_arr,copy_A_arr, count-1, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE,
        VAL_SOLID, 1, VAL_RED);
					break;
			}
            break;
    }
    return 0;
}
int CVICALLBACK resumefunc (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (panelHandle, PANEL_FILE, ATTR_VISIBLE,0);
			SetCtrlAttribute (panel2, PANEL_2_TIMER, ATTR_ENABLED, 1);
			SetCtrlAttribute (panelHandle, PANEL_CONTINUE, ATTR_VISIBLE,0);
			SetCtrlAttribute (panelHandle, PANEL_BACK, ATTR_VISIBLE,0);
			break;
	}
	return 0;
}

int CVICALLBACK writefile (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	int ySwitch = 0;
	switch (event)
	{
		case EVENT_COMMIT:
			if (countnumber==1){
				fp=fopen(data,"w");
				fprintf (fp,"Kinetics Simulation Data");
				fclose(fp);}
			fp=fopen(data,"a");	
			fprintf (fp,"\n\nKinetics Simulation Data Run Number %d\n\n",countnumber);
			GetCtrlVal (panel1,PANEL_1_REAC_TYP, &ySwitch);
			switch (ySwitch){
				case 1: case 2: case 5:
					fprintf (fp,"%-15s %-15s%-15s\n","[t]","[A]","[B]");
					for(int	j=0;j<count;j++){
						fprintf(fp,"%-15lf	%-15lf%-15lf\n",time_arr[j],A_arr[j],B_arr[j]);}
						break;
				case 3: case 4: case 6:
					fprintf (fp,"%-15s %-15s%-15s%-15s\n","[t]","[A]","[B]","[C]");
					for(int	j=0;j<count;j++){
						fprintf(fp,"%-15lf	%-15lf%-15lf%-15lf\n",time_arr[j],A_arr[j],B_arr[j],C_arr[j]);}
						break;
			}		
	fclose(fp);}
	return 0;
}

int CVICALLBACK graphfunc (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	int ySwitch = 0;
    switch (event)
    {
        case EVENT_TIMER_TICK:
            GetCtrlVal (panel1, PANEL_1_REAC_TYP,&ySwitch);
				switch (ySwitch)
				{
                case 1:
					SetCtrlAttribute (panelHandle, PANEL_BINARYSWITCH, ATTR_VISIBLE,1);
					PlotXY (panelHandle, PANEL_GRAPH_2, time_arr,A_arr, count, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE,
        VAL_SOLID, 1, VAL_RED );
					SetCtrlAttribute (panelHandle, PANEL_GRAPH_2, ATTR_YMAP_MODE, VAL_LOG);
					PlotXY (panelHandle, PANEL_GRAPH, time_arr, A_arr, count, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE,
        VAL_SOLID, 1, VAL_RED);
					PlotXY (panelHandle, PANEL_GRAPH, time_arr, B_arr, count, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE,
        VAL_SOLID, 1, VAL_BLUE);
					break;
                case 2:
					SetCtrlAttribute (panelHandle, PANEL_BINARYSWITCH, ATTR_VISIBLE,0);
					PlotXY (panelHandle, PANEL_GRAPH, time_arr, A_arr, count, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE,
        VAL_SOLID, 1, VAL_RED);
					PlotXY (panelHandle, PANEL_GRAPH, time_arr, B_arr, count, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE,
        VAL_SOLID, 1, VAL_BLUE);
					break;
                case 3:
					SetCtrlAttribute (panelHandle, PANEL_BINARYSWITCH, ATTR_VISIBLE,0);
					PlotXY (panelHandle, PANEL_GRAPH, time_arr, A_arr, count, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE,
        VAL_SOLID, 1, VAL_RED);
					PlotXY (panelHandle, PANEL_GRAPH, time_arr, B_arr, count, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE,
        VAL_SOLID, 1, VAL_BLUE);
					PlotXY (panelHandle, PANEL_GRAPH, time_arr, C_arr, count, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE,
        VAL_SOLID, 1, VAL_GREEN);
                    break;
                case 4:
					SetCtrlAttribute (panelHandle, PANEL_BINARYSWITCH, ATTR_VISIBLE,0);
					PlotXY (panelHandle, PANEL_GRAPH, time_arr, A_arr, count, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE,
        VAL_SOLID, 1, VAL_RED);
					PlotXY (panelHandle, PANEL_GRAPH, time_arr, B_arr, count, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE,
        VAL_SOLID, 1, VAL_BLUE);
					PlotXY (panelHandle, PANEL_GRAPH, time_arr, C_arr, count, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE,
        VAL_SOLID, 1, VAL_GREEN);
                    break;
                case 5:
					SetCtrlAttribute (panelHandle, PANEL_BINARYSWITCH, ATTR_VISIBLE,1);
					for(int j=0;j<count;j++){
						copy_A_arr[j]=1/A_arr[j];}
					PlotXY (panelHandle, PANEL_GRAPH_2, time_arr,copy_A_arr, count, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE,
        VAL_SOLID, 1, VAL_RED);
					SetCtrlAttribute (panelHandle, PANEL_GRAPH_2, ATTR_YMAP_MODE, VAL_LOG);
					PlotXY (panelHandle, PANEL_GRAPH, time_arr, A_arr, count, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE,
        VAL_SOLID, 1, VAL_RED);
					PlotXY (panelHandle, PANEL_GRAPH, time_arr, B_arr, count, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE,
        VAL_SOLID, 1, VAL_BLUE);
                    break;
				case 6:
					PlotXY (panelHandle, PANEL_GRAPH, time_arr, A_arr, count, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE,
        VAL_SOLID, 1, VAL_RED);
					PlotXY (panelHandle, PANEL_GRAPH, time_arr, B_arr, count, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE,
        VAL_SOLID, 1, VAL_BLUE);
					PlotXY (panelHandle, PANEL_GRAPH, time_arr, C_arr, count, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE,
        VAL_SOLID, 1, VAL_GREEN);
                    break;}
			}
    return 0;
}

int CVICALLBACK back3_func (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			stopfunc ( panel,  control,  event,
						  callbackData,  eventData1, eventData2);
			if (A_arr[0]!=0.0){
			DiscardPanel (panelHandle);
			DisplayPanel (panel2);}
			if (count>0){
			cleanMat( A_arr, count);
			cleanMat( B_arr, count);
			cleanMat( C_arr, count);
			cleanMat( time_arr, count);
			cleanMat( copy_A_arr, count);
			}
			A=B=K1=K_1=K2=dt=C=half_T=Ai=Bi=percnt_A=percnt_B=percnt_C=dA=dB=dC=0.0;
			count =0;
			break;
	}
	return 0;
}

int CVICALLBACK bin_func (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	int switchVal = 0;
	int ySwitch = 0;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel1, PANEL_1_REAC_TYP,&ySwitch);
			GetCtrlVal(panelHandle, PANEL_BINARYSWITCH, &switchVal);
			if (switchVal == 1)
			{
				if (ySwitch==1){
					SetCtrlVal(panelHandle, PANEL_EQ_LINER,1);
					SetCtrlAttribute (panelHandle, PANEL_GRAPH_2, ATTR_YNAME, "ln(Concentration [M])");
				}
				if (ySwitch==5){
					SetCtrlVal(panelHandle, PANEL_EQ_LINER,2);
					SetCtrlAttribute (panelHandle, PANEL_GRAPH_2, ATTR_LABEL_TEXT, "1/[A] vs t)");
					SetCtrlAttribute (panelHandle, PANEL_GRAPH_2, ATTR_YNAME, "1/Concentration [M]");}
				SetCtrlAttribute (panelHandle, PANEL_GRAPH, ATTR_VISIBLE,0);
				SetCtrlAttribute (panelHandle, PANEL_GRAPH_2, ATTR_VISIBLE,1);
				SetCtrlAttribute (panelHandle, PANEL_EQ_LINER, ATTR_VISIBLE,1);
				SetCtrlAttribute (panelHandle, PANEL_GRAPH_2, ATTR_XMAP_MODE, VAL_LINEAR);
				SetCtrlAttribute (panelHandle, PANEL_GRAPH_2, ATTR_YMAP_MODE, VAL_LINEAR);
			}
			else
			{
				SetCtrlAttribute (panelHandle, PANEL_EQ_LINER, ATTR_VISIBLE,0);
				SetCtrlAttribute (panelHandle, PANEL_GRAPH, ATTR_VISIBLE,1);
				SetCtrlAttribute (panelHandle, PANEL_GRAPH_2, ATTR_VISIBLE,0);
				SetCtrlAttribute (panelHandle, PANEL_GRAPH, ATTR_XMAP_MODE, VAL_LINEAR);
				SetCtrlAttribute (panelHandle, PANEL_GRAPH, ATTR_YMAP_MODE, VAL_LINEAR);
			}
			break;
	}
	return 0;
}
