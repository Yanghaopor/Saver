
function OneCpuName(){
    var xhrCPUname = new XMLHttpRequest();
    xhrCPUname.open('GET', 'http://127.0.0.1:80?IDGetCpuName=&', true);
    xhrCPUname.send();
    xhrCPUname.onreadystatechange = function(){if (xhrCPUname.readyState === XMLHttpRequest.DONE){
        if (xhrCPUname.status === 200) {
                var Data = String(xhrCPUname.responseText);
                document.getElementById('Cpuname').innerHTML="CPU型号:"+Data;
            } else {
                //alert("NoRemData");
            }
        }
    }
}

document.addEventListener('keydown', function(event) {
    // 检测 F12 键（keyCode 为 123）
    if (event.keyCode === 123) {
        event.preventDefault(); // 阻止默认行为
    }
});

OneCpuName();
