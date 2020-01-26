<?php
//Creates new record as per request
    //Connect to database
    $servername = "localhost";
    $username = "root";
    $password = "";
    $dbname = "espdemo2";

    // Create connection
    $conn = new mysqli($servername, $username, $password, $dbname);
    // Check connection
    if ($conn->connect_error) {
        die("Database Connection failed: " . $conn->connect_error);
        echo "error1";
    }

    //Get current date and time
    date_default_timezone_set('Asia/Kolkata');
    $d = date("Y-m-d");
    //echo " Date:".$d."<BR>";
    $t = date("H:i:s");
    

    if(empty($_POST['status'])) echo "string1";


    if(!empty($_POST['station'])) echo "string2";

    if(!empty($_POST['status2'])) echo "string3";

    if(!empty($_POST['remark'])) echo "string4";


    if(!empty($_POST['status']) && !empty($_POST['status2']) && !empty($_POST['station']) && !empty($_POST['remark']))
    {
        //echo "string";
        $status = $_POST['status'];
        $status2 = $_POST['status2'];
        $station = $_POST['station'];
        $remark = $_POST['remark'];

        $sql = "INSERT INTO logs (station, status,status2,remark, Date, Time)
        
        VALUES ('".$station."', '".$status."','".$status2."','".$remark."', '".$d."', '".$t."')";

        if ($conn->query($sql) === TRUE) {
            echo "OK";
        } else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    }
    //echo "2";
    /*else
    {
        echo "err";
        $sql = "INSERT INTO logs (station, status, Date, Time)
        
        VALUES ('Arpit', 'hee', '.hee', 'hee')";
        if ($conn->query($sql) === TRUE) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}
    }*/


    $conn->close();
?>
