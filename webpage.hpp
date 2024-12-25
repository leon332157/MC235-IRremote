const char INDEX[] = R""""(
<html>

<head>IR Remote</head>

<body>
    <h1>IR Remote</h1>
    <h2>IP Addr: %s</h2>
    <h3>msg: %s</h3>
    <script>
        function sendCode(code) {
            fetch('/ir?code=' + code)
                .then(response => {console.log(response);console.log(response.text())})
        }
    </script>
    <style>
        .parent {
            display: grid;
            grid-template-columns: repeat(5, 1fr);
            grid-template-rows: repeat(5, 1fr);
            grid-column-gap: 0px;
            grid-row-gap: 0px;
        }

        .div1 {
            grid-area: 1 / 1 / 2 / 2;
        }

        .div2 {
            grid-area: 1 / 2 / 2 / 3;
        }

        .div3 {
            grid-area: 2 / 1 / 3 / 2;
        }

        .div4 {
            grid-area: 2 / 2 / 3 / 3;
        }

        .div5 {
            grid-area: 2 / 3 / 3 / 4;
        }

        .div6 {
            grid-area: 2 / 4 / 3 / 5;
        }

        .div7 {
            grid-area: 2 / 5 / 3 / 6;
        }

        .div8 {
            grid-area: 3 / 5 / 4 / 6;
        }

        .div9 {
            grid-area: 3 / 4 / 4 / 5;
        }

        .div10 {
            grid-area: 3 / 3 / 4 / 4;
        }

        .div11 {
            grid-area: 3 / 2 / 4 / 3;
        }

        .div12 {
            grid-area: 3 / 1 / 4 / 2;
        }

        .div13 {
            grid-area: 4 / 1 / 5 / 2;
        }

        .div14 {
            grid-area: 4 / 2 / 5 / 3;
        }

        .div15 {
            grid-area: 4 / 3 / 5 / 4;
        }

        .div16 {
            grid-area: 4 / 4 / 5 / 5;
        }

        .div17 {
            grid-area: 4 / 5 / 5 / 6;
        }

        .div18 {
            grid-area: 5 / 5 / 6 / 6;
        }

        .div19 {
            grid-area: 5 / 4 / 6 / 5;
        }

        .div20 {
            grid-area: 5 / 3 / 6 / 4;
        }

        .div21 {
            grid-area: 5 / 2 / 6 / 3;
        }

        .div22 {
            grid-area: 5 / 1 / 6 / 2;
        }
    </style>
    <div class="parent">
        <div class="div1">
            <button onclick="sendCode(12)">Power</button> </div>
        <div class="div2"> <button onclick="sendCode(45)">Open/Close</button> </div>
        <div class="div3"> <button onclick="sendCode(63)">Source</button> </div>
        <div class="div4"> <button onclick="sendCode(70)">DBB</button> </div>
        <div class="div5"> <button onclick="sendCode(36)">Program</button> </div>
        <div class="div6"> <button onclick="sendCode(29)">Repeat</button> </div>
        <div class="div7"> <button onclick="sendCode(28)">Shuffle</button> </div>
        <div class="div8"> <button onclick="sendCode(53)">Play</button> </div>
        <div class="div9"> <button onclick="sendCode(16)">Volume Up</button> </div>
        <div class="div10"> <button onclick="sendCode(17)">Volume Down</button> </div>
        <div class="div11"> <button onclick="sendCode(13)">Mute</button> </div>
        <div class="div12"> <button onclick="sendCode(15)">RDS</button> </div>
        <div class="div13"> <button onclick="sendCode(52)">Fast Forward</button> </div>
        <div class="div14"> <button onclick="sendCode(50)">Rewind</button> </div>
        <div class="div15"> <button onclick="sendCode(33)">Previous</button> </div>
        <div class="div16"> <button onclick="sendCode(32)">Next</button> </div>
        <div class="div17"> <button onclick="sendCode(54)">Stop</button> </div>
        <div class="div18"> <button onclick="sendCode(42)">Set Clock</button> </div>
        <div class="div19"> <button onclick="sendCode(89)">Timer</button> </div>
        <div class="div20"> <button onclick="sendCode(38)">Sleep</button> </div>
        <div class="div21"> </div>
        <div class="div22"> </div>
    </div>
</body>

</html>
)"""";