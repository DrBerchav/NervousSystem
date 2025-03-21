<?php
function domouth(&$WorkingMemory,&$state_of_mind)
{
global $DEBUG;
$base=dirname(__FILE__);
$base=str_replace("/spine/mouth","",$base);
if ($DEBUG == 1) echo "INSIDE MOUTH!\n";
//fetch should return a JSON array of Energy+1,Hunger-3
$ary=array();
$ary["energy"]=1;
$ary["hunger"]=-3;
$json=json_encode($ary);
$filename = $base . "/www/output.txt";
if ($DEBUG ==1) echo "out file is $filename\n";
file_put_contents($filename,$json);
}
