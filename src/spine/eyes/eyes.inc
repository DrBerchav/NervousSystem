<?php
function dolook(&$WorkingMemory,&$state_of_mind)
{
$base=dirname(__FILE__);
$base=str_replace("/spine/eyes","",$base);
global $DEBUG;
//fetch should return a JSON array of Salivates, Happy+2
$ary=array();
$ary["salivates"]=1;
//$ary["happy"]=2;
$json=json_encode($ary);
$filename=$base . "/www/output.txt";
file_put_contents($filename,$json);
}
?>
