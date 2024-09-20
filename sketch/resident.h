const char PAGE_RES[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Residents</title>
    <style>
        body {
            font-family: 'Arial', sans-serif;
            background-color: #f4f4f9;
            color: #333;
            margin: 0;
            padding: 20px;
            display: flex;
            justify-content: center;
            align-items: flex-start;
            min-height: 100vh;
        }

        .container {
            background-color: white;
            padding: 20px;
            border-radius: 10px;
            box-shadow: 0 4px 10px rgba(0, 0, 0, 0.1);
            max-width: 1200px;
            width: 100%;
        }

        h1 {
            text-align: center;
            color: #555;
        }

        .toggle-view {
            background-color: gray;
            color: white;
            border: none;
            /* padding: 10px 20px; */
            border-radius: 5px;
            cursor: pointer;
            /* margin-bottom: 20px; */
            /* font-size: 16px; */
            width: 100%;
            padding: 12px;
            font-size: 14px;
        }

        .toggle-view:hover {
            background-color: gray;
        }

        .search-bar {
            display: flex;
            justify-content: space-between;
            margin-bottom: 10px;
            flex-wrap: wrap;
            gap: 10px;
            margin-top:10px;
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

        input[type="text"] {
            padding: 10px;
            font-size: 16px;
            border: 1px solid #ccc;
            border-radius: 5px;
            width: 100%;
        }

        select {
            padding: 10px;
            font-size: 16px;
            border: 1px solid #ccc;
            border-radius: 5px;
            width: 100%;
        }

        table {
            width: 100%;
            border-collapse: collapse;
        }

        table thead {
            background-color: gray;
            color: white;
        }

        table th, table td {
            padding: 15px;
            text-align: left;
            border-bottom: 1px solid #ddd;
        }

        table tr:nth-child(even) {
            background-color: #f9f9f9;
        }

        /* table tr:hover {
            background-color: #f1f1f1;
        } */

        /* Responsive Design */
        @media (max-width: 768px) {
            .search-bar {
                flex-direction: column;
                align-items: flex-start;
            }

            /* input[type="datetime-local"] {
                width: 100%;
                margin-bottom: 10px;
            } */

            table th, table td {
                font-size: 14px;
            }

            table th, table td {
                padding: 10px;
            }
        }

        @media (max-width: 480px) {
            .container {
                padding: 15px;
            }

            table th, table td {
                padding: 8px;
                font-size: 12px;
            }
        }
    </style>
    <script src="https://www.gstatic.com/firebasejs/10.13.1/firebase-app-compat.js"></script>
    <script src="https://www.gstatic.com/firebasejs/10.13.1/firebase-database-compat.js"></script> <!-- For Realtime Database -->
    <script src="https://www.gstatic.com/firebasejs/10.13.1/firebase-firestore-compat.js"></script> <!-- For Firestore -->
</head>
<body>

<div class="container">
    <h1>Residents</h1>
    <button id="viewLogsButton" class="toggle-view" onclick="window.location.href='/'">Go Back</button>

    <div class="search-bar">
        <!-- From Date Section -->
        <div class="date-container">
            <label for="fromDate"></label>
            <input class="dateInput" type="text" id="searchBar" placeholder="Search" />
        </div>

        <select title="" name="dropdown" id="dropdown">
            <option value="lastName">Last Name</option>
            <option value="firstName">First Name</option>
            <option value="middleName">Middle Name</option>
            <option value="street">Street</option>
            <option value="block">Block</option>
            <option value="lot">Lot</option>
        </select>

        <button class="toggle-view" onclick="search()">Search</button>
    </div>

    <table>
        <thead>
            <tr>
                <th>Last Name</th>
                <th>First Name</th>
                <th>Middle Name</th>
                <th>Street</th>
                <th>Block</th>
                <th>Lot</th>
            </tr>
        </thead>
        <tbody id="output">
        </tbody>
    </table>
</div>

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

    async function fetchReferenceData(ref) {
        const doc = await ref.get();
        return doc.exists ? doc.data() : {};
    }

    readDataFromFirestore();

    async function readDataFromFirestore() {
        const outputDiv = document.getElementById('output');
        outputDiv.innerHTML = '';  // Clear current data

        const querySnapshot = await db.collection("Residents").get();

        for (const doc of querySnapshot.docs) {
            const data = doc.data();
            
            // const vehicleData = await fetchReferenceData(data.vehicle);

            // New row of table
            const row = document.createElement('tr');
            row.id = doc.id;

            row.addEventListener('click', function() {
                console.log('Row clicked:', doc.id);
                // You can perform any action here
                alert(`Resident ID: ${doc.id}`);
            });

            // Add table data
            row.innerHTML = `
                <td>${data.lastName}</td>
                <td>${data.firstName || 'N/A'}</td>
                <td>${data.middleName || 'N/A'}</td>
                <td>${data.street || 'N/A'}</td>
                <td>${data.block}</td>
                <td>${data.lot || 'N/A'}</td>
            `;
            outputDiv.appendChild(row);
        }
    }

    

    function search() {
        const dropdownValue = document.getElementById('dropdown').value;
        const searchBarValue = document.getElementById('searchBar').value;
        console.log(dropdownValue);
        console.log(searchBarValue);
        if (searchBarValue != null) {
            db.collection("Residents")
            .where(dropdownValue, ">=", searchBarValue)
            .where(dropdownValue, "<=", searchBarValue + '\uf8ff')
            .get()
            .then((querySnapshot) => {
                const outputDiv = document.getElementById('output');
                outputDiv.innerHTML = '';
                querySnapshot.forEach(async (doc) => {
                    const data = doc.data();

                    const row = document.createElement('tr');

                    row.innerHTML = `
                        <td>${data.lastName}</td>
                        <td>${data.firstName || 'N/A'}</td>
                        <td>${data.middleName || 'N/A'}</td>
                        <td>${data.street || 'N/A'}</td>
                        <td>${data.block}</td>
                        <td>${data.lot || 'N/A'}</td>
                    `;
                    outputDiv.appendChild(row);
                });
            });
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

    // function filterLogs() {
    //     const fromDateValue = document.getElementById('fromDate').value;
    //     const toDateValue = document.getElementById('toDate').value;

    //     if (fromDateValue && toDateValue) {
    //         const fromDate = new Date(fromDateValue);
    //         const toDate = new Date(toDateValue);

    //         const fromTimestamp = firebase.firestore.Timestamp.fromDate(fromDate);
    //         const toTimestamp = firebase.firestore.Timestamp.fromDate(toDate);

    //         db.collection("History")
    //             .where("datetime", ">=", fromTimestamp)
    //             .where("datetime", "<=", toTimestamp)
    //             .get()
    //             .then((querySnapshot) => {
    //                 const outputDiv = document.getElementById('output');
    //                 outputDiv.innerHTML = '';  // Clear current data

    //                 querySnapshot.forEach(async (doc) => {
    //                     const data = doc.data();
                        
    //                     const vehicleData = await fetchReferenceData(data.vehicle);
    //                     const residentData = await fetchReferenceData(vehicleData.owner);

    //                     const row = document.createElement('tr');
    //                     let accessStatus = data.entry ? 'Entry' : 'Exit';

    //                     row.innerHTML = `
    //                         <td>${formatTimestamp(data.datetime)}</td>
    //                         <td>${vehicleData.vBrand || 'N/A'}</td>
    //                         <td>${vehicleData.vType || 'N/A'}</td>
    //                         <td>${residentData.firstName || 'N/A'} ${residentData.lastName || 'N/A'}</td>
    //                         <td>${accessStatus}</td>
    //                         <td>${vehicleData.licensePlate || 'N/A'}</td>
    //                     `;

    //                     outputDiv.appendChild(row);
    //                 });
    //             });
    //     } else {
    //         readDataFromFirestore();  // Reset and show all logs if no date range is selected
    //     }
    // }
</script>

</body>
</html>

)=====";