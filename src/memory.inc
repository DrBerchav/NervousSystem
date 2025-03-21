<?php
function LoadFile($FileName,&$Dictionary)
{
//Load into Dictionary
$fp=fopen($FileName,"r");
while ($line = fgets($fp))
 {
 $l=trim($line);
 $ce=strpos($line,"=");
// if ($ce === false) echo "Cannot find equals in $line";
 if ($ce !== false)
 {
 $ar=explode("=",$l);
 $Dictionary[trim($ar[0])]=trim($ar[1]);
 }
 }
fclose($fp);
}
function  LoadTable($TableName,$ReadFrom,&$Dictionary)
{
//Read a table from the object by read from. For example could be a mysql 
//database, an xmlblob or a text file, etc
$checkfile=file_exists($ReadFrom);
if ($checkfile == true)
 {
 $Dictionary=file($ReadFrom);
 }
return true;
}
?>
