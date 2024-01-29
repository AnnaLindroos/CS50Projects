document.addEventListener("DOMContentLoaded", run);

function run() {
    let one = document.getElementById("firstCard");
    let two = document.getElementById("secondCard");

    one.addEventListener("click", function() {
        one.style.position= "absolute";
        one.style.top = "50%";
        one.style.left ="50%";
        one.style.transform = "translate(-50%, -50%)";
        two.style.display = "none";
    });

    two.addEventListener("click", function() {
        two.style.position= "absolute";
        two.style.top = "50%";
        two.style.left ="50%";
        two.style.transform = "translate(-50%, -50%)";
        one.style.display = "none";
    });

};
