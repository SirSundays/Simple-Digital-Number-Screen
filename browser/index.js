$(function () {
    var canvas = $("#splitFlapCanvas").fallBlatt({
        flapSpacingExtraWidth: 10,
        flapSpacingExtraHeight: 10,
        flapScale: 2
    });

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

    showTime();
    setInterval(function () {
        showTime();
    }, 1000 * 60);

    window.api.receive('new-number', (data) => {
        console.log(data);
        let displayNumber = data.displayNumber.toString().padStart(4, '0');
        console.log(displayNumber);
        for (var i = 0; i < displayNumber.length; i++) {
            $("#splitFlapCanvas").fallBlatt("display", {
                pos: [4 + i, 1],
                content: displayNumber[i]
            });
        }
    });
});