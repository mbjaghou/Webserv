<?php
if ($_SERVER['REQUEST_METHOD'] == 'DELETE') {
    echo 'request method is DELETE';
} else {
    echo 'Invalid request method';
}
?>