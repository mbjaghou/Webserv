<?php
session_start();

// Set a session variable
$_SESSION["test_session"] = "test_value";

// Check if the session variable is set
if (isset($_SESSION["test_session"])) {
  echo "Sessions are working!";
} else {
  echo "Sessions are not working.";
}

// Destroy the session
session_destroy();
?>