$(function () {
    var canvas = $("#splitFlapCanvas").fallBlatt({
        flapSpacingExtraWidth: 10,
        flapSpacingExtraHeight: 10,
        flapScale: 2
    });

    const hideCursor = true;
    const activateTime = false;

    function showTime() {
        let date = new Date();
        let time = `${date.getHours().toString().padStart(2, '0')}:${date.getMinutes().toString().padStart(2, '0')}`;
        for (var i = 0; i < time.length; i++) {
            $("#splitFlapCanvas").fallBlatt("display", {
                pos: [i, 3],
                content: time[i]
            });
        }
    }

    if (activateTime) {
        showTime();
        setInterval(function () {
            showTime();
        }, 1000 * 60);
    }

    if (hideCursor) {
        function hideCursor(){
            document.body.style.cursor = "none"; 
        }
        setTimeout(hideCursor,1000);       
    }

    window.api.receive("new-number", (data) => {
        let displayNumber = data.displayNumber.toString().padStart(4, '0');
        for (var i = 0; i < displayNumber.length; i++) {
            $("#splitFlapCanvas").fallBlatt("display", {
                pos: [3 + i, 1],
                content: displayNumber[i]
            });
        }
    });
});