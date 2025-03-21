<?php
function testcron()
{
$f=fopen("/home/adminbrad/tmp/YESGOTIT.TXT","w");
fwrite ($f,"Yep I wrote this at: " . date('l jS \of F Y h:i:s A'));
fclose ($f);
}
function sad()
{
global $DEBUG;
if ($DEBUG == 0) echo "inside sad\n";
$base=dirname(__FILE__);
$base=str_replace("/spine/sys","",$base);
$ary=array();
$ary["happy"]=-1;
$json=json_encode($ary);
$filename = $base . "/www/output.txt";
if ($DEBUG ==1) echo "out file is $filename\n";
file_put_contents($filename,$json);
}

function dohunger()
{
global $DEBUG;
if ($DEBUG == 0) echo "inside hunger\n";
$base=dirname(__FILE__);
$base=str_replace("/spine/sys","",$base);
$ary=array();
$ary["hunger"]=1;
$json=json_encode($ary);
$filename = $base . "/www/output.txt";
if ($DEBUG ==1) echo "out file is $filename\n";
file_put_contents($filename,$json);
}

function dotired()
{
global $DEBUG;
if ($DEBUG == 0) echo "inside tired\n";
$base=dirname(__FILE__);
$base=str_replace("/spine/sys","",$base);
$ary=array();
$ary["energy"]=-1;
$json=json_encode($ary);
$filename = $base . "/www/output.txt";
if ($DEBUG ==1) echo "out file is $filename\n";
file_put_contents($filename,$json);
}

?>
