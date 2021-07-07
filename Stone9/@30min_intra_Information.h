Inputs: nn(1), td_min_n(13), hist_num(5), closing_time(050000);
Vars: sisum(0), i(0), si(0),Cr(0),phr(0),pcr(0),plr(0),s_day_range(0),true_range(0),day_range(0),up_trigger(0), down_trigger(0);




/// 5시종가 1 Or 0 signal

if sTime=closing_time then si=1 
Else si=0;




///////////// 현물 시장중, 고가, 저가,

phr=Highest(H,td_min_n);
plr=Lowest(L,td_min_n);



////전일 종가구하기

for i=0 to 500 Step 1
Begin
sisum=AccumN(si,i+1);
	if sTime[i]=closing_time And sisum =nn Then
	Begin
	pcr=c[i] of Data1;

	i=2000;
	End;
End;


////////////////장중__True_range
if pcr =0 Then
Begin
day_range=0;
End
Else
Begin
day_range=(phr-plr)/pcr*100;
End;


// signal_day_range

s_day_range=si*day_range;






//// hist_n_True_Range_

for i=0 to 500 Step 1
Begin
sisum=AccumN(si,i+1);
	if sTime[i]=closing_time And sisum =hist_num Then
	Begin
	true_range=AccumN(s_day_range,i+1)/hist_num*0.5;

	i=20000;
	End;
End;



if true_range = 0 Then
Begin
up_trigger=pcr;
down_trigger=pcr;
End
Else
Begin
up_trigger=pcr+true_range*pcr/100;
down_trigger=pcr-true_range*pcr/100;
End;


plot1(up_trigger,"Up_trigger",GREEN);
plot2(down_trigger,"Down_trigger",RED);
plot4(C,"Current_Price",BLUE);
Plot3(pcr,"pre_Closing_Price");