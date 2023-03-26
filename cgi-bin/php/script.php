<?php
session_start();
if(isset($_COOKIE["visited"])){
    $visited = $_COOKIE["visited"] + 1;
    setcookie("visited", $visited, time() + 60);
}
else{
    setcookie("visited", 1, time() + 1);
    $visited = 1;
}
echo "You have visited this page ".$visited." times.<br>";
?>
