[IOG=True];

Inputs: SSTIME(233000), EETIME(045000), CCTIME(050000), num_contract(2) ;
Vars: up_trigger(0), down_trigger(0), TCOND(False),SellA_Result(False),CCOND(False);




/////////////////////Trading_Time/////////////////////////////
IF SSTIME < EETIME Then 
  Begin
  IF SSTIME <= Currtime And currtime <= EETIME Then TCOND = True
  Else TCOND = False;
  End
Else 
  Begin
  If SSTIME <= Currtime Or currtime <= EETIME Then TCOND = True
  Else TCOND = False;
  End;

/////////////////Trading_Signal/////////////////////////////////

SellA_Result = FALSE;
IF TCOND And  C < down_trigger  Then
	SellA_Result = TRUE;

if ( SellA_Result )
Then
Begin
	Sell("매도",AtMarket,DEF,num_contract);
End;

/////////////////////////////////////////////////////////////////////

/////////////////////Close_Time/////////////////////////////
IF SSTIME < CCTIME Then 
  Begin
  IF SSTIME <= currtime And TIME = CCTIME Then CCOND = True
  Else CCOND = False;
  End
Else 
  Begin
  If currtime = CCTIME Then CCOND = True
  Else CCOND = False;
  End;

////////////////////////////////종가 청산 //////////////////////////////////////////

	

var : ExitShortA_Result(FALSE);

ExitShortA_Result = FALSE;
IF CCOND Then
	ExitShortA_Result = TRUE;

if ( ExitShortA_Result )
Then
Begin
	ExitShort();
End;
