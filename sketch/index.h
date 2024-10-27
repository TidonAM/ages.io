const char PAGE_MAIN[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>AGES</title>
    <script src="https://www.gstatic.com/firebasejs/10.13.1/firebase-app-compat.js"></script>
    <script src="https://www.gstatic.com/firebasejs/10.13.1/firebase-database-compat.js"></script>
    <script src="https://www.gstatic.com/firebasejs/10.13.1/firebase-firestore-compat.js"></script> 
    <!-- <link rel="stylesheet" href="style.css"> -->
    <style>
        .loader {
            border: 16px solid #f3f3f3; /* Light grey */
            border-top: 16px solid orange; /* Blue */
            border-radius: 50%;
            width: 120px;
            height: 120px;
            animation: spin 2s linear infinite;
            }
            @keyframes spin {
            0% { transform: rotate(0deg); }
            100% { transform: rotate(360deg); }
            }
        .resident input[type="text"] {
            padding: 10px;
            font-size: 16px;
            border: 1px solid #ccc;
            border-radius: 5px;
            width: 60%;
        }
        .date-container input[type="text"] {
            padding: 10px;
            font-size: 16px;
            border: 1px solid #ccc;
            border-radius: 5px;
            width: 100%;
        }
        .search-bar {
            display: flex;
            justify-content: space-between;
            margin-bottom: 10px;
            flex-wrap: wrap;
            gap: 10px;
            margin-top:10px;
        }

        .flex {
            display: flex;
        }

        .search-bar label {
            font-size: 16px;
            color: #555;
            /* margin-right: 10px; */
        }
        .date-container {
            display: flex;
            width: 100%;
            align-items: center;
        }
        h4 {
            margin-bottom: 15px;
            font-size: 18px;
            color: #333;
            border-bottom: 1px solid #d0d0d0;
            padding-bottom: 5px;
        }
        /* Vehicle Row Styling */
        .vehicle-row {
            display: flex;
            justify-content: space-between;
            gap: 10px;
        }

        .vehicle-row .info {
            flex-basis: 48%;
        }
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

        .toggle-view{
            background-color: lightgray;
            border: none;
            padding: 10px;
            font: inherit;
            border-radius: 10px;
        }

        .toggle-view:active {
            background-color: gray;
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

        .toggle-view:hover {
            background-color: darkgray;
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
            /* margin: 5px 0; */
            align-items: center;
            padding: 10px;
        }

        .info-row2 {
            display: flex;
            justify-content: space-between;
            /* margin: 5px 0; */
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
            /* margin: 5px 0; */
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
            grid-template-columns: repeat(2, 1fr);
            gap:10px;
            /* gap: 10px; */
            /* margin-bottom: 15px; */
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
            width: 100%;
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
            width: 100%;
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
            width: 100%;
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
            /* margin: 5px 0; */
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
    <!-- Main Container -->
    <div class="container main" id="container-main">
        
        <div class="image-box">
            <img src="hillcrest.webp" alt="Gate Image">
            <!-- <iframe src="http://192.168.1.54" width="100%" height="600" id="myIframe" frameborder="0" allowfullscreen></iframe> -->
        </div>

        <div class="driver-info">
            <div class="info-row">
                <div class="info-label">Last Detected Driver Details</div>
            </div>
            <div id="LastDriverElement" class="flex" style="flex-direction: column;">
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

            <div id="LastDriverLoader" class="hidden" style="justify-content: center; width: 80%; padding: 10%;">
                <div class="loader" id="loader" style="height:120px;">
                </div>
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

        <button id="viewLogsButton" class="toggle-view" onclick="window.location.href='/logs.html'">View Logs</button>

        <button id="manageResidentsButton" class="toggle-view" onclick="window.location.href='/vehicle.html'">Manage Vehicles</button>

        <button id="manageVehiclesButton" class="toggle-view" onclick="window.location.href='/resident.html'">Manage Residents</button>

        <div style="display: flex; justify-content: space-between;">
            <button id="addResident" style="width: 48%;" class="toggle-view" onclick="modalOpen('addResident')">Add Resident</button>
            <button id="addVehicle" style="width: 48%;" class="toggle-view" onclick="modalOpen('addVehicle')">Add Vehicle</button>
        </div>

        <button id="changeViewButton" class="toggle-view" style="display: none;">Change View</button>

        <div id="status-info" class="status-info hidden">
            <div class="info-row-top">
                <div class="info-label">Gate Status</div>
            </div>
            <div class="info-row">
                <div class="info-label">Position</div>
                <div id="info-label-gate" class="info-value">Closed</div>
            </div>
            <div class="info-row">
                <div class="info-label">Obstacle Detection</div>
                <div id="info-label-obs" class="info-value">Blocked</div>
            </div>
            <div class="info-row2">
                <div class="info-label">Board</div>
            </div>
            <div class="info-row">
                <div class="info-label">Temperature</div>
                <div id="info-label-temp" class="info-value">36°C</div>
            </div>
            <div class="info-row">
                <div class="info-label">RFID Reader Status</div>
                <div id="info-label-rfid" class="info-value">Online</div>
            </div>
        </div>

        <div id="status-icons" class="status-icons">
            <!-- <div id="gate-connection" class="icon-box green">
                <svg xmlns="http://www.w3.org/2000/svg" width="30" height="30" fill="currentColor" class="bi bi-door-closed-fill" viewBox="0 0 16 16">
                    <path d="M12 1a1 1 0 0 1 1 1v13h1.5a.5.5 0 0 1 0 1h-13a.5.5 0 0 1 0-1H3V2a1 1 0 0 1 1-1zm-2 9a1 1 0 1 0 0-2 1 1 0 0 0 0 2"/>
                </svg>
                <div class="icon-label-online">Online</div>
            </div> -->
            <div id="gate-position" class="icon-box red icon-clickable">
                <svg id="svgGatePosition" xmlns="http://www.w3.org/2000/svg" width="30" height="30" fill="currentColor" class="bi bi-door-open-fill" viewBox="0 0 16 16">
                    <path d="M1.5 15a.5.5 0 0 0 0 1h13a.5.5 0 0 0 0-1H13V2.5A1.5 1.5 0 0 0 11.5 1H11V.5a.5.5 0 0 0-.57-.495l-7 1A.5.5 0 0 0 3 1.5V15zM11 2h.5a.5.5 0 0 1 .5.5V15h-1zm-2.5 8c-.276 0-.5-.448-.5-1s.224-1 .5-1 .5.448.5 1-.224 1-.5 1"/>
                </svg>
                <div id="icon-label-gate" class="icon-label-gate">Closed</div>
            </div>
            <div id="gate-obstacle" class="icon-box red">
                <svg id="svgGateObstacle" xmlns="http://www.w3.org/2000/svg" width="30" height="30" fill="currentColor" class="bi bi-slash-circle" viewBox="0 0 16 16">
                    <path d="M8 15A7 7 0 1 1 8 1a7 7 0 0 1 0 14m0 1A8 8 0 1 0 8 0a8 8 0 0 0 0 16"/>
                    <path d="M11.354 4.646a.5.5 0 0 0-.708 0l-6 6a.5.5 0 0 0 .708.708l6-6a.5.5 0 0 0 0-.708"/>
                </svg>
                <div id="icon-label-obs" class="icon-label-obs">Blocked</div>
            </div>
            <!-- <div id="camera-connection" class="icon-box red">
                <svg xmlns="http://www.w3.org/2000/svg" width="30" height="30" fill="currentColor" class="bi bi-camera-video" viewBox="0 0 16 16">
                    <path fill-rule="evenodd" d="M0 5a2 2 0 0 1 2-2h7.5a2 2 0 0 1 1.983 1.738l3.11-1.382A1 1 0 0 1 16 4.269v7.462a1 1 0 0 1-1.406.913l-3.111-1.382A2 2 0 0 1 9.5 13H2a2 2 0 0 1-2-2zm11.5 5.175 3.5 1.556V4.269l-3.5 1.556zM2 4a1 1 0 0 0-1 1v6a1 1 0 0 0 1 1h7.5a1 1 0 0 0 1-1V5a1 1 0 0 0-1-1z"/>
                </svg>
                <div class="icon-label-camol">Offline</div>
            </div> -->
            <!-- <div id="board-temp" class="icon-box green">
                <svg xmlns="http://www.w3.org/2000/svg" width="30" height="30" fill="currentColor" class="bi bi-thermometer-half" viewBox="0 0 16 16">
                    <path d="M9.5 12.5a1.5 1.5 0 1 1-2-1.415V6.5a.5.5 0 0 1 1 0v4.585a1.5 1.5 0 0 1 1 1.415"/>
                    <path d="M5.5 2.5a2.5 2.5 0 0 1 5 0v7.55a3.5 3.5 0 1 1-5 0zM8 1a1.5 1.5 0 0 0-1.5 1.5v7.987l-.167.15a2.5 2.5 0 1 0 3.333 0l-.166-.15V2.5A1.5 1.5 0 0 0 8 1"/>
                </svg>
                <div id="icon-label-temp" class="icon-label-temp">Temp</div>
            </div>
            <div id="rfid-connection" class="icon-box green">
                <svg xmlns="http://www.w3.org/2000/svg" width="30" height="30" viewBox="0 0 122.88 122.02"><title>rfid</title>
                    <path d="M62.19,48.52a9.83,9.83,0,0,0-.25-19.61h-1a9.83,9.83,0,0,0,0,19.63h1.25ZM24.53,91q6,0,9.29,2.7a8.86,8.86,0,0,1,3.24,7.16q0,5.11-3.17,7.7c-2.11,1.72-5.19,2.58-9.22,2.58l-1.08.56H18.42V122H7.72V91Zm-1.88,13.52a4.41,4.41,0,0,0,2.6-.63,3.27,3.27,0,0,0,0-4.44,4.26,4.26,0,0,0-2.6-.66H18.42v5.73Zm6.47,2.3L38.79,122H26.92l-7.23-13.56,9.43-1.6Zm37.37-7.79H51.75v4.32H63.67v8H51.75V122H40.81V91H66.49v8Zm14.08-8v31H69.63V91Zm19.9,0q7.27,0,11,4t3.71,11.45q0,7.36-3.71,11.43t-11,4.06H85.26V91Zm-1.55,23.19c2,0,3.38-.62,4.06-1.86a12.78,12.78,0,0,0,1-5.84,12.78,12.78,0,0,0-1-5.84c-.68-1.24-2-1.86-4.06-1.86H96.19v15.4ZM41.57,21.77a4.5,4.5,0,0,0-.51-6.2l-.29-.23a4.4,4.4,0,0,0-3.14-.86,4.45,4.45,0,0,0-2.9,1.5,1.79,1.79,0,0,0-.22.25,41.63,41.63,0,0,0-6.45,10.92A31.56,31.56,0,0,0,28,50.43a40.44,40.44,0,0,0,6.49,10.93,4.49,4.49,0,0,0,6.31.65h0a4.5,4.5,0,0,0,.65-6.32h0a31.57,31.57,0,0,1-5-8.36,22.93,22.93,0,0,1-1.65-8.51,23.32,23.32,0,0,1,1.71-8.56,32.39,32.39,0,0,1,5.08-8.49ZM22.4,7.54a1.37,1.37,0,0,0,.19-.23,4.45,4.45,0,0,0-.43-6.1,1.37,1.37,0,0,0-.22-.2,4.48,4.48,0,0,0-6.18.5A67.93,67.93,0,0,0,3.84,19.91,46.8,46.8,0,0,0,0,39,46.8,46.8,0,0,0,4.47,58,68.05,68.05,0,0,0,17,76.05l.11.11a4.48,4.48,0,0,0,6.23.08l.11-.1a4.56,4.56,0,0,0,1.31-3,4.48,4.48,0,0,0-1.22-3.21A59.49,59.49,0,0,1,12.72,54.48,38.08,38.08,0,0,1,9,38.89a38.45,38.45,0,0,1,3.23-15.72A59,59,0,0,1,22.4,7.54ZM81.31,21.77a4.5,4.5,0,0,1,.51-6.2l.28-.23a4.49,4.49,0,0,1,6.05.64,1.27,1.27,0,0,1,.21.25,41.4,41.4,0,0,1,6.46,10.92,31.56,31.56,0,0,1,.07,23.28A40.44,40.44,0,0,1,88.4,61.36a4.49,4.49,0,0,1-6.31.65h0a4.48,4.48,0,0,1-1.63-3,4.55,4.55,0,0,1,1-3.3h0a31.57,31.57,0,0,0,5-8.36,22.93,22.93,0,0,0,1.65-8.51,23.32,23.32,0,0,0-1.71-8.56,32.39,32.39,0,0,0-5.08-8.49ZM100.48,7.54a1.37,1.37,0,0,1-.19-.23,4.45,4.45,0,0,1,.43-6.1,1.37,1.37,0,0,1,.22-.2,4.48,4.48,0,0,1,6.18.5A67.93,67.93,0,0,1,119,19.91,46.8,46.8,0,0,1,122.87,39a46.8,46.8,0,0,1-4.46,19,68.05,68.05,0,0,1-12.52,18l-.11.11a4.48,4.48,0,0,1-6.23.08l-.11-.1a4.56,4.56,0,0,1-1.31-3,4.48,4.48,0,0,1,1.22-3.21,59.49,59.49,0,0,0,10.81-15.42,38.08,38.08,0,0,0,3.76-15.59,38.45,38.45,0,0,0-3.23-15.72A59,59,0,0,0,100.48,7.54Z"/>
                </svg>
                <div class="icon-label-scanner">Online</div>
            </div> -->
            <!-- <div id="board-signal" class="icon-box yellow">
                <svg xmlns="http://www.w3.org/2000/svg" width="30" height="30" fill="currentColor" class="bi bi-bar-chart-fill" viewBox="0 0 16 16">
                    <path d="M1 11a1 1 0 0 1 1-1h2a1 1 0 0 1 1 1v3a1 1 0 0 1-1 1H2a1 1 0 0 1-1-1zm5-4a1 1 0 0 1 1-1h2a1 1 0 0 1 1 1v7a1 1 0 0 1-1 1H7a1 1 0 0 1-1-1zm5-5a1 1 0 0 1 1-1h2a1 1 0 0 1 1 1v12a1 1 0 0 1-1 1h-2a1 1 0 0 1-1-1z"/>
                </svg>
                <div id="icon-label-signal" class="icon-label-signal">Signal</div>
            </div> -->
            <!-- <div id="obstacle-connection" class="icon-box green">
                <svg class="svg-icon" width="30" height="30" fill="currentColor" viewBox="0 0 1024 1024" version="1.1" xmlns="http://www.w3.org/2000/svg">
                    <path d="M492.251429 907.337143H245.76a91.428571 91.428571 0 0 1-91.428571-91.428572v-601.6a91.428571 91.428571 0 0 1 91.428571-91.428571h246.491429a91.428571 91.428571 0 0 1 91.428571 91.428571v602.331429a91.428571 91.428571 0 0 1-91.428571 90.697143zM245.76 178.285714a36.571429 36.571429 0 0 0-36.571429 36.571429v601.782857a36.571429 36.571429 0 0 0 36.571429 36.571429h246.491429a36.571429 36.571429 0 0 0 36.571428-36.571429V214.308571a36.571429 36.571429 0 0 0-36.571428-36.571428z" /><path d="M334.262857 302.994286H182.857143a27.428571 27.428571 0 0 1 0-54.857143h151.771428a27.428571 27.428571 0 0 1 0 54.857143zM277.028571 420.571429H182.857143a27.428571 27.428571 0 0 1 0-54.857143h94.537143a27.428571 27.428571 0 0 1 0 54.857143zM334.262857 537.6H182.857143a27.428571 27.428571 0 1 1 0-54.857143h151.771428a27.428571 27.428571 0 0 1 0 54.857143zM277.028571 654.994286H182.857143a27.428571 27.428571 0 1 1 0-54.857143h94.537143a27.428571 27.428571 0 0 1 0 54.857143zM334.262857 772.388571H182.857143a27.428571 27.428571 0 1 1 0-54.857142h151.771428a27.428571 27.428571 0 0 1 0 54.857142zM676.571429 663.405714a27.428571 27.428571 0 0 1-19.382858-46.811428 142.994286 142.994286 0 0 0 0-202.24A27.428571 27.428571 0 0 1 694.857143 375.588571a197.851429 197.851429 0 0 1 0 279.771429 27.977143 27.977143 0 0 1-18.285714 8.045714z"/><path d="M778.971429 766.171429a27.062857 27.062857 0 0 1-19.382858-8.045715 27.611429 27.611429 0 0 1 0-38.765714 288.548571 288.548571 0 0 0 0-407.954286 27.611429 27.611429 0 0 1 0-38.765714 27.245714 27.245714 0 0 1 38.765715 0 343.222857 343.222857 0 0 1 0 485.485714 26.514286 26.514286 0 0 1-19.382857 8.045715z"/>
                </svg>
                <div class="icon-label-sensor">Online</div>
            </div> -->
        </div>
    </div>

    <div class="container modal resident" id="container-addresident" style="display: none;">
        <div style="display: flex; justify-content: space-between; align-items: center;">
            <h2>Add Resident</h2>
            <button class="toggle-view" style="height: 40px; width: 40px;" onclick="modalOpen('main')">X</button>
        </div>
        <div class="info-row">
            <label for="modal-addr-last-name">Last name:</label>
            <input type="text" id="modal-addr-last-name" class="info"></input>
        </div>
        <div class="info-row">
            <label for="modal-addr-first-name">First name:</label>
            <input type="text" id="modal-addr-first-name" class="info"></input>
        </div>
        <div class="info-row">
            <label for="modal-addr-middle-initial">Middle Initial:</label>
            <input type="text" id="modal-addr-middle-initial" class="info"></input>
        </div>
        <div class="info-row">
            <label for="modal-addr-street">Street:</label>
            <input type="text" id="modal-addr-street" class="info"></input>
        </div>
        <div class="info-row">
            <label for="modal-addr-block">Block:</label>
            <input type="text" id="modal-addr-block" class="info"></input>
        </div>
        <div class="info-row">
            <label for="modal-addr-lot">Lot:</label>
            <input type="text" id="modal-addr-lot" class="info"></input>
        </div>
        <button id="viewLogsButton" class="toggle-view" onclick="addResident()" style="margin-top: 10px;">Add Resident</button>
    </div>

    <div class="container modal" id="container-waitrfid" style="display: none;">
        <div style="display: flex; justify-content: space-between; align-items: center;">
            <div style="display: flex; gap: 10%; width: 100%;">
                <div class="loader" id="loader" style="height:20px; width: 20px;"></div>
                <p style="display: flex; align-self: center;">Waiting For RFID...</p>
            </div>

            <button class="toggle-view" style="height: 40px; width: 40px;" onclick="modalOpen('addVehicle')">X</button>
        </div>
        
    </div>
    

    <div class="container modal vehicle" id="container-addvehicle" style="display: none;">
        <div style="display: flex; justify-content: space-between; align-items: center;">
            <h2>Add Vehicle</h2>
            <button class="toggle-view" style="height: 40px; width: 40px;" onclick="modalOpen('main')">X</button>
        </div>
        <div class="search-bar">
            <!-- From Date Section -->
            <div class="date-container" style="align-items: center; display: flex; gap: 10px;">
                <input class="dateInput" type="text" id="searchBar" placeholder="Search Resident" />
                <button class="toggle-view" onclick="searchResidents()" style="margin-bottom: 0px !important; height: 100%;">Search</button>
            </div>
        </div>
        <div style="display: flex; justify-content: space-between; align-items: center;">
            <label for="resident">Resident:</label>
            <select id="resident" style="padding: 10px; width: 220px;font-size: 16px; border: 1px solid #ccc; border-radius: 5px; margin-bottom: 10px;">
                <option value="na" disabled selected>Search Resident First</option>
            </select>
        </div>
        <div style="display: flex; justify-content: space-between; align-items: center;">
            <label for="license-plate">License Plate:</label>
            <input id="license-plate" type="text" style="padding: 10px; width: 200px;font-size: 16px; border: 1px solid #ccc; border-radius: 5px;margin-bottom: 10px;">
            </input>
        </div>
        <div style="display: flex; justify-content: space-between; align-items: center;">
            <label for="rfid">RFID Tag:</label>
            <button class="toggle-view" onclick="modalOpen('waitRFID')" style="margin-bottom: 0px !important; height: 100%;">Scan Now</button>
            <input id="addvehiclerfid" type="text">
        </div>
        <div class="vehicle-row" style="margin-bottom: 10px;">
            <div class="info"  style="display: flex; flex-direction: column; gap: 10px; margin-top: 10px;">
                <label for="vehicle-type">Vehicle Type:</label>
                <select id="vehicle-type" style="padding: 10px; font-size: 16px; border: 1px solid #ccc; border-radius: 5px;">
                    <option value="Sedan">Sedan</option>
                    <option value="SUV">SUV</option>
                    <option value="Truck">Truck</option>
                    <option value="MC">Motorcycle</option>
                    <option value="Jeepney">Jeepney</option>
                </select>
            </div>
            <div class="info" style="display: flex; flex-direction: column; gap: 10px; margin-top: 10px;">
                <label for="vehicle-brand">Vehicle Brand:</label>
                <select id="vehicle-brand" style="padding: 10px; font-size: 16px; border: 1px solid #ccc; border-radius: 5px;">
                    <option value="Toyota">Toyota</option>
                    <option value="Honda">Honda</option>
                    <option value="Mitsubishi">Mitsubishi</option>
                    <option value="Nissan">Nissan</option>
                    <option value="Suzuki">Suzuki</option>
                    <option value="Ford">Ford</option>
                    <option value="Hyundai">Hyundai</option>
                    <option value="Kia">Kia</option>
                    <option value="Geely">Geely</option>
                    <option value="NA">N/A</option>
                </select>
            </div>
        </div>
        <button id="addVehicle" class="toggle-view" onclick="addVehicle()">Add Vehicle</button>

    </div>
</body>

<script> 
    function addVehicle() {
        // Get the values from the form
        const resident = document.getElementById('resident').value;
        const licensePlate = document.getElementById('license-plate').value;
        const vehicleType = document.getElementById('vehicle-type').value;
        const vehicleBrand = document.getElementById('vehicle-brand').value;
        const vehicleRfid = document.getElementById('addvehiclerfid').value;

        const residentRef = db.collection('Residents').doc(resident);

        if (!resident || !licensePlate || !vehicleType || !vehicleBrand || !vehicleRfid) {
            alert("Please fill in all fields.");
            return; // Exit the function if any field is empty
        }

        // Validation can be added here if needed

        // Create the vehicle data object
        const vehicleData = {
            owner: residentRef,
            licensePlate: licensePlate,
            vType: vehicleType,
            vBrand: vehicleBrand,
            uid: vehicleRfid,
            dateAdded: firebase.firestore.FieldValue.serverTimestamp() // To store the current timestamp
        };

        // Add the vehicle data to the 'vehicles' collection in Firestore
        db.collection('Vehicle').add(vehicleData)
        .then(() => {
            alert("Vehicle added successfully!");
            document.getElementById('resident').selectedIndex = 0; // Reset resident dropdown
            document.getElementById('license-plate').value = '';   // Clear license plate field
            document.getElementById('vehicle-type').selectedIndex = 0; // Reset vehicle type dropdown
            document.getElementById('vehicle-brand').selectedIndex = 0; // Reset vehicle brand dropdown
            document.getElementById('addvehiclerfid').value = '';  // Clear RFID input
            modalOpen('main');
        })
        .catch((error) => {
            alert("Error adding vehicle: ", error);
        });
    }
</script>

<script>
    // Function to search for residents
    function searchResidents() {
    const searchValue = document.getElementById('searchBar').value.trim().toLowerCase();

    // Ensure search value is not empty
    if (searchValue === "") {
        alert("Please enter a search term.");
        return;
    }

    const residentsRef = db.collection('Residents');

    // Fetch all residents and perform the search locally
    residentsRef
        .get()
        .then((querySnapshot) => {
            const residentSelect = document.getElementById('resident');
            
            // Clear previous options
            residentSelect.innerHTML = '<option value="na" disabled selected>Search Resident First</option>';

            let found = false;

            // Loop through the query results
            querySnapshot.forEach((doc) => {
                const resident = doc.data();

                // Concatenate the full name fields
                const fullName = `${resident.firstName.toLowerCase()} ${resident.MiddleName ? resident.MiddleName.toLowerCase() + ' ' : ''}${resident.lastName.toLowerCase()}`;

                // Check if the full name matches the search value (partial matching)
                if (fullName.startsWith(searchValue)) {
                    found = true;

                    // Add an option for each matching resident
                    const option = document.createElement('option');
                    option.value = doc.id; // Use resident document ID as the value
                    option.textContent = `${resident.firstName} ${resident.MiddleName || ''} ${resident.lastName}`.trim(); // Display full name

                    // Append the option to the select field
                    residentSelect.appendChild(option);
                }
            });

            // Handle case when no residents match
            if (!found) {
                const noOption = document.createElement('option');
                noOption.value = "na";
                noOption.textContent = "No residents found";
                residentSelect.appendChild(noOption);
            }
        })
        .catch((error) => {
            console.error("Error searching residents: ", error);
        });
}


</script>


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

    // handles esp32 response
    function response() {
        var message;
        var currentSensor;
        var xmlResponse;
        var xmldoc;

        //get xml stream
        xmlResponse = xmlHttp.responseXML;

        if (xmlResponse != null) {

            xmldoc = xmlResponse.getElementsByTagName("SD");
            message = xmldoc[0].firstChild.nodeValue;

            if (message > 10) {
                document.getElementById("gate-obstacle").classList.add("green");
                document.getElementById("gate-obstacle").classList.remove("red");
                document.getElementById("icon-label-obs").innerHTML = "Clear";
                document.getElementById("info-label-obs").innerHTML = "Clear";
                changeSVG(svg_obsOpen, "svgGateObstacle", "gate-obstacle");
            } else {
                document.getElementById("gate-obstacle").classList.add("red");
                document.getElementById("gate-obstacle").classList.remove("green");
                document.getElementById("icon-label-obs").innerHTML = "Blocked";
                document.getElementById("info-label-obs").innerHTML = "Blocked";
                changeSVG(svg_obsClose, "svgGateObstacle", "gate-obstacle");
            }

            // document.getElementById("icon-label-obs").innerHTML = message;

            xmldoc = xmlResponse.getElementsByTagName("GPOS");
            message = xmldoc[0].firstChild.nodeValue;

            console.log(`gateMessage: ` + message);

            if (message == "0") {
                document.getElementById("gate-position").classList.add("green");
                document.getElementById("gate-position").classList.remove("red");
                document.getElementById("gate-position").classList.remove("yellow");
                document.getElementById("icon-label-gate").innerHTML = "Closed";
                document.getElementById("info-label-gate").innerHTML = "Closed";
                changeSVG(svg_gateClose, "svgGatePosition", "gate-position");

                xmldoc = xmlResponse.getElementsByTagName("RFID");

                if (xmldoc.length > 0 && xmldoc[0].firstChild != null && xmldoc[0].firstChild.nodeValue != null) {
                    message = xmldoc[0].firstChild.nodeValue;
                    console.log(message);
                    checkRFID(message).then(isFound => {
                        if (isFound) {
                            processGatePosition("1");   
                             // Wait 3 seconds for the icon-label-obs innerHTML to be 'blocked'
                            setTimeout(() => {
                                // Check if the innerHTML is 'blocked' after 3 seconds
                                const element = document.getElementById('icon-label-obs');
                                if (element && element.innerHTML === "Blocked") {
                                    // Close the gate after 3 seconds
                                    processGatePosition("0"); 
                                } else {
                                    processGatePosition("0"); 
                                }
                            }, 3000);  // 3000 milliseconds = 3 seconds
                        } else {
                            if (document.getElementById('container-waitrfid').style.display === 'flex') {
                                console.log(message);
                                document.getElementById('addvehiclerfid').value = message;
                                modalOpen('addVehicle');
                            }
                        }
                    });
                    // if (message == " 53 49 43 34") {
                    //     processGatePosition("1");
                    // }
                }


            } else if (message == "1") {
                document.getElementById("gate-position").classList.add("red");
                document.getElementById("gate-position").classList.remove("green");
                document.getElementById("gate-position").classList.remove("yellow");
                document.getElementById("icon-label-gate").innerHTML = "Open";
                document.getElementById("info-label-gate").innerHTML = "Open";
                changeSVG(svg_gateOpen, "svgGatePosition", "gate-position");
            } else if (message == "2") {
                document.getElementById("gate-position").classList.add("yellow");
                document.getElementById("gate-position").classList.remove("green");
                document.getElementById("gate-position").classList.remove("red");
                document.getElementById("icon-label-gate").innerHTML = "Rotating";
                document.getElementById("info-label-gate").innerHTML = "Rotating";
                changeSVG(svg_gateOpen, "svgGatePosition", "gate-position");
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

    function processGatePosition(value, retries = 3) {
        var xhttp = new XMLHttpRequest();
        xhttp.open("PUT", "/gateposition?position=" + value, true);  // Send value as a query parameter
        xhttp.onload = function() {
            if (xhttp.status >= 200 && xhttp.status < 300) {
                console.log('Success:', xhttp.responseText);
            } else {
                console.error('Error:', xhttp.statusText);
                if (retries > 0) {
                    console.log(`Retrying... Attempts left: ${retries}`);
                    processGatePosition(value, retries - 1); // Retry the request
                } else {
                    console.error('Max retries reached. Request failed.');
                }
            }
        };
        xhttp.send();
    }

    function modalOpen(type) {
        const contMain = document.getElementById('container-main');
        const contAddResident = document.getElementById('container-addresident');
        const contAddVehicle = document.getElementById('container-addvehicle');
        const contWaitRFID = document.getElementById('container-waitrfid');
        if (type == 'addResident') {
            contMain.style.display = "none";
            contAddResident.style.display = "flex";
            contAddVehicle.style.display = "none";
            contWaitRFID.style.display = "none";
        } else if (type == 'addVehicle') {
            contMain.style.display = "none";
            contAddResident.style.display = "none";
            contAddVehicle.style.display = "flex";
            contWaitRFID.style.display = "none";
        } else if (type == 'main') {
            contMain.style.display = "flex";
            contAddResident.style.display = "none";
            contAddVehicle.style.display = "none";
            contWaitRFID.style.display = "none";
        } else if (type == 'waitRFID') {
            contMain.style.display = "none";
            contAddResident.style.display = "none";
            contAddVehicle.style.display = "none";
            contWaitRFID.style.display = "flex";
        }
    }

</script>


<script>
        const firebaseConfig = {
            apiKey: "AIzaSyBtBfdvrpXq1tJSBGMEqziGOj2LFKsvSTQ",
            authDomain: "ages-cd6bc.firebaseapp.com",
            projectId: "ages-cd6bc",
            storageBucket: "ages-cd6bc.appspot.com",
            messagingSenderId: "800033951916",
            appId: "1:800033951916:web:9c97b66c162577998b0f09",
            measurementId: "G-2F3CSHCZZ7"
        };
        const app = firebase.initializeApp(firebaseConfig);
        const db = firebase.firestore();
        const database = firebase.database();

        async function fetchReferenceData(ref) {
            if (!ref) {
                console.error("Reference is undefined or null.");
                return {};
            }

            const doc = await ref.get();
            return doc.exists ? doc.data() : {};
        }


        function changeSVG(path, oldsvgId, divId) {
            const oldsvg = document.getElementById(oldsvgId);
            oldsvg.innerHTML = path;
        }

        function isLoading(a) {
            const element = document.getElementById("LastDriverElement");
            const loader = document.getElementById("LastDriverLoader");
            if (a === true) {
                loader.classList.add('flex');
                loader.classList.remove('hidden');
                element.classList.add('hidden');
                element.classList.remove('flex');
            } else {
                loader.classList.add('hidden');
                loader.classList.remove('flex');
                element.classList.add('flex');
                element.classList.remove('hidden');
            }
        }

        const svg_gateClose =  `
                <path d="M12 1a1 1 0 0 1 1 1v13h1.5a.5.5 0 0 1 0 1h-13a.5.5 0 0 1 0-1H3V2a1 1 0 0 1 1-1zm-2 9a1 1 0 1 0 0-2 1 1 0 0 0 0 2"/>
        `;
        const svg_gateOpen =  `
                <path d="M1.5 15a.5.5 0 0 0 0 1h13a.5.5 0 0 0 0-1H13V2.5A1.5 1.5 0 0 0 11.5 1H11V.5a.5.5 0 0 0-.57-.495l-7 1A.5.5 0 0 0 3 1.5V15zM11 2h.5a.5.5 0 0 1 .5.5V15h-1zm-2.5 8c-.276 0-.5-.448-.5-1s.224-1 .5-1 .5.448.5 1-.224 1-.5 1"/>
        `;
        const svg_obsClose =  `
                <path d="M8 15A7 7 0 1 1 8 1a7 7 0 0 1 0 14m0 1A8 8 0 1 0 8 0a8 8 0 0 0 0 16"/>
                <path d="M11.354 4.646a.5.5 0 0 0-.708 0l-6 6a.5.5 0 0 0 .708.708l6-6a.5.5 0 0 0 0-.708"/>
        `;
        const svg_obsOpen =  `
                <path d="M8 15A7 7 0 1 1 8 1a7 7 0 0 1 0 14m0 1A8 8 0 1 0 8 0a8 8 0 0 0 0 16"/>
                <path d="m10.97 4.97-.02.022-3.473 4.425-2.093-2.094a.75.75 0 0 0-1.06 1.06L6.97 11.03a.75.75 0 0 0 1.079-.02l3.992-4.99a.75.75 0 0 0-1.071-1.05"/>        
        `;

        function getDriverDetails(lastname, firstname, datetime, plate, street){
            document.getElementById("current-driver-name").innerHTML = lastname+", "+firstname;
            document.getElementById("current-driver-plate").innerHTML = plate;
            document.getElementById("current-driver-date").innerHTML = datetime;
            document.getElementById("current-driver-street").innerHTML = street;
        }

        async function fetchReferenceData(ref) {
            const doc = await ref.get();
            return doc.exists ? doc.data() : {};
        }

        getLastDetectedDriver();

        async function getLastDetectedDriver() {
            isLoading(true);
            const querySnapshot = await db.collection("History")
                .orderBy("datetime", "desc")  // Order by datetime in descending order
                .limit(1)  // Get the most recent entry
                .get();

            if (!querySnapshot.empty) {
                const doc = querySnapshot.docs[0];  // Get the first document
                const data = doc.data();

                // Fetch vehicle data
                const vehicleData = await fetchReferenceData(data.vehicle);
                if (!vehicleData) {
                    throw new Error("Vehicle data not found.");
                }

                // Fetch resident data
                const residentData = await fetchReferenceData(vehicleData.owner);
                if (!residentData) {
                    throw new Error("Resident data not found.");
                }

                let accessStatus = data.entry ? 'Entry' : 'Exit';

                const lastname = residentData.lastName || 'N/A';  
                const firstname = residentData.firstName || 'N/A'; 
                const datetime = formatTimestamp(data.datetime) || 'N/A'; 
                const plate = vehicleData.licensePlate || 'N/A';  
                const street = residentData.street || 'N/A';  

                getDriverDetails(lastname, firstname, datetime, plate, street);
                isLoading(false);

            } else {
                console.log("No history found.");
            }
        }

        function formatTimestamp(timestamp) {
            if (!timestamp) return 'N/A';
            
            const date = timestamp.toDate();

            const year = date.getFullYear();
            const month = String(date.getMonth() + 1).padStart(2, '0');
            const day = String(date.getDate()).padStart(2, '0');
            const hours = String(date.getHours()).padStart(2, '0');
            const minutes = String(date.getMinutes()).padStart(2, '0');

            return `${year}-${month}-${day} ${hours}:${minutes}`;
        }
        async function checkRFID(rfidUID) {
            try {
                const trimmedRfidUID = String(rfidUID).trim();;
                console.log("RFIDUID detected is: "+trimmedRfidUID);

                // Reference to the vehicle collection
                const vehicleRef = db.collection("Vehicle");


                // Query to f    the document where uid field matches rfidUID
                // const q = query(vehicleRef, where("uid", "==", trimmedRfidUID));
                const querySnapshot = await vehicleRef.where("uid", "==", trimmedRfidUID).get();
                // Execute the query
                // const querySnapshot = await getDocs(q);

                // Check if any document matches the query
                if (querySnapshot.empty) {
                    console.log("No matching documents.");
                    return false;
                } else {
                    console.log("Document found!");
                    querySnapshot.forEach(async (doc) => {
                        const data = doc.data();
                        const residentData = await fetchReferenceData(data.owner);

                        const lastname = residentData.lastName || 'N/A';  // Assuming the field is 'lastname'
                        const firstname = residentData.firstName || 'N/A';  // Assuming the field is 'firstname'
                        const today = new Date();
                        const datetime = data.datetime || today.toLocaleString();  // Assuming the field is 'datetime'
                        const plate = data.licensePlate || 'N/A';  // Assuming the field is 'plate'
                        const street = residentData.street || 'N/A';  // Assuming the field is 'street'
                        console.log(data.licensePlate);

                        // Save to the History collection with the vehicle reference
                        const vehicleRefDoc = vehicleRef.doc(doc.id); // Get the reference path

                        const historyQuerySnapshot = await db.collection("History")
                        .where("vehicle", "==", vehicleRefDoc)
                        .orderBy("datetime", "desc") // Get the most recent entry first
                        .limit(1) // Limit to one document
                        .get();

                        let lastEntryType = null;

                        // Check if there's any previous history for the vehicle
                        if (!historyQuerySnapshot.empty) {
                            const lastHistoryDoc = historyQuerySnapshot.docs[0];
                            lastEntryType = lastHistoryDoc.data().entry;  // Get the entry type of the last history record
                        }

                        // Only save to History if the last entry is false or if there's no previous entry
                        if (lastEntryType === false || lastEntryType === null) {
                            await saveToHistory(vehicleRefDoc, true, true); // Save with the entry set to true
                            console.log("Last history is exit, saving as entry");
                        } else {
                            await saveToHistory(vehicleRefDoc, true, false); // Save with the entry set to true
                            console.log("Last history is entry, saving as exit");
                        }
                    });
                    return true;
                }
            } catch (error) {
                console.error("Error checking RFID in database:", error);
            }
        }
        async function saveToHistory(vehicleRef, isResident, entry) {
            const historyRef = db.collection("History");

            const historyData = {
                datetime: new Date(),  // Set to the current date and time
                entry: entry,          // Set to true or false based on your application logic
                isResident: isResident, // True if the person is a resident, else false
                vehicle: vehicleRef    // Reference to the vehicle
            };

            try {
                await historyRef.add(historyData);
                console.log("History record added successfully:", historyData);
            } catch (error) {
                console.error("Error saving to History collection:", error);
            }
        }
</script>

<script>
    const statusInfo = document.getElementById('status-info');
    const statusIcons = document.getElementById('status-icons');
    const changeViewButton = document.getElementById('changeViewButton');
    const iconBox  = document.getElementsByClassName('icon-clickable');
    const alertBox = document.getElementById('alert-box');
    const closeAlertButton = document.getElementById('close-alert');
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
            let gatePositionText = document.getElementById('icon-label-gate').textContent;
            const ButtonId = element.id;
            console.log(`Clicked element ID: ${ButtonId}`);
            if (ButtonId == "gate-position") {
                console.log(`gate-position: ` + gatePositionText);
                if (gatePositionText.toUpperCase() === "OPEN") {
                    console.log(`Requesting gate to close.`);
                    processGatePosition("0");  // Command to close the gate
                } else if (gatePositionText.toUpperCase() === "CLOSED") {
                    console.log(`Requesting gate to open.`);
                    processGatePosition("1");  // Command to open the gate
                }
                
            }
            //alerted
            // if (alertBox.classList.contains('hidden')) {
            //     alertBox.classList.remove('hidden');

            //     const progressBar = document.getElementById('progress-bar');
            //     progressBar.style.width = '0%';

            //     setTimeout(() => {
            //         progressBar.style.width = '100%';
            //     }, 10); 

            //     closeAlertTimeOut = setTimeout(() => {
            //         alertBox.classList.add('hidden');
            //     }, 5000);
            // }
        });
    });

    closeAlertButton.addEventListener('click', () => {
        if (!alertBox.classList.contains('hidden')) {
            alertBox.classList.add('hidden');
            clearTimeout(closeAlertTimeOut);
        }
    });
</script>
<script>
    async function addResident() {
        // Gather input values
        const lastName = document.getElementById('modal-addr-last-name').value;
        const firstName = document.getElementById('modal-addr-first-name').value;
        const middleInitial = document.getElementById('modal-addr-middle-initial').value;
        const street = document.getElementById('modal-addr-street').value;
        const block = document.getElementById('modal-addr-block').value;
        const lot = document.getElementById('modal-addr-lot').value;

        if (!lastName || !firstName || !middleInitial || !street || !block || !lot) {
            alert("Please fill in all fields.");
            return; // Exit the function if any field is empty
        }
    
        // Create the resident data object
        const residentData = {
            archived: false, // Setting archived to false
            block: block,
            datetimeAdded: new Date(), // Current date and time as timestamp
            firstName: firstName,
            lastName: lastName,
            lot: lot,
            middleName: middleInitial,
            street: street,
        };
    
        // Add the resident data to the 'Residents' collection in Firestore
        try {
            await db.collection('Residents').add(residentData);
            alert("Resident added successfully!");
            // Optionally, reset the input fields
            resetForm();
        } catch (error) {
            console.error("Error adding resident: ", error);
            alert("Error adding resident: " + error.message);
        }
    }
    
    function resetForm() {
        document.getElementById('modal-addr-last-name').value = '';
        document.getElementById('modal-addr-first-name').value = '';
        document.getElementById('modal-addr-middle-initial').value = '';
        document.getElementById('modal-addr-street').value = '';
        document.getElementById('modal-addr-block').value = '';
        document.getElementById('modal-addr-lot').value = '';
    }
    </script>
    
</html>




)=====";
