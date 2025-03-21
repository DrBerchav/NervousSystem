<?php
function dopraise(&$WorkingMemory,&$TheMatrix)
{
global $DEBUG;
if ($DEBUG == 1) echo "inside dopraise()\n";
$base=dirname(__FILE__);
$base=str_replace("/spine/ears","",$base);
global $DEBUG;
$ary=array();
$ary["happy"]=1;
$json=json_encode($ary);
$filename=$base . "/www/output.txt";
if ($DEBUG == 1) echo "file name is $filename\n";
file_put_contents($filename,$json);
}
?>
