<?php
//$TickerConst=72000000; // 'Estimated ticks in an 8 hour period
$BrainFrequency=16;
$TickerConst=3600000; // 'Estimated ticks in an 8 hour period
$ticker=$TickerConst;
$firsttime=true;
$currenttime=0;
$estimatedseconds=0;
$lasttime=time();
$lastseconds=0;
$waittime=100;

function auto_relax($Level,&$TheMatrix)
{
global $BrainFrequency;
$BrainFrequency = $BrainFrequency - $Level;
echo "Brain Frequency reduced to $BrainFrequency\n";
if ($BrainFrequency < 4) $BrainFrequency=4;
if ($BrainFrequency > 4)
                {
                release_beta_endorphin($TheMatrix);
                }
        else
                {
                release_melatonin($TheMatrix);
                }
}

function IsDate( $Str )
{
  if (strpos($Str,"*") !== false) return false;
  $arr_time = preg_split('/[\s]+/', $Str);
  if (count($arr_time) == 5) return false;
  $Stamp = strtotime( $Str );
  $Month = date( 'm', $Stamp );
  $Day   = date( 'd', $Stamp );
  $Year  = date( 'Y', $Stamp );

  return checkdate( $Month, $Day, $Year );
}

function at($atstring)
{
//compare at string in same as "cron" format
if (IsDate($atstring))
{
$Time=strtotime($atstring);
if (time() == $Time) return true;
else return false;
}

$arr_time = preg_split('/[\s]+/', $atstring);
$Hour=intval(date("G"));
$Minute=intval(date("i"));
$MonthDay=intval(date("j"));
$Month=intval(date("n"));
$Dow=intval(date("N"));
if ($arr_time[0]=="*") $arr_time[0]=$Minute; //Minute
if ($arr_time[1]=="*") $arr_time[1]=$Hour; // Hour
if ($arr_time[2]=="*") $arr_time[2]=$MonthDay; // Day within month
if ($arr_time[3]=="*") $arr_time[3]=$Month; // Month (1-12)
if ($arr_time[4]=="*") $arr_time[4]=$Dow; // day of week (Mon-Fri)
//echo "Here!";
//print_r($arr_time);
if ($arr_time[0] == $Minute && $arr_time[1] == $Hour && $arr_time[2] == $MonthDay && $arr_time[3] == $Month && $arr_time[4] == $Dow)
{
return true;
}
return false;
}

function autonomic($input) { 
global $DEBUG;
global $lastseconds;
global $estimatedseconds;
if ($DEBUG == 1) echo "Inside autonomic $input!\n";
if ($input == 0) return true;
if ($lastseconds != $estimatedseconds)
 {
 if ($DEBUG == 1) echo "inside autonomic $input LastSeconds $lastseconds Estimated $estimatedseconds \n";

  if (($estimatedseconds % $input) == 0) 
    {
  //  echo "Input was $input";
  $lastseconds=$estimatedseconds;
    return true;
//    die();
    }
 }
 else
 {
//echo "was inside autonomic $input LastSeconds $lastseconds Estimated $estimatedseconds \n";
 }
  return false;
}

function tickdown()
{
global $ticker;
global $TickerConst;
global $waittime;
global $estimatedseconds;
global $firsttime;
$ticker--;
//echo $ticker . "\n";
if (($ticker % $waittime) == 0) 
{
$estimatedseconds++;
}
if ($ticker <= 0) readclock(false);
if ($ticker == ($TickerConst - 200)) 
{
if ($firsttime) { $firsttime=false; readclock(true);}
}
}

function guesstime()
{
global $currenttime;
global $estimatedseconds;
$retval=0;
if ($currenttime != 0) 
{
//	echo "E: " . $estimatedseconds;
	$trytime=$currenttime + $estimatedseconds;
	$ctime=time();
	if ($trytime > $ctime)
		 $retval=$ctime - $estimatedseconds;
	else
		 $retval=$ctime + $estimatedseconds;
}
return $retval;
}

function readclock($force)
{
global $BrainFrequency;
//echo "Inside readclock $force";
global $TickerConst;
global $ticker;
global $currenttime;
global $lasttime;
global $waittime;
$currenttime=time();
if ($force == false)
{
$BrainFrequency=$BrainFrequency * 2;
if ($BrainFrequency > 32) $BrainFrequency=4;
}
$elapsed=$currenttime - $lasttime;
$lasttime=time();
if ($elapsed == 0) 
{
$ticker=$TickerConst;
return true;
}
if ($ticker < 0) $ticker=0;
$totalticks=$TickerConst - $ticker;
//echo "Total Ticks $totalticks";
$tickspersecond=$totalticks / $elapsed;
if ($tickspersecond > $TickerConst)
 {
 $waittime = $waittime * 10;
 }
$CircadianDay=$TickerCosnt / 125; //Cercadian day in seconds elapsed
if (($estimatedseconds > $CircadianDay) || $force)
 {
   $estimatedseconds=0;
   $waittime=$tickspersecond;
   //echo $waittime;
 }	
$ticker=$TickerConst;
//echo "Left Readclock\n";
}

function showticker()
{
global $ticker;
global $systime;
if ($systime == "") 
 $systime=time();
else
 {
 $elapsed=time() - $systime;
 $systime=time();
if ($DEBUG == 1)
{
 echo "Elapsed: " . $elapsed . " seconds!\n";
 echo "Guess: " . date("H:i:s",guesstime()) . "\n";
 echo "Actual: " . date("H:i:s") . "\n";
}
 }
}
function getticker()
{
global $ticker;
return $ticker;
}
function setticker($newtick)
{
global $ticker;
$ticker=$newtick;
}
function checkticker()
{
global $ticker;
if ($ticker <= 0) resettick();
}
?>
