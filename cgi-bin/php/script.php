<?php

session_start();
if (!isset($_SESSION['counter'])) {
  $_SESSION['counter'] = 0;
} else {
  $_SESSION['counter']++;
}

if (!isset($_COOKIE['user'])) {
  $user = "guest";
  setcookie("user", $user);
} else {
  $user = $_COOKIE['user'];
}
echo "You have visited this page " . $_SESSION['counter'] . " times. <br>";
echo "Your name is " . $user . ". <br>";
?>
