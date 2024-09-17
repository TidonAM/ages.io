const char PAGE_LOGS[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>AGES Logs</title>
    <script src="https://www.gstatic.com/firebasejs/10.13.1/firebase-app-compat.js"></script>
    <script src="https://www.gstatic.com/firebasejs/10.13.1/firebase-database-compat.js"></script> <!-- For Realtime Database -->
    <script src="https://www.gstatic.com/firebasejs/10.13.1/firebase-firestore-compat.js"></script> <!-- For Firestore -->
</head>
<body>

    <button id="viewLogsButton" class="toggle-view" onclick="window.location.href='/'">Go Back</button>

    <table border="1" cellspacing="0" cellpadding="5">
        <thead>
            <tr>
                <th>DateTime</th>
                <th>Vehicle Brand</th>
                <th>Vehicle Type</th>
                <th>Resident Owner</th>
                <th>Access</th>
                <th>License Plate</th>
            </tr>
        </thead>
        <tbody id="output">
            <tr>
                <td>2024-09-18 14:35</td>
                <td>Toyota </td>
                <td>Sedan</td>
                <td>John Doe</td>
                <td>Entry</td>
                <td>ABC123</td>
            </tr>
            <!-- Add more rows as needed -->
        </tbody>
    </table>

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
            const doc = await ref.get();
            return doc.exists ? doc.data() : {};
        }

        readDataFromFirestore();

        // Function to read data from Firestore and populate the table
        async function readDataFromFirestore() {
            const outputDiv = document.getElementById('output');

            // Read all documents from the "History" collection
            const querySnapshot = await db.collection("History").get();

            for (const doc of querySnapshot.docs) {
                const data = doc.data();

                const vehicleData = await fetchReferenceData(data.vehicle);
                console.log(vehicleData);
                const residentData = await fetchReferenceData(vehicleData.owner);

                // Create a new row for the table
                const row = document.createElement('tr');

                let accessStatus = data.entry ? 'Entry' : 'Exit';

                // Create and append table cells with document data
                row.innerHTML = `
                    <td>${formatTimestamp(data.datetime)}</td>
                    <td>${vehicleData.vBrand || 'N/A'}</td>
                    <td>${vehicleData.vType || 'N/A'}</td>
                    <td>${residentData.firstName || 'N/A'} ${residentData.lastName || 'N/A'}</td>
                    <td>${accessStatus}</td>
                    <td>${vehicleData.licensePlate || 'N/A'}</td>
                `;

                // Append the new row to the table body
                outputDiv.appendChild(row);
            }
        }

        function formatTimestamp(timestamp) {
            if (!timestamp) return 'N/A';
            
            // Convert Firestore Timestamp to JavaScript Date
            const date = timestamp.toDate();

            // Get the date and time components
            const year = date.getFullYear();
            const month = String(date.getMonth() + 1).padStart(2, '0'); // Months are zero-indexed
            const day = String(date.getDate()).padStart(2, '0');
            const hours = String(date.getHours()).padStart(2, '0');
            const minutes = String(date.getMinutes()).padStart(2, '0');

            // Return formatted as YYYY-MM-DD HH:MM
            return `${year}-${month}-${day} ${hours}:${minutes}`;
        }

    </script>

</body>
</html>



)=====";
