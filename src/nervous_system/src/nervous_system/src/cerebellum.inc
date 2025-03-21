<?php
function contains($InputObj,$Target)
{
$r=stripos($InputObj,$Target);
if ($r === false) return false;
return true;
}
function SAY_YES()
{
echo "YES!\n";
}
function ECHOLN($String)
{
echo $String . "\n";
}
function equals($InputObj,$Target)
{
$r=strcasecmp($InputObj,$Target);
if ($r == 0) return true;
return false;
}
function setintent($area,$action,$data,$filename)
{
return sendintent($area,$action,$data,$filename);
}
function sendintent($area,$action,$data,$filename)
{
$path=GetAIPath() . "spine/" . $area;
if ($filename == "")
 {
$tmpfname = tempnam($path, $action);
 }
else
 {
 $tmpfname=$path . "/" . $filename;
 }
if ($data != "")
 {
 $fp=fopen($tmpfname . ".out","w");
 fwrite ($fp,$data);
 fclose ($fp);
 }
 $fp=fopen($tmpfname . ".in","w");
 fwrite ($fp,$action);
 fclose ($fp);
@unlink ($tmpfname);
}

function get_intent_info($inputstring)
{
 $splitter=explode(",",$inputstring);
 $retval=str_replace("\"","",$splitter[2]);
 $retval=str_replace("(","",$retval);
 $retval=str_replace(")","",$retval);
 $retval=str_replace(";","",$retval);
 return $retval;
}

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
