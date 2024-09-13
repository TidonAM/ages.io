const char PAGE_MAIN[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>AGES</title>
    <!-- <link rel="stylesheet" href="style.css"> -->
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f2f2f2;
            margin: 0;
            padding: 0;
        }

        .navbar-title{
            font-weight: bold;
        }

        .burger{
            background: none;
            border: none;
            color: orange;
        }

        .profile{
            background: none;
            border: none;
            color: orange;
        }

        .status-icons{
            justify-items: center;
        }
        /* Navbar Styles */
        .navbar {
            display: flex;
            justify-content: space-between;
            align-items: center;
            background-color: #c6ec8d;
            padding: 10px;
        }

        .navbar-item img {
            width: 24px;
            height: 24px;
        }

        .navbar-title {
            font-size: 20px;
            color: black;
        }

        /* Container Styles */
        .container {
            max-width: 400px;
            margin: 20px auto;
            background-color: white;
            border: 1px solid #ddd;
            border-radius: 10px;
            padding: 15px;
            display: flex;
            flex-direction: column;
            justify-content: flex-end;
        }

        .header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            background-color: #c6ec8d;
            padding: 10px;
            border-radius: 10px;
            margin-bottom: 10px;
        }

        .header h1 {
            margin: 0;
            font-size: 20px;
            color: black;
        }

        .menu-btn, .search-btn {
            background: none;
            border: none;
            cursor: pointer;
            width: 20px;
            height: 20px;
        }

        .image-box {
            width: 100%;
            height: 200px;
            background-color: #e0e0e0;
            display: flex;
            justify-content: center;
            align-items: center;
            border-radius: 10px;
        }

        .image-box img {
            max-width: 100%;
            max-height: 100%;
            border-radius: 10px;
        }

        .alert-cont {
            display: flex;
            justify-content: space-between;
            align-items: center;
            width: 95%;
            padding: 0px 10px 10px 10px;
        }

        .alert-box {
            display: flex;
            flex-direction: column;
            justify-content: space-between;
            align-items: center;
            background-color: none;
            border: 3px solid lightgray;
            color: #b30000;
            font-weight: bolder;
            padding: 10px 0px 0px 0px;
            border-radius: 8px;
            margin-bottom: 10px;
        }
        .alert{
            display: flex;
        }
        .alert-box p {
            margin: 0;
            font-size: 14px;
            padding-left: 10px;
        }

        .hidden {
            display: none !important;
        }

        .toggle-view {
            margin-bottom: 10px;

        }

        .close-alert {
            background: none;
            border: none;
            font-size: 18px;
            cursor: pointer;
            color: #b30000;
        }

        .status-info {
            margin-bottom: 15px;
            border: 3px solid lightgray;
            border-radius: 8px;
        }

        .info-row {
            display: flex;
            justify-content: space-between;
            margin: 5px 0;
            padding: 10px;
        }

        .info-row2 {
            display: flex;
            justify-content: space-between;
            margin: 5px 0;
            padding: 10px;
            background-color: lightgray;
        }

        .info-row-top {
            display: flex;
            justify-content: space-between;
            padding: 10px;
            background-color: lightgray;
        }

        .info-row3{
            display: flex;
            justify-content: space-between;
            margin: 5px 0;
            padding: 10px;
            background-color: lightgray;
        }
        .info-label {
            font-weight: bold;
            color: #555;
        }


        .info-value {
            color: #555;
        }

        .status-icons {
            display: grid;
            grid-template-columns: repeat(4, 1fr);
            gap: 10px;
            margin-bottom: 15px;
        }

        .icon-box {
            width: 50px;
            height: 50px;
            display: flex;
            justify-content: center;
            align-items: center;
            border-radius: 10px;
            cursor: pointer;
        }

        .icon-box.green {
            background-color: #ccffcc;
            height: 80px;
            width: 80px;
            display: flex;
            flex-direction: column;
            align-items: center;
            text-align: center;
        }

        .icon-label-online{
            margin-top: 10px;
            font-size: 12px; 
            color: #000; 
            font-weight: bold;
        }

        .icon-label-scanner{
            margin-top: 10px;
            font-size: 12px; 
            color: #000; 
            font-weight: bold;
        }

        .icon-label-camol{
            margin-top: 10px;
            font-size: 12px; 
            color: #000; 
            font-weight: bold;
        }

        .icon-label-sensor{
            margin-top: 10px;
            font-size: 12px; 
            color: #000; 
            font-weight: bold;
        }

        .icon-box.red {
            background-color: #ffcccc;
            height: 80px;
            width: 80px;
            display: flex;
            flex-direction: column;
            align-items: center;
            text-align: center;
        }

        .icon-label-gate{
            margin-top: 10px;
            font-size: 12px; 
            color: #000; 
            font-weight: bold;
        }

        .icon-label-obs{
            margin-top: 10px;
            font-size: 12px; 
            color: #000; 
            font-weight: bold;
        }

        .icon-box.yellow {
            background-color: #ffffcc;
            height: 80px;
            width: 80px;
            display: flex;
            flex-direction: column;
            align-items: center;
            text-align: center;
        }

        .icon-label-temp{
            margin-top: 10px;
            font-size: 12px; 
            color: #000; 
            font-weight: bold;
        }

        .icon-label-signal{
            margin-top: 10px;
            font-size: 12px; 
            color: #000; 
            font-weight: bold;
        }

        .icon-box img {
            max-width: 30px;
            max-height: 30px;
        }

        .icon-box:hover {
            transform: scale(1.2);
            transition: transform 0.2s;
        }

        .driver-info {
            margin: 10px 0;
            border: 3px solid lightgray;
            border-radius: 8px;
        }

        .driver-info .info-row {
            display: flex;
            justify-content: space-between;
            margin: 5px 0;
        }

        #progress-container {
            width: 100%;
            height: 10px;
            background-color: #b30000; /* Background color of the container */
            position: relative;
            overflow: hidden;
        }

        #progress-bar {
            width: 100%;
            height: 100%;
            background-color: #ddd; /* Progress bar color */
            position: absolute;
            right: 0; /* Align to the right side */
            transition: width 5s linear; /* Smooth transition over 5 seconds */
        }
    </style>
</head>
<body onload="process()">
    <!-- Navbar -->
    <!--
    <div class="navbar">
        <button class="burger">
            <svg xmlns="http://www.w3.org/2000/svg" width="30" height="30" fill="currentColor" class="bi bi-list" viewBox="0 0 16 16">
                <path fill-rule="evenodd" d="M2.5 12a.5.5 0 0 1 .5-.5h10a.5.5 0 0 1 0 1H3a.5.5 0 0 1-.5-.5m0-4a.5.5 0 0 1 .5-.5h10a.5.5 0 0 1 0 1H3a.5.5 0 0 1-.5-.5m0-4a.5.5 0 0 1 .5-.5h10a.5.5 0 0 1 0 1H3a.5.5 0 0 1-.5-.5"/>
            </svg>
        </button>
        <div class="navbar-title">AGES</div>
        <button class="profile">
            <svg xmlns="http://www.w3.org/2000/svg" width="30" height="30" fill="currentColor" class="bi bi-person-circle" viewBox="0 0 16 16">
                <path d="M11 6a3 3 0 1 1-6 0 3 3 0 0 1 6 0"/>
                <path fill-rule="evenodd" d="M0 8a8 8 0 1 1 16 0A8 8 0 0 1 0 8m8-7a7 7 0 0 0-5.468 11.37C3.242 11.226 4.805 10 8 10s4.757 1.225 5.468 2.37A7 7 0 0 0 8 1"/>
            </svg>
        </button>
    </div>
    -->
    <!-- Main Container -->
    <div class="container">
        
        <div class="image-box">
            <img src="C:\Users\Jm\Desktop\AGES\img\hillcrest.jpg" alt="Gate Image">
        </div>

        <div class="driver-info">
            <div class="info-row">
                <div class="info-label">Last Detected Driver Details</div>
            </div>
            <div class="info-row2">
                <div class="info-label">Name</div>
                <div id="current-driver-name" class="info-value">Dela Cruz, Juan</div>
            </div>
            <div class="info-row">
                <div class="info-label">Plate Number</div>
                <div id="current-driver-plate" class="info-value">ABC123</div>
            </div>
            <div class="info-row3">
                <div class="info-label">Entry Info</div>
                <div id="current-driver-date" class="info-value">hh:mm:ss | yyyy mm dd</div>
            </div>
            <div class="info-row">
                <div class="info-label">Street</div>
                <div id="current-driver-street" class="info-value">Molave Street</div>
            </div>
        </div>

        <div id="alert-box" class="alert-box hidden">
            <div class="alert-cont">
                <div class="alert">
                    <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-exclamation-circle-fill" viewBox="0 0 16 16">
                        <path d="M16 8A8 8 0 1 1 0 8a8 8 0 0 1 16 0M8 4a.905.905 0 0 0-.9.995l.35 3.507a.552.552 0 0 0 1.1 0l.35-3.507A.905.905 0 0 0 8 4m.002 6a1 1 0 1 0 0 2 1 1 0 0 0 0-2"/>
                    </svg>
                    <p>Error!</p>
                </div>
                <button id="close-alert" class="close-alert">✕</button>
            </div>
            <div id="progress-container">
                <div id="progress-bar"></div>
            </div>
        </div>

        <button id="changeViewButton" class="toggle-view">Change View</button>

        <div id="status-info" class="status-info hidden">
            <div class="info-row-top">
                <div class="info-label">Gate Status</div>
            </div>
            <div class="info-row">
                <div class="info-label">Connection Status</div>
                <div class="info-value">Online</div>
            </div>
            <div class="info-row">
                <div class="info-label">Position</div>
                <div class="info-value">Open</div>
            </div>
            <div class="info-row">
                <div class="info-label">Obstacle Detection</div>
                <div class="info-value">Blocked</div>
            </div>
            <div class="info-row2">
                <div class="info-label">Board</div>
            </div>
            <div class="info-row">
                <div class="info-label">Temperature</div>
                <div class="info-value">36°C</div>
            </div>
            <div class="info-row">
                <div class="info-label">RFID Reader Status</div>
                <div class="info-value">Online</div>
            </div>
            <div class="info-row">
                <div class="info-label">Obstacle Sensor Status</div>
                <div class="info-value">Online</div>
            </div>
            <div class="info-row">
                <div class="info-label">Signal to Current Device</div>
                <div class="info-value">50/100</div>
            </div>
            <div class="info-row2">
                <div class="info-label">Board</div>
            </div>
            <div class="info-row">
                <div class="info-label">Camera</div>
                <div class="info-value">Online</div>
            </div>
            <div class="info-row">
                <div class="info-label">Plate Detection Status</div>
                <div class="info-value">ABC123</div>
            </div>
        </div>

        <div id="status-icons" class="status-icons">
            <div id="gate-connection" class="icon-box green">
                <svg xmlns="http://www.w3.org/2000/svg" width="30" height="30" fill="currentColor" class="bi bi-door-closed-fill" viewBox="0 0 16 16">
                    <path d="M12 1a1 1 0 0 1 1 1v13h1.5a.5.5 0 0 1 0 1h-13a.5.5 0 0 1 0-1H3V2a1 1 0 0 1 1-1zm-2 9a1 1 0 1 0 0-2 1 1 0 0 0 0 2"/>
                </svg>
                <div class="icon-label-online">Online</div>
            </div>
            <div id="gate-position" class="icon-box red icon-clickable">
                <svg xmlns="http://www.w3.org/2000/svg" width="30" height="30" fill="currentColor" class="bi bi-door-open-fill" viewBox="0 0 16 16">
                    <path d="M1.5 15a.5.5 0 0 0 0 1h13a.5.5 0 0 0 0-1H13V2.5A1.5 1.5 0 0 0 11.5 1H11V.5a.5.5 0 0 0-.57-.495l-7 1A.5.5 0 0 0 3 1.5V15zM11 2h.5a.5.5 0 0 1 .5.5V15h-1zm-2.5 8c-.276 0-.5-.448-.5-1s.224-1 .5-1 .5.448.5 1-.224 1-.5 1"/>
                </svg>
                <div id="icon-label-gate" class="icon-label-gate">Open</div>
            </div>
            <div id="gate-obstacle" class="icon-box red">
                <svg xmlns="http://www.w3.org/2000/svg" width="30" height="30" fill="currentColor" class="bi bi-slash-circle" viewBox="0 0 16 16">
                    <path d="M8 15A7 7 0 1 1 8 1a7 7 0 0 1 0 14m0 1A8 8 0 1 0 8 0a8 8 0 0 0 0 16"/>
                    <path d="M11.354 4.646a.5.5 0 0 0-.708 0l-6 6a.5.5 0 0 0 .708.708l6-6a.5.5 0 0 0 0-.708"/>
                </svg>
                <div id="icon-label-obs" class="icon-label-obs">Obstructed</div>
            </div>
            <div id="rfid-connection" class="icon-box green">
                <svg xmlns="http://www.w3.org/2000/svg" width="30" height="30" fill="currentColor" class="bi bi-qr-code-scan" viewBox="0 0 16 16">
                    <path d="M0 .5A.5.5 0 0 1 .5 0h3a.5.5 0 0 1 0 1H1v2.5a.5.5 0 0 1-1 0zm12 0a.5.5 0 0 1 .5-.5h3a.5.5 0 0 1 .5.5v3a.5.5 0 0 1-1 0V1h-2.5a.5.5 0 0 1-.5-.5M.5 12a.5.5 0 0 1 .5.5V15h2.5a.5.5 0 0 1 0 1h-3a.5.5 0 0 1-.5-.5v-3a.5.5 0 0 1 .5-.5m15 0a.5.5 0 0 1 .5.5v3a.5.5 0 0 1-.5.5h-3a.5.5 0 0 1 0-1H15v-2.5a.5.5 0 0 1 .5-.5M4 4h1v1H4z"/>
                    <path d="M7 2H2v5h5zM3 3h3v3H3zm2 8H4v1h1z"/>
                    <path d="M7 9H2v5h5zm-4 1h3v3H3zm8-6h1v1h-1z"/>
                    <path d="M9 2h5v5H9zm1 1v3h3V3zM8 8v2h1v1H8v1h2v-2h1v2h1v-1h2v-1h-3V8zm2 2H9V9h1zm4 2h-1v1h-2v1h3zm-4 2v-1H8v1z"/>
                    <path d="M12 9h2V8h-2z"/>
                </svg>
                <div class="icon-label-scanner">Online</div>
            </div>
            <div id="camera-connection" class="icon-box green">
                <svg xmlns="http://www.w3.org/2000/svg" width="30" height="30" fill="currentColor" class="bi bi-camera-video" viewBox="0 0 16 16">
                    <path fill-rule="evenodd" d="M0 5a2 2 0 0 1 2-2h7.5a2 2 0 0 1 1.983 1.738l3.11-1.382A1 1 0 0 1 16 4.269v7.462a1 1 0 0 1-1.406.913l-3.111-1.382A2 2 0 0 1 9.5 13H2a2 2 0 0 1-2-2zm11.5 5.175 3.5 1.556V4.269l-3.5 1.556zM2 4a1 1 0 0 0-1 1v6a1 1 0 0 0 1 1h7.5a1 1 0 0 0 1-1V5a1 1 0 0 0-1-1z"/>
                </svg>
                <div class="icon-label-camol">Camera Online</div>
            </div>
            <div id="board-temp" class="icon-box green">
                <svg xmlns="http://www.w3.org/2000/svg" width="30" height="30" fill="currentColor" class="bi bi-thermometer-half" viewBox="0 0 16 16">
                    <path d="M9.5 12.5a1.5 1.5 0 1 1-2-1.415V6.5a.5.5 0 0 1 1 0v4.585a1.5 1.5 0 0 1 1 1.415"/>
                    <path d="M5.5 2.5a2.5 2.5 0 0 1 5 0v7.55a3.5 3.5 0 1 1-5 0zM8 1a1.5 1.5 0 0 0-1.5 1.5v7.987l-.167.15a2.5 2.5 0 1 0 3.333 0l-.166-.15V2.5A1.5 1.5 0 0 0 8 1"/>
                </svg>
                <div id="icon-label-temp" class="icon-label-temp">Temperature</div>
            </div>
            <div id="board-signal" class="icon-box yellow">
                <svg xmlns="http://www.w3.org/2000/svg" width="30" height="30" fill="currentColor" class="bi bi-bar-chart-fill" viewBox="0 0 16 16">
                    <path d="M1 11a1 1 0 0 1 1-1h2a1 1 0 0 1 1 1v3a1 1 0 0 1-1 1H2a1 1 0 0 1-1-1zm5-4a1 1 0 0 1 1-1h2a1 1 0 0 1 1 1v7a1 1 0 0 1-1 1H7a1 1 0 0 1-1-1zm5-5a1 1 0 0 1 1-1h2a1 1 0 0 1 1 1v12a1 1 0 0 1-1 1h-2a1 1 0 0 1-1-1z"/>
                </svg>
                <div class="icon-label-signal">Signal</div>
            </div>
            <div id="obstacle-connection" class="icon-box green">
                <svg xmlns="http://www.w3.org/2000/svg" width="30" height="30" fill="currentColor" class="bi bi-upc-scan" viewBox="0 0 16 16">
                    <path d="M1.5 1a.5.5 0 0 0-.5.5v3a.5.5 0 0 1-1 0v-3A1.5 1.5 0 0 1 1.5 0h3a.5.5 0 0 1 0 1zM11 .5a.5.5 0 0 1 .5-.5h3A1.5 1.5 0 0 1 16 1.5v3a.5.5 0 0 1-1 0v-3a.5.5 0 0 0-.5-.5h-3a.5.5 0 0 1-.5-.5M.5 11a.5.5 0 0 1 .5.5v3a.5.5 0 0 0 .5.5h3a.5.5 0 0 1 0 1h-3A1.5 1.5 0 0 1 0 14.5v-3a.5.5 0 0 1 .5-.5m15 0a.5.5 0 0 1 .5.5v3a1.5 1.5 0 0 1-1.5 1.5h-3a.5.5 0 0 1 0-1h3a.5.5 0 0 0 .5-.5v-3a.5.5 0 0 1 .5-.5M3 4.5a.5.5 0 0 1 1 0v7a.5.5 0 0 1-1 0zm2 0a.5.5 0 0 1 1 0v7a.5.5 0 0 1-1 0zm2 0a.5.5 0 0 1 1 0v7a.5.5 0 0 1-1 0zm2 0a.5.5 0 0 1 .5-.5h1a.5.5 0 0 1 .5.5v7a.5.5 0 0 1-.5.5h-1a.5.5 0 0 1-.5-.5zm3 0a.5.5 0 0 1 1 0v7a.5.5 0 0 1-1 0z"/>
                </svg>
                <div class="icon-label-sensor">Online</div>
            </div>
        </div>
    </div>
</body>

<script type = "text/javascript">
    var xmlHttp = createXmlHttpObject();

    function createXmlHttpObject() {
        if(window.XMLHttpRequest) {
            xmlHttp = new XMLHttpRequest();
        } else {
            xmlHttp = new ActiveXObject("Microsoft.XMLHTTP");
        }
        return xmlHttp;
    }

    function gateChangePosition(value) {
        var xhttp = new XMLHttpRequest();
        var message;
        xhttp.open("PUT", "gateposition", value);
        xhttp.send();
    }

    // handles esp32 response
    function response() {
        var message;
        var currentSensor;
        var xmlResponse;
        var xmldoc;
        // var dt = new Date();
        var color = "e8e8e8";

        //get xml stream
        xmlResponse = xmlHttp.responseXML;

        if (xmlResponse != null) {

            xmldoc = xmlResponse.getElementsByTagName("SD");
            message = xmldoc[0].firstChild.nodeValue;

            document.getElementById("icon-label-obs").innerHTML = message;

            xmldoc = xmlResponse.getElementsByTagName("T");
            message = xmldoc[0].firstChild.nodeValue;

            document.getElementById("icon-label-temp").innerHTML = message;

            xmldoc = xmlResponse.getElementsByTagName("GPOS");
            message = xmldoc[0].firstChild.nodeValue;

            if (message == "0") {
                document.getElementById("icon-label-gate").innerHTML = "Closed";
            } else if (message == "1") {
                document.getElementById("icon-label-gate").innerHTML = "Open";
            } else if (message == "2") {
                document.getElementById("icon-label-gate").innerHTML = "Rotating";
            }

        }

    }

    function process(){
        if(xmlHttp.readyState==0 || xmlHttp.readyState==4) {
            xmlHttp.open("PUT","xml",true);
            xmlHttp.onreadystatechange=response;
            xmlHttp.send(null);
        }       
        setTimeout("process()",1000);
    }

</script>

<script>
    
    const statusInfo = document.getElementById('status-info');
    const statusIcons = document.getElementById('status-icons');
    const changeViewButton = document.getElementById('changeViewButton');
    const iconBox  = document.getElementsByClassName('icon-clickable');
    const alertBox = document.getElementById('alert-box');
    const closeAlertButton = document.getElementById('close-alert');
    const gatePositionText = document.getElementById('icon-label-gate').textContent;
    let closeAlertTimeOut;

    changeViewButton.addEventListener('click', () => {
    if (!statusInfo.classList.contains('hidden')) {
        statusInfo.classList.add('hidden');
        statusIcons.classList.remove('hidden');
    } else {
        statusInfo.classList.remove('hidden');
        statusIcons.classList.add('hidden');
    }
    });

    Array.from(iconBox).forEach(element => {
        element.addEventListener('click', () => {
            const ButtonId = element.id;
            console.log(`Clicked element ID: ${ButtonId}`);

            if (ButtonId == "gate-position") {
                console.log(`gate-position: ` + gatePositionText);
                if (gatePositionText == "Open") {
                    console.log(`gateposition is open: ` + gatePositionText);
                    processGatePosition("1");
                } else if (gatePositionText == "Closed") {
                    console.log(`gateposition is close: ` + gatePositionText);
                    processGatePosition("0");
                }
                
            }

            //alerted
            if (alertBox.classList.contains('hidden')) {
                alertBox.classList.remove('hidden');

                const progressBar = document.getElementById('progress-bar');
                progressBar.style.width = '0%';

                setTimeout(() => {
                    progressBar.style.width = '100%';
                }, 10); 

                closeAlertTimeOut = setTimeout(() => {
                    alertBox.classList.add('hidden');
                }, 5000);
            }
        });
    });

    closeAlertButton.addEventListener('click', () => {
        if (!alertBox.classList.contains('hidden')) {
            alertBox.classList.add('hidden');
            clearTimeout(closeAlertTimeOut);
        }
    });

    function processGatePosition(value) {
        var xhttp = new XMLHttpRequest();
        var message;
        xhttp.open("PUT", "gateposition", value);
        xhttp.send();
    }
</script>

</html>








)=====";
