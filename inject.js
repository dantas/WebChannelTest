<script type="text/javascript" src="./qwebchannel.js"></script>
<script type="text/javascript">
	window.%1 = %2;

	(function() {
        var socket = new WebSocket("%3");

        socket.onclose = function() {
            console.log("channel closed");
        };
        socket.onerror = function(error) {
            console.log("error" );
        };
        socket.onopen = function() {
            console.log("connected to websocket");

            new QWebChannel(socket, function(channel) {
                console.log("connected to qwebchannel");

                window.%1 = channel.objects.%1;
            });
        };
    })();
</script>
