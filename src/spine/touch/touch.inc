<?php
function playfetch()
{
$base=dirname(__FILE__);
$base=str_replace("/spine/touch","",$base);
global $DEBUG;
if ($DEBUG == 1) echo "INSIDE FETCH!!\n";
$ary=array();
$ary["happy"]=3;
$ary["energy"]=-2;
$ary["hunger"]=1;
$json=json_encode($ary);
$filename = $base . "/www/output.txt";
if ($DEBUG ==1) echo "out file is $filename\n";
file_put_contents($filename,$json);
}

function dopet()
{
$base=dirname(__FILE__);
$base=str_replace("/spine/touch","",$base);
global $DEBUG;
if ($DEBUG == 1) echo "INSIDE FETCH!!\n";
$ary=array();
$ary["happy"]=2;
$json=json_encode($ary);
$filename = $base . "/www/output.txt";
if ($DEBUG ==1) echo "out file is $filename\n";
file_put_contents($filename,$json);
}


?>
