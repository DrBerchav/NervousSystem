<?php
error_reporting(E_ERROR);
$DEBUG=0;
include("memory.inc");
include("cerebellum.inc");
include("suprachiasmatic_nucleus.inc");
include("constants.inc");
$llm=0;
$done=false;
$WorkingMemory[0]=Array("1","2");
$speed=500;
$path = realpath('./' . $spine . "/");
$file="includes.inc";
$fp=fopen($file,"w");
fwrite($fp,"<?php\n");
$objects = new RecursiveIteratorIterator(new RecursiveDirectoryIterator($path), RecursiveIteratorIterator::SELF_FIRST);
$fileobjects=Array();
foreach($objects as $fileinfo){
	$fileName = $fileinfo->getFilename();
//        echo "File is: $fileName" . "\n";
	$pos_dot = strrpos($fileName, "."); // find '.'
	$ext = ($pos_dot !== false) ? substr($fileName, $pos_dot+1) : null;
    if (($ext != "") && (strcasecmp("inc",$ext) == 0))
          {
	    $loadit=$fileinfo->getRealPath();
	    if ($DEBUG == 1) echo "Loading Extra Functions: $loadit\n ";
	    fwrite($fp,"include(\"" . $loadit . "\");\n");
	}
}
fwrite($fp,"\n?>");
fclose ($fp);
if ($DEBUG == 1) echo "Done!\n";
sendintent("sys","go","","autonomic");

include("includes.inc");
$done=false;
$LastDistance=0;

while (!$done)
{
$lm=filemtime("msgqueue.dat");
if ($lm == "") $lm=0;
//echo "lm is $lm\n";
if ($lm > $llm)
{
//echo "file modiifed\n";
$llm=$lm;
$fileobjects=file("msgqueue.dat");
//print_r($fileobjects);
unlink("msgqueue.dat");
}
else
{
//echo "file not modified\n";
}
tickdown();
$speed=$WorkingMemory[0]["speed"];
if ($speed == "") $speed=10;
foreach($fileobjects as $fileinfo) {
    if(trim($fileinfo) !="")
   {
    $tmpfile = trim("./" . $fileinfo);
    $name=realpath($tmpfile);
    $inf=pathinfo($name);
    $basename=basename($name,".in");
    $path=$inf["dirname"];
    $rulesfile=$path . "/" . $basename . ".rules";
    $functions=$path . "/" . $basename . ".inc";
     $pos_dot = strrpos($name, "."); 
   $ext = ($pos_dot !== false) ? substr($name, $pos_dot+1) : null;

    if (($ext != "") && (strcasecmp("inc",$ext) == 0))
	{
	$mtime=filemtime($tmpfile)+5;
	if ($mtime > time()) 
	{
	echo "File was recenlty modified in last 5 seconds reloading required";
	$done=true;
	}

	}
    if (($ext != "") && (strcasecmp("in",$ext) == 0))
          {

	   if ($DEBUG == 1)
		  {
		   if (trim($name) !== "") echo "\nRecieved Message: $name\n";
		  }

            if ($DEBUG == 1)
            {
             echo "\nFound input in $name\n";
             echo "Base is is $basename\n";
             echo "Rules file is $rulesfile\n";
             echo "Functions are in $functions\n";
            }
	    if (!file_exists($rulesfile)) $rulesfile=$path . "/rules.dat";
	    if (!file_exists($rulesfile)) $rulesfile="autonomic.rules";
            if ($DEBUG == 1)   echo "\nRules file would be $rulesfile\n";
	    unset($RulesTable);
	    LoadTable("N/A",$rulesfile,$RulesTable);
	    $WorkingMemory[0]["filename"]=$name;
  	    // open input file read each line and call ProcessRules
	    $fp = fopen($name,"r");
	 	if ($fp)
		{
		while (($TheLine=fgets($fp,4096)) !== false)
			{
			$InputObject=trim($TheLine);
			$WorkingMemory[0]["LAST-INPUT"]=$InputObject;
                        $State_Of_Mind=Array();
			$r=ProcessRules($InputObject,$State_Of_Mind,$WorkingMemory,$RulesTable);
			if ($r !="") $WorkingMemory[0]["LAST-RESPONSE"]=$r;
			if ($r == "RELOAD") $done=true;
			}
		fclose ($fp);
		$r=strpos($name,"autonomic.in");
		if ($r ===  false) 
		{
		if ($DEBUG == 1) echo "Deleting $name";
		unlink ($name);
		if ($DEBUG == 1)  echo "...Done!\n\n";
		}
	}
    $fileobjects=array();
}		
	

	} //end of while 

}
//echo "Erase file objets...\n\n";

//echo "Speed is $speed\n";;
usleep($speed * 5000);
sendintent("sys","go","","autonomic");
$llm=0;
}
function GetAIPath()
{
return "./";
}

?>
