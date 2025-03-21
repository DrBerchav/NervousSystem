<?php
function ProcessRules($InputObject,&$state_of_mind,&$WorkingMemory,$RulesTable)
{
global $DEBUG;
if ($DEBUG ==1) echo "Inside Process Rules For $InputObject\n";
$WorkingMemory[0]["RETURN"]="";
$WorkingMemory[0]["LASTINPUT"]=$InputObject;
//echo "DEBUG is $DEBUG\n";
for ($rulenumber=0;$rulenumber<count($RulesTable);$rulenumber++)
{
if ($DEBUG == 1) echo "Processing: Rule $rulenumber Count is " . count($RulesTable) . "\n";
 $TheLine=trim($RulesTable[$rulenumber]); 
 if ($TheLine != "")
 {
 $RuleData=explode("\t",$TheLine);
 $RuleType=$RuleData[1];
 $PatternMatch=$RuleData[2];
 $Action=$RuleData[4];
 $Action=str_replace("\n",":",$Action);
 $TheFunction='DORULE($WorkingMemory,$state_of_mind,' . $PatternMatch . ",'" . $Action . "');";
 $semicheck=substr($TheFunction,-1);
 if ($semicheck != ";") $TheFuntion=$TheFunction .";";
if ($DEBUG ==1) echo $TheFunction; 
eval ($TheFunction);
 }

}
}

function ProcessRules1($InputObject,&$state_of_mind,&$WorkingMemory,$RulesTable)
{
$WorkingMemory[0]["RETURN"]="";
$WorkingMemory[0]["LASTINPUT"]=$InputObject;
for ($rulenumber=0;$rulenumber<count($RulesTable);$rulenumber++)
 {
// echo "Processing: Rule $rulenumber Count is " . count($RulesTable) . "\n";
 $TheLine=trim($RulesTable[$rulenumber]); 
 if ($TheLine != "")
 {
 $RuleData=explode("\t",$TheLine);
 $RuleType=$RuleData[1];
 $PatternMatch=$RuleData[2];
 $Action=$RuleData[4];
 $Action=str_replace("\n",":",$Action);
 $TheFunction='DORULE(&$WorkingMemory,&$state_of_mind,' . $PatternMatch . ",'" . $Action . "');";
 $semicheck=substr($TheFunction,-1);
 if ($semicheck != ";") $TheFuntion=$TheFunction .";";
 eval ($TheFunction);
 }
 }

$RetVal=$WorkingMemory[0]["RETURN"];
$cnt=0;
if (function_exists("makechoice"))
 {
 
// echo "here!\n";
 for ($v=0;$v<count($WorkingMemory);$v++)
 {
 if ($WorkingMemory[$v]["RETURN"] != "") 
       {
      $Options[$cnt]=$WorkingMemory[$v]["RETURN"];
	$cnt++;
       }
 }
$ShrinkVal=$WorkingMemory[0]["LAST-RESPONSE"];
if ($StrinkVal != "") echo "Shrink Val is: $ShrinkVal\n";
//echo "c: " . count($Options) . "\n";
if ($ShrinkVal != "" && count($Options) > 0) 
 {
$Options=shrink_choices($Options,$ShrinkVal);
$RetVal=makechoice($state_of_mind,$Options);
 }
$WorkingMemory[0]["LAST-RESPONSE"]=$RetVal;
 }
return $RetVal;
}

function DORULE(&$WorkingMemory,&$state_of_mind,$EvalData,$ActionString)
{
if ($EvalData)
 {
 $check=strpos($ActionString,":");
 if ($check === false) 
 {
 $semicheck=substr($ActionString,-1);
 if ($semicheck != ";") $ActionString=$ActionString .";";
// echo $ActionString;
 $intent=substr($ActionString,1,10);
 if ($intent == "setintent(") writeintent($ActionString);
 $WorkingMemory[0]["REFLECTION"]="";
 eval ($ActionString);
 $ret=$WorkingMemory[0]["REFLECTION"];
// echo "\nReflection is $ret\n";
 if ($ret != "") writeintent($ret);
 }
 else
 { 
$T=explode(":",$ActionString);
 for ($i=0;$i<=count($T);$i++)
  {
// print_r($T);
 $ActionStr=$T[$i];
 $semicheck=substr($ActionStr,-1);
 if ($semicheck != ";") $ActionStr=$ActionStr .";";
  //echo $ActionStr;
 $intent=substr($ActionStr,1,10);
if ($intent == "setintent(") writeintent($ActionStr);
 $WorkingMemory[0]["REFLECTION"]="";
  eval($ActionStr); 
 $ret=$WorkingMemory[0]["REFLECTION"];
 if ($ret != "") writeintent($ret);
  }
 }
 }
return true;
}

function writeintent($Intention)
{
//echo "I: $Intention\n";
//Writes out the string Intention to the hippocampus for memory encoding
$FileName="/usr/local/share/ai/hippocampus/" . time() . ".mem";
$fp=fopen($FileName,"w");
fwrite($fp,$Intention);
fclose($fp);
}
?>
