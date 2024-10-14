const char PAGE_VEH[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Vehicles</title>
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
            border-radius: 5px;
            cursor: pointer;
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
    <script src="https://www.gstatic.com/firebasejs/10.13.1/firebase-database-compat.js"></script> 
    <script src="https://www.gstatic.com/firebasejs/10.13.1/firebase-firestore-compat.js"></script> 
</head>
<body>

<div class="container">
    <h1>Vehicles</h1>
    <button id="viewLogsButton" class="toggle-view" onclick="window.location.href='/'">Go Back</button>

    <div class="search-bar">
        <!-- From Date Section -->
        <div class="date-container">
            <label for="fromDate"></label>
            <input class="dateInput" type="text" id="searchBar" placeholder="Search" />
        </div>

        <select title="filterSelect" name="dropdown" id="dropdown">
            <option value="lastName">Last Name</option>
            <option value="firstName">First Name</option>
            <option value="middleName">Middle Name</option>
            <option value="vType">Vehicle Type</option>
            <option value="vBrand">Vehicle Brand</option>
            <option value="licensePlate">License Plate</option>
        </select>

        <button class="toggle-view" onclick="search()">Search</button>
    </div>

    <table>
        <thead>
            <tr>
                <th>Last Name</th>
                <th>First Name</th>
                <th>Middle Name</th>
                <th>Type</th>
                <th>Brand</th>
                <th>License Plate</th>
            </tr>
        </thead>
        <tbody id="output">
                    </tbody>
    </table>
</div>

<script>
    function isLoading(a) {
        if (a === true) {
            return '<tr><td colspan="6"><div style="display: flex; justify-content: center; width: 80%; padding: 10%;"><div class="loader" id="loader" style="height:120px;"></div></div></td></tr>';
        } else {
            return '';
        }
    }

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
        outputDiv.innerHTML = isLoading(true);

        const querySnapshot = await db.collection("Vehicle").get();

        outputDiv.innerHTML = isLoading(false);

        for (const doc of querySnapshot.docs) {
            const data = doc.data();
            
            const residentData = await fetchReferenceData(data.owner);

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
                <td>${residentData.lastName || 'N/A'}</td>
                <td>${residentData.firstName || 'N/A'}</td>
                <td>${residentData.middleName || 'N/A'}</td>
                <td>${data.vType || 'N/A'}</td>
                <td>${data.vBrand || 'N/A'}</td>
                <td>${data.licensePlate || 'N/A'}</td>
            `;
            outputDiv.appendChild(row);
        }
    }

    function search() {
    const dropdownValue = document.getElementById('dropdown').value;
    const searchBarValue = document.getElementById('searchBar').value;
    const outputDiv = document.getElementById('output');
    outputDiv.innerHTML = isLoading(true);

    if (searchBarValue != null) {
        if (dropdownValue === "firstName" || dropdownValue === "lastName" || dropdownValue === "middleName") {
            // Search in the Residents collection first
            db.collection("Residents")
            .where(dropdownValue, ">=", searchBarValue)
            .where(dropdownValue, "<=", searchBarValue + '\uf8ff')
            .get()
            .then(async (querySnapshot) => {
                outputDiv.innerHTML = isLoading(false);
                // Process each matching resident
                for (const residentDoc of querySnapshot.docs) {
                    const residentData = residentDoc.data();
                    
                    // Now query Vehicle collection for this resident reference
                    const vehicleSnapshot = await db.collection("Vehicle")
                        .where("owner", "==", db.doc(`/Residents/${residentDoc.id}`))
                        .get();

                    for (const vehicleDoc of vehicleSnapshot.docs) {
                        const vehicleData = vehicleDoc.data();

                        // New row of table
                        const row = document.createElement('tr');
                        row.id = vehicleDoc.id;

                        // Add table data
                        row.innerHTML = `
                            <td>${residentData.lastName || 'N/A'}</td>
                            <td>${residentData.firstName || 'N/A'}</td>
                            <td>${residentData.middleName || 'N/A'}</td>
                            <td>${vehicleData.vType || 'N/A'}</td>
                            <td>${vehicleData.vBrand || 'N/A'}</td>
                            <td>${vehicleData.licensePlate || 'N/A'}</td>
                        `;
                        outputDiv.appendChild(row);
                    }
                }
            });
        } else {
            // If searching within Vehicle collection (e.g., vType, vBrand)
            db.collection("Vehicle")
            .where(dropdownValue, ">=", searchBarValue)
            .where(dropdownValue, "<=", searchBarValue + '\uf8ff')
            .get()
            .then(async (querySnapshot) => {
                const outputDiv = document.getElementById('output');
                outputDiv.innerHTML = isLoading(false);
                for (const doc of querySnapshot.docs) {
                    const data = doc.data();
                    const residentData = await fetchReferenceData(data.owner);

                    // New row of table
                    const row = document.createElement('tr');
                    row.id = doc.id;

                    // Add table data
                    row.innerHTML = `
                        <td>${residentData.lastName || 'N/A'}</td>
                        <td>${residentData.firstName || 'N/A'}</td>
                        <td>${residentData.middleName || 'N/A'}</td>
                        <td>${data.vType || 'N/A'}</td>
                        <td>${data.vBrand || 'N/A'}</td>
                        <td>${data.licensePlate || 'N/A'}</td>
                    `;
                    outputDiv.appendChild(row);
                }
            });
        }
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